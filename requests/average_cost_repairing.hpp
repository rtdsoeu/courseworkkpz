#pragma once
#ifndef COURSEWORK_AVERAGE_COST_REPAIRING_HPP
#define COURSEWORK_AVERAGE_COST_REPAIRING_HPP

#include "../imwindows/imwindows.hpp"
#include "../nlohmann/json/json.hpp"
#include "../plumbing/accident.hpp"
#include "utils.hpp"

namespace Requests {
    struct AverageCostRepairing {
        static const char *getMenuName() {
            return "Середня вартість усунення аварії";
        }

        static void render() {
            struct {
                double all;
                size_t amount_all;
                double easy;
                size_t amount_easy;
                double medium;
                size_t amount_medium;
                double hard;
                size_t amount_hard;
            } result{};
            const auto &accidents = GetAllAccidents();
            for (const auto &accident: accidents) {
                const auto &cost = accident["cost"].get<double>();
                result.all += cost;
                ++result.amount_all;
                switch (accident["type"].get<Accident::Type>()) {
                    case Accident::Type::kEasy:
                        result.easy += cost;
                        ++result.amount_easy;
                        break;
                    case Accident::Type::kMedium:
                        result.medium += cost;
                        ++result.amount_medium;
                        break;
                    case Accident::Type::kHard:
                        result.hard += cost;
                        ++result.amount_hard;
                        break;
                }
            }

            ImGui::Text("Всього аварій: %zu\nСередня вартість усунення аварій: %.2f", accidents.size(),
                        result.all / static_cast<double>(result.amount_all));
            ImGui::Separator();
            ImGui::Text("Всього легких аварій: %zu\nСередня вартість усунення легких аварій: %.2f", result.amount_easy,
                        result.easy / static_cast<double>(result.amount_easy));
            ImGui::Separator();
            ImGui::Text("Всього середніх аварій: %zu\nСередня вартість усунення середніх аварій: %.2f",
                        result.amount_medium, result.medium / static_cast<double>(result.amount_medium));
            ImGui::Separator();
            ImGui::Text("Всього складних аварій: %zu\nСередня вартість усунення складних аварій: %.2f",
                        result.amount_hard, result.hard / static_cast<double>(result.amount_hard));
        }
    };
}
#endif //COURSEWORK_AVERAGE_COST_REPAIRING_HPP
