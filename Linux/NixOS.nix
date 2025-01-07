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

	# Network
	networking.hostName = "nixos";
	# networking.wireless.enable = true; # Conflict with networking.networkmanager.enable = true;
	# networking.proxy.default = "http://user:password@proxy:port/";
	# networking.proxy.noProxy = "127.0.0.1,localhost,internal.domain";
	networking.networkmanager.enable = true;
    
    # Storage
    services.btrfs = {
        autoScrub.enable = true;
        autoScrub.interval = "weekly";
    };
    # services.snapper = {
    #     snapshotRootOnBoot = true;
    #     snapshotInterval = "hourly";
    #     cleanupInterval = "1d";
    #     persistentTimer = true;
    #     configs.root = {
    #         SUBVOLUME = "/";
    #         ALLOW_USERS = [ "yaner" ];
    #         ALLOW_GROUPS = [ "root" ];
    #         TIMELINE_CREATE = true;
    #         TIMELINE_CLEANUP = true;
    #         TIMELINE_LIMIT_HOURLY = 1;
    #         TIMELINE_LIMIT_DAILY = 24;
    #         TIMELINE_LIMIT_WEEKLY = 1;
    #         TIMELINE_LIMIT_MONTHLY = 1;
    #         TIMELINE_LIMIT_YEARLY = 12;
    #     };
    # };

	# Font
	fonts = {
		enableDefaultPackages = true;
		fontDir = { enable = true; };
		packages = with pkgs; [
			noto-fonts noto-fonts-cjk-sans noto-fonts-cjk-serif noto-fonts-emoji-blob-bin
			nerd-fonts.caskaydia-cove
			cascadia-code sarasa-gothic
		];
		fontconfig = {
			defaultFonts = {
				monospace = [ "CascadiaCode" ];
			};
			useEmbeddedBitmaps = true;
		};
	};
	
	# Time and Locale
	time.timeZone = "Asia/Shanghai";
	i18n = {
		defaultLocale = "zh_CN.UTF-8";
		extraLocaleSettings = {
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
		inputMethod = {
			enable = true;
			type = "fcitx5";
			fcitx5.addons = with pkgs; [ 
				fcitx5-skk fcitx5-lua fcitx5-gtk fcitx5-skk
				librime fcitx5-rime rime-data
				fcitx5-fluent
				fcitx5-chinese-addons
				fcitx5-pinyin-zhwiki fcitx5-pinyin-moegirl fcitx5-pinyin-minecraft
				fcitx5-configtool
			];
			fcitx5.waylandFrontend = true;
		};
	};

	# Desktop Environment
	services.xserver.enable = true;
	services.xserver.displayManager.gdm.enable = true;
	services.xserver.desktopManager.gnome.enable = true;
	services.xserver.xkb = { layout = "cn"; variant = ""; };

        ## >>> Customize: Gnome tweaks
        services.gnome = {
            core-shell.enable = true;
            core-utilities.enable = true;
            glib-networking.enable = true;
            gnome-browser-connector.enable = true;
        };
        programs.gnome-terminal.enable = true;
        
        ## >>> Customize: Xrdp
        services.xrdp = {
            enable = true; audio.enable = true;
            port = 3389;
            defaultWindowManager = "gnome-session";
            openFirewall = true;
        };

		## >>> Customize: Support Hyper-V to avoiding "no screens found" error of X11 <<<
		# services.xserver.displayManager.gdm.wayland = true;
		services.xserver.modules = [ pkgs.xorg.xf86videofbdev pkgs.xorg.xsm ];
		services.xserver.videoDrivers = [ "hyperv_fb" "nvidia" "modesetting" "fbdev" ];
		users.users.gdm = { extraGroups = [ "video" ]; }; # Also ensure that all users are added to user group "video"!
        hardware.graphics.enable = true;
        hardware.nvidia.open = false;


		qt = {
			enable = true;
			style = "adwaita";
			platformTheme = "kde";
		};
		
		## Hyprland
		# programs.hyprland = {
		#	enable = true;
		#	withUWSM = true;
		#	xwayland.enable = true;
		#};

	# Enable CUPS to print documents.
	services.printing.enable = true;

	# Enable sound with pipewire.
	services.pulseaudio.enable = false;
	security.rtkit.enable = true;
	services.pipewire = {
	    enable = true;
	    alsa.enable = true;
	    alsa.support32Bit = true;
	    pulse.enable = true;
		# If you want to use JACK applications, uncomment this
	    #jack.enable = true;
	};

	# Enable touchpad support (enabled default in most desktopManager).
	# services.xserver.libinput.enable = true;

    services.flatpak.enable = true;

	# User
	users.users.yaner = {
	    isNormalUser = true;
	    description = "Yaner";
	    extraGroups = [ "networkmanager" "wheel" "video" ];
	    packages = with pkgs; [ ];
	};

	# Allow unfree packages
	nixpkgs.config.allowUnfree = true;

    # Shell
    programs.zsh.enable = true;
    programs.fish.enable = true;
    programs.fish.vendor.config.enable = true;
    programs.starship = { enable = true; };
    users.defaultUserShell = pkgs.fish;
    environment.shellAliases = {
    	ls = "lsd -laAhFg --total-size --inode --header --hyperlink always --date +'%Y-%m-%d %H:%M:%S'";
        cp = "cp -i";
        mv = "mv -i";
        mkdir = "mkdir -p";
        hexdump = "hexdump -CL";
        gpustat = "gpustat -cupF -P limit --watch 1";
        sqlite3 = "litecli --auto-vertical-output --table";
        nixbuild = "sudo nixos-rebuild switch --option substituters 'https://mirrors.tuna.tsinghua.edu.cn/nix-channels/store'";
    };

    # NixOS Package Manager Mirror Source
    # nix-channel --add https://nixos.org/channels/nixos-unstable nixos
    # nix-channel --add https://mirrors.tuna.tsinghua.edu.cn/nix-channels/nixos-unstable nixos
    nix.settings.substituters = [ "https://mirrors.tuna.tsinghua.edu.cn/nix-channels/store" ];

    # Disable IPv6
    # boot.kernel.sysctl."new.ipv6.conf.eth0.disable_ipv6" = true;

    # System
    system.autoUpgrade.enable = true;
    system.autoUpgrade.allowReboot = false;
    system.autoUpgrade.channel = "https://nixos.org/channels/nixos-24.11";

    services.n8n = {
        # enable = true;
        openFirewall = false;
        settings = {
            
        };
    };

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
            packages.myVimPackage = with pkgs.vimPlugins; {
                start = [ LazyVim ];
                opt = [];
            };
        };
        viAlias = true;
        vimAlias = true;
    };

    # npm
    programs.npm = {
        enable = true;
        npmrc = ''
            color=true
            http-proxy=${builtins.getEnv "HTTP_PROXY"}
            https-proxy=${builtins.getEnv "HTTPS_PROXY"}
        '';
    };

    # Apache
    services.httpd = {
        enable = false;
        group = "wwwrun";
        enablePHP = true; enablePerl = true;
        phpPackage = pkgs.php.buildEnv {
            extensions = ({ enabled, all }: enabled ++ (with all; [xdebug]));
            extraConfig = ''
            '';
        };
    };
    services.freshrss = {
        enable = true;
        language = "zh-cn";
        defaultUser = "yaner";
        passwordFile = "/run/secrets/freshrss";
        dataDir = "/var/lib/freshrss"; database.type = "sqlite";
        baseUrl = "http://yaner.com/";
        extensions = with pkgs.freshrss-extensions; [ 
            youtube title-wrap reddit-image reading-time 
        ];
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
    programs.clash-verge = { package = pkgs.clash-verge-rev; enable = true; autoStart = true; };

    # Docker
    virtualisation.docker = {
        enable = true;
        storageDriver = "btrfs";
        daemon.settings = {
            "default-address-pools" = [{ "base" = "172.27.0.0/16"; "size" = 24; }];
        };
        autoPrune = {
            enable = true;
            dates = "1d";
            flags = [ "--all" ];
        };
    };
    hardware.nvidia-container-toolkit.enable = true;

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

    # Tailscale
    services.tailscale = {
        enable = true;
        openFirewall = true;
    };

	environment.systemPackages = with pkgs; [
        stdenv
        bat # cat
        git-credential-oauth gh # Git
        docker lazydocker # Docker
        compsize
        tree dutree
        busybox
        btrfs-progs
        lsd eza # ls
        fd
        xh
        fastfetch
        cmd-wrapped
        yazi
        btop htop gpustat mission-center # top
        nginx # Web Server
        php phpPackages.composer # PHP
        sqlite litecli # Database
        zip  p7zip # Compression
        gcc gnumake cmake # C/C++ Compilier
        python3 conda # Python
        gedit neovide # GUI Editor
        nodejs_23 yarn pnpm bun
        tmux waveterm # Shell Emulator
	    rustc rustup cargo # Rust
        antigen # zsh
        vscode
		obsidian
        doggo # DNS
        clash-nyanpasu v2rayn
        gnome-tweaks gnome-shell gnome-shell-extensions dconf-editor gnome-power-manager
        indicator-application-gtk3 gnomeExtensions.just-perfection gnomeExtensions.dash-to-panel gnomeExtensions.hot-edge gnomeExtensions.appindicator
        cudatoolkit # CUDA
        nmap file tldr
        google-chrome
        flatpak-builder
        monolith
        vlc # Media Player
        mkcert # Cert
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
