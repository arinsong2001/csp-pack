se et ts=4 sw=4
se ai si nu rnu

filet indent on
syn on

se mouse=a
se clipboard=unnamed,unnamedplus

let g:mapleader = " "

let s:rc = "(trap 'rm -f a.out' INT && g++ -std=c++23 -O2 % && ./a.out; rm -f a.out)"
let s:rp = "python3 %"

nn <leader>t :bel ter<CR>

nn <leader>r :w<CR>:call RunFile()<CR>

fun! RunFile()
    if &ft == 'cpp'
        exe "!" . s:rc
    else
        exe "!" . s:rp
    en
endf
