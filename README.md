# cpp_list_comprehension
A library which introduces pythons list comprehension to C++ based on `boost::phoenix`.
# Usage example
## 1. example common C++ way to C++ list comprehension
This C++ code:
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
## 2. example Python3 to C++ with for_each_
This Python3 code:
```python
listOfWords = ["this","is","a","list","of","words"]
items = [ word[0] for word in listOfWords ]
```
can be written in C++ like:
```C++
int main()
{
    std::vector<std::string> listOfWords{"this","is","a","list","of","words"}
    std::string str;
    comprehension::CompVec<std::vector<char>> vec
        (
              ref(str)[val(0)]
            , for_each_(val(listOfWords), ref(str))
        );
}
```
## 3. example Python3 to C++ with for_each_
This Python code:
```python
[x.lower() for x in ["A","B","C"]]
```
can be writtein in C++ like:
```C++
struct Lower
{
    using result_type = char;
    char operator()(char chr) const
    {
        return std::toupper(chr);
    }
};
boost::phoenix::function<Upper> ph_lower;
int main()
{
    char e;
    comprehension::CompVec<std::vector<char>> vec
        (
              ph_lower(ref(e))
            , for_each_(val(std::string("ABC")), ref(e))
        );
}
```
## 4. example if_
```C++
int main()
{
    int i;
    // vector with all even numbers from 0 to 100
    comprehension::CompVec<std::vector<int>> l2
        (
              ref(i)
            , for_(ref(i) = 0, ref(i) <= 100, ref(i)++)
            , if_(ref(i) % 2 == 0)
	);
}
```
