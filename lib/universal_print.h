#define debug if(1)
#define watch(x) debug {cout << __LINE__ << ": " << (#x) << " is " << (x) << endl ;}
#define watch_tab(x,n) debug {cout << __LINE__ << ": " << (#x) << " is "; \
    for(int very_long_index=0;very_long_index<n;very_long_index++){ cout << x[very_long_index] << ", ";}\
    cout << endl;}
