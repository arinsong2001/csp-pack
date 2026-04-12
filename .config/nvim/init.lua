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

vim.keymap.set("n", "<leader>t", ":bel ter<CR>i", { noremap = true, silent = true })

vim.keymap.set("n", "<leader>r", function()
  local ft = vim.bo.filetype

  local cmd
  if ft == "cpp" then
    cmd = "(trap 'rm -f a.out' INT && g++ -std=c++23 -O2 % && ./a.out; rm -f a.out)"
  elseif ft == "python" then
    cmd = "python3 %"
  else
    return
  end

  vim.cmd("w")
  vim.cmd("bel ter " .. cmd)
  vim.cmd("startinsert")
end, { noremap = true, silent = true })

if vim.g.vscode then
  local vscode = require("vscode")

  vim.defer_fn(function()
    vim.cmd("se rnu")
  end, 200)

  vim.keymap.set("n", "<leader>t", function()
    vscode.action("workbench.action.terminal.toggleTerminal")
  end, { noremap = true, silent = true })

  vim.keymap.set("n", "<leader>r", function()
    local ft = vim.bo.filetype
    local f= vim.fn.expand("%:p")

    local vcmd
    if ft == "cpp" then
      vcmd = "(trap 'rm -f a.out' INT && g++ -std=c++23 -O2 " .. f.. " && ./a.out; rm -f a.out)"
    elseif ft == "python" then
      vcmd = "python3 " .. f
    else
      return
    end

    vscode.action("workbench.action.files.save")
    vscode.action("workbench.action.terminal.focus")

    vim.defer_fn(function()
      vscode.action("workbench.action.terminal.sendSequence", { args = { text = vcmd .. "\r"} })
    end, 200)
  end, { noremap = true, silent = true })
end

if vim.g.neovide then
  vim.o.guifont = "Monaco:h15"
  vim.o.linespace = 5
end

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
