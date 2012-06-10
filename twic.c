#include "twic.h"
#include <curl/curl.h>

int main(int argc, char* argv[]) {

    if (argc < 3) {
        twic_usage(argv[0]);
        exit(0);
    }

    char query[1024];
    
    twic_construct_query(query, argc, argv);
    
    // Checking the query is well constructed
    // printf("%s\n", query);

    
    CURL *curl;
    CURLcode res;
       
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, query);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, twic_write_response);
        curl_easy_perform(curl);

        // always cleanup
        curl_easy_cleanup(curl);
    }

        
    // Let's parse
    cJSON *root = cJSON_Parse(response);
    
    if (!root) error("initial parsing error");

    cJSON *tweets = cJSON_GetObjectItem(root, "results");

    cJSON *a_tweet = tweets->child;
    while (a_tweet) {
        char buff[256];
        char message[256];
        sprintf(buff, "%s: ", cJSON_GetObjectItem(a_tweet, "from_user")->valuestring);
        strcpy(message, buff);
        sprintf(buff, "%s", cJSON_GetObjectItem(a_tweet, "text")->valuestring);
        strcat(message, buff);
        a_tweet = a_tweet->next;
        printf("%s\n", message);
    }

    cJSON_Delete(root);
    twic_clean_exit();
}
