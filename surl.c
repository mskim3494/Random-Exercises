/*
** surl.c: a simple URL grabber for cs154-2015 hw8
** based on http://beej.us/guide/bgnet/examples/client.c
** Compile with:

gcc -Wall -Werror -o surl surl.c

** and run with:

./surl

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFF_SIZE 200
int main() {
  int clientfd;
  struct addrinfo hints, *servinfo, *pp;
  int gairet;
  char *buff=NULL;
  ssize_t red, count;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  buff = malloc(BUFF_SIZE);

  /* vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv */
  /* edit the following two lines */
#define HOST "people.cs.uchicago.edu"
#define PORT "80"
  /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */

  if ((gairet = getaddrinfo(HOST, PORT, &hints, &servinfo))) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(gairet));
    return 1;
  }

  /* loop through all the results and connect to the first we can */
  for (pp = servinfo; pp != NULL; pp = pp->ai_next) {
    if (-1 == (clientfd = socket(pp->ai_family, pp->ai_socktype,
                                 pp->ai_protocol))) {
      perror("client: socket");
      continue;
    }
    if (-1 == connect(clientfd, pp->ai_addr, pp->ai_addrlen)) {
      close(clientfd);
      perror("client: connect");
      continue;
    }
    /* connect() worked, so no more looping through ai_next */
    break;
  }
  if (pp == NULL) {
    fprintf(stderr, "client: failed to connect\n");
    return 2;
  }
  freeaddrinfo(servinfo);

  /* vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv */
    memset(buff, '\0', BUFF_SIZE);
    snprintf(buff, BUFF_SIZE, "GET /~glk/154hw8/mskim3494.txt HTTP/1.1\r\nHost: \r\nConnection: close\r\n\r\n");
    
    red = send (clientfd, buff, BUFF_SIZE, 0);
    if (red==-1){
        perror("send\n");
        exit(1);
    }
    
    red = count = 0;

    while((count=recv(clientfd, buff, BUFF_SIZE, 0)) > 0){
        write(STDOUT_FILENO, buff, count);
    } if (count == -1){
        perror("recv\n");
        exit(1);
    } else if (count==0){
        close(clientfd);
    }     
  /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
    free(buff);
  exit(0);
}
