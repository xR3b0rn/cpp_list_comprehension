# cpp_list_comprehension
A library which introduces pythons list comprehension to C++ based on `boost::phoenix`.
# Usage example
`boost::phoenix` uses function which are evaluated later, so called layz funcitons. For any function which shall be invoked in lazy context must previously made lazy.
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
// make sqrt lazy
int main()
{
    using namespace boost::phoenix;
    auto ph_isqrt = comprehension::make_lazy<int, decltype(::sqrt), ::sqrt>();
    int var = 1028;
    comprehension::CompVec<std::vector<int>> lis
        (
            // use lazy ph_isqrt in lazy context
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
    using namespace boost::phoenix;
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
// make std::tolower lazy
int main()
{
    using namespace boost::phoenix;
    auto ph_lower = comprehension::make_lazy<char, decltype(std::tolower), std::tolower>()
    char e;
    comprehension::CompVec<std::vector<char>> vec
        (
            // use lazy function ph_lower in lazy context
              ph_lower(ref(e))
            , for_each_(val(std::string("ABC")), ref(e))
        );
}
```
## 4. example if_
```C++
int main()
{
    using namespace boost::phoenix;
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
