void 
file_cli(int sockfd){
	//variables
	ssize_t len;
	int n, fileSize;
	char buffer[LENGTH];
 	char fileSizeBuffer[LENGTH];
  	//for directory accessing
  	DIR *dir;
  	struct dirent *directory;
  	dir = opendir("./folder-local");
	//loop 
	do{
	   printf("\n[CLIENT] Hello user, enter the message or command you want : ");
	   //gets user entered info
	   fgets(buffer, LENGTH - 1, stdin);
	   n = strlen(buffer);//length of buffer
	   if(n > 0 && buffer[n-1] == '\n') //line break
		  buffer[n-1] = '\0';
		//send
	   n = send(sockfd, buffer, strlen(buffer), 0);
	   printf("[CLIENT] has sent the command/message!%s\n", buffer);
	  	
	   if(n < 0) //couldn't send
		 syserr("****[CLIENT] The message/command can't be send to server****");
	
	  //user calls download
	  if(buffer[0] == 'f' && buffer[1] == 'g' && buffer[2] == 'e' && buffer[3] == 't' && buffer[4] == 's' && buffer[5] == ' ') {
		  printf("****[CLIENT] has requested a download of file from server****\n");
		 //we try to get filename 
		  char fileName[LENGTH];
		  memset(&fileName, 0, sizeof(fileName));
		  int j = 0, i;
		  for(i = 6; i <= strlen(buffer); i++){
			  fileName[j] = buffer[i];
			  j++;
		  }
		  //get file size:
		  recv(sockfd, buffer, sizeof(buffer), 0);
		  fileSize = atoi(buffer);
		  //send size back as ACK:
		  send(sockfd, buffer, sizeof(buffer), 0);
		  //print file name and size:
		  printf("[CLIENT] The File name and size is : '%s' (%d bytes)\n",fileName, fileSize);
		  //receive data:
		  memset(&buffer, 0, sizeof(buffer));
		  int remainingData = 0;
		  //directory accessing
		  char path[LENGTH] = "./folder-local/";
		  strcat(path, fileName); //strcats file path
		  printf("path: %s", path);//print the path
		  FILE* fp;
		  fp = fopen(path, "wb");
		  //overwrite if existing, create if not
		  remainingData = fileSize;

		  printf("The data remaining is : %d", remainingData);
		  //while loop untill data remainining uis zero while transfer process
		  while(remainingData != 0) {
			  if(remainingData < LENGTH){
				  len = recv(sockfd, buffer, remainingData, 0);
				  fwrite(buffer, sizeof(char), len, fp);
				  remainingData -= len;
				  printf("[CLIENT] has received %lu bytes, expecting %d bytes\n", len, remainingData);
				  break;
			  }else{
			  	len = recv(sockfd, buffer, LENGTH, 0); //256
			  	fwrite(buffer, sizeof(char), len, fp);
		      	remainingData -= len;
			  	printf("Received %lu bytes, expecting: %d bytes\n", len, remainingData);
			  }
		  }
		  fclose(fp);
		  n = recv(sockfd, buffer, LENGTH, 0); //receive bizarre lingering packet.
		  //clean buffer
		  memset(&buffer, 0, sizeof(buffer));
	  }
      //send file to server! (upload)
	  else if(buffer[0] == 'f' && buffer[1] == 'p' && buffer[2] == 'u' && buffer[3] == 't' && buffer[4] == 's' && buffer[5] == ' '){
		  printf("*****[Client] has requested an upload of file to server******\n");
                  //we wait for the server's ACK
	      n = recv(sockfd, buffer, sizeof(buffer), 0);
		  int j = 0, i;
		  for(i = 6; i <= strlen(buffer); i++){
			  buffer[j] = buffer[i];
			  j++;
		  }
		  char address[LENGTH] = "./folder-local/";
		  strcat(address, buffer); //get file path
		  //open file path
          FILE* fp;
		  fp = fopen(address, "rb"); //filename, read bytes
		  if(fp == NULL)
			  printf("error opening file in: %s\n", buffer);
		  printf("File opened successfully!\n");
		  int file_size = 0;
		  if(fseek(fp, 0, SEEK_END) != 0)
			printf("Error determining file size\n");
		  file_size = ftell(fp);//file size
		  rewind(fp);//go back again 
		  printf("File size: %lu bytes\n", file_size);
		  //clen buffer
		  memset(&fileSizeBuffer, 0, sizeof(fileSizeBuffer));
		  sprintf(fileSizeBuffer, "%d", file_size);
		  //send
		  n = send(sockfd, fileSizeBuffer, sizeof(fileSizeBuffer), 0);
		  if(n < 0)
			  printf("Error sending file size information\n"); 
          n = recv(sockfd, fileSizeBuffer, sizeof(fileSizeBuffer), 0);
          
		  char byteArray[LENGTH];
          memset(&byteArray, 0, sizeof(byteArray));
          int buffRead = 0;
          int bytesRemaining = file_size;
          while(bytesRemaining != 0){
               	if(bytesRemaining < LENGTH){
            	buffRead = fread(byteArray, 1, bytesRemaining, fp);
                bytesRemaining = bytesRemaining - buffRead;
            	n = send(sockfd, byteArray, LENGTH, 0);
                if(n < 0)
                	printf("Error sending data chunks\n");
                    printf("The sent %d chunks of data is \n", buffRead);
           }else{
            	buffRead = fread(byteArray, 1, LENGTH, fp);
            	bytesRemaining = bytesRemaining - buffRead;
            	n = send(sockfd, byteArray, LENGTH, 0);
            	if(n < 0)
                  printf("Error sending data chunks\n");
                	printf("The sent %d chunks of data is \n", buffRead);
                }
           }
    	   printf("The File is successfully sent!\n");
           memset(&buffer, 0, sizeof(buffer));
    	   memset(&byteArray, 0, sizeof(byteArray));
	  }else if(strcmp(buffer, "ls-client") == 0){
		  memset(&buffer, 0, sizeof(buffer));
		  printf("Running ls-client command:");
		  if(dir){
		  	while((directory = readdir(dir)) != NULL){
				if(strcmp(directory->d_name, ".") == 0 || strcmp(directory->d_name, "..") == 0){
					//do nothing
				}else	
					printf("\n%s", directory->d_name);
			}
			printf("\n");
		  	//rewind
		  	rewinddir(dir);
		  }else
			  printf("could not open directory");
		  n = recv(sockfd, buffer, sizeof(buffer), 0);
		  if(n < 0) //couldn't receive
			  syserr("can't receive from server");
		  //clean buffer
		  memset(&buffer, 0, sizeof(buffer));
	  }
	  else if(strcmp(buffer, "ls-server") == 0){
		 n = recv(sockfd, buffer, sizeof(buffer), 0);
		 if(n < 0) //couldn't receive
			 syserr("can't receive from server");
		 printf("running ls-server command: %s\n", buffer);
		 //clean buffer
		 memset(&buffer, 0, sizeof(buffer));
	  }
	  //user exits
	  else if(strcmp(buffer, "exit") == 0){
		  break;
	  }
	  else{
	  //if client sends a regualr message

		  n = recv(sockfd, buffer, sizeof(buffer), 0);
  		  if(n < 0) //unable to receive 
			  syserr("can't receive from server"); 
		  else
			  buffer[n] = '\0';
	  		  printf("[Client] has  message: %s\n", buffer);
		  		  //clean buffer
		  memset(&buffer, 0, sizeof(buffer));
	  }
	  //clean buffer here maybe
	  memset(&buffer, 0, sizeof(buffer));
  } while(strcmp(buffer, "exit") != 0);
  close(sockfd);
}