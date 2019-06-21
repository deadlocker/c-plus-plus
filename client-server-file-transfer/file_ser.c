void
file_ser(int sockfd){
    //variables
    int n;
    ssize_t len;
    int fp, fileSize;
    char buffer[LENGTH];
    char fileBuffer[LENGTH];
    char clAddr[INET6_ADDRSTRLEN]; // used to store ip address of the client
    //directory access
    DIR *dir;
    struct dirent *directory;
    dir = opendir("./folder-remote");
    //loop
    do{
    //clen buffer
        memset(&buffer, 0, sizeof(buffer));        
                //read client message:
        printf("New incoming connection, block on receive\n");
                      //we receive on specific socket:        
        n = recv(sockfd, buffer, sizeof(buffer), 0);
        if(n < 0)//if recieve is less than zero
            syserr("****[Server]can't receive from client****");
        else
            buffer[n] = '\0';
            printf("server got message: %s\n", buffer);
        if(strcmp(buffer, "exit") == 0){
        //send exit back to client
            send(sockfd, buffer, sizeof(buffer), 0);
            printf("Terminating the connection...\n");
            close(sockfd);
            exit(0);
        }else if(strcmp(buffer, "ls-server") == 0){
                //clean buffer with request
            memset(buffer, 0, sizeof(buffer));
            printf("These are the files at server:");
            if(dir){//look for directory
                while((directory = readdir(dir)) != NULL){
                    if(sizeof(buffer) == 0){
                        if(strcmp(directory->d_name, ".") == 0 || strcmp(directory->d_name, "..") == 0)
                        //do nothing and catch unnecessary info
                        	printf("");
                        else{
                            printf("\n%s", directory->d_name);
                            sprintf(buffer, "\n%s", directory->d_name);
                        }
                    }else//if buffer not full, pick up where we left off{
                        if(strcmp(directory->d_name, ".") == 0 || strcmp(directory->d_name, "..") == 0)
                        	//do nothing
                        	printf("");
                        else{
                            printf("\n%s", directory->d_name);
                            sprintf(buffer+strlen(buffer),"\n%s", directory->d_name);
                    }
                }
                printf("\n");
                            //we only send after we catch all files
                n = send(sockfd, buffer, sizeof(buffer), 0);
                            //rewind!
                rewinddir(dir);
            }else{
                //if unable to open directory
                    sprintf(buffer, "[SERVER] could not open directory");
                        //b = send(sockfd, buffer, sizeof(buffer), 0);
            }
        }else if(buffer[0] == 'f' && buffer[1] == 'g' && buffer[2] == 'e' && buffer[3] == 't'
                && buffer[4] == 's' && buffer[5] == ' '){
            //user wants to download file
            //send user file from server
                printf("Client  typed fgets command \n");
                //parse the string
                int j = 0, i;
                for(i = 6; i <= strlen(buffer); i++){
                    buffer[j] = buffer[i];
                    j++;
                }
                char address[LENGTH] = "./folder-remote/";
                strcat(address, buffer); //get file path
                FILE* fp;
                fp = fopen(address, "rb");
                if(fp == NULL)
                    printf("error opening file in: %s\n", buffer);
                    printf("File opened successfully!\n");
                    int file_size = 0;
                    //read the file and try to send bytes in the LENGTH size each time
                if(fseek(fp, 0, SEEK_END) != 0)
                    printf("Error determining file size\n");
                    file_size = ftell(fp);
                    rewind(fp);
                    printf("File size: %d bytes\n", file_size);
                    //clean buffer
                    memset(&fileBuffer, 0, sizeof(fileBuffer));
                    sprintf(fileBuffer, "%d", file_size);
                        //send file size:
                n = send(sockfd, fileBuffer, sizeof(fileBuffer), 0);
                if(n < 0) //n < 0
                    //acknowledge client and give time to clent to get file size
                    printf("Error sending file size.\n");

                n = recv(sockfd, fileBuffer, sizeof(fileBuffer), 0);
                if(n < 0)
                    printf("Error receiving handshake");
                //creat arry to sen data 
                char byteArray[LENGTH];
                memset(&byteArray, 0, sizeof(byteArray));
                int readBuffer = 0;
                int bytesLeft = file_size;
                    //while there are still bytes to be sent:
                while(bytesLeft != 0){
                    if(bytesLeft < LENGTH){
                        readBuffer = fread(byteArray, 1, bytesLeft, fp);
                        bytesLeft = bytesLeft - readBuffer;
                        n = send(sockfd, byteArray, LENGTH, 0);
                        if(n < 0)
                            printf("Error sending small data chunks\n");
                            printf("sent %d data chunks\n", readBuffer);
                    }else{
                        readBuffer = fread(byteArray, 1, LENGTH, fp);
                        bytesLeft = bytesLeft - readBuffer;
                        n = send(sockfd, byteArray, LENGTH, 0);
                        if(n < 0)
                            printf("Error sending data chunks\n");
                            printf("sent %d data chunks\n", readBuffer);
                    }
                }
                printf("File sent!\n");
                //end of file send job
                    //clean buffers
                memset(&buffer, 0, sizeof(buffer));
                memset(&byteArray, 0, sizeof(byteArray));
                //if client wants to upload the file
                //to the server we processs request
        }else if(buffer[0] == 'f' && buffer[1] == 'p' && buffer[2] == 'u' && buffer[3] == 't'
                && buffer[4] == 's' && buffer[5] ==' '){
                printf("User typed fputs command\n");

                n = send(sockfd, buffer, sizeof(buffer), 0);
                if(n < 0)
                   printf("Error sending file ACK\n");
                    //we receive on the fileBuffer
                memset(&fileBuffer, 0, sizeof(fileBuffer));
                n = recv(sockfd, fileBuffer, sizeof(fileBuffer), 0);
                if(n < 0)
                      printf("Error receiving file size\n");   
                    printf("size should be: %s\n", fileBuffer);
                n = send(sockfd, fileBuffer, sizeof(fileBuffer), 0);
                if(n < 0)
                   printf("Error sending ACK for file size\n");
                        //we catch the file name
                char fileName[LENGTH];
                memset(&fileName, 0, sizeof(fileName));
                        //parse
                int j = 0, i;
                for(i = 6; i <= strlen(buffer); i++){
                            //pass to name buffer
                    fileName[j] = buffer[i];
                    j++;
                }
                //get file size
                fileSize = atoi(fileBuffer);
                        //print file name and size:
                printf("File: '%s' (%d bytes)\n", fileName, fileSize);
                        //receive data
                memset(&buffer, 0, sizeof(buffer));
                int dataLeft = 0;
        
                char path[LENGTH] = "./folder-remote/";
                strcat(path, fileName);
                printf("path: %s\n", path);
                FILE* fileprocessor;
                fileprocessor = fopen(path, "wb"); //overwrite if existing
                        //create if not
                dataLeft = fileSize;
                //do untill all file uploaded
                while(dataLeft != 0){
                    if(dataLeft < LENGTH){
                        len = recv(sockfd, buffer, dataLeft, 0);
                        fwrite(buffer, sizeof(char), len, fileprocessor);
                        dataLeft -= len;
                        printf("Received %lu bytes, expecting %d bytes\n", len, dataLeft);
                        break;
                    }else{
                        len = recv(sockfd, buffer, 256, 0); //256
                        fwrite(buffer, sizeof(char), len, fileprocessor);
                        dataLeft -= len;
                           printf("Received %lu bytes, expecting: %d bytes\n", len, dataLeft);
                       }
                }
                //gets fil esuccessfully and now close it
                fclose(fileprocessor);
                n = recv(sockfd, buffer, LENGTH, 0); //receive bizarre lingering packet.
                memset(&buffer, 0 , sizeof(buffer));
        }else{    
            n = send(sockfd, buffer, sizeof(buffer), 0);
                    //b = recv(sockfd, buffer, sizeof(buffer), 0);
                                               //b = recv(sockfd, buffer, sizeof(buffer), 0);
            if(n < 0)
                syserr("can't send to server");
                printf("send message...%s\n", buffer);
            }//close switch
                    
                //clean buffer
        memset(&buffer, 0, sizeof(buffer));
    }while(strcmp(buffer, "exit") != 0); //close while loop here
}
