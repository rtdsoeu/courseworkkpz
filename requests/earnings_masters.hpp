#ifndef COURSEWORK_EARNINGS_MASTERS_HPP
#define COURSEWORK_EARNINGS_MASTERS_HPP

#include "../imguiaddons/imguidatechooser.h"
#include "../imwindows/imwindows.hpp"
#include "../nlohmann/json/json.hpp"
#include "../plumbing/master.hpp"
#include "utils.hpp"

namespace Requests {
    class EarningsMasters {
        bool date_filtering{false};
        ImGuiTextFilter name_filter;
        tm date_chooser_begin;
        tm date_chooser_end;
        time_t begin_t;
        time_t end_t;
    public:
        auto getMenuName() {
            return "Заробіток майстра з ... по ...";
        }

        void render() {
            ImGui::Text("Заробіток майстра розраховується за формулою: зарплата(15.000 грн/місяць) + премії");

            name_filter.Draw("Пошук по імені");

            if (ImGui::Checkbox("Фільтр по періоду", &date_filtering)) {
                begin_t = mktime(&date_chooser_begin);
                end_t = mktime(&date_chooser_end);
            }
            if (ImGui::DateChooser("Початок", date_chooser_begin))
                begin_t = mktime(&date_chooser_begin);
            if (ImGui::DateChooser("Кінець", date_chooser_end))
                end_t = mktime(&date_chooser_end);

            std::unordered_map<int, double> brigade_earnings;
            for (const auto &accident: GetAllAccidents()) {
                auto accident_time = accident["date"].get<time_t>();
                if (date_filtering && (accident_time - begin_t < -1000 || accident_time > end_t))
                    continue;
                auto cost = accident["cost"].get<double>();
                auto brigade_number = accident["brigade_number"].get<int>();
                switch (accident["type"].get<Accident::Type>()) { // розрахунок премій 1%, 3% або 5%
                    case Accident::Type::kEasy:
                        brigade_earnings[brigade_number] += cost * 0.01;
                        break;
                    case Accident::Type::kMedium:
                        brigade_earnings[brigade_number] += cost * 0.03;
                        break;
                    case Accident::Type::kHard:
                        brigade_earnings[brigade_number] += cost * 0.05;
                        break;
                }
            }

            if (ImGui::BeginTable("Заробіток майстрів", 2)) {
                ImGui::TableSetupColumn("Майстер");
                ImGui::TableSetupColumn("Заробіток");
                ImGui::TableHeadersRow();
                for (const auto &master: GetAllMasters()) {
                    const auto full_name = master["full_name"].get<std::string>();
                    if (!name_filter.PassFilter(full_name.c_str())) // Фільтр по імені майстра
                        continue;
                    const auto brigade_number = master["brigade_number"].get<int>();
                    double master_earnings = calculate_earnings(brigade_earnings[brigade_number]);
                    ImGui::TableNextColumn();
                    ImGui::Text("%s", full_name.c_str());
                    ImGui::TableNextColumn();
                    ImGui::Text("%.2f", master_earnings);
                }
                ImGui::EndTable();
            }
        }
    private:
        double calculate_earnings(double brigade_earnings) {
            if (date_filtering) // Якщо фільтр по датам активний - рахувати зарплату по дням 
                return brigade_earnings + (date_chooser_end.tm_yday - date_chooser_begin.tm_yday +
                        ((date_chooser_end.tm_year - date_chooser_begin.tm_year) * 365)) * 500;
            else // інакше рахувати стандартну зарплату за місяць
                return brigade_earnings + 15000;
        }
    };
}

#endif //COURSEWORK_EARNINGS_MASTERS_HPP
