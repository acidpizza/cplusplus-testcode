#include <iostream>

#include <boost/bind.hpp>
#include <boost/function.hpp>

using namespace std;

void f(int a, int b)
{
	cout << "Function f: " << a << " + " << b << " = " << a + b << endl;

}

// method wants a void function pointer
void g(void(*func)(), int a)
{
	cout << "Function g: " << a << endl;
}

int main()
{
	boost::function<void(int)> newfunc = boost::bind(&f, _1, 2);
	newfunc(6);


	cout << "Program End";

}




