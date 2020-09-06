
#include <iostream>
#include <boost/thread.hpp>
#include <boost/thread/locks.hpp>

using namespace std;

typedef boost::shared_mutex Lock;
typedef boost::unique_lock< Lock > WriteLock;
typedef boost::shared_lock< Lock > ReadLock;

Lock myLock;

bool reader1 = true;
bool reader2 = true;
bool writer1 = true;

void reader(int tid)
{
	while(true)
	{
		cout << tid << ": before acquiring lock ..." << endl;

		if(tid == 1)
		{
			while(reader1)
			{
				sleep (1);
			}

			ReadLock r_lock(myLock);
			cout << tid << ": acquired lock ..." << endl;
			//sleep(1);
			reader1 = true;
			while(reader1)
			{
				sleep (1);
			}
			reader1 = true;
		}
		else if(tid == 2)
		{
			while(reader2)
			{
				sleep(1);
			}

			ReadLock r_lock(myLock);
			cout << tid << ": acquired lock ..." << endl;
			//sleep (1);
			reader2 = true;
			while(reader2)
			{
				sleep (1);
			}
			reader2 = true;
		}

		cout << tid << ": freed lock ..." << endl;
	}
}

void writer()
{
	while(true)
	{
		cout << "writer: before acquiring lock ..." << endl;

		{
			while(writer1)
			{

				sleep (1);
			}
			WriteLock w_lock(myLock);
			writer1 = true;
			cout << "writer: acquired lock ..." << endl;
			//sleep (1);
			while(writer1)
			{
				sleep (1);
			}
			writer1 = true;
		}
		cout << "writer: freed lock ..." << endl;
	}
}


int main()
{
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	boost::thread_group tgroup;

	for(unsigned int i=1; i <= 2; i++)
	{
		tgroup.create_thread( boost::bind(&reader,i) );
	}

	tgroup.create_thread(boost::bind(&writer));

	int cmd;
	while(true)
	{
		cin >> cmd;
		if(cmd == 1)
		{
			reader1 = false;
		}
		if(cmd == 2)
		{
			reader2 = false;
		}
		if(cmd == 3)
		{
			writer1 = false;
		}
	}

	tgroup.join_all();

	return 0;
}
