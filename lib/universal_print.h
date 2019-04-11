/* ==============================================================================
 *
 *  Contributors:
 *      Name:       Adam Jeliñski & Kajetan Lewandowski
 *      Nickname:   charodziej & LegwanXDL
 *
 *  Description:    A library implementing a uniform method of printing variables in C++
 *                  Mainly intended for competetive programming, to greatly speedup debugging
 *
 *  Created:        08.04.2019
 *  Last updated:   11.04.2019
 *
 *  universal-print-in-cpp
 *  Universal print in C++
 *
 *  g++ -std=c++11 -o template.o template.cpp
 *  ./template.o
 *
 * ============================================================================== */

#include<bits/stdc++.h>
#ifndef _MSC_VER
#   include <cxxabi.h>
#endif

#define debug if(1)

#ifndef SHOW_TYPE_NAME
#define SHOW_TYPE_NAME 1
#endif

bool ANSIsupport = true;

#if defined _WIN32 || defined _WIN64
    #include <windows.h>
     bool functionCaller = []{
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut == INVALID_HANDLE_VALUE){ANSIsupport=0; return 0;}
        DWORD dwMode = 0;
        if (!GetConsoleMode(hOut, &dwMode)){ANSIsupport=0; return 0;}
        dwMode |= 0x0004;
        if (!SetConsoleMode(hOut, dwMode)){ANSIsupport=0; return 0;}
        return 1;
    }();
#endif

std::string indent="";

/* ------------------------------------------------------------------------------
 *  Method of determining if a variable is iterable
 *  thx to Jarod42
 *  https://stackoverflow.com/questions/13830158/check-if-a-variable-is-iterable
 * ------------------------------------------------------------------------------ */
namespace detail
{

using std::begin;
using std::end;

template <typename T>
auto is_iterable_impl(int)
-> decltype (
    begin(std::declval<T&>()) != end(std::declval<T&>()),   // begin/end and operator !=
    void(),                                                 // Handle evil operator ,
    ++std::declval<decltype(begin(std::declval<T&>()))&>(), // operator ++
    void(*begin(std::declval<T&>())),                       // operator*
    std::true_type {});

template <typename T>
std::false_type is_iterable_impl(...);

}

template <typename T>
using is_iterable = decltype(detail::is_iterable_impl<T>(0));

/* ------------------------------------------------------------------------------
 *  Method of determining variables type ( may not be used in the final version )
 *  thx to Howard Hinnant
 *  https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c
 * ------------------------------------------------------------------------------ */
template <class T>
std::string type_name()
{
    typedef typename std::remove_reference<T>::type TR;
    std::unique_ptr<char, void(*)(void*)> own
    (
#ifndef _MSC_VER
        abi::__cxa_demangle(typeid(TR).name(), nullptr,
                            nullptr, nullptr),
#else
        nullptr,
#endif
        std::free
    );
    std::string r = own != nullptr ? own.get() : typeid(TR).name();
    if (std::is_const<TR>::value)
        r += " const";
    if (std::is_volatile<TR>::value)
        r += " volatile";
    if (std::is_lvalue_reference<T>::value)
        r += "&";
    else if (std::is_rvalue_reference<T>::value)
        r += "&&";
    return r;
}

/* ------------------------------------------------------------------------------
 *  Declaration of all the functions to prevent errors related to definition order
 * ------------------------------------------------------------------------------ */
template <typename T, typename std::enable_if< (std::is_arithmetic<T>::value),T>::type* =nullptr> void print_process(T &x);
template <typename T, typename std::enable_if< (std::is_pointer   <T>::value),T>::type* =nullptr> void print_process(T &x);
template <typename T, typename std::enable_if< (     is_iterable  <T>::value),T>::type* =nullptr> void print_process(T &x);

template <typename T, typename std::enable_if<!(     is_iterable  <T>::value),T>::type* =nullptr> void array_process(T &x, std::queue<int> sizes);
template <typename T, typename std::enable_if< (     is_iterable  <T>::value),T>::type* =nullptr> void array_process(T &x, std::queue<int> sizes);

void print_process(std::string            &x);
template <size_t   T                                                                            > void print_process(std::bitset<T>         &x);
template <typename T, typename U                                                                > void print_process(std::pair<T,U>         &x);
template <typename T                                                                            > void print_process(std::stack<T>          &x);
template <typename T                                                                            > void print_process(std::queue<T>          &x);
template <typename T                                                                            > void print_process(std::priority_queue<T> &x);


/* ------------------------------------------------------------------------------
 *  Colours!
 * ------------------------------------------------------------------------------ */
std::string colour(int val){if(ANSIsupport) return "\033[38;5;"+to_string(val)+"m";return "";}
std::string bold() {if(ANSIsupport) return "\033[1m";return "";}
std::string clear(){if(ANSIsupport) return "\033[0m";return "";}

/* ------------------------------------------------------------------------------
 *  The main definition called by the user from the main program
 * ------------------------------------------------------------------------------ */
