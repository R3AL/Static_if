#include "static_if.hpp"

#include <type_traits>
#include <string>
#include <iostream>

template <typename T>
void foo(const T& value)
{
	using namespace si;
	using namespace stdx;

	Static_If<is_same_v<T, std::string>>([&](auto _)
	{
		std::cout << _(value).substr(0, 2) << std::endl;
	})
	.Else_if(is_same_v<T, int>, [&](auto _)
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
	
	int b 		= 42;
	double d 	= 3.14;

	foo(a); // Prints "Te"
	foo(b); // Prints 21
	foo(d); // Prints 3.14
}
