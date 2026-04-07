se et ts=4 sw=4
se ai si nu rnu

filet indent on
syn on

se mouse=a
se clipboard=unnamed,unnamedplus

let g:mapleader = " "

let s:cmd = "(trap 'rm -f a.out' INT && g++ -std=c++23 -O2 % && ./a.out; rm -f a.out)"

nn <C-t> :bel ter<CR>
nn <leader>t :bel ter<CR>
exe "nn <leader>r :w<CR>:!" . s:cmd . "<CR>"
