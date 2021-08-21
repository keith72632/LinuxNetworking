#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "utils.h"
#include "colors.h"

typedef enum { WAIT_FOR_MSG, IN_MSG } ProcessingState;

void serve_connection(int sockfd)
{
	if(send(sockfd, "*", 1, 0) < 1)
	{
		perror_die("send");
	}

    ProcessingState state = WAIT_FOR_MSG;

    while(1)
    {
        uint8_t buf[1024];
        int len = recv(sockfd, buf, sizeof(buf), 0);
        printf("Buf: %s\n", buf);
        memset(buf, 0, sizeof(buf));

        if(len < 0)
        {
            perror_die("recv");
        }
        else if(len == 0)
        {
            break;
        }

	    for(size_t i = 0; i < len; ++i)
	    {
		    switch(state)
		    {
                case WAIT_FOR_MSG:
                    if(buf[i] == '^')
                    {
                        state = IN_MSG;
                    }
                    break;
                case IN_MSG:
                    if(buf[i] == '$')
                    {
                        state = WAIT_FOR_MSG;
                    }
                    else
                    {
                        buf[i] += 1;
                        if(send(sockfd, &buf[i], 1, 0) < 1)
                        {
                            perror("send error");
                            close(sockfd);
                            return;
                        }
                    }
                    break;
            }   
	    }
        puts((char *)buf);
    }

    close(sockfd);
}

int main()
{
	int port = 9090;

	int sockfd = listen_inet_socket(port);

	while(1)
	{
		struct sockaddr_in peer_addr;
		socklen_t peer_addr_len = sizeof(peer_addr);

		int newsockfd =
			accept(sockfd, (struct sockaddr *)&peer_addr, &peer_addr_len);

		if(newsockfd < 0)
		{
			perror_die("ERROR on accept");
		}

		report_peer_connected(&peer_addr, peer_addr_len);
        serve_connection(newsockfd);
        printf("Peer finished\n");
	}

}
