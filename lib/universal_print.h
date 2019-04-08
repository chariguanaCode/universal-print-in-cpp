#define debug if(1)
#define watch_tab(x,n) debug {cout << __LINE__ << ": " << (#x) << " is "; \
    for(int very_long_index=0;very_long_index<n;very_long_index++){ cout << x[very_long_index] << ", ";}\
    cout << endl;}

#include<bits/stdc++.h>
namespace detail
{
    // To allow ADL with custom begin/end
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

#define watch(x)\
    cout << __LINE__ << ": " << #x << " is ";\
    print_process(x);\
    cout << '\n';

template <typename T,
          typename std::enable_if<!(is_iterable<T>::value),T>::type* =nullptr>
void print_process(T&x){
    std::cout << x << " ";
}

template <typename T,
          typename std::enable_if<is_iterable<T>::value,T>::type* =nullptr>
void print_process(T&x){
    for (auto e : x) {
        print_process(e);
    }
}
