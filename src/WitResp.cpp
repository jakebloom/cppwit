#include "WitResp.h"

#include <stdio.h>

WitResp::WitResp(std::string _id, std::string _text, json _entities) {
    msg_id = _id;
    text = _text;

    if (_entities != NULL) {
        for (
            json::iterator it = _entities.begin();
            it != _entities.end();
            ++it
        ) {
            struct entities entity;
            entity.name = it.key();
            for (
                json::iterator jt = it.value().begin();
                jt != it.value().end();
                ++jt
            ) {
                struct instance in;
                try {
                    in.confidence = jt->at("confidence").get<float>();
                } catch (json::out_of_range& e) {}

                try {
                    in.type = jt->at("type").get<std::string>();
                } catch (json::out_of_range& e) {}

                try {
                    in.value = jt->at("value").get<std::string>();
                } catch (json::out_of_range& e) {}

                entity.instances.push_back(in);
            }

            entities.push_back(entity);
        }
    }
}

void WitResp::print() {
    printf("ID: %s\nText: %s\n", msg_id.data(), text.data());
    for (struct entities entity : entities) {
        printf("Entity: %s\n", entity.name.data());
        for (struct instance i : entity.instances) {
            printf("\tConfidence: %f\n\tType: %s\n\tValue: %s\n\n", i.confidence, i.type.data(), i.value.data());
        }
    }
}