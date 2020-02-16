#define DEBUG 1
#include <iostream>
#include <vector>
#include <bitset>
#ifndef DEBUG
#define DEBUG 0
#elif DEBUG==1
#include "../lib/universal_print.h"
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
    void print_process(...);
}
void print_process(...);
#endif

///binary tree in array (a)

int a[10]={-2113,-15,113,-132,14,51,-15,521,13,12};

bool a_doesExist(int val){ return val<10;}
int a_getValue(int val){return a[val];}
//we don't need functions below because there
//are default functions to binary tree in array
int a_getLeftSon(int val){return val*2;}
int a_getRightSon(int val){return val*2+1;}

///binary tree in array (b)

std::vector<std::vector<int> > b[10] = {{{1,2},{2,3}},{{1,2},{2,3}},{{1,2},{2,3}},{{1,2},{2,3}},{{1,2},{2,3}},{{1,2},{2,3}},{{1,2},{2,3}},{{1,2},{2,3}},{{1,2},{2,3}},{{1,2},{2,3}}};

bool b_doesExist(int val){return val<10;}
std::vector<std::vector<int> > b_getValue(int val){return b[val];}

///binary tree in array (c)

//to see numbers with bigger precision change std::cout precision in User setup in universal_print.h
std::pair<std::bitset<10>,long double> c[10] = {std::make_pair(100101,3.7628321),std::make_pair(10101,777.777),std::make_pair(0,32.3264),std::make_pair(11111,1.123581321345589),std::make_pair(100101,3.7628321),std::make_pair(101,3.161616),std::make_pair(11,314141),std::make_pair(1111,2.67),std::make_pair(001,13.13),std::make_pair(100101,3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481117450284102701938521105559644622948954930381964428)};

bool c_doesExist(int val){return val<10;}
std::pair<std::bitset<10>,long double> c_getValue(int val){return c[val];}

///binary tree in array (d)

int d[14]={0,1,2,3,4,5,6,7,8,9,10,11,12,13};

bool d_doesExist(int val){ return val<14;}
int d_getValue(int val){return d[val];}
//we can change right son with left son
int d_getLeftSon(int val){return val*2+1;}
int d_getRightSon(int val){return val*2;}

///binary tree in array (e)

int e[14]={0,1,2,3,4,5,6,7,8,9,10,11,12,13};
//we can add more conditions to doesExist
//now we won't show left subtree
bool e_doesExist(int val){return val<14 && val!=2;}
int e_getValue(int val){return e[val];}

///binary tree in array (f)

int f[14]={0,1,2,3,4,5,6,7,8,9,10,11,12,13};
//we can also use lambda functions on calling (however, we can not yet)

///binary tree in adjacency matrix (a)

int aa[9][9];
//1 for left son, 2 for right son
bool aa_setValues = [](){aa[1][2]=1; aa[1][3]=2; aa[2][4]=1; aa[2][5]=2; aa[3][6]=1; aa[3][7]=2; aa[4][8]=2;
aa[1][1]=1; aa[2][2]=1; aa[3][3]=2; aa[4][4]=3; aa[5][5]=5; aa[6][6]=8; aa[7][7]=13; aa[8][8]=6; return 0;}();

bool aa_doesExist(int val){return val<9;}
int aa_getValue(int val){return aa[val][val];}
int aa_getLeftSon(int val) {
    for(int i=1; i<9; ++i) {
            if(i!=val && aa[val][i]==1) return i;
    }
    return 9;
}
int aa_getRightSon(int val) {
    for(int i=1; i<9; ++i) {
            if(i!=val && aa[val][i]==2) return i;
    }
    return 9;
}


int main() {
    ///binary tree in array (a)
    //we can also call watchb(1,a_doesExist,a_getValue,a_getLeftSon, a_getRightSon)
    //but it isn't necessary because there are default functions to binary tree in array
    watchb(1,a_doesExist,a_getValue);

    //we can also set root in other vertex
    watchb(2,a_doesExist,a_getValue);

    ///binary tree in array (b)
    watchb(1,b_doesExist,b_getValue);

    ///binary tree in array (c)
    watchb(1,c_doesExist,c_getValue);

    ///binary tree in array (d)
    watchb(1,d_doesExist,d_getValue,d_getLeftSon,d_getRightSon);

    ///binary tree in array (e)
    watchb(1,e_doesExist,e_getValue);

    ///binary tree in array (f)
    //watchb(1,[](int val){return val<14;},[](int val){return f[val];}) //it doesn't work yet

    ///binary tree in adjacency matrix (a)
    watchb(1,aa_doesExist,aa_getValue,aa_getLeftSon,aa_getRightSon);

}