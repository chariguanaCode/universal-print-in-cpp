# Universal Print in Cpp

This is a library mainly meant to increase the efficiency of debugging C++ programs. 
Very handy when used for competetive programming.

## Installation

 1. Clone this repository using
    ```
    git clone https://gitlab.com/charodziej/universal-print-in-cpp
    ```
    or by downloading it from [here](https://gitlab.com/charodziej/universal-print-in-cpp/-/archive/master/universal-print-in-cpp-master.zip)
 2. Make sure that everything works on your platform by compiling at least one of the examples (__TODO__) in your programming environment
 3. If everything is working properly, include the `universal_print.h` library to your project and copy the contents of `template.cpp` to the main file of that project (not necessary but recommended)

## Usage

 1. To enable the library, you only need to add 
    ```cpp
    #define DEBUG 1
    ```
    to the beginning of a project based on `template.cpp`.
    At this point your program should be showing a banner, informing you that you are in debug mode.

 2. To make use of the basic functionality you only need to call
    ```cpp
    watch(<variable_name>);
    ```
    where `<variable_name>` is the name of your variable.

 3. If you do not fancy seeing the names of types you can disable them using
    ```cpp
    cupl::showTypes(false);
    ```
    and reenable them using
    ```cpp
    cupl::showTypes(true);
    ```
    if that's what you need to do.

 4. If your data type isn't supported (for example because it's a `struct`) you will need to implement an expansion to the library in your main cpp file.
 
    You can do it as follows:
    ```cpp
    #if DEBUG==1
    void cupl::print_process(<data_type> name){
        <custom_printing_code>
    }
    #endif
    ```
    where `<data_type>` would be the your custom data type and `<custom_printing_code>` would be your method of printing the variable. 
    
    After each `endln` or `\n` in your `<custom_printing_code>` you have to print the variable `cupl::indentation` to make everything look properly.
    
    Please note that if your custom type contains other types that are supported by our library you can just call `cupl::print_process();` on those members of your type.
    
    You may want to check out this example (__TODO__) to better understand how to implement this.

## Special functions and declarations

To further improve your debugging capabilities this library gives you access to various internal functions it uses:

* `debug`:                                                Equivalent to `if(DEBUG)`

* `cupl::print_main(variable, int line, string name)`:    Allows you to `watch()` your variable with a custom line number and name
 
* `cupl::indent();`:                                      Allows you to indent all following lines within this `watch()` 
    
* `cupl::unindent();`:                                    Allows you to unindent all following lines within this `watch()` 
   
* `cupl::colour(int val)`:                                Returns the string required to change the foreground colour to `val` (8 bit colours)
    
* `cupl::backgr(int val)`:                                Returns the string required to change the background colour to `val` (8 bit colours)
    
* `cupl::bold()`:                                         Returns the string required to make the text bold
    
* `cupl::clr()`:                                          Returns the string required to reset any changes to text appearence
    
* `cupl::is_iterable(variable)`:                          Returns `true` if your `variable` is iterable and `false` otherwise

## Screenshots

## TODO

* [ ] examples
* [x] support for const
* [ ] printing binary trees nicely
* [ ] printing other graphs _nicely_
* [ ] screenshots

## Issues

If you encounter any issues or come up with nice improvements please report them on the Issue Tracker.

Merge requests are welcome too :).

## Contributors

* Adam Jeliński (charodziej)
* Kajetan Lewandowski (LegwanXDL)
