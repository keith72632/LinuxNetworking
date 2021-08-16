#include "utils.h"
#include "colors.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <netdb.h>

void perror_die(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void report_peer_connected(const struct sockaddr_in* sa, socklen_t salen)
{
	char hostbuf[NI_MAXHOST];
	char portbuf[NI_MAXSERV];

	if(getnameinfo((struct sockaddr*)sa, salen, hostbuf, NI_MAXHOST, portbuf, 
		NI_MAXSERV, 0) == 0)
	{
		printf("[%s OK %s] peer (%s, %s) connected\n", KGRN, KNRM, hostbuf, portbuf);
	} else {
		printf("[%s X %s] peer (unknown) connected\n", KRED, KNRM);
	}
}
int listen_inet_socket(int portnum)
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd < 0)
	{
		perror_die("Error opening socket\n");
	}
	printf("[%s OK %s] Socket Created\n", KGRN, KNRM);

	//This helps spurious EADDRINUSE when the previous instance of this server died
	int opt = 1;

	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		perror_die("setsockopt");
	}
	printf("[%s OK %s] Socket OPT Complete\n", KGRN, KNRM);

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portnum);

    if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror_die("ERROR on binding");
    }

	printf("[%s OK %s] Socket bound to port %d\n", KGRN, KNRM, portnum);

	if(listen(sockfd, 3) < 0)
	{
		perror_die("ERROR on listen");
	}
	printf("[%s OK %s] listening on port %d\n", KGRN, KNRM, portnum);


	return sockfd;
}


