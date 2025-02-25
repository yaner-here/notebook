{ config, lib, pkgs, ... }:
{
    options = { };
    config = {

        programs.nvf = {
            enable = true;
            settings = {
                vim.viAlias = true;
                vim.vimAlias = true;
                vim.lsp = {
                    enable = true;
                };
                vim.theme = {
                    enable = true;
                    name = "catppuccin";
                    style = "mocha";
                    transparent = true;
                };
                vim.languages = {
                    enableLSP = true;
                    enableTreesitter = true;

                    clang.enable = true;
                    nix.enable = true;
                    go.enable = true;
                    python.enable = true;
                    rust.enable = true;
                };
                vim.options = {
                    tabstop = 4;
                    shiftwidth = 4;
                    autoindent = true;
                };
                vim.autocomplete = {
                    blink-cmp.enable = true;
                    enableSharedCmpSources = true;
                };
            };
        };

    };
}
