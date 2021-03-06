![Banner](/screenshots/Banner.jpg)

# Universal Print in C++ 
#### also known as the Competetive Universal Print Library (cupl)

This is a library mainly meant to increase the efficiency of debugging C++ programs. 
Very handy when used for competetive programming.

The efficiency increase is possible thanks to the `watch()` function introduced by this library.
It can print out the value of _almost_ every variable, structure or expression, along with the context that it appears in (line number, variables name and type name).

The current version compiles __only__ with the c++17 standard! (and probably higher standards when they come out)

## Supported and tested types

* all numeric variables (`bool`, `char`, `short`, `int`, `long`, `long long`, `float`, `double`, `long double`) both `signed` and `unsigned`
* `std::string`
* `std::bitset`
* `std::vector`, `std::array` and arrays with defined dimensions
* `std::stack`, `std::queue`, `std::deque`, `std::priority_queue`
* `std::list`
* `std::pair`
* `std::map`, `std::multimap`, `std::set`, `std::multiset`
* all pointers of any type that is supported
* all `const` variants of supported types
* all arithmetic expressions of supported types
* binary trees
* probably more are supported but we haven't tested them (everything from STL)

## Contributors

* Adam Jeliński (charodziej)
* Kajetan Lewandowski (LegwanXDL)

## Installation

 1. Clone this repository using
    ```
    git clone https://github.com/chariguanaCode/universal-print-in-cpp
    ```
    or by downloading it from [here](https://github.com/chariguanaCode/universal-print-in-cpp/archive/master.zip)
 2. Make sure that everything works on your platform by compiling at least one of the [examples](/examples/) in your programming environment
 3. If everything is working properly, include the `universal_print.h` library from the `lib` folder in your project and copy the contents of `template.cpp` to the main file of that project (not necessary but recommended)

## Documentation

The full documentation describing all the functions can be found [here](/documentation/README.md)

## Usage

 1. To enable the library, you only need to add 
    ```cpp
    #define DEBUG 1
    ```
    to the beginning of a project based on `template.cpp`.
    At this point your program should print a banner, informing you that you are in debug mode.

 2. To make use of the basic functionality you only need to call
    ```cpp
    watch(<variable_name>);
    ```
    where `<variable_name>` is the name of your variable.

 3. If you do not fancy seeing the names of types you can disable them using
    ```cpp
    cupl::showTypes(false);
    ```
    and re-enable them using
    ```cpp
    cupl::showTypes(true);
    ```
    if that's what you need to do.

 4. If your data type isn't supported you will need to implement an expansion to the library in your main cpp file.
 
    You can do it as follows:
    ```cpp
    void print_process(<data_type> name){
        <custom_printing_code>
    }
    ```
    where `<data_type>` would be the your custom data type and `<custom_printing_code>` would be your method of printing the variable. 
    
    Each `endln` or `\n` printed by your `<custom_printing_code>` has to be followed by the variable `cupl::indentation` to make everything look properly.
    
    Please notice that if your custom type contains other types that are supported by our library you can just call `cupl::print_process();` on those members of your type.

    Due to C++ limitations `struct`s aren't supported by default and each `struct` has to have their members provided to cupl like so:
    ```cpp
    struct my_struct{
        type1 member1;
        type2 member2;
        <more_members>
        ...
        declare_struct(member1, member2, <more_members>...);
    }
    ```
    You may want to check out [this example](/examples/structs.cpp) to better understand how to implement this.

## Customization

If you would like to change the colours of objects, change the precision `std::cout` uses or binary trees look weird on your system, you should take a look at the beginning of the `universal_print.h` file.

The "User setup" section will allow you to change all of those things easily.

## TODO

* [x] support for const
* [x] examples
* [x] screenshots
* [x] printing binary trees nicely
* [x] embracing new features of c++17
* [ ] printing other graphs _nicely_

## Issues

If you encounter any issues or come up with nice improvements please report them on the Issue Tracker.

Merge requests are welcome too :).

## Screenshots

![basic.cpp on Linux](/screenshots/Linux_basic.png)

![structs.cpp on Linux](/screenshots/Linux_structs.png)

![math.cpp on Linux](/screenshots/Linux_math.png)

![trees.cpp on Linux](/screenshots/Linux_trees.png)

![extreme.cpp on Linux](/screenshots/Linux_extreme.png)

![random.cpp on Linux](/screenshots/Linux_random.png)

