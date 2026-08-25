#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

int main() {

  struct addrinfo hints;
  struct addrinfo *result;

  memset(&hints, 0, sizeof(hints)); // 0 out all the bytes of hints struct
  hints.ai_family =
      AF_UNSPEC; // UNSPEC will allow to get all ipv4 and ipv6 ip's
  hints.ai_socktype =
      SOCK_STREAM; // SOCK_STREAM provides reliable ordered connection
  hints.ai_flags = AI_PASSIVE; // AI_PASSIVE flag is used to indicate that the

  int res = getaddrinfo(NULL, "8088", &hints, &result);

  if (res != 0)
    perror("unsbale to get address info");

  int sd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

  if (sd < 0) {
    perror("socket creation falied");
  }

  int cr = connect(sd, result->ai_addr, result->ai_addrlen);

  if (cr < 0) {
    perror("error on connecting");
  }
}