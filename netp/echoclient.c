/*
 * echoclient.c - An echo client
 * Protocol: TCP / HTTP
 *           TCP: For establishing a reliable connection between client and server
 *           Optionsally, HTTP: For transferring data between client and server
 *                              which uses HTTP to format the data being sent
 * HOW TO USE: ./echoclient <host> <port-number>
 */
/* $begin echoclientmain */
#include "csapp.h"

int main(int argc, char **argv) {
    
    int clientfd;
    char *host, *port, buf[MAXLINE];
    rio_t rio;

    if (argc != 3) {
	fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
	exit(0);
    }
    host = argv[1];
    port = argv[2];

    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);

    while (Fgets(buf, MAXLINE, stdin) != NULL) {
	Rio_writen(clientfd, buf, strlen(buf));
	Rio_readlineb(&rio, buf, MAXLINE);
	Fputs(buf, stdout);
    }
    Close(clientfd); //line:netp:echoclient:close
    exit(0);
}
/* $end echoclientmain */
