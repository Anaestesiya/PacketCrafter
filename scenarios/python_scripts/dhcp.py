#!/usr/bin/env python3

from scapy.all import *
from scapy.arch import get_if_hwaddr
import argparse

conf.checkIPaddr = False

def mac_to_bytes(mac_addr: str) -> bytes:
    """ Converts a MAC address string to bytes.
    """
    return int(mac_addr.replace(":", ""), 16).to_bytes(6, "big")

def get_mac_address(interface):
    try:
        mac_address = get_if_hwaddr(interface)
        return mac_address
    except Exception as e:
        print(f"Failed to retrieve MAC address for interface {interface}. Error: {str(e)}")
        return None

# configuration

parser = argparse.ArgumentParser()
parser.add_argument('--new_ip', help='Source IP address')
parser.add_argument('--iface', help='Network interface', required=True)
args = parser.parse_args()

new_ip = args.new_ip
localiface = args.iface

requestMAC = get_mac_address(localiface)

localmacraw=mac_to_bytes(requestMAC)
subprocess.run(["dhclient", "-r", localiface])

# craft DHCP DISCOVER
dhcp_discover = Ether(src=requestMAC,dst='ff:ff:ff:ff:ff:ff')/IP(src='0.0.0.0', dst='255.255.255.255')/UDP(dport=67, sport=68)/BOOTP(chaddr=localmacraw,xid=RandInt())/DHCP(options=[('message-type', 'discover'), 'end'])

# send discover, wait for reply
dhcp_offer = srp1(dhcp_discover, timeout=3, retry=1, iface=localiface)

offer_ip = dhcp_offer[BOOTP].yiaddr
server_ip = dhcp_offer[IP].src

print("DHCP Offer Received - IP:", offer_ip)
print("Send request:", new_ip)

request_packet = (
    Ether(dst="ff:ff:ff:ff:ff:ff", src=requestMAC) /
    IP(src="0.0.0.0", dst="255.255.255.255") /
    UDP(sport=68, dport=67) /
    BOOTP(chaddr=mac_to_bytes(requestMAC)) /
    DHCP(options=[("message-type", "request"), ("server_id", server_ip), ("requested_addr", new_ip), "end"])
)

dhcp_ack = srp1(request_packet,iface=localiface)

subprocess.run(["ip", "address", "add", new_ip + "/24", "dev", localiface])

