#include "static_if.hpp"

#include <type_traits>
#include <string>
#include <iostream>

template <typename T>
void foo(const T& value)
{
	using namespace si;

	Static_If< std::is_same<T, std::string>::value >([&](auto _)
	{
		std::cout << _(value).substr(0, 2) << std::endl;
	})
	.Else_if< std::is_same<T, int>::value >([&](auto _)
	{
		std::cout << _(value) / 2 << std::endl;
	})
	.Else([&](auto _)
	{
		std::cout << _(value) << std::endl;
	});
}

int main()
{
	std::string a = "Test";
	int b = 42;
	double d = 3.14;

	foo(a); // Prints "Te"
	foo(b); // Prints 12
	foo(d); // Prints 3.14
}