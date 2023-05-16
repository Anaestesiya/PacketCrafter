from scapy.all import IP, TCP, sr, sr1, send
import sys
import argparse
from scapy.all import get_if_addr

def get_interface_ip(interface):
    try:
        ip_address = get_if_addr(interface)
        return ip_address
    except:
        return None

# Parse command-line arguments
parser = argparse.ArgumentParser()
parser.add_argument('--src_ip', help='Source IP address')
parser.add_argument('--dst_ip', help='Destination IP address', required=True)
parser.add_argument('--src_port', type=int, help='Source port',required=True)
parser.add_argument('--dst_port', type=int, help='Destination port', required=True)
parser.add_argument('--iface', help='Network interface')
args = parser.parse_args()

# Get source IP address from interface if not provided
if args.iface and not args.src_ip:
    args.src_ip = get_interface_ip(args.iface)

src_ip = args.src_ip
dst_ip = args.dst_ip
src_port = args.src_port
dst_port = args.dst_port
iface = args.iface

# Create SYN packet (Step 1: Send SYN)
syn_packet = IP(src=src_ip, dst=dst_ip) / TCP(sport=src_port, dport=dst_port, flags="S")

# Send SYN packet and receive response packets
syn_ack_packets, _ = sr(syn_packet, timeout=3, retry=3, iface=iface)

# Check if SYN+ACK is received
if syn_ack_packets:
    # Extract the first SYN+ACK packet from the response
    syn_ack_packet = syn_ack_packets[0][1]

    if syn_ack_packet.haslayer(TCP) and syn_ack_packet[TCP].flags == "SA":
        print("SYN+ACK received")

        # Create ACK packet (Step 2: Send ACK)
        ack_packet = IP(src=src_ip, dst=dst_ip) / TCP(sport=src_port, dport=dst_port, flags="A",
                                                      ack=syn_ack_packet[TCP].seq + 1)

        # Send ACK packet
        send(ack_packet, iface=iface)
        print("ACK sent")
    else:
        print("SYN+ACK not received")
else:
    print("No response to SYN packet")

