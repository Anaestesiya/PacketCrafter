from scapy.all import IP, UDP, DNS, DNSQR, sendp, sr1

iface="wlp1s0"

def send_dns_query(domain, dns_server):
    # Craft DNS query packet
    dns_query = IP(dst=dns_server) / UDP(sport=12345, dport=53) / DNS(qd=DNSQR(qname=domain))

    # Send the DNS query packet
    answer=sr1(dns_query, iface=iface)
    print(answer[DNS].summary())


# Specify the domain and DNS server
domain = "example.com"
dns_server = "8.8.8.8"  # Google Public DNS

# Send the DNS query
send_dns_query(domain, dns_server)

