#pragma once

#include <condition_variable>
#include <mutex>


class semaphore
{
	private:
	uint32_t _count{1};
	std::condition_variable _cond;
	std::mutex _mutex;
	public:
	semaphore() = default;
	~semaphore() = default;

	semaphore(const semaphore&) = delete;
	semaphore& operator=(const semaphore&) = delete;
	semaphore(semaphore&&) = delete;

	bool post()
	{
		{
			std::lock_guard<std::mutex> lock(_mutex);
			_count++;
		}

		_cond.notify_one();
	}

	bool wait()
	{
		std::unique_lock<std::mutex> lock(_mutex);
		_cond.wait(lock, [&](){ return _count>0; });
		_count--;
		// lock.unlock();
	}
};