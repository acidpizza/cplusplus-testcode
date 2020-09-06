/*
 * Open MP : add -fopenmp option to misc of C compiler, c++ compiler, linker
 */

#include <omp.h>
#include <time.h>
#include <sys/time.h> //gettimeofday

#include <stdlib.h> // rand()
#include <list>

#include <iostream>

using namespace std;

int main()
{
	int size = 10000;
	//int *a = new int[size];

	int max = 0;
	list<int> myList;

//	for(int i=0; i<size; i++)
	//	a[i] = rand()%1000;



/*
// Coarse timer to 1 second accuracy. No need to link to any libraries.
	time_t before = time(NULL);
	sleep(2);
	for (int i = 0 ; i < size; i++)
	{
		a[i] = i*i;
	}
	time_t after = time(NULL);
	cout << "Time taken = " << after - before << " seconds" << endl;
*/

/*
//	Better resolution timer probably to millisecond accuracy.
//	Should not be used to measure time intervals! It is affected by time correction to time server.

	timeval beforetv;
	gettimeofday(&beforetv, NULL);
	double before = beforetv.tv_sec + beforetv.tv_usec / 1000000.0;

	sleep(2);
	for (int i = 0 ; i < size; i++)
	{
		a[i] = i*i;
	}

	timeval aftertv;
	gettimeofday(&aftertv, NULL);
	double after = aftertv.tv_sec + aftertv.tv_usec / 1000000.0;
	cout << "Time taken = " << (after - before) * 1000 << " microseconds" << endl;

	//for(int i=0; i<size; i++)
		//cout << a[i];
	cout << "Max is : " << max;

	cout << endl;
*/


// 	Can use different system clocks. Use monotonic to measure physical world time intervals.
//	Manually use the number of the clock because the #defines are missing in time.h (found in linux/time.h)
//	Include -lrt library
//#define CLOCK_REALTIME                  0
//#define CLOCK_MONOTONIC                 1
//#define CLOCK_PROCESS_CPUTIME_ID        2
//#define CLOCK_THREAD_CPUTIME_ID         3
	timespec ts1;
	clock_gettime(1, &ts1);
	double before = ts1.tv_sec + ts1.tv_nsec / 1000000000.0;

#pragma omp parallel num_threads(8)
{
//	int tid = omp_get_thread_num();

#pragma omp for
	for(int i=0; i<size; i++)
		myList.push_back(rand()%1000);

	for(list<int>::iterator it = myList.begin(); it != myList.end(); it++)
	{

#pragma omp critical(maxvalue)
		{
			if(max < *it)
				max = *it;
		}

	}

}

	timespec ts2;
	clock_gettime(1, &ts2);
	double after = ts2.tv_sec + ts2.tv_nsec / 1000000000.0;

	cout << "Time taken = " << (after - before) * 1000 << " microseconds" << endl;

	//for(int i=0; i<size; i++)
		//cout << a[i];
	cout << "Max is : " << max;

	cout << endl;


	//delete[] a;

	return 0;
}
