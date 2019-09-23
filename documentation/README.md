# Documentation

To further expand your debugging capabilities this library gives you access to various internal functions it uses.

Here by variables we mean variables, data structures and expressions.

## `watch(variable)`
This is the main function of the library. By calling this your `variable` will be printed nicely with the line number, `variable` type and `variable` name.  

## `watch(variable, int mode)`
You can call `watch` with a second parameter which determines the `watch` mode. There are three modes available at the moment of writing (release 1.0). 

* Mode 0 is the default mode which is selected, when only a single parameter is given
* Mode 1 is binary trees mode <3
* Mode 2 prints the `variable` value without the line number, `variable` type nor `variable` name.


## `watch(variable, 1, root, doesExist, getValue, getLeftSon, getRightSon)`
This is THE binary trees mode. The last 2 arguments aren't necessary for standard binary trees in an array.

* `root` is just the root of the tree

* `doesExist` has to be a function returning if a vertex exist. For a standard binary tree in an array this function can look like this:
```
bool doesExist(int val){return val<tree_size;}
```

* `getValue` has to be a function returning the value of a vertex. For a standard binary tree in an array this function can look like this:
```
int getValue(int val){return my_tree[val];};
```

* `getLeftSon` has to be a function returning a 'reference' to the left son of a vertex. For a standard binary tree in an array this function can look like this:
```
int getValue(int val){return val*2;}
```

* `getRightSon` has to be a function returning a 'reference' to the right son of a vertex. For a standard binary tree in an array this function can look like this:
```
int getValue(int val){return val*2+1;}
```


## `cupl::showTypes(bool val)`
This function is used to enable or disable showing types' names when calling `watch()`.


## `debug` 
Equivalent to `if(DEBUG)`.


## `cupl::checkEncodingCompatibility()` 
If binary trees look very weird on your system, you will want to change the default character encoding.

This function will print the custom characters in all supported encodings, so you can pick the one that suits you best.

![character encoding.png](/screenshots/character_encoding.png)

This is what the characters should look like, in the encoding you selected.


## `cupl::print_main(variable, int line, string name)` 
Allows you to `watch()` your variable with a custom line number and name.
 

## `cupl::print_process(variable)` 
The most _basic_ component of the core library functionality. Prints the `variable` without anything before or after it.
 

## `cupl::indent();` 
Allows you to indent all following lines within this `watch()`.
   
 
## `cupl::unindent();` 
Allows you to unindent all following lines within this `watch()`.
  
 
## `cupl::colour(int val)` 
Returns the string required to change the foreground colour to `val` (8-bit colours).
    

## `cupl::backgr(int val)` 
Returns the string required to change the background colour to `val` (8-bit colours).
    

## `cupl::bold()` 
Returns the string required to make the text bold.
    

## `cupl::clr()` 
Returns the string required to reset any changes to the text appearence.
    

## `cupl::type_name(variable)` 
Returns a string that contains the type name of your `variable` that the compiler creates.


## `cupl::is_iterable<decltype(variable)>::value` 
Returns `true` if your `variable` is iterable and `false` otherwise.

(iterable means that `for(auto e: variable)` works properly on it).
