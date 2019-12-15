# cpp_list_comprehension
Library which introduces pythons list comprehension to C++.
# Usage example
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
	using namespace boost::phoenix::placeholders;
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
Produces:
```
32
2
```
