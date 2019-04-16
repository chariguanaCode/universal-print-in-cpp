#define DEBUG 1
#include <string>
#include <stack>
#include <vector>
#include <queue>
#include <tuple>
#include <iostream>
#include <ctime>
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

using namespace std;

//structure for each vertex
struct node {
    node * r = NULL;
    node * l = NULL;
    stack<vector<pair<string,queue<pair<int, string>>>>> val;
    void print_process(){
        cupl::print_process(r);   cout << " ";
        cupl::print_process(l);   cout << " ";
        cupl::print_process(val); cout << " ";
    }
};

//functions required for printing a binary tree (check out the tree example for more details)
bool   doesExist (node * x){ return x!=NULL; }

stack<vector<pair<string,queue<pair<int, string>>>>> value(node * x){ return x->val; }

node * rightChild(node * x){ return x->r; }

node * leftChild (node * x){ return x->l; }

//words by LegwanXDL
string words[11]={"love","u","guys","dance","dog","VS sucks","pls","hard","debugging","3301","Do not use VS"};

//a function randomly generating this very simple structure
void build(node * x, int level){
    if(level>0){
        if(rand()%10>3) {
            x->r = new node;
            build(x->r,level-1);
        }

        stack<vector<pair<string,queue<pair<int, string>>>>> my_stack;
        for (int k = 0; k < rand()%10; ++k) {
            vector<pair<string,queue<pair<int, string>>>> my_vector;
            for (int j = 0; j < rand()%5; ++j) {
                string my_string = words[rand()%11];
                queue<pair<int, string>> my_queue;
                for (int i = 0; i < rand()%10; ++i) {
                    string my_string2 = words[rand()%11];
                    pair<int, string> base = make_pair(rand()%1000,my_string2);
                    my_queue.push(base);
                }
                my_vector.push_back(make_pair(my_string,my_queue));
            }
            my_stack.push(my_vector);
        }

        x->val=my_stack;
        if(rand()%10>3) {
            x->l = new node;
            build(x->l,level-1);
        }
    }
}

int main(){
    //some randomness
    srand(time(NULL));

    //building
    node * root = new node;
    build(root,5);

    //and watching (details in the tree example)
    watch(root,1,root,doesExist,value,rightChild,leftChild);
}
