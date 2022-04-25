#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char *argv[]) {

	int sockfd, newfd; // socekt file descriptor, new file descriptor
	socklen_t length;  // socket length (length of clinet address)
	struct sockaddr_in saddr, caddr; // server address, client address
	time_t itime; // time format

	if(argc != 2) {
		write(0, "Uporaba: TCPtimes vrata (vrata 0-1024 so rezervirana za jedro)\n\0", 25);
		exit(1);
	}
	
	// create socket
	if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
	}

	saddr.sin_family = AF_INET; // IPv4 
	saddr.sin_addr.s_addr = INADDR_ANY; // localhost
	saddr.sin_port = htons(atoi(argv[1])); // port converted from ascii to integer

        // binds the socket file description to the actual port (similar to open)
	if (bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
		perror("bind");
	}

	// start listening on the given port
	if(listen(sockfd, 0) < 0) {
		perror("listen");
	}
	

	length = sizeof(caddr); // length of client address

	int numbytes;
	char buf[5];

	while(1) {

		// accept new client (wait for him!)
		//perror("start waiting...");
		if((newfd = accept(sockfd, (struct sockaddr *)&caddr, &length)) < 0) {
			perror("accept");
		}	
		

		//prejemanje
		while(numbytes != 0) {
	
			// receive numbytes from server...
			if ((numbytes = recv(newfd, buf, 4, 0)) == -1) {
				perror("recv");
				exit(1);
			}
			
			buf[numbytes] = '\0'; // all strings in c ends with \0 (see strlen)
		}

		break;
	}

	printf("%d", numbytes);

	close(newfd); // close socket

	//close(sockfd);
	
	return 0;
}
