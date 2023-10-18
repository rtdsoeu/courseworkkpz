#pragma once

#ifndef COURSEWORK_PLUMBING_CONNECTION_QUEUE_HPP_
#define COURSEWORK_PLUMBING_CONNECTION_QUEUE_HPP_
#include <string>
#include <queue>
#include <format>
#include "contract.hpp"
class ConnectionQueue
{
	std::queue<Contract> queue;
 public:
	std::string getAvaliableDate()
	{
		return std::format("Мінімальна доступна дата підключення: через {} днів", queue.size());
	}
	void addContract(Contract c)
	{
		queue.push(c);
	}
	Contract& getTop() {
		return queue.back();
	}
	void removeContract()
	{
		queue.pop();
	}
};

#endif //COURSEWORK_PLUMBING_CONNECTION_QUEUE_HPP_
