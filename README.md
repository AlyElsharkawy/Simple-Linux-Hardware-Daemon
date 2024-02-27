# Simple-Linux-Hardware-Daemon
This is a simple daemon that collects utilization information and sends it via email

## Features
- Customizable email send interval
- Customizable sender and reciever email
- Collects information about CPU utilization, load factor, disk usage, network usage, and memory utilization.

## Installation
This daemon has been tested extensively on Arch Linux, Fedora, and Ubuntu. The `install.sh` will install the daemon and automatically resolve dependencies during install. SLHD uses systemd to run in the background. Installation is a very simple 3 step process. The first step is cloning the repo, the second step is modifying the `userVariables.cpp` file in the `src` directory. Populate the files `SENDER_EMAIL`, `SENDER_PASSWORD`, `RECEPIENT_EMAIL`, and `TIMER_DELAY`. The First field is the email address that will be used to send the log file. The second field is the password of the email account used to send the log file. The third field is the email address that will recieve the log file. The fourth field is the delay in minutes that the demain will wait for before creating a new log file and sending it. The installation steps are listed below. Make sure all fields are populated before running `install.sh`

```bash
git clone xyz.com
cd ./Simple-Linux-Hardware-Daemon
sudo ./install.sh
```

## Important Notes
If you ever wish to uninstall the daemon, then simply run `uninstall.sh`. Also, if any changes are made in the source code or `userVariables.cpp`'s values are changed, then you must rerun `install.sh` in order for the changes to take effect.

## Issues
If you ever find an issue or have a suggestion, then please open an issue in the issues tab.
