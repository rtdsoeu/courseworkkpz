#pragma once
#ifndef COURSEWORK_ACCIDENTS_TYPES_HPP
#define COURSEWORK_ACCIDENTS_TYPES_HPP

#include "../imwindows/imwindows.hpp"

namespace Requests {
    struct AccidentsTypes {
        static const char *getMenuName() {
            return "Типи аварій";
        }

        static void render() {
            ImGui::Text(
                    "На даний момент система підтримує три типи аварій, класифіковані по вартості та складності ремонту");
            ImGui::Text(
                    "Легка - вартість усунення до 10.000 грн та вирішується малою бригадою. Премія 1%% від вартості");
            ImGui::Text(
                    "Середня - вартість усунення від 10.000 до 100.000 грн та вирішується малою чи середньою бригадою. Премія 3%%");
            ImGui::Text(
                    "Важка - вартість усунення понад 100.000 грн та великою бригадою з задіянням важкої техніки. Премія 5%%");
        }
    };
}
#endif //COURSEWORK_ACCIDENTS_TYPES_HPP