#define watch(x)\
    print_main(x,__LINE__,#x);

/* ------------------------------------------------------------------------------
 *  The main function doing all the magic
 * ------------------------------------------------------------------------------ */
template <typename T>
void print_main(T &x, int line, std::string name)
{

#if SHOW_TYPE_NAME==1
    std::cout << colour(220) << line << colour(15) << ": "\
              << colour(250) << type_name<T>() << " "\
              << colour( 40) << bold() << name << clear()\
              << colour( 15) << " = ";
#else
    std::cout << colour(220) << line << colour(15) << ": "\
              << colour( 40) << bold() << name << clear()\
              << colour( 15) << " = ";
#endif
    print_process(x);
    std::cout << std::endl << clear();
}

/* ------------------------------------------------------------------------------
 *  Printing variables compatible with std::cout
 * ------------------------------------------------------------------------------ */
template <typename T, typename std::enable_if< (std::is_arithmetic<T>::value),T>::type* =nullptr>
void print_process(T &x)
{
    std::cout << colour(44) << bold() << x << clear();
}

/* ------------------------------------------------------------------------------
 *  Printing bitsets ( compatible with std::cout but aren't arithmetic )
 * ------------------------------------------------------------------------------ */
template <size_t T>
void print_process(std::bitset<T> &x)
{
    std::cout << colour(48) << bold() << x << clear();
}

/* ------------------------------------------------------------------------------
 *  Handling pointers
 * ------------------------------------------------------------------------------ */
template <typename T, typename std::enable_if< (std::is_pointer   <T>::value),T>::type* =nullptr>
void print_process(T &x)
{
    std::cout << colour(213) << bold() << '*' << clear();
    if(x!=nullptr)
        print_process(*x);
    else
        std::cout << colour(196) << bold() << "NULL" << clear();
}

/* ------------------------------------------------------------------------------
 *  Handling strings ( they are iterable, but shouldn't be shown like arrays )
 * ------------------------------------------------------------------------------ */
void print_process(std::string &x)
{
    std::cout << colour(28) << bold() << "\"" << x << "\"" << clear();
}

/* ------------------------------------------------------------------------------
 *  Handling pairs
 * ------------------------------------------------------------------------------ */
template <typename T, typename U>
void print_process(std::pair<T,U> &x)
{
    std::cout << colour(31) << "( " << clear();
    print_process(x.first);
    std::cout << ", ";
    print_process(x.second);
    std::cout << colour(31) << " )" << clear();
}

/* ------------------------------------------------------------------------------
 *  Handling stacks
 * ------------------------------------------------------------------------------ */
template <typename T>
void print_process(std::stack<T> &x)
{
    std::stack<T>  tmp=x;
    std::vector<T> result;

    while(!tmp.empty())
    {
        result.push_back(tmp.top());
        tmp.pop();
    }

    print_process(result);
}

/* ------------------------------------------------------------------------------
 *  Handling queues
 * ------------------------------------------------------------------------------ */
template <typename T>
void print_process(std::queue<T> &x)
{
    std::queue<T>  tmp=x;
    std::vector<T> result;

    while(!tmp.empty())
    {
        result.push_back(tmp.front());
        tmp.pop();
    }

    print_process(result);
}

/* ------------------------------------------------------------------------------
 *  Handling priority queues
 * ------------------------------------------------------------------------------ */
template <typename T>
void print_process(std::priority_queue<T> &x)
{
    std::priority_queue<T>  tmp=x;
    std::vector<T> result;

    while(!tmp.empty())
    {
        result.push_back(tmp.top());
        tmp.pop();
    }

    print_process(result);
}

/* ------------------------------------------------------------------------------
 *  Iterating over iterable objects
 *  std::rank returns the number of dimensions of a standard array, allowing us to process
 *  multi dimensional arrays ( only the first level is iterable )
 * ------------------------------------------------------------------------------ */
#define array_extent_push(i) if(i<rank)sizes.push(std::extent<T,i>::value);
template <typename T, typename std::enable_if< (       is_iterable<T>::value),T>::type* =nullptr>
void print_process(T &x)
{
    if(std::rank<T>::value)
    {
        std::queue<int>sizes;
        unsigned int rank=std::rank<T>::value;
        array_extent_push(0);
        array_extent_push(1);
        array_extent_push(2);
        array_extent_push(3);
        array_extent_push(4);
        array_extent_push(5);

        array_process(x,sizes);

    }
    else
    {
        std::cout << colour(31) << "{ " << clear();
        for (int i = 0; i < 4; ++i)
            indent.push_back(' ');

        if(is_iterable<decltype(*begin(x))>::value&&begin(x)!=end(x))
            std::cout << '\n' << indent;

        for (auto e : x)
        {

            print_process(e);

            if(is_iterable<decltype(*begin(x))>::value&&begin(x)!=end(x))
            {
                std::cout << '\n' << indent;
            }
            else
            {
                std::cout << ' ';
            }
        }

        if(is_iterable<decltype(*begin(x))>::value&&begin(x)!=end(x))
            std::cout << "\033[4D";

        for (int i = 0; i < 4; ++i)
            indent.pop_back();
        std::cout << colour(31) << "}" << clear();
    }
}

/* ------------------------------------------------------------------------------
 *  Recursively go through all dimensions of an array
 * ------------------------------------------------------------------------------ */
template <typename T, typename std::enable_if< (       is_iterable<T>::value),T>::type* =nullptr>
void array_process(T &x, std::queue<int> sizes)
{
    int n=sizes.front();
    sizes.pop();

    std::cout << colour(31) << "{ " << clear();
    for (int i = 0; i < 4; ++i)
        indent.push_back(' ');

    if(sizes.size()>0)
        std::cout << '\n' << indent;

    for (int i = 0; i < n; ++i)
    {

        array_process(x[i],sizes);

        if(sizes.size()>0)
        {
            std::cout << '\n' << indent;
        }
        else
        {
            std::cout << ' ';
        }
    }

    if(sizes.size()>0)
        std::cout << "\033[4D";

    for (int i = 0; i < 4; ++i)
        indent.pop_back();
    std::cout << colour(31) << "}" << clear();
}

/* ------------------------------------------------------------------------------
 *  When reached the last dimension of an array, print its contents using previously defined methods
 * ------------------------------------------------------------------------------ */
template <typename T, typename std::enable_if<!(       is_iterable<T>::value),T>::type* =nullptr>
void array_process(T &x, std::queue<int> sizes)
{
    print_process(x);
}


