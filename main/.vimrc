command MakeDebug  :w|!echo -e "\#define DEBUG 1\\n$(cat %)">debug.cpp && g++ -std=c++11 -o %<.o debug.cpp && ./%:t:r.o
command MakeNormal :w|!g++ -std=c++11 -o %<.o % && ./%:t:r.o
nnoremap <F4> :MakeDebug <cr>
nnoremap <F8> :MakeNormal<cr>
