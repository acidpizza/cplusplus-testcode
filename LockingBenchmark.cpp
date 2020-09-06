#include <iostream>
#include <boost/interprocess/detail/atomic.hpp>
#include <boost/atomic.hpp>
#include <boost/thread.hpp>
#include <boost/smart_ptr/detail/spinlock.hpp>
#include <list>
#include <pthread.h>

#define ADD_COUNT 20000003
#define SUBTRACT_COUNT 20000000
#define NUM_THREADS 2 // num of threads for add and subtract separately (total = *2)

//volatile boost::uint32_t value = 0;
//boost::interprocess::ipcdetail::atomic_add32()

volatile boost::atomic<unsigned int> _atomicValue(0);

void AtomicAdd(unsigned int num)
{
	for(unsigned int i=0 ; i<num; i++)
	{
		_atomicValue++;
		//_atomicValue += 1000000;
	}
}

void AtomicSubtract(unsigned int num)
{
	for(unsigned int i=0 ; i<num; i++)
	{
		_atomicValue--;
		//_atomicValue -= 1000000;
	}
}

void Atomic()
{
	boost::thread_group t;

	for(int i=0; i<NUM_THREADS; i++)
	{
		t.create_thread(boost::bind(AtomicAdd, ADD_COUNT));
		t.create_thread(boost::bind(AtomicSubtract, SUBTRACT_COUNT));
	}
	t.join_all();
	std::cout << "Atomic: " <<  _atomicValue << std::endl;
}

// -------------------------------------------------------------

volatile unsigned int _value = 0;
boost::detail::spinlock _spinlock;
std::list<unsigned int> _list;

void SpinAddReal()
{
	_value += 1000000;
}

void SpinSubtractReal()
{
	_value -= 1000000;
}

void SpinAdd(unsigned int num)
{
	for(unsigned int i=0 ; i< num; i++)
	{
		boost::lock_guard<boost::detail::spinlock> lock(_spinlock);
		//_value++;
		//_value += 1000000;
		SpinAddReal();
	}
}

void SpinSubtract(unsigned int num)
{
	for(unsigned int i=0 ; i<num; i++)
	{
		boost::lock_guard<boost::detail::spinlock> lock(_spinlock);
		//_value--;
		//_value -= 1000000;
		SpinSubtractReal();
	}
}

void Spinlock()
{
	boost::thread_group t;

	for(int i=0; i<NUM_THREADS; i++)
	{
		t.create_thread(boost::bind(SpinAdd, ADD_COUNT));
		t.create_thread(boost::bind(SpinSubtract, SUBTRACT_COUNT));
	}

	t.join_all();
	std::cout << "Spin: " << _value << std::endl;
}

// -------------------------------------------------------------

boost::mutex _mutex;

void MutexAdd(unsigned int num)
{
	for(unsigned int i=0 ; i< num; i++)
	{
		boost::lock_guard<boost::mutex> lock(_mutex);
		//_value++;
		SpinAddReal();
	}
}

void MutexSubtract(unsigned int num)
{
	for(unsigned int i=0 ; i<num; i++)
	{
		boost::lock_guard<boost::mutex> lock(_mutex);
		//_value--;
		SpinSubtractReal();
	}
}

void Mutex()
{
	boost::thread_group t;
	for(int i=0; i<NUM_THREADS; i++)
	{
		t.create_thread(boost::bind(MutexAdd, ADD_COUNT));
		t.create_thread(boost::bind(MutexSubtract, SUBTRACT_COUNT));
	}
	t.join_all();
	std::cout << "Mutex: " << _value << std::endl;
}

// --------------------------------------------------

pthread_mutex_t _pmutex;


void PthreadAdd(unsigned int num)
{
	for(unsigned int i=0 ; i< num; i++)
	{
		pthread_mutex_lock(&_pmutex);
		_value++;
		pthread_mutex_unlock(&_pmutex);
	}
}

void PthreadSubtract(unsigned int num)
{
	for(unsigned int i=0 ; i<num; i++)
	{
		pthread_mutex_lock(&_pmutex);
		_value--;
		pthread_mutex_unlock(&_pmutex);
	}
}

void Pthread()
{
	pthread_mutex_init(&_pmutex, NULL);

	boost::thread_group t;
	for(int i=0; i<NUM_THREADS; i++)
	{
		t.create_thread(boost::bind(PthreadAdd, ADD_COUNT));
		t.create_thread(boost::bind(PthreadSubtract, SUBTRACT_COUNT));
	}
	t.join_all();

	pthread_mutex_destroy(&_pmutex);

	std::cout << "Pthread: " << _value << std::endl;
}

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		std::cout << "Usage:" << argv[0] << " < atomic | spin | mutex | pthread > " << std::endl;
		return 1;
	}

	std::string option(argv[1]);

	if(option == "atomic")
	{
		Atomic();
	}
	else if(option == "spin")
	{
		Spinlock();
	}
	else if(option == "mutex")
	{
		Mutex();
	}
	else if(option == "pthread")
	{
		Pthread();
	}

	return 0;
}



