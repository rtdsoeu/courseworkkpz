#pragma once
#ifndef COURSEWORK_AMOUNT_BRIGADES_HPP
#define COURSEWORK_AMOUNT_BRIGADES_HPP

#include "../imwindows/imwindows.hpp"
#include "../nlohmann/json/json.hpp"
#include "utils.hpp"

namespace Requests {
    struct AmountBrigades {
        static const char *getMenuName() {
            return "Кількість бригад";
        }

        static void render() {
            std::map<int, std::vector<std::string>> brigades;
            for (const auto &master: GetAllMasters())
                brigades[master["brigade_number"].get<int>()].push_back(master["full_name"].get<std::string>());
            ImGui::Text("Кількість бригад: %zu", brigades.size());
            for (const auto &[key, value]: brigades)
                if (ImGui::CollapsingHeader(("Бригада #" + std::to_string(key)).c_str()))
                    for (const auto &name: value)
                        ImGui::Text("%s", name.c_str());
        }
    };
}
#endif //COURSEWORK_AMOUNT_BRIGADES_HPP
