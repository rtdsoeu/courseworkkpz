#pragma once
#ifndef COURSEWORK_AMOUNT_BRIGADES_HPP
#define COURSEWORK_AMOUNT_BRIGADES_HPP

#include "../imwindows/imwindows.hpp"
#include "../nlohmann/json/json.hpp"
#include "utils.hpp"

namespace Requests {
    struct AmountBrigades {
        static auto getMenuName() {
            return "Кількість бригад";
        }

        static void render() {
            std::map<int, std::vector<std::string>> brigades;
            for (const auto &master: GetAllMasters()) {
                auto brigade_number = master["brigade_number"].get<int>();
                auto master_fullname = master["full_name"].get<std::string>();
                brigades[brigade_number].push_back(master_fullname);
            }
            ImGui::Text("Кількість бригад: %zu", brigades.size());
            for (const auto &[brigade_number, masters]: brigades)
                if (ImGui::CollapsingHeader(std::format("Бригада #{}", brigade_number).c_str()))
                    for (const auto &master_fullname: masters)
                        ImGui::Text("%s", master_fullname.c_str());
        }
    };
}
#endif //COURSEWORK_AMOUNT_BRIGADES_HPP
