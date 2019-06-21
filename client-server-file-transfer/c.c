#include "header.h"
#include "file_cli.c"
#define SA struct sockaddr


//for error logs
void syserr(char* msg){
    perror(msg);
    exit(-1); 
}

//main function
int 
main(int argc, char **argv){
  //variables
  int sockfd;
  struct sockaddr_in servaddr;

  if(argc != 2){
    fprintf(stderr, "usage : tcpcli <IPaddress>");
    exit(1);
  }
  //create socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(portno);
  inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

  connect(sockfd, (SA*) &servaddr, sizeof(servaddr));
  //menu 
  printf("\n#################################################################\n");
  printf("\t\tWELCOME TO FILE TRANSFER PROGRAM\n");
  printf("\t\tDEVELOPER :\tRAJESH MANI POUDEL and PRAMOD POUDEL\n");
  printf("\t\tClass : Network Programming CS 3013\n");
  printf("\n#################################################################\n");
  printf("\tHere's a list with the possible commands \n");
  printf("- `~$ ls-server` lists files available in the server (remotely)\n");
  printf("- `~$ ls-client` lists files available in the client (locally)\n");
  printf("- `~$ fgets filename.extension` download remote file to client\n");
  printf("- `~$ fputs filename.extension` upload local file to server.\n");
  printf("- `~$ exit` exit gracefully\n");
  printf("- `~$ normal text input will be just echoed. This is for file transfer only\n");
  printf("\n#################################################################\n");
  //do it all// calls file_cli for file transfer
  file_cli(sockfd);
  exit(0);
}