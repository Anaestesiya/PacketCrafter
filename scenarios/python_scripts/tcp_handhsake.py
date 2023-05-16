from scapy.all import IP, TCP, sr, sr1, send
import sys

# Read source and destination IP addresses and port numbers from script arguments
src_ip = sys.argv[1]
dst_ip = sys.argv[2]
src_port = int(sys.argv[3])
dst_port = int(sys.argv[4])
iface = sys.argv[5]  # Interface name

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

