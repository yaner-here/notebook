{
    description = "Yaner's NixOS flake";
    inputs = {
        nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
        #nixpkgs.url = "github:NixOS/nixpkgs/master";

        nvf.url = "github:notashelf/nvf";
    };

    outputs = { self, nixpkgs, nvf, ... }: let
        system = "x86_64-linux";
        pkgs = import nixpkgs {
            inherit system;
            config = {
                allowUnfree = true;
            };
        };
    in {
        nixosConfigurations.nixos = nixpkgs.lib.nixosSystem { # Hostname: nixos
            modules = [
                nvf.nixosModules.default

                ./configuration.nix
                ./modules
            ];
        };
    };
}
