#pragma once

#ifndef COURSEWORK_PLUMBING_CONNECTION_QUEUE_HPP_
#define COURSEWORK_PLUMBING_CONNECTION_QUEUE_HPP_
#include <string>
#include <queue>

class ConnectionQueue
{
	using none_t = bool;
	std::queue<none_t> queue;
 public:
	std::string getAvaliableDate()
	{
		return {"Мінімальна доступна дата підключення: через " + std::to_string(queue.size()) + " днів"};
	}
	void addContract()
	{
		queue.push(0);
	}
	void removeContract()
	{
		queue.pop();
	}
};

#endif //COURSEWORK_PLUMBING_CONNECTION_QUEUE_HPP_
