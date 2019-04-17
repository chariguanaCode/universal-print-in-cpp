
command MakeDebug   :w|!echo -e "\#define DEBUG 1\n" | cat - % > debug.cpp && g++ -std=c++11 -o %<.o debug.cpp && echo -e "\e[1;33mCompilation successful\!\e[0m" && ./%:t:r.o;
command MakeRelease :w|!g++ -std=c++11 -O3 -static -o %<.o % && echo -e "\e[1;33mCompilation successful\!\e[0m" && ./%:t:r.o;
nnoremap <F4> :MakeDebug  <cr>
nnoremap <F8> :MakeRelease<cr>
