#define DEBUG 1
#include <iostream>
#include<tuple>
#include <string>
#ifndef DEBUG
#define DEBUG 0
#elif DEBUG==1
#include "../lib/universal_print.h"
#endif
#if DEBUG==0
#define watch(...)
#define watchb(...)
#define declare_struct(...)
#define debug if(0)
namespace cupl{
    template <typename T> void print_main(T &x, int y, std::string z){return;}
    std::string indentation = "";
    void indent(){return;}
    void unindent(){return;}
    std::string bold(){return "";}
    std::string clr(){return "";}
    std::string backgr(int x){return "";}
    std::string colour(int x){return "";}
    void showTypes(bool val){return;}
    template <typename T> bool is_iterable(T x){return 0;}
    void print_process(...);
}
void print_process(...);
#endif

//definition of my struct
struct my_list{
    int id;
    std::pair<int, float> value;
    my_list* next=NULL;

    //declaring that all of the members should be printed
    declare_struct(id, value, next);
};

int main(){
    //all the data
    int integers[10] = {  6,   2,   1,   0,   5,   7,   9,   5,   8,   3};
    float floats[10] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.1};

    //defining the root and helper pointer for the list
    my_list* start   = new my_list;
    my_list* current = new my_list;
    //setting up all the root
    start->id    = 0;
    start->value = std::make_pair(integers[0], floats[0]);
    current = start;

    //building the list
    for (int i = 1; i < 10; ++i) {
        my_list* tmp = new my_list;
        current->next  = tmp;
        current = tmp;

        current->id    = i;
        current->value = std::make_pair(integers[i], floats[i]);
    }
    //watching the results ^.^
    watch(integers, floats, start);
}
