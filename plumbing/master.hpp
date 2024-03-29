#pragma once
#ifndef COURSEWORK_MASTER_HPP
#define COURSEWORK_MASTER_HPP
#include "person.hpp"
#include <string>
#include "../nlohmann/json/json.hpp"

class Master: public Person
{
	int experience;
	int brigade_number;
public:
	Master() = default;
	explicit Master(int departament_number,
	       const std::string &full_name,
	       const std::string &address,
	       const std::string &phone_number = "",
	       int experience = 0,
	       int brigade_number = 1)
		: Person(departament_number, full_name, address, phone_number), experience(experience),
          brigade_number(brigade_number)
	{
	}
	int getExperience() const
	{
		return experience;
	}
	void setExperience(int exp)
	{
		experience = exp;
	}
	int getBrigadeNumber() const
	{
		return brigade_number;
	}
	void setBrigadeNumber(int brigade_number_)
	{
		brigade_number = brigade_number_;
	}
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Master,
	                               departament_number,
	                               full_name,
	                               address,
	                               phone_number,
	                               experience,
	                               brigade_number);
};
#endif //COURSEWORK_MASTER_HPP
