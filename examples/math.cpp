#include <string>
#include <math.h>
#ifndef DEBUG
//if there is no DEBUG defined it turns DEBUG mode off
#define DEBUG 0
#elif DEBUG==1
//if DEBUG mode is on it includes the universal_print library
#include "../lib/universal_print.h"
#endif
#if DEBUG==0
//if DEBUG mode is off it defines all debug mode functions to "turn them off"
//so you don't have to delete all library functions before submiting the final code
#define watch(...)
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

int main(){
    double pi = 3.14159265359;
    double gamma = 70.0;
    double a = 10.0, b = 30.0;
    watch(pi);
    watch(gamma);
    watch(a);
    watch(b);
    watch(sin(gamma*pi/180.0));
    double surface = 0.5*a*b*sin(gamma*pi/180.0);
    watch(surface);
}
