#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/if_packet.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>
#include <netinet/ether.h>


int main (void)
{
        int sock_fd;
        struct sockaddr_ll dest_addr;
        const char *iface_name = "eth0";
        size_t iface_name_len = strlen (iface_name);
        struct ifreq ifr;
        uint8_t dest_mac [] = {0xab, 0xcd, 0xef, 0x12, 0x34, 0x56};


        // get iface index
        memset (&ifr ,0 ,sizeof (struct ifreq));
        memcpy (ifr.ifr_name, iface_name, iface_name_len);

        ifr.ifr_ifindex = if_nametoindex (iface_name);

        
        // open l2 socket
        sock_fd = socket (AF_PACKET, SOCK_DGRAM, 0);
        /* sock_fd = socket (AF_PACKET, SOCK_DGRAM, IPPROTO_ETHERNET); */
        if (sock_fd < 0)
                printf ("socket creation error: %s\n", strerror (errno));


        // payload
        uint8_t buffer[] = {'j', 'a', 'm', 'e', 's', 0x0};


        // setting destination
        dest_addr.sll_ifindex = ifr.ifr_ifindex;
        dest_addr.sll_halen = ETH_ALEN;
        dest_addr.sll_protocol = 0x1020;
        memcpy(dest_addr.sll_addr, dest_mac, ETH_ALEN);


        // sending
        int ret = sendto(sock_fd, buffer, 6, 0,
                        (struct sockaddr*)&dest_addr,
                        sizeof(struct sockaddr_ll));
        if (ret < 0)
                printf("Send failed(%d): %s\n", ret, strerror (errno));

        close (sock_fd);
        return 0;
}
