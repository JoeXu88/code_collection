#include <condition_variable>
#include <mutex>
#include <thread>
#include <atomic>
#include <string>
#include <functional>
#include <vector>
#include <assert.h> 
#include "../c++11/spinlock.h"
#include "../c++11/timecost.h"
#include "../c++11/semaphore.h"

semaphore g_sem;
spinlock g_spinlock;
uint32_t g_xi = 0;
std::atomic<uint32_t> g_atomic_int(0);
const uint32_t g_thres = 1000000;

void work()
{
	for(int i=0; i<g_thres; i++)
	{
		g_xi++;
	}
}
void thread_func_sem()
{
	g_sem.wait();
	work();
	g_sem.post();
}

void thread_func_spinlock()
{
	g_spinlock.lock();
	work();
	g_spinlock.unlock();
}

void thread_func_atomic()
{
	for(int i=0; i<g_thres; i++)
		g_atomic_int++;
}

void test_time(const std::function<void()>& f, const std::string& name)
{
	g_xi = 0;
	g_atomic_int = 0;
	int n = 3;
    uint32_t expect = n*g_thres;

	std::vector<std::thread*> pthreads;
	usCost cost(name);

	for(int i=0; i<n; i++)
	{
		pthreads.push_back(new std::thread(f));
	}

	for(int i=0; i<n; i++)
	{
		pthreads[i]->join();
	}
	// printf("x: %d\n", g_xi);
	// printf("atomic x: %d\n", g_atomic_int.load());
    assert(g_xi == expect || g_atomic_int.load() == expect);
    
	for(int i=0; i<n; i++)
    {
        delete pthreads[i];
    }
	pthreads.clear();
}

int main(int argc, char** argv)
{
	test_time(thread_func_sem, "sem_cond");
	test_time(thread_func_spinlock, "spin");
	test_time(thread_func_atomic, "atomic");

    return 0;
}