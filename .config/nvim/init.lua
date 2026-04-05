vim.o.expandtab = true
vim.o.tabstop = 4
vim.o.shiftwidth = 4

vim.o.autoindent = true
vim.o.smartindent = true
vim.o.number = true
vim.o.relativenumber = true

vim.o.mouse = "a"
vim.o.clipboard = "unnamed,unnamedplus"

vim.cmd("filet indent on")
vim.cmd("syn on")

vim.g.mapleader = " "

local cmd = "(trap 'rm -f a.out' INT && g++ -std=c++23 -O2 % && ./a.out; rm -f a.out)"

vim.keymap.set("n", "<leader>t", ":bel ter<CR>i", { noremap = true, silent = true })
vim.keymap.set("n", "<leader>r", ":w<CR>:bel ter " .. cmd .. "<CR>i", { noremap = true, silent = true })

vim.pack.add({ "https://github.com/ellisonleao/gruvbox.nvim" })

local res = {}
res.contrast = "soft"
if vim.g.neovide then
  res.transparent_mode = false
else
  res.transparent_mode = true
end

require("gruvbox").setup(res)

vim.cmd("colo gruvbox")

vim.pack.add({ "https://github.com/nvim-mini/mini.pairs" })

require("mini.pairs").setup()
