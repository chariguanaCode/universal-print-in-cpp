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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int a[1]={0};
    int*b=new int[10];
    vector<int> c;
    int xd=10;
    string ala="ma kota";
    xdxd d;
    cin >> d.x;
    cout << typeid(a).name() << endl;
    //watch(10);         //nie działa :'(
    watch(a);
    watch(b);
    watch(c);
    watch(d);
    watch(xd);
    watch(ala);
}
