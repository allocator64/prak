#include <ctime>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <functional>

template<class T>
struct IsClass
{
    typedef char yes[1];
    typedef char no[2];
    
    template <class P>
    static yes& test(void(P::*)());
 
    template <class>
    static no& test(...);
    
    static const bool value = sizeof(test<T>(0)) == sizeof(yes);   
};
