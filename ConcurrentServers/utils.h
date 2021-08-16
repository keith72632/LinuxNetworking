#ifndef UTILS_H
#define UTILS_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>


int listen_inet_socket(int portnum);
void perror_die(char *msg);
void report_peer_connected(const struct sockaddr_in* sa, socklen_t salen);

#endif
