#!/usr/bin/env bash

# envs
export EDITOR='vim'
export VISUAL='nvim'

# dir motion
alias l='ls --color'
alias la='l -a'
alias ll='l -lh'
alias lla='l -lah'

alias md='mkdir -p'

test "${BASH_VERSINFO[0]}" -ge 4 && shopt -s autocd

d() { cd $1 && l; }

# editors
alias v='vim'
alias n='nvim'

# coding
alias p='python3'

c() (
  trap 'rm -f a.out' INT
  g++ -std=c++23 -O2 "$1" && ./a.out
  ret=$?
  rm -f a.out
  return $ret
)

# others
alias e='echo'
alias g='git'
alias o='open'
alias s='o -a Safari'
alias x='chmod +x'

# theme and appearance
PROMPT_COMMAND='
exit_code="$?"
if ! (($exit_code)); then
  exit_code=""
else
  exit_code="C:$exit_code"
fi
'

PS1='
\[\e[1;34m\]# \
\[\e[1;33m\]\u \
\[\e[0m\]@ \
\[\e[1;32m\]\h \
\[\e[0m\]in \
\[\e[1;33m\]\w\[\e[0m\] \
[\t] \[\e[1;31m\]$exit_code\[\e[0m\]
\[\e[1;31m\]$\[\e[0m\] '
