#include <iostream>
#include <boost/thread.hpp>
#include <boost/asio.hpp>

/*
void handler1(const boost::system::error_code &ec)
{
	std::cout << "Handler function called." << std::endl;
}

void handler2()//const boost::system::error_code &ec)
{
	std::cout << "Handler function 2 called." << std::endl;
}

boost::asio::io_service ioService;
boost::asio::io_service ioService2;

void run()
{
  ioService.run();
}
void run2()
{
  ioService2.run();
}

void program1_singleIoSerivceMultipleThreads()
{
	  boost::asio::deadline_timer timer1(ioService, boost::posix_time::seconds(5));
	  timer1.async_wait(handler1);
	  boost::asio::deadline_timer timer2(ioService2, boost::posix_time::seconds(3));
	  timer2.async_wait(handler2);

	  boost::thread thread1(run);
	  boost::thread thread2(run2);
	  thread1.join();
	  thread2.join();

	std::cout << "End!" << std::endl;
}

void program2_MultipleIoSerivceMultipleThreads()
{
	  boost::asio::deadline_timer timer1(ioService, boost::posix_time::seconds(5));
	  timer1.async_wait(handler1);
	  boost::asio::deadline_timer timer2(ioService, boost::posix_time::seconds(3));
	  timer2.async_wait(handler2);

	  boost::thread thread1(run);
	  boost::thread thread2(run);
	  thread1.join();
	  thread2.join();

	std::cout << "End!" << std::endl;
}
*/

boost::asio::io_service io_service;
boost::asio::ip::tcp::resolver resolver(io_service);
boost::asio::ip::tcp::socket sock(io_service);


void program3()
{

}

int main()
{
	//program1_singleIoSerivceMultipleThreads();
	//program2_MultipleIoSerivceMultipleThreads();
	program3();

	return 0;
}


