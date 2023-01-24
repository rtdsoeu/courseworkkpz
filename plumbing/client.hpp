#pragma once
#ifndef CLIENT_HPP
#define CLIENT_HPP
#include "person.hpp"
#include <string>
#include "../nlohmann/json/json.hpp"
class Client: public Person
{
	int accident_id{};
public:
	Client(int department_number,
	       const std::string &full_name,
	       const std::string &address,
	       const std::string &phone_number = "",
	       int accident_id = 0)
		: Person(department_number, full_name, address, phone_number), accident_id(accident_id)
	{}
	int getAccidentId() const
	{
		return accident_id;
	}
	void setAccidentId(int accidentId)
	{
		accident_id = accidentId;
	}
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Client, department_number, full_name, address, phone_number, accident_id);
};
#endif //CLIENT_HPP
