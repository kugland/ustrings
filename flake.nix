{
  description = "ustrings - A UTF-8 aware version of the `strings` utility.";
  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  inputs.flake-parts.url = "github:hercules-ci/flake-parts";
  inputs.flake-compat.url = "https://flakehub.com/f/edolstra/flake-compat/1.tar.gz";

  outputs = inputs @ {
    nixpkgs,
    flake-parts,
    ...
  }:
    flake-parts.lib.mkFlake {inherit inputs;} {
      systems = [
        "i686-linux"
        "x86_64-linux"
        "aarch64-linux"
        "x86_64-darwin"
        "aarch64-darwin"
      ];
      perSystem = {
        pkgs,
        config,
        ...
      }: {
        packages = {
          ustrings = pkgs.callPackage ./package.nix {inherit pkgs;};
          default = config.packages.ustrings;
        };
        apps = {
          ustrings = {
            type = "app";
            program = "${config.packages.ustrings}/bin/ustrings";
          };
          default = config.apps.ustrings;
        };
      };
    };
}
