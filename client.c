#include <stdio.h> // perror, printf
#include <stdlib.h> // exit, atoi
#include <unistd.h> // write, read, close
#include <arpa/inet.h> // sockaddr_in, AF_INET, SOCK_STREAM,
                       // INADDR_ANY, socket etc...
#include <string.h> // strlen, memset

const char message[] = "Hello sockets world\n";

int main(int argc, char const *argv[]) {

  int serverFd;
  struct sockaddr_in server;
  socklen_t len;
  int port = 1234;
  char const *server_ip = "192.168.1.105";
  char buffer[1024];
  *buffer = "hello server";
  if (argc == 3) {
    server_ip = argv[1];
    port = atoi(argv[2]);
  }
  serverFd = socket(AF_INET, SOCK_DGRAM, 0);
  if (serverFd < 0) {
    perror("Cannot create socket");
    exit(1);
  }
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(server_ip);
  server.sin_port = htons(port);
  len = sizeof(server);

  int n;
  sendto(serverFd,(const char*)"buenas tardes",strlen("buenas tardes"),MSG_CONFIRM,(const struct sockaddr*) &server,sizeof(server));
  printf("message sent\n");
  n = recvfrom(serverFd,(char*)buffer,1024,MSG_WAITALL,(struct sockaddr*)&server,&len);
  buffer[n] ='\0';
  printf("Server: %s\n",buffer);

  close(serverFd);
  return 0;
}
