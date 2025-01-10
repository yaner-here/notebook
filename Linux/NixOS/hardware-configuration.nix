# Do not modify this file!  It was generated by ‘nixos-generate-config’
# and may be overwritten by future invocations.  Please make changes
# to /etc/nixos/configuration.nix instead.
{ config, lib, pkgs, modulesPath, ... }:

{
  imports = [ ];

  boot.initrd.availableKernelModules = [ "sd_mod" "sr_mod" "btrfs" "nvme" ];
  boot.initrd.kernelModules = [ "nvme" ];
  boot.kernelModules = [ "nvme" ];
  boot.extraModulePackages = [ ];

  fileSystems."/" =
    { device = "/dev/disk/by-uuid/7db0220a-c7af-4821-bda0-b5fc06eab352";
      fsType = "btrfs";
      options = [ "subvol=@" "compress=zstd:10" ];
    };

  fileSystems."/boot" =
    { device = "/dev/disk/by-uuid/9F2E-37D0";
      fsType = "vfat";
      options = [ "fmask=0077" "dmask=0077" ];
    };

  swapDevices =
    [ { device = "/dev/disk/by-uuid/b6cafc12-1e83-4b45-bda6-7c4deb721b76"; }
    ];

  # Enables DHCP on each ethernet and wireless interface. In case of scripted networking
  # (the default) this is the recommended approach. When using systemd-networkd it's
  # still possible to use this option, but it's recommended to use it in conjunction
  # with explicit per-interface declarations with `networking.interfaces.<interface>.useDHCP`.
  networking.useDHCP = lib.mkDefault true;
  # networking.interfaces.eth0.useDHCP = lib.mkDefault true;

  # >>> Customize: Hyper-V support
  nixpkgs.hostPlatform = lib.mkDefault "x86_64-linux";
  virtualisation.hypervGuest.enable = true;

  # >>> Customize: enable all hardware
  hardware.enableAllHardware = true;
}
