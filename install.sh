#!/usr/bin/env bash

cd && mkdir -p ~/.local

arch="$(uname -m)"
if test "$arch" = "aarch64"; then arch="arm64"; fi

curl -L "https://github.com/neovim/neovim/releases/download/v0.12.0/nvim-linux-$arch.tar.gz" -o nvim.tar.gz
tar xzf nvim.tar.gz -C ~/.local

target=~/.local/nvim-linux-$arch/bin/nvim

sudo rm -f /usr/local/bin/nvim *.gz
sudo ln -s "$target" /usr/local/bin/nvim
