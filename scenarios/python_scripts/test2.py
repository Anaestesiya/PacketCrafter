#!/usr/bin/env python3

from scapy.all import *

localiface = "wlp1s0"
conf.checkIPaddr = False
def mac_to_bytes(mac_addr: str) -> bytes:
    return int(mac_addr.replace(":", ""), 16).to_bytes(6, "big")

requestMAC="30:24:32:53:eb:43"
localmacraw=mac_to_bytes(requestMAC)
new_ip="192.168.31.11"

#dhcp_discover = Ether(src=requestMAC, dst='ff:ff:ff:ff:ff:ff')/IP(src='0.0.0.0', dst='255.255.255.255')/UDP(dport=67, sport=68)/BOOTP(chaddr=localmacraw,xid=RandInt())/DHCP(options=[('message-type', 'discover'), 'end'])

# send discover, wait for reply

dhcp_discover = Ether(dst='ff:ff:ff:ff:ff:ff', src=requestMAC, type=0x0800) / IP(src='0.0.0.0', dst='255.255.255.255') / UDP(dport=67,sport=68) / BOOTP(op=1, chaddr=localmacraw) / DHCP(options=[('message-type','discover'), ('end')])

dhcp_offer = srp1(dhcp_discover,iface=localiface)
if DHCP in dhcp_offer and dhcp_offer[DHCP].options[0][1] == 2:
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

