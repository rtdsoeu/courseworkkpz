#pragma once
#ifndef COURSEWORK_AMOUNT_ACCIDENTS_HPP
#define COURSEWORK_AMOUNT_ACCIDENTS_HPP

#include "../imguiaddons/imguidatechooser.h"
#include "../imwindows/imwindows.hpp"
#include "../nlohmann/json/json.hpp"
#include "../plumbing/accident.hpp"
#include "utils.hpp"

namespace Requests {
    class AmountAccidents {
        inline static bool filtering{false};
        inline static tm date_chooser_begin;
        inline static tm date_chooser_end;
        inline static time_t begin_t;
        inline static time_t end_t;
    public:
        static const char *getMenuName() {
            return "Кількість аварій";
        }

        static void render() {
            if (ImGui::Button("Зареєструвати аварію"))
                ImGui::OpenPopup("Зареєструвати аварію");
            ImGui::SameLine();
            ImGui::Text("Всього аварій: %zu", GetAllAccidents().size());
            if (ImGui::BeginPopup("Зареєструвати аварію")) {
                ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1);
                renderAddAccident();
                ImGui::PopStyleVar(1);
                ImGui::EndPopup();
            }
            if (ImGui::Checkbox("Фільтр по періоду", &filtering)) {
                begin_t = mktime(&date_chooser_begin);
                end_t = mktime(&date_chooser_end);
            }
            if (ImGui::DateChooser("Початок", date_chooser_begin))
                begin_t = mktime(&date_chooser_begin);
            if (ImGui::DateChooser("Кінець", date_chooser_end))
                end_t = mktime(&date_chooser_end);
            if (ImGui::BeginTable("tablemasters", 8, ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_RowBg)) {
                ImGui::TableSetupColumn("Адреса");
                ImGui::TableSetupColumn("Стан");
                ImGui::TableSetupColumn("Дата");
                ImGui::TableSetupColumn("Тип");
                ImGui::TableSetupColumn("Вартість");
                ImGui::TableSetupColumn("Id");
                ImGui::TableSetupColumn("Закріплена бригада");
                ImGui::TableSetupColumn("##delete", ImGuiTableColumnFlags_WidthFixed, 20.f);

                ImGui::TableSetupScrollFreeze(0, 1);
                ImGui::TableHeadersRow();

                size_t remove_item_index{0};
                for (size_t i{0}; const auto &accident : GetAllAccidents()) {
                    time_t accident_time{accident["date"].get<time_t>()};
                    if (filtering && (accident_time - begin_t < -1000 || accident_time > end_t)) {
                        ++i;
                        continue;
                    }
                    ImGui::TableNextColumn();
                    ImGui::Text("%s", accident["address"].get<std::string>().c_str());
                    ImGui::TableNextColumn();
                    switch (accident["status"].get<Accident::Status>()) {
                        using
                        enum Accident::Status;
                        case kSolved:
                            ImGui::Text("Вирішено");
                            break;
                        case kInProcess:
                            ImGui::Text("В процесі");
                            break;
                        case kQueue:
                            ImGui::Text("В черзі");
                            break;
                    }
                    ImGui::TableNextColumn();
                    {
                        tm date{};
                        localtime_s(&date, &accident_time);
                        ImGui::Text("%d/%d/%d", date.tm_mday, date.tm_mon + 1, 1900 + date.tm_year);
                    }
                    ImGui::TableNextColumn();
                    switch (accident["type"].get<Accident::Type>()) {
                        using
                        enum Accident::Type;
                        case kEasy:
                            ImGui::Text("Легка");
                            break;
                        case kMedium:
                            ImGui::Text("Середня");
                            break;
                        case kHard:
                            ImGui::Text("Важка");
                            break;
                    }
                    ImGui::TableNextColumn();
                    ImGui::Text("%.02f", accident["cost"].get<double>());
                    ImGui::TableNextColumn();
                    ImGui::Text("%i", accident["id"].get<int>());
                    ImGui::TableNextColumn();
                    ImGui::Text("%i", accident["brigade_number"].get<int>());
                    ImGui::TableNextColumn();
                    if (ImGui::Button(("x##" + std::to_string(i++)).c_str()))
                        remove_item_index = i;
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
                        ImGui::SetTooltip("Видалити запис");
                }
                if (remove_item_index != 0)
                    GetAllAccidents().erase(remove_item_index - 1);
                ImGui::EndTable();
            }
        }

        static void renderAddAccident() {
            static struct {
                char address[256];
                int status;
                tm date;
                int type;
                double cost;
                int id;
                int brigade_number;
            } input_accident{.id = static_cast<int>(GetAllAccidents().size() + 1)};
            ImGui::InputText("Адреса##input", input_accident.address, IM_ARRAYSIZE(input_accident.address));
            constexpr const char *status_names[] = {"Вирішено", "В процесі", "В черзі"};
            ImGui::Combo("Статус##input", &input_accident.status, status_names, IM_ARRAYSIZE(status_names));
            ImGui::DateChooser("Дата##input", input_accident.date);
            constexpr const char *type_names[] = {"Легка", "Середня", "Важка"};
            ImGui::Combo("Тип##input", &input_accident.type, type_names, IM_ARRAYSIZE(type_names));
            ImGui::InputDouble("Ціна##input", &input_accident.cost, 0, 0, "%.2f");
            ImGui::InputInt("Id##input", &input_accident.id);
            std::vector<int> brigades;
            for (const auto &m: GetAllMasters()) {
                auto brigade_number{m["brigade_number"].get<int>()};
                if (std::find(brigades.begin(), brigades.end(), brigade_number) == brigades.end())
                    brigades.push_back(brigade_number);
            }
            std::sort(brigades.begin(), brigades.end());
            static std::stringstream ss;
            ss.clear();
            for (const auto &e: brigades)
                ss << e << '\0';
            ss << '\0';
            ImGui::Combo("Закріплена бригада##input", &input_accident.brigade_number, ss.str().c_str());
            if (ImGui::Button("Зареєструвати аварію##input", {-1, 30})) {
                if (strlen(input_accident.address) == 0 || AccidentIdExists(input_accident.id)) {
                    ImGui::OpenPopup("Помилка");
                } else {
                    Accident::Status s{input_accident.status};
                    Accident::Type t{input_accident.type};
                    Accident temp{input_accident.address, s, mktime(&input_accident.date), t, input_accident.cost,
                                  input_accident.id, brigades[input_accident.brigade_number]};
                    GetAllAccidents().emplace_back(temp);
                    ZeroMemory(&input_accident, sizeof(input_accident));
                    input_accident.id = temp.getId() + 1;
                }
            }
            ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), 0, {0.5f, 0.5f});
            if (ImGui::BeginPopupModal("Помилка", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
                if (strlen(input_accident.address) == 0)
                    ImGui::Text("Заповніть поле з адресою");
                if (AccidentIdExists(input_accident.id))
                    ImGui::Text("Аварія з таким Id вже існує, введіть інший");
                if (ImGui::Button("Закрити##input", {-1, 0}))
                    ImGui::CloseCurrentPopup();
                ImGui::EndPopup();
            }
        }
    };
}

#endif //COURSEWORK_AMOUNT_ACCIDENTS_HPP
