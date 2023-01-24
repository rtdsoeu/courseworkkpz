#pragma once
#ifndef COURSEWORK_CONFIG_HPP
#define COURSEWORK_CONFIG_HPP

#include <fstream>
#include "../nlohmann/json/json.hpp"

namespace Config {
    using json = nlohmann::json;

    class Config {
        json data;
        const char *file;
    public:
        explicit Config(const char *file = "config.json") : file(file) {
            std::ifstream f{file};
            if (f.good()) {
                try {
                    f >> data;
                } catch (...) {

                }
            }
            if (data["masters"].is_null())
                data["masters"] = json::array({});
            if (data["accidents"].is_null())
                data["accidents"] = json::array({});
        }

        ~Config() {
            std::ofstream o{file};
            o << std::setw(5) << data << std::endl;
        }
        
        json &getData() {
            return data;
        }
    };

    //Global сonfig file(config.json)
    auto &GetGlobalConfig() {
        static Config cfg{};
        return cfg;
    }
}


#endif //COURSEWORK_CONFIG_HPP
