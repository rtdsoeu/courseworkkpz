#include <gtest/gtest.h>
#include "test_common.hpp"
#include "../plumbing/service_area.hpp"

TEST(ServiceAreaTest, IsAddressAvailableValid) {
	ServiceArea area;
	area.addArea("Odesa");
	ASSERT_TRUE(area.isAddressAvailable("Odesa"));
}

TEST(ServiceAreaTest, IsAddressAvailableInvalid) {
	ServiceArea area;
	area.addArea("Kyiv");
	ASSERT_FALSE(area.isAddressAvailable("Lviv"));
}

TEST(ServiceAreaTest, SupportV) {
	ServiceArea area;
	area.addArea("ZoneA");
	ASSERT_TRUE(area.supportV(10));
	ASSERT_FALSE(area.supportV(100));
}

TEST(ServiceAreaTest, AddArea) {
	ServiceArea area;
	ASSERT_NO_THROW(area.addArea("ZoneA"));
	ASSERT_TRUE(area.isAddressAvailable("ZoneA"));
}

TEST(ServiceAreaTest, RemoveArea) {
	ServiceArea area;
	area.addArea("ZoneB");
	ASSERT_NO_THROW(area.removeArea("ZoneB"));
	ASSERT_FALSE(area.isAddressAvailable("ZoneB"));
}

TEST(ServiceAreaTest, AddAreaAfterRemove) {
	ServiceArea area;
	area.addArea("ZoneC");
	area.removeArea("ZoneC");
	ASSERT_NO_THROW(area.addArea("ZoneC"));
	ASSERT_TRUE(area.isAddressAvailable("ZoneC"));
}
