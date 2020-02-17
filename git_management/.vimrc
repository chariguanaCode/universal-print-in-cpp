
command MakeDebug   :w|!g++ -std=c++17 -DDEBUG -o %<.o % && echo -e "\e[1;33mCompilation successful\!\e[0m" && ./%:t:r.o;
command MakeRelease :w|!g++ -std=c++17 -O3 -static -o %<.o % && echo -e "\e[1;33mCompilation successful\!\e[0m" && ./%:t:r.o;
nnoremap <F4> :MakeDebug  <cr>
nnoremap <F8> :MakeRelease<cr>
