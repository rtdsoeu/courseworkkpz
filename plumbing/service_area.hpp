#pragma once
#ifndef COURSEWORK_PLUMBING_SERVICE_AREA_HPP_
#define COURSEWORK_PLUMBING_SERVICE_AREA_HPP_
#include <string>
#include <vector>

class ServiceArea
{
	int minV = 10;
	int maxV = 40;
	std::vector<std::string> areas {"Одеса", "Чорноморськ", "Подільск"};
	int v;
 public:
	bool isAddressAvailable(std::string_view address) {
		return std::find(areas.begin(), areas.end(), address) != areas.end();
	}
	bool supportV(int v_) const
	{
		return v_ >= minV && v_ <= maxV;
	}
	void setV(int v_) {
		if (supportV(v_))
			v = v_;
	}
	int getPrice() const {
		return v * 400 / 7;
	}
	void addArea(const std::string& area) {
		areas.push_back(area);
	}
	void removeArea(std::string_view area) {
		areas.erase(std::remove_if(areas.begin(), areas.end(), [&area](std::string_view s) {
		  return s.find(area) != std::string::npos;
		}), areas.end());
	}
};

#endif //COURSEWORK_PLUMBING_SERVICE_AREA_HPP_
