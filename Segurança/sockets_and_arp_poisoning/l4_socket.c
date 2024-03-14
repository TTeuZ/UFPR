#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/if_packet.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>
#include <netinet/ether.h>
#include <arpa/inet.h>



int main (void)
{
        int sock_fd;
        char *ip = "10.137.0.15";
        short port = 5555;

        // open l4 socket
        sock_fd = socket (AF_INET, SOCK_DGRAM, 0);
        if (sock_fd < 0)
                printf ("socket creation error: %s\n", strerror (errno));

        struct sockaddr_in sin;
        sin.sin_family = AF_INET;
        sin.sin_addr.s_addr = inet_addr(ip);
        sin.sin_port = htons (port);

        // payload
        uint8_t buffer[] = {'j', 'a', 'm', 'e', 's', 0x0};


        // sending
        int ret = sendto(sock_fd, buffer, 6, 0,
                        (struct sockaddr*)&sin,
                        sizeof(struct sockaddr_in));
        if (ret < 0)
                printf("Send failed(%d): %s\n", ret, strerror (errno));

        close (sock_fd);
        return 0;
}
