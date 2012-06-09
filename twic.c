#include "twic.h"
#include <curl/curl.h>
#

#define MAX_STRING 65535

int main(int argc, char* argv[]) {

    if (argc < 3) {
        usage(argv[0]);
        exit(0);
    }

    char query[512];
    sprintf(query, "http://search.twitter.com/search.json?q=%s&rpp=%d&result_type=recent&include_entities=false", argv[1], atoi(argv[2]));
    
    CURL *curl;
    CURLcode res;
       
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, query);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_response);
        curl_easy_perform(curl);

        //res = curl_easy_perform(curl);
                       
        /* always cleanup */ 
        curl_easy_cleanup(curl);
    }

    //printf("%s\n\n", response);
    // Let's parse
    cJSON *root = cJSON_Parse(response);
    
    if (root) {
        char *out=cJSON_Print(root);
        printf("%s\n",out);
        free(out);
    }

    double time_elapsed = cJSON_GetObjectItem(root, "completed_in")->valuedouble;
    printf("Time elapsed: %f\n", time_elapsed);

    printf("b\n");

    cJSON_Delete(root);
    free(out);
    free(response);
    return 0;
}
