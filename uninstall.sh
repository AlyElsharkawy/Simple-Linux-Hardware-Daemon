sudo systemctl disable --now SLHD
sudo rm /etc/systemd/system/SLHD.service
sudo rm /usr/local/bin/SimpleHardwareDaemon
echo "SLHD has been succesfully uninstalled. Feel free to delete this folder."
