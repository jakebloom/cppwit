#ifndef _WITRESP_H_
#define _WITRESP_H_

#include<string>
#include<vector>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct instance {
    float confidence;
    std::string type;
    std::string value;
};

struct entities {
    std::string name;
    std::vector<struct instance> instances;
};

class WitResp {
    public:
        std::string text;
        std::string msg_id;
        std::vector<struct entities> entities;
        WitResp(std::string _id, std::string _text, json _entities);
        void print();
};

#endif