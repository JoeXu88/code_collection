#pragma once

#include <atomic>

class spinlock
{
	private:
	std::atomic_flag _flag{false};

	public:
	spinlock() {}
	~spinlock() {}

	inline void lock()
	{
		while(_flag.test_and_set(std::memory_order_acquire));
	}

	inline void unlock()
	{
		_flag.clear(std::memory_order_release);
	}

};