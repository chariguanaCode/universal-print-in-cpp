#define DEBUG 1
#include <string>
#include <math.h>
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

double pi = 3.14159265359;

double a[5] = {13.0,27.0,14.0,61.0,3.14159265359};
double b[5] = { 0.0,3.14159265359,15.0,61.0,71.0};
double T    = 8.0;

double s(double x){
    double result = a[0]/2.0;
    for (int i = 1; i < 5; ++i) {
        watch(2.0*i*pi/T);
        watch(sin(2.0*i*pi/T));
        watch(cos(2.0*i*pi/T));
        watch(result);
        result+=a[i]*cos(2.0*i*pi*x/T)+b[i]*sin(2.0*i*pi*x/T);
    }
    return result;
}

int main(){
    watch(s(10));
}
