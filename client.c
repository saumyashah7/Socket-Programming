// Saumya Shah
// CSC 255
// Client code
#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 

#define DELIM "." 
#define BUF_SIZE 50 
#define PORT 4455 
#define SA struct sockaddr 

// Chat function between client and server. 
void chat(int sockfd)
{
	char buff[BUF_SIZE];
	int n;
	for (;;) {
		
		bzero(buff, sizeof(buff));
		// writing and sending message to server
		n = 0;
		while ((buff[n++] = getchar()) != '\n')
			;
		write(sockfd, buff, sizeof(buff));
	}
}
int checkdigit(char *digit)
{
	while (*digit) 
	{
		if (*digit >= '0' && *digit < '10')
			digit+=1;
		else
			return 0;
	}
	return 1;
}
int checkip(char *ip)
{
	int number, dots = 0;
	char *ptr;

	if (ip == NULL)
		return 0;

	//splitting the ip sectoins using dots
	ptr = strtok(ip, DELIM);
	if (ptr == NULL)
		return 0;
	while (ptr)
	{
		//checking if all characters are digits
		if (!checkdigit(ptr))
			return 0;
		//converting string to number
		number = atoi(ptr);

		//check for valid IP 
		if (number >= 0 && number <= 255)
		{
			ptr = strtok(NULL, DELIM);
			if (ptr != NULL)
				dots+=1;
		}
		else
			return 0;
	}

	// valid IP string must contain 3 dots 
	if (dots != 3)
		return 0;
	return 1;
}
int main(int argc, char* argv[])
{	
	int cs;
	struct sockaddr_in servaddr;
	char* tmp = argv[1];

	// Creating a client socket
	cs = socket(AF_INET, SOCK_STREAM, 0);
	if (cs == -1)
	{
		printf("socket creation failed...\n");
		exit(0);
	}
	
	bzero(&servaddr, sizeof(servaddr));

	// Configuring IP, PORT 
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	servaddr.sin_port = htons(PORT);
	//checking if user has given valid ip
	if (checkip(tmp))
		;
	else
	{
		printf("invalid ip\n");
		close(cs);
		exit(0);
	}


	// connect the client socket to server socket 
	if (connect(cs, (SA*)&servaddr, sizeof(servaddr)) != 0) 
	{
		printf("connection with the server failed...\n");
		exit(0);
	}
	
	// function for chat 
	chat(cs);

	// closing the client socket 
	close(cs);
	return 0;
}
