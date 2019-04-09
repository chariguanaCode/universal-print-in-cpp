/* ==============================================================================
 *  
 *  Contributors:
 *      Name:       Adam Jeliński
 *      Nickname:   charodziej
 *
 *  Description:    A library implementing a uniform method of printing variables in C++
 *                  Mainly directed for competetive programming, to greatly speedup debugging
 *
 *  Created:        08.04.2019
 *  Last updated:   09.04.2019
 *
 *  universal-print-in-cpp
 *  Universal print in C++
 *
 *  g++ -std=c++11 -o template.o template.cpp
 *  ./template.o
 *
 * ============================================================================== */

#include<bits/stdc++.h>

#define debug if(1)
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
        std::true_type{});

    template <typename T>
    std::false_type is_iterable_impl(...);

}

template <typename T>
using is_iterable = decltype(detail::is_iterable_impl<T>(0));

/* ------------------------------------------------------------------------------
 *  Declaration of all the functions to prevent errors related to definition order
 * ------------------------------------------------------------------------------ */
template <typename T, typename std::enable_if<!(     is_iterable<T>::value||
                                                std::is_pointer <T>::value),T>::type* =nullptr> void print_process(T &x);
template <typename T, typename std::enable_if< (std::is_pointer <T>::value),T>::type* =nullptr> void print_process(T &x);
template <typename T, typename std::enable_if< (     is_iterable<T>::value),T>::type* =nullptr> void print_process(T &x);

template <typename T, typename std::enable_if<!(     is_iterable<T>::value),T>::type* =nullptr> void array_process(T &x, std::queue<int> sizes);
template <typename T, typename std::enable_if< (     is_iterable<T>::value),T>::type* =nullptr> void array_process(T &x, std::queue<int> sizes);

                                                                                                void print_process(std::string    &x);
template <typename T, typename U                                                              > void print_process(std::pair<T,U> &x);

/* ------------------------------------------------------------------------------
 *  The main definition called by the user from the main program
 * ------------------------------------------------------------------------------ */
#define watch(x)\
    std::cout << __LINE__ << ": " << #x << " is ";\
    print_process(x);\
    std::cout << '\n';

/* ------------------------------------------------------------------------------
 *  Printing of variables compatible with std::cout TODO: probably should check using is_arithmetic
 * ------------------------------------------------------------------------------ */
template <typename T, typename std::enable_if<!(     is_iterable<T>::value||
                                                std::is_pointer <T>::value),T>::type* =nullptr>
void print_process(T &x){
    std::cout << x;
}

/* ------------------------------------------------------------------------------
 *  Handling pointers
 * ------------------------------------------------------------------------------ */
template <typename T, typename std::enable_if< (std::is_pointer <T>::value),T>::type* =nullptr>
void print_process(T &x){
    print_process(*x);
}

/* ------------------------------------------------------------------------------
 *  Handling strings ( they are iterable, but shouldn't be shown like arrays )
 * ------------------------------------------------------------------------------ */
void print_process(std::string &x){
    std::cout << "\"" << x << "\"";
}

/* ------------------------------------------------------------------------------
 *  Handling pairs
 * ------------------------------------------------------------------------------ */
template <typename T, typename U>
void print_process(std::pair<T,U> &x){
    std::cout << "( ";
    print_process(x.first);
    std::cout << ", ";
    print_process(x.second);
    std::cout << " )";
}

/* ------------------------------------------------------------------------------
 *  Iterating over iterable objects
 *  std::rank returns the number of dimensions of a standard array, allowing us to process
 *  multi dimensional arrays ( only the first level is iterable )
 * ------------------------------------------------------------------------------ */
#define array_extent_push(i) if(i<rank)sizes.push(std::extent<T,i>::value);
template <typename T, typename std::enable_if< (     is_iterable<T>::value),T>::type* =nullptr>
void print_process(T &x){
    if(std::rank<T>::value){
        std::queue<int>sizes;
        unsigned int rank=std::rank<T>::value;
        array_extent_push(0);
        array_extent_push(1);

        array_process(x,sizes);
    } else {
        std::cout << "{ ";
        for (int i = 0; i < 4; ++i) indent.push_back(' ');
        if(is_iterable<decltype(*begin(x))>::value)
            std::cout << '\n' << indent;
        for (auto e : x) {
            print_process(e);
            if(is_iterable<decltype(*begin(x))>::value) {
                std::cout << '\n' << indent;
            } else {
                std::cout << ' ';
            }
        }
        for (int i = 0; i < 4; ++i) indent.pop_back();
        if(is_iterable<decltype(*begin(x))>::value)
            std::cout << "\e[4D";
        std::cout << "}";
    }
}

/* ------------------------------------------------------------------------------
 *  Recurrently go through all dimensions of an array
 * ------------------------------------------------------------------------------ */
template <typename T, typename std::enable_if< (     is_iterable<T>::value),T>::type* =nullptr>
void array_process(T &x, std::queue<int> sizes){
    unsigned int n=sizes.front();
    sizes.pop();

    std::cout << "{ ";
    for (int i = 0; i < 4; ++i) indent.push_back(' ');
    if(sizes.size()>0)
        std::cout << '\n' << indent;

    for (int i = 0; i < n; ++i) {
        array_process(x[i],sizes);
        if(sizes.size()>0) {
            std::cout << '\n' << indent;
        } else {
            std::cout << ' ';
        }
    }
    for (int i = 0; i < 4; ++i) indent.pop_back();
    if(sizes.size()>0)
        std::cout << "\e[4D";
    std::cout << "}";
}

/* ------------------------------------------------------------------------------
 *  When reached the last dimension of an array, print its contents using previously defined methods
 * ------------------------------------------------------------------------------ */
template <typename T, typename std::enable_if<!(     is_iterable<T>::value),T>::type* =nullptr>
void array_process(T &x, std::queue<int> sizes){
    print_process(x);
}

