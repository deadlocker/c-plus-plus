

#ifndef header_file
#define header_file

//libraries required for the file transfer client server program
#include <stdlib.h>			/* for convenience */
#include <stdio.h>			/* for convenience */
#include <time.h>			/* for convenience */
#include <errno.h>
#include <string.h>			/* for convenience */
#include <unistd.h>			/* for convenience */
#include <sys/socket.h> 	/* basic socket definitions */
#include <sys/time.h>		/* timeval{} for select() */
#include <netinet/in.h>		/* sockaddr_in{} and other Internet defns */
#include <sys/types.h> 		/* basic system data types */
#include <sys/un.h>			/* for Unix domain sockets */
#include <sys/uio.h>    
#include <signal.h>         /*signal handlers*/
#include <stdarg.h>     
#include <fcntl.h>          /*for file trannsfer functions*/
#include <dirent.h>
#include <sys/sendfile.h>
#define portno 5000
#define LENGTH 4096
#endif

