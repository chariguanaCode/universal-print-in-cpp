
let &makeprg="echo -e \"\\\#define DEBUG 1\\n$(cat %)\"\\\|g++ -std=c++11 -o %<.o -xc++ -"
nnoremap <F4> :w<cr>:make<cr>
nnoremap <F5> :!./%:t:r.o<cr>
