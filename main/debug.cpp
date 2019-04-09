#define DEBUG 1
#include"bits/stdc++.h"
using namespace std;

#ifndef DEBUG
#define DEBUG 0
#endif

#if DEBUG==1
#include"../lib/universal_print.h"
#else
#define watch(x)
#endif

typedef long long ll;
typedef unsigned long long ull;

struct xdxd {int x;};

void print_process(xdxd t){
    cout << t.x << " ";
}

int main(){
#if DEBUG==0
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
#endif

    int a[4]={0,2,3,4};
    int two_d[4][2]={{0,1},{2,3},{4,5},{6,7}};
    int*b=new int[10];
    vector<int> c;
    int xd=10;
    string ala="ma kota";
    xdxd d;
    pair<int,string> my_pair=make_pair(29,"testing");

    //watch(10);         //nie działa :'(
    watch(a);
    watch(a[0]);
    watch(b);
    watch(c);
    watch(d);
    watch(xd);
    watch(two_d);
    watch(ala);
    watch(my_pair);
}
