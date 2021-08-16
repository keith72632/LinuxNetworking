#include "utils.h"
#include "colors.h"

void serve_connection(int sockfd)
{
	if(send(sockfd, "*", 1, 0) < 1)
	{
		perror_die("send");
	}
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
	}

}
