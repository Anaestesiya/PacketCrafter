#!/bin/bash

sudo apt-get install scapy
sudo apt-get install python3

mkdir /tmp/PacketCrafter
mkdir /tmp/PacketCrafter/scripts
mkdir /tmp/PacketCrafter/logs
sudo mkdir /etc/PacketCrafter
sudo mkdir 
sudo cp PacketCrafter /usr/sbin/
sudo cp PacketCrafter_uk_UA.qm /etc/PacketCrafter/
sudo chmod +x /usr/sbin/PacketCrafter

