### Setting up the project: ###

//Go to the download or the directory where the program is downlaoded

Navigate into the folder: ~$ `cd project`

Compile the code with Makefile: `~$ make`
First, run the server in a terminal window,
`~$ ./server `
(The server will automatically run on its local loopback IP: 127.0.0.1 or localhost)
On another terminal window, pane, or tab, run the client: `~$ ./client localhost`

If the client connects successfully, it will prompt you for a message.
Here's a list with the possible commands:
- `ls-server` lists files available in the server (remotely)
- `ls-client` lists files available in the client (locally)
- `fgets filename.extension` to  download remote file to client
- `fputs filename.extension` to upload local file to server
- `exit` to  exit gracefully
- 
If you enter other than abouve command server will just acknowledge and echo the command
back to the client.

Client files are located in `./folder-local/`
Server files are located in `./folder-remote/` 

This Program should work in any Unix system

System Information in which program is written
Distributor ID:	    Kali
Description:	    Kali GNU/Linux Rolling
Release:        	kali-rolling
Codename:	        kali-rolling

To delete the compiled files just type `make clean` command
