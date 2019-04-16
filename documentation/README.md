# Documentation

To further expand your debugging capabilities this library gives you access to various internal functions it uses.


## `debug` 
Equivalent to `if(DEBUG)`.


## `cupl::checkEncodingCompatibility()` 
If binary trees look very weird on your system, you will want to change the default character encoding.

This function will print the custom characters in all supported encodings, so you can pick the one that suits you best.


## `cupl::print_main(variable, int line, string name)` 
Allows you to `watch()` your variable with a custom line number and name.
 

## `cupl::print_process(variable)` 
The most basic component of the core library functionality. Prints the variable without anything before or after it.
 

## `cupl::indent();` 
Allows you to indent all following lines within this `watch()`.
   
 
## `cupl::unindent();` 
Allows you to unindent all following lines within this `watch()`.
  
 
## `cupl::colour(int val)` 
Returns the string required to change the foreground colour to `val` (8 bit colours).
    

## `cupl::backgr(int val)` 
Returns the string required to change the background colour to `val` (8 bit colours).
    

## `cupl::bold()` 
Returns the string required to make the text bold.
    

## `cupl::clr()` 
Returns the string required to reset any changes to text appearence.
    

## `cupl::type_name(variable)` 
Returns a string that contains the type name of your variable that the compiler creates.


## `cupl::is_iterable(variable)` 
Returns `true` if your `variable` is iterable and `false` otherwise.

(iterable means that `for(auto e: variable)` works properly on it).
