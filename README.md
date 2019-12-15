# cpp_list_comprehension
A library which introduces pythons list comprehension to C++ based on `boost::phoenix`.
# Usage example
This code:
```C++
#include <vector>
#include <iostream>
int main()
{
        std::vector<int> vec;
	int var = 1028;
	do
	{
	    int r = ::sqrt(var);
	    vec.push_back(r);
	    var -= r * r;
	} while (var > 0)
	for (const auto& e : lis)
	{
		std::cout << e << std::endl;
	}
}
```
can be written with list comprehension:
```C++
#include <vector>
#include <iostream>
#include <comprehension.h>
struct Isqrt
{
	using result_type = int;
	template <class T>
	int operator()(const T& val) const
	{
		return (int)::sqrt(val);
	}
};
boost::phoenix::function<Isqrt> ph_isqrt;
int main()
{
	using namespace boost::phoenix;
	int var = 1028;
	comprehension::CompVec<std::vector<int>> lis
		(
			  ph_isqrt(ref(var))
			, do__((ref(var) -= (ph_isqrt(ref(var)) * ph_isqrt(ref(var)))) > 0)
		);
	for (const auto& e : lis)
	{
		std::cout << e << std::endl;
	}
}
```
and produces:
```
32
2
```
