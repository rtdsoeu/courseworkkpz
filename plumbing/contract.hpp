#pragma once
#ifndef COURSEWORK_CONTRACT_HPP
#define COURSEWORK_CONTRACT_HPP
#include <string>
#include "../nlohmann/json/json.hpp"

struct Contract
{
	std::string full_name;
	std::string phone_number;
	std::string address;
	int volume;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Contract, full_name, phone_number, address, volume);
};
#endif //COURSEWORK_CONTRACT_HPP
