#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_socklen_t.h>
#include <sys/socket.h>

void log_client_conect(struct sockaddr *client_addr) {
  char address[INET6_ADDRSTRLEN];

  if (client_addr->sa_family == AF_INET) {
    struct sockaddr_in *temp = (struct sockaddr_in *)client_addr;
    inet_ntop(AF_INET, &temp->sin_addr, address, sizeof(address));
  } else {

    struct sockaddr_in6 *temp = (struct sockaddr_in6 *)client_addr;
    inet_ntop(AF_INET6, &temp->sin6_addr, address, sizeof(address));
  }

  printf("New client connected IP: %s\n", address);
}

int main() {

  struct addrinfo hints;
  struct addrinfo *result;
  struct sockaddr_storage
      client_addr; // used to store accepted client's address info

  memset(&hints, 0, sizeof(hints)); // 0 out all the bytes of hints struct
  hints.ai_family =
      AF_UNSPEC; // UNSPEC will allow to get all ipv4 and ipv6 ip's
  hints.ai_socktype =
      SOCK_STREAM; // SOCK_STREAM provides reliable ordered connection
  hints.ai_flags = AI_PASSIVE; // AI_PASSIVE flag is used to indicate that the
                               // socket will be used for listening
  int res = getaddrinfo(NULL, "8088", &hints, &result);

  if (res != 0)
    perror("unsbale to get address info");

  int sd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

  if (sd < 0) {
    perror("socket creation falied");
  }

  int br = bind(sd, result->ai_addr, result->ai_addrlen);

  if (br < 0) {
    perror("error on port binding");
    exit(1);
  }

  int lr = listen(sd, 10); // the second int is the backlog value amount of
                           // connection req os will queue for us

  if (lr < 0) {
    perror("error in listen call");
  } else {
    printf("started listening for conections\n");
  }
  socklen_t client_addr_len = sizeof(client_addr);
  int client_fd = accept(sd, (struct sockaddr *)&client_addr, &client_addr_len);

  if (client_fd < 0) {
    perror("error accepting client conection");
  }
  log_client_conect((struct sockaddr *)&client_addr);
}