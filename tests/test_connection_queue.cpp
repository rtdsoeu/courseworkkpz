#include <gtest/gtest.h>
#include "test_common.hpp"
#include "../plumbing/connection_queue.hpp"

TEST(ConnectionQueueTest, AddContract) {
	ConnectionQueue queue;
	queue.addContract({});
	queue.addContract({});
	ASSERT_EQ(queue.getAvaliableDate(), "Мінімальна доступна дата підключення: через 2 днів");
}

TEST(ConnectionQueueTest, RemoveContract) {
	ConnectionQueue queue;
	queue.addContract({});
	queue.removeContract();
	ASSERT_EQ(queue.getAvaliableDate(), "Мінімальна доступна дата підключення: через 0 днів");
}
