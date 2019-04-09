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
    std::cout << __LINE__ << ": " << #x << " is ";\
    print_process(x);\
    std::cout << '\n';

template <typename T,
          typename std::enable_if<!(is_iterable<T>::value||std::is_pointer<T>::value),T>::type* =nullptr>
void print_process(T&x){
    if(std::is_pointer<T>::value){
        std::cout << "pointer" << std::endl;
    } else {
        std::cout << x << " ";
    }
}

template <typename T,
          typename std::enable_if<(std::is_pointer<T>::value),T>::type* =nullptr>
void print_process(T&x){
    print_process(*x);
}


template <typename T,
          typename std::enable_if<!(is_iterable<T>::value),T>::type* =nullptr>
void array_process(T &x, std::queue<int> sizes){
    print_process(x);
}

template <typename T,
          typename std::enable_if<(is_iterable<T>::value),T>::type* =nullptr>
void array_process(T &x, std::queue<int> sizes){
    std::cout << "{ ";
    unsigned int n=sizes.front();
    sizes.pop();
    for (int i = 0; i < n; ++i) {
        array_process(x[i],sizes);
        if(sizes.size()>0)std::cout << '\n';
    }
    std::cout << "}";
}

#define array_extent_push(i) if(i<rank)sizes.push(std::extent<T,i>::value);

template <typename T,
          typename std::enable_if<is_iterable<T>::value,T>::type* =nullptr>
void print_process(T&x){
    if(std::rank<T>::value){
        std::queue<int>sizes;
        unsigned int rank=std::rank<T>::value;
        array_extent_push(0);
        array_extent_push(1);

        array_process(x,sizes);
    } else {
        std::cout << "{ ";
        for (auto e : x) {
            print_process(e);
        }
        std::cout << "}";
    }
}

