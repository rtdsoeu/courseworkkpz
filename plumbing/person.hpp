#pragma once
#ifndef COURSEWORK_PERSON_HPP
#define COURSEWORK_PERSON_HPP
#include <string>
#include "../nlohmann/json/json.hpp"
class Person
{
protected:
	std::string phone_number;
	std::string address;
	std::string full_name;
	int departament_number{};
public:
	Person() = default;
	Person(int departament_number, std::string full_name, std::string address, std::string phone_number = "")
		: departament_number(departament_number), full_name(std::move(full_name)), address(std::move(address)),
          phone_number(std::move(phone_number))
	{}
	int getDepartamentNumber() const
	{
		return departament_number;
	}
	void setDepartamentNumber(int departament_number_)
	{
		departament_number = departament_number_;
	}
	const std::string &getFullName() const
	{
		return full_name;
	}
	void setFullName(const std::string &fullName)
	{
		full_name = fullName;
	}
	const std::string &getAddress() const
	{
		return address;
	}
	void setAddress(const std::string &address_)
	{
		address = address_;
	}
	const std::string &getPhoneNumber() const
	{
		return phone_number;
	}
	void setPhoneNumber(const std::string &phone_number_)
	{
		phone_number = phone_number_;
	}

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Person, departament_number, full_name, address, phone_number);
};
#endif //COURSEWORK_PERSON_HPP
