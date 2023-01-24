#pragma once
#ifndef COURSEWORK_UTILS_HPP
#define COURSEWORK_UTILS_HPP

#include "../nlohmann/json/json.hpp"
#include "../plumbing/accident.hpp"
#include "../plumbing/master.hpp"
#include "../imwindows/imwindows.hpp"
#include "../config/config.hpp"

namespace Requests {
    auto &GetAllAccidents() {
        return Config::GetGlobalConfig().getData()["accidents"];
    }

    auto &GetAllMasters() {
        return Config::GetGlobalConfig().getData()["masters"];
    }

    bool AccidentIdExists(int id) {
        return std::ranges::any_of(GetAllAccidents(), [id](const auto &accident) {
            return id == accident["id"].template get<int>();
        });
    }

    void SortMasters() {
        auto &masters{GetAllMasters()};
        std::sort(masters.begin(), masters.end(), [](const auto &m_1, const auto &m_2) {
            return m_1["departament_number"].template get<int>() < m_2["departament_number"].template get<int>();
        });
    }

    void SortAccidents() {
        auto &accidents{GetAllAccidents()};
        std::sort(accidents.begin(), accidents.end(), [](const auto &a_1, const auto &a_2) {
            return a_1["date"].template get<time_t>() < a_2["date"].template get<time_t>();
        });
    }
}
#endif //COURSEWORK_UTILS_HPP
