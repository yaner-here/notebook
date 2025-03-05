{ config, lib, pkgs, ... }:
{
    options = { };
    config = {

        # environment.systemPackages = with pkgs; [
        #     (config.boot.kernelPackages.nvidiaPackages.beta)
        # ];

        systemd.timers."nvidia-power-limit-high" = {
            wantedBy = [ "timers.target" ];
            timerConfig = {
                Unit = "nvidia-power-limit-high.service";
                OnCalendar = "*-*-* 02:00:00";
            };
        };
        systemd.services."nvidia-power-limit-high" = {
            path = [ config.hardware.nvidia.package ];
            script = ''
                nvidia-smi -pl 280
            '';
            serviceConfig = {
                Type = "oneshot";
                User = "root";
            };
        };
        
        systemd.timers."nvidia-power-limit-low" = {
            wantedBy = [ "timers.target" ];
            timerConfig = {
                Unit = "nvidia-power-limit-low.service";
                OnCalendar = "*-*-* 06:15:00";
                Persistent = true;
            };
        };
        systemd.services."nvidia-power-limit-low" = {
            path = [ config.hardware.nvidia.package ];
            script = ''
                nvidia-smi -pl 120
            '';
            serviceConfig = {
                Type = "oneshot";
                User = "root";
            };
        };

    };
}
