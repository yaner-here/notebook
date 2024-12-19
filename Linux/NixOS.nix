# Edit this configuration file to define what should be installed on
# your system.  Help is available in the configuration.nix(5) man page
# and in the NixOS manual (accessible by running ‘nixos-help’).

{ config, pkgs, ... }:

{
	imports = [
	    ./hardware-configuration.nix
	];

	# Bootloader
	boot.loader.systemd-boot.enable = true;
	boot.loader.efi.canTouchEfiVariables = true;

	networking.hostName = "nixos"; # Define your hostname.
	# networking.wireless.enable = true;  # Enables wireless support via wpa_supplicant.

	# Configure network proxy if necessary
	# networking.proxy.default = "http://user:password@proxy:port/";
	# networking.proxy.noProxy = "127.0.0.1,localhost,internal.domain";

	networking.networkmanager.enable = true;
	time.timeZone = "Asia/Shanghai";
	i18n.defaultLocale = "zh_CN.UTF-8";
	i18n.extraLocaleSettings = {
	    LC_ADDRESS = "zh_CN.UTF-8";
	    LC_IDENTIFICATION = "zh_CN.UTF-8";
	    LC_MEASUREMENT = "zh_CN.UTF-8";
	    LC_MONETARY = "zh_CN.UTF-8";
	    LC_NAME = "zh_CN.UTF-8";
	    LC_NUMERIC = "zh_CN.UTF-8";
	    LC_PAPER = "zh_CN.UTF-8";
	    LC_TELEPHONE = "zh_CN.UTF-8";
	    LC_TIME = "zh_CN.UTF-8";
	};

	services.xserver.enable = true;
	services.xserver.displayManager.gdm.enable = true;
	services.xserver.desktopManager.gnome.enable = true;
	services.xserver.xkb = { layout = "cn"; variant = ""; };

	# >>> Customize: Support Hyper-V to avoiding "no screens found" error of X11 <<<
	services.xserver.displayManager.gdm.wayland = true;
	services.xserver.modules = [ pkgs.xorg.xf86videofbdev ];
	services.xserver.videoDrivers = [ "hyperv_fb" ];
	users.users.gdm = { extraGroups = [ "video" ]; }; # Also ensure that all users are added to user group "video"!

	# Enable CUPS to print documents.
	services.printing.enable = true;

	# Enable sound with pipewire.
	hardware.pulseaudio.enable = false;
	security.rtkit.enable = true;
	services.pipewire = {
	    enable = true;
	    alsa.enable = true;
	    alsa.support32Bit = true;
	    pulse.enable = true;
		# If you want to use JACK applications, uncomment this
	    #jack.enable = true;

		# use the example session manager (no others are packaged yet so this is enabled by default,
	    # no need to redefine it in your config for now)
	    #media-session.enable = true;
	};

	# Enable touchpad support (enabled default in most desktopManager).
	# services.xserver.libinput.enable = true;

	# Define a user account. Don't forget to set a password with ‘passwd’.
	users.users.yaner = {
	    isNormalUser = true;
	    description = "Yaner";
	    extraGroups = [ "networkmanager" "wheel" "video" ];
	    packages = with pkgs; [
		    #  thunderbird
	    ];
	};

	# Allow unfree packages
	nixpkgs.config.allowUnfree = true;

    # Shell
    programs.zsh.enable = true;
    programs.fish.enable = true;
    programs.fish.vendor.config.enable = true;
    users.defaultUserShell = pkgs.fish;
    environment.shellAliases = {
        cp = "cp -i"; # 文件名重复时需手动确认
        mv = "mv -i"; # 文件名重复时需手动确认
        mkdir = "mkdir -p"; # 目录路径不存在时自动创建
    };

    # NixOS Package Manager Mirror Source
    nix.settings.substituters = [ "https://mirrors.tuna.tsinghua.edu.cn/nix-channels/store" ];

    # Disable IPv6
    # boot.kernel.sysctl."new.ipv6.conf.eth0.disable_ipv6" = true;

    # System
    system.autoUpgrade.enable = true;
    system.autoUpgrade.allowReboot = false;
    system.autoUpgrade.channel = "https://nixos.org/channels/nixos-24.11";

    # Neovim
    programs.neovim = {
        enable = true;
        defaultEditor = true;
        configure = {
            customRC = ''
                set tabstop=4
                set shiftwidth=4
                set smartindent
                set expandtab
                set autoindent
            '';
        };
        viAlias = true;
        vimAlias = true;
    };

    # npm
    programs.npm = {
        enable = true;
        npmrc = ''
            color=true
        '';
    };

    # Atuin
    services.atuin = { enable = true; };

    # Atd
    services.atd = { enable = true; };

    # Cron
    services.cron = {
        enable = true;
        mailto = "";
        cronFiles = [];
        systemCronJobs = [];
    };

    # Clash Verge
    programs.clash-verge = { package = pkgs.clash-verge-rev; enable = true; tunMode = false; autoStart = true; };

	# Firefox
	programs.firefox.enable = true;

    # Git
    programs.git = {
        enable = true;
        prompt.enable = true;
        lfs.enable = true;
        config = {
            aliases = {
                undo = "reset --soft HEAD^";
                cancel = "reset --hard HEAD^";
                append = "commit -a --amend --no-edit";
            };
            user = {
                email = "1468275133@qq.com";
                name = "yaner-here";
            };
        };
    };

    # Java(OpenJDK)
    programs.java = { enable = true; };

	environment.systemPackages = with pkgs; [
        pkgs.stdenv
        pkgs.git-credential-oauth pkgs.gh # Git
        pkgs.docker pkgs.lazydocker # Docker
        pkgs.tree
        pkgs.busybox
        pkgs.btrfs-progs
        pkgs.dutree
        pkgs.lsd pkgs.eza # ls
        pkgs.fd
        pkgs.xh
        pkgs.fastfetch
        pkgs.cmd-wrapped
        pkgs.yazi
        pkgs.btop pkgs.htop # top
        pkgs.apacheHttpd pkgs.nginx # Web Server
        pkgs.php84 pkgs.php84Packages.composer # PHP
        pkgs.sqlite pkgs.datasette # Database
        pkgs.zip  pkgs.p7zip # Compression
        pkgs.gcc pkgs.gnumake pkgs.cmake # C/C++ Compilier
        pkgs.python3 pkgs.conda # Python
        pkgs.gedit pkgs.neovide # GUI Editor
        pkgs.nodejs pkgs.yarn pkgs.pnpm pkgs.bun
        pkgs.tmux pkgs.waveterm # Shell Emulator
	    pkgs.rustc pkgs.cargo # Rust
        pkgs.antigen # zsh
        # pkgs.vscode pkgs.obsidian
	];

	# Some programs need SUID wrappers, can be configured further or are
	# started in user sessions.
	# programs.mtr.enable = true;
	# programs.gnupg.agent = {
	#   enable = true;
	#   enableSSHSupport = true;
	# };

	# List services that you want to enable:
	
	# Enable the OpenSSH daemon.
	# services.openssh.enable = true;
	
	# Open ports in the firewall.
	# networking.firewall.allowedTCPPorts = [ ... ];
	# networking.firewall.allowedUDPPorts = [ ... ];
	# Or disable the firewall altogether.
	# networking.firewall.enable = false;

	# This value determines the NixOS release from which the default
	# settings for stateful data, like file locations and database versions
	# on your system were taken. It‘s perfectly fine and recommended to leave
	# this value at the release version of the first install of this system.
	# Before changing this value read the documentation for this option
	# (e.g. man configuration.nix or on https://nixos.org/nixos/options.html).
	system.stateVersion = "24.11"; # Did you read the comment?
}
