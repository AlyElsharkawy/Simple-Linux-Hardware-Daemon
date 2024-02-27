#!/bin/bash
releaseFile=/etc/os-release

if [ $(id -u) != 0 ]
then
  echo "ERROR: This script must be run as root"
  exit 2
fi

echo "Installing Simple Linux Hardware Daemon..."

if grep -qi "arch" $releaseFile
then
  echo "System is Arch based and uses pacman!"
  sudo pacman -Qi vnstat &>/dev/null || sudo pacman -Sy --noconfirm vnstat
  sudo pacman -Qi cmake &>/dev/null || sudo pacman -Sy --noconfirm cmake
  sudo pacman -Qi curl &>/dev/null || sudo pacman -Sy --noconfirm curl
  sudo pacman -Qi gcc &>/dev/null || sudo pacman -Sy --noconfirm gcc
fi 

if grep -qi "ubuntu\|debian" $releaseFile
then
  echo "System is Ubuntu/Debian based and uses APT!"
  sudo apt update
  sudo apt install vnstat cmake curl libcurl4-openssl-dev build-essential -y
fi 

if grep -qi "fedora" $releaseFile
then
  echo "System is RPM based and uses dnf!"
  sudo dnf install vnstat cmake curl libcurl-devel gcc-c++ -y
fi

#vnstat (network monitor) is now enabled but it must be enabled as a background service
sudo systemctl enable --now vnstat

#We will now compile the program
echo "Compiling the daemon with user variables..."
mkdir ./build
cmake -S ./src -B ./build/
cd ./build/ && sudo make install && cd ..
sudo cp ./SLHD.service /etc/systemd/system/ 
sudo systemctl enable --now SLHD.service
sudo systemctl restart SLHD.service

echo "Thank you for installing the Simple Linux Hardware Daemon!"
