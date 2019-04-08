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

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int a[1]={0};
    int*b=new int[10];
    cout << is_iterable<decltype(a)>::value << endl;
    cout << is_iterable<decltype(b)>::value << endl;
}
