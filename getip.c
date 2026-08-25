#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <unistd.h>

void getReadableIp(char buf[], size_t buff_size, struct addrinfo *result) {

  if (result->ai_family == AF_INET) {
    struct sockaddr_in *s = (struct sockaddr_in *)result->ai_addr;
    inet_ntop(AF_INET, &s->sin_addr, buf, buff_size);
  } else {
    struct sockaddr_in6 *s = (struct sockaddr_in6 *)result->ai_addr;
    inet_ntop(AF_INET6, result->ai_addr, buf, buff_size);
  }
}

int main(int argc, char **argv) {

  char *domain = argv[1];

  struct addrinfo hints;
  struct addrinfo *result;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  int res = getaddrinfo(domain, "https", &hints, &result);

  if (res != 0) {
    perror("error in finding site");
  }
  struct addrinfo *temp = result;

  while (temp != NULL) {
    char address[INET6_ADDRSTRLEN];
    getReadableIp(address, sizeof(address), result);
    printf("Ip is: %s\n", address);
    printf("type is: %d\n", temp->ai_socktype);
    printf("Family type: %d\n", temp->ai_family);
    temp = temp->ai_next;
  }

  freeaddrinfo(result);
}