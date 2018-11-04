#ifndef _WIT_H_
#define _WIT_H_

#include<string>

#include "WitResp.h"

class Wit {
    private:
        std::string token;
    public:
        Wit(std::string token);
        WitResp message(std::string input);
        WitResp speech(FILE * fd);
};

#endif