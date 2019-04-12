#include"bits/stdc++.h"
using namespace std;

#ifndef DEBUG
#define DEBUG 0
#endif

#if DEBUG==1
#include"../lib/universal_print.h"
#else
#define watch(x)
#define debug if(0)
string indentation="";
void indent(){};
void unindent(){};
#endif

typedef long long ll;
typedef unsigned long long ull;

struct xdxd {int x;};

#if DEBUG==1
void print_process(xdxd t){
    cupl::print_process(t.x);
}
#endif

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
    stack<int> my_stack;
    queue<int> my_queue;
    deque<int> my_deque;
    priority_queue<int> my_priority_queue;
    int* null_pointer=nullptr;
    bitset<100> my_bitset;
    for (auto e : a) {
        my_stack.push(e);
        my_queue.push(e);
        my_deque.push_front(e);
        my_deque.push_back(e);
        my_priority_queue.push(e);
    }

    //watch(10);         //nie działa :'(
    watch(a);
    watch(a[0]);
    watch(b);
    watch(c);
    watch(d);
    watch(xd);
    watch(two_d);
    watch(ala);
    debug {
        cout << "Looks like serious debugging is happening here!" << '\n';
    }
    watch(my_pair);
    watch(my_stack);
    watch(my_queue);
    watch(my_deque);
    watch(my_priority_queue);
    watch(null_pointer);
    watch(my_bitset);
}
