/* ==============================================================================
 *
 *  Based on the template from the Competetive Universal Print Library
 *  Created by:
 *   - Adam Jeliński (charodziej)
 *   - Kajetan Lewandowski (LegwanXDL)
 *
 *   https://github.com/chariguanaCode/universal-print-in-cpp
 *
 * ============================================================================== */

#include <bits/stdc++.h>
using namespace std;

#ifndef DEBUG
#define DEBUG 0
#elif DEBUG==1
#include "universal_print.h"
#endif
#if DEBUG==0
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
    void print_process(...){return;}
}
void print_process(...){return;}
#endif

/* ============================================================================== *
 *     /\                   Please pardon the code above                   /\     *
 *     ||  It is necessary for the debugging library to function properly  ||     *
 * ============================================================================== */

typedef   signed long long  ll;
typedef unsigned long long ull;

int main(){
    
}
