#include "header.h"
#define SA struct sockaddr
#include "file_ser.c"
#define lISTENQ 1024

//signal handler signal child
void sig_chld(int signo){
	pid_t pid;
	int stat;
	pid = wait(&stat);
	printf("\n Child %d terminated\n", pid);
}

//for error logs
void syserr(char* msg){
    perror(msg);
    exit(-1); 
}

//main function
int 
main(int argc, char **argv){
	//variables
	int listenfd, connfd, errno;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;
	//socket
	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(portno);
	//errno handler while binding
	errno = bind(listenfd, (SA*) &servaddr, sizeof(servaddr));

	printf("\n%d\n", errno);

	listen(listenfd, lISTENQ);
	//must cal signal handler for child process
	signal(SIGCHLD, sig_chld);

	for(;;){
		printf("Ready to recieve connections\n");
		clilen = sizeof(cliaddr);

		if((connfd = accept(listenfd, (SA*) &cliaddr, &clilen)) < 0){
			if(errno == EINTR)
				continue;
			else{
				fprintf(stderr, "accept error\n");
				exit(1);
			}
		}
		//forking
		if((childpid = fork()) == 0){
			fprintf(stderr, "%s Forking\n" );
			close(listenfd);
			file_ser(connfd);
			exit(0);
		}
		close(connfd);
	}
}