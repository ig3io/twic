#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "cJSON.h"

char *response;

void twic_usage(char* comm) {
    char buff[128];
    sprintf(buff, "Usage: %s <search term> <result limit>\n", comm);
    write(STDOUT_FILENO, buff, strlen(buff)); 
}

void error(char* msg) {
    perror(msg);
    exit(1);
}

void twic_write_response(void* ptr, size_t size, size_t nmemb, void* userdata) {
    int data_size = size*nmemb;
    response = malloc(data_size);
    if (response < 0) error("null message");
    int i = 0;
    char* aux_rd = ptr;
    char* aux_wr = response;
    for (i = 0; i < data_size; i++) {
        sprintf(aux_wr, "%c", *aux_rd);
        ++aux_wr;
        ++aux_rd;
    }
}

void twic_construct_query(char* query, int arg_num, char* arg_vec[]) {
    strcpy(query, "http://search.twitter.com/search.json?q=");
    char buff[2048];
    int i = 1;
    while (i < arg_num - 1) {
        if (i == arg_num - 2) sprintf(buff, "%s", arg_vec[i]);
        else sprintf(buff, "%s+", arg_vec[i]);
        strcat(query, buff);
        i++;
    }
    sprintf(buff, "&rpp=%d&result_type=recent&include_entities=false", atoi(arg_vec[i]));
    strcat(query, buff);
}

void twic_clean(void) {
    free(response);
}
