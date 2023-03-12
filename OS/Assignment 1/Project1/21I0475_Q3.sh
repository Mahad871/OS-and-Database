#!/bin/bash
#LAB2
clear

echo "I21-0475-Mahad"

create_user(){
echo "Creating User"
sudo useradd -s /bin/bash -d /home/OS1/ -m -G sudo OS_Assignment_1
sudo passwd OS_Assignment_1

echo "User created Successfully and Admin permissions are granted"
}

installed_programs(){
echo "List of all the installed programs on this Device"
apt list --installed

}

set_ip(){

echo "Setting ip"
sudo ip addr add 10.0.0.1/24 dev lo
sudo ip route add default via 10.0.0.254
sudo sed -i 's/nameserver.*/nameserver 8.8.8.8/' /etc/resolv.conf
echo "Network preferences updated"
}

install_dropbox(){

    sudo wget https://www.dropbox.com/download?dl=packages/ubuntu/dropbox_2020.03.04_amd64.deb
    sudo dpkg -i dropbox_2020.03.04_amd64.deb
    sudo apt-get install -f

}

inst(){
    # add Dropbox repository key
        sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 1C61A2656FB57B7E4DE0F4C1FC918B335044912E
        # add Dropbox repository
        sudo add-apt-repository "deb [arch=amd64] https://linux.dropbox.com/ubuntu $(lsb_release -sc) main"
        # update apt-get
        sudo apt-get update

}

display_help() {
    echo "Usage: ./OS_Assignment_1.sh [OPTIONS]"
    echo "Options:"
    echo "  -uc    [Create a new user with administrator privileges]"
    echo "  -ld    [List all installed applications]"
    echo "  -ins   [Install Dropbox]"
    echo "  -ipcon [Set IP configuration]"
    echo "  -h     [Display this help message]"
}


while [ : ]; do
  case "$1" in
    -uc)
    	create_user
        ;;
    -id)
        installed_programs
        ;;
    -ins)
        install_dropbox
        break
        ;;
    -ipcon)
        set_ip
        ;;
    -h)  display_help
        ;;
     
  esac
  shift


done
