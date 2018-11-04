#include <curl/curl.h>
#include <nlohmann/json.hpp>

#include "Wit.h"
#include "WitResp.h"

#define MESSAGE_URL "https://api.wit.ai/message?q="
#define SPEECH_URL  "https://api.wit.ai/speech"

using json = nlohmann::json;

size_t getResp(char *ptr, size_t size, size_t nmemb, void *usrptr);

Wit::Wit(std::string _token) {
   token = _token;
}

WitResp Wit::message(std::string message) {
    CURL *curl = curl_easy_init();
    CURLcode res;
    WitResp client_response ("", "", NULL);

    std::string url = std::string(MESSAGE_URL) + 
        std::string(curl_easy_escape(curl, message.data(), 0));
    curl_easy_setopt(curl, CURLOPT_URL, url.data());

    std::string auth_header = std::string("Authorization: Bearer ") + token;
    struct curl_slist *list = curl_slist_append(NULL, auth_header.data());    
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, getResp);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &client_response);
    
    res = curl_easy_perform(curl);
    
    curl_slist_free_all(list);
    curl_easy_cleanup(curl);

    return client_response;
}

WitResp Wit::speech(FILE * fd) {
    CURL *curl = curl_easy_init();
    CURLcode res;
    WitResp client_response ("", "", NULL);

    fseek(fd, 0, SEEK_END);
    int fsize = ftell(fd);
    rewind(fd);

    curl_easy_setopt(curl, CURLOPT_URL, SPEECH_URL);

    std::string auth_header = std::string("Authorization: Bearer ") + token;
    struct curl_slist *list = curl_slist_append(NULL, auth_header.data()); 
    curl_slist_append(list, "Content-Type: audio/wav");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, getResp);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &client_response);
    
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_READDATA, fd);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, fsize);

    res = curl_easy_perform(curl);
    
    curl_slist_free_all(list);
    curl_easy_cleanup(curl);

    return client_response;
}

size_t getResp(char *ptr, size_t size, size_t nmemb, void *usrptr) {
    WitResp *ret = (WitResp *)usrptr;
    json res = json::parse(ptr);

    std::string id = res["msg_id"].dump();
    id = id.substr(1, id.size() - 2);
    
    std::string text = res["_text"].dump();
    text = text.substr(1, text.size() - 2);

    *ret = WitResp(id, text, res["entities"]);

    return 0;
}