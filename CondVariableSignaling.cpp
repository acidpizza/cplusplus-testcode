/*
 *
 * Libraries: -lpthread
 *
 */



#include <iostream>
#include <pthread.h>

using namespace std;

pthread_mutex_t condV_mutex;
pthread_cond_t condV;
bool running = true;

void *sleepthread(void *arg)
{
	int i = (int)arg;

	while (running)
	{
		pthread_mutex_lock(&condV_mutex);

		cout << "SleepThread: going to sleep" << endl;
		pthread_cond_wait(&condV, &condV_mutex);

		cout << "SleepThread: The number is " << i << endl;
		pthread_mutex_unlock(&condV_mutex);
	}
	pthread_exit(NULL);
}


int main()
{
	pthread_t myThread;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	pthread_mutex_init(&condV_mutex, NULL);
	pthread_cond_init(&condV, NULL);

	pthread_create(&myThread, &attr, sleepthread, (void*)5);

	cout << "Thread created" << endl;

	int value = 0;

	while(running)
	{
		cin >> value;
		if(value==1)
		{
			cout << "Waking thread NOW" << endl;
			pthread_mutex_lock(&condV_mutex);
			pthread_cond_signal(&condV);
			pthread_mutex_unlock(&condV_mutex);
		}
		else if(value == 9)
		{
			cout << "Quiting!" << endl;
			pthread_mutex_lock(&condV_mutex);
			pthread_cond_signal(&condV);
			pthread_mutex_unlock(&condV_mutex);

			running = false;
		}

	}

	pthread_join(myThread, NULL);

	cout << "Program End" << endl;
	return 0;
}
