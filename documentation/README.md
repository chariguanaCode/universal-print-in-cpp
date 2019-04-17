# Documentation

To further expand your debugging capabilities this library gives you access to various internal functions it uses.

By variable we mean variables, data structures and expressions.

## `watch(variable)` 
This is the main function of the library. By calling this your `variable` will be printed nicely with line in code, `variable` type and `variable` name.  

## 'watch(variable, int mode)`
You can call `watch` with second parameter which is determining `watch` mode. There are three modes available at this time (release 1.0). 

* Mode 0 is default mode and is calling when there is given one parameter
* Mode 1 is binary trees mode
* Mode 2 is printing `variable` value without line in code, `variable` type and `variable` name.


## `watch(variable, 1, root, doesExist, getValue, getLeftSon, getRightSon)`
This is binary trees mode. Last 2 arguments aren't necessary for standart binary trees in array.

* `root` is just root of the tree

* `doesExist` is a function which is determining if vertex exist. For standart binary tree in array this function can look like that:
```
bool doesExist(int val){return val<tree_size;}
```

* `getValue` needs to be a function returning value of vertex. For standart binary tree in array this function can look like that:
```
int getValue(int val){return my_tree[val];};
```

* `getLeftSon` needs to be a function returning left son of vertex. For standart binary tree in array this function can look like that:
```
int getValue(int val){return val*2;}
```

* `getRightSon` is a function which is returning right son of vertex. For standart binary tree in array this function can look like that:
```
int getValue(int val){return val*2+1;}
```


## `cupl::showTypes(bool val)`
This function able or disable showing types' names after calling `watch()`.


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
