#pragma once
#ifndef COURSEWORK_ACCIDENT_HPP
#define COURSEWORK_ACCIDENT_HPP
#include <string>
#include <ctime>
#include "../nlohmann/json/json.hpp"
class Accident
{
public:
	enum class Status
	{
		kSolved,
		kInProcess,
		kQueue,
	};
	enum class Type
	{
		kEasy,
		kMedium,
		kHard
	};
private:
	std::string address;
	Status status;
	time_t date;
	Type type;
	double cost;
	int id;
    int brigade_number;
public:
    Accident(std::string address, Status status, const time_t &date, Type type, double cost, int id, int brigade_number = 0)
		: address(std::move(address)), status(status), date(date), type(type), cost(cost), id(id), brigade_number(brigade_number)
	{}
	const std::string &getAddress() const
	{
		return address;
	}
	void setAddress(const std::string &address_)
	{
		address = address_;
	}
	Status getStatus() const
	{
		return status;
	}
	void setStatus(Status status_)
	{
		Accident::status = status_;
	}
	const time_t &getDate() const
	{
		return date;
	}
	void setDate(const time_t &date_)
	{
		date = date_;
	}
	Type getType() const
	{
		return type;
	}
	void setType(Type type_)
	{
		type = type_;
	}
	double getCost() const
	{
		return cost;
	}
	void setCost(double cost_)
	{
		cost = cost_;
	}
	int getId() const
	{
		return id;
	}
	void setId(int id_)
	{
		id = id_;
	}
    int getBrigadeNumber() const {
        return brigade_number;
    }
    void setBrigadeNumber(int brigade_number_) {
        brigade_number = brigade_number_;
    }
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Accident, address, status, date, type, cost, id, brigade_number);
};
#endif //COURSEWORK_ACCIDENT_HPP
