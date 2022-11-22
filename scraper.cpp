#include <string>
#include <iostream>
#include "curl/curl.h"

typedef size_t (* curl_write)(char *, size_t, size_t, std::string * );

std::string request(std::string link){
    CURLcode res_code = CURLE_FAILED_INIT;
    CURL * curl = curl_easy_init();
    std::string result;
    std::string url = link;

    curl_global_init(CURL_GLOBAL_ALL);

    if (curl) {
        curl_easy_setopt(
            curl,
            CURLOPT_WRITEFUNCTION,
            static_cast < curl_write > ([](char * contents, size_t size,
                size_t nmemb, std::string * data) -> size_t {
                size_t new_size = size * nmemb;
                if (data == NULL){
                    return 0;
                } 
                data -> append(contents, new_size);
                return new_size;
                }));
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, & result);
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/107.0.0.0 Safari/537.36");

            res_code = curl_easy_perform(curl);
            if (res_code != CURLE_OK){
                return curl_easy_strerror(res_code);
            }

            curl_easy_cleanup(curl);        
    }
    curl_global_cleanup();
    return result;
}

int main(int argc, char **argv){
    if (argc != 2){
        std::cout << "INVALID LINK" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string arg = argv[1];
    std::string r = request(arg);

    return EXIT_SUCCESS;
}