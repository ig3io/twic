#include "twic.h"
#include <curl/curl.h>

int main(int argc, char* argv[]) {

    if (argc < 3) {
        twic_usage(argv[0]);
        exit(0);
    }

    int debug = 0;
    if (strcmp(argv[argc - 1], "-d") == 0) {
            debug = 1;
            printf("twic: debugging on\n");
    }

    char query[1024];
    
    twic_construct_query(query, argc - debug, argv);
    
    // Checking the query is correctly constructed
    printf("twic: query: %s\n", query);

    
    // CURL initialization
    CURL *curl;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, query);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, twic_write_response);
        curl_easy_perform(curl);
        // According to the documentation, "always cleanup"
        curl_easy_cleanup(curl);
    }
        
    // Let's parse now
    if (debug) printf("twic: debug: preparing to parse root node\n");
    cJSON *root = cJSON_Parse(response);
    if (debug) printf("twic: debug: root node parsed\n");
    if (!root) error("no valid root node pointer returned");

    if (debug) printf("twic: debug: preparing to parse child nodes\n");
    cJSON *tweets = cJSON_GetObjectItem(root, "results");
    if (debug) printf("twic: debug: preparing to treat first child\n");
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
        if (debug) printf("twic: debug: preparing to treat next child, if any\n");
    }
    if (debug) printf("twic: debug: child nodes treated\n");


    cJSON_Delete(root);
    twic_clean();
    exit(0);
}
