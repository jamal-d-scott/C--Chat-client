#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>

void readLine(char line[]);

int main()
{
	char username[20];
	char ipAddress[15];
	unsigned int port;
	
	printf("\n");
	printf("Enter IP: ");
	scanf("%s" , ipAddress);
	
	printf("Enter a port number: ");
	scanf("%i" ,&port);
	
	while(port > 65535 || port < 1024)
	{
		port = 0;
		printf("Invalid input.\nEnter a port number: ");
		scanf("%i" , &port);
	}
	
	printf("Enter username: ");
	scanf("%s" , username);

	int sockFD = -1;
	sockFD = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in address;
	memset(&address,0,sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress, &(address.sin_addr));
	
	connect(sockFD, (struct sockaddr *) &address,sizeof(address));
	
	char buffer[255] = "";
	char message[255];
	
	getchar();
	while(strcmp("quit",buffer) != 0)
	{
		printf("%s: ",username);
		readLine(buffer);
		strcpy(message,username);
		strcat(message, ": ");
		strcat(message,buffer);
		send(sockFD,message,strlen(message),0);
	}
	
	printf("\n");
	
	send(sockFD,buffer,strlen(buffer)+1,0);
	close(sockFD);
	return 0;
}

void readLine(char line[])
{	
	int c = 0;	
	int i = 0;

	while( (c = getchar()) != '\n' )
	{
		line[i] = c;
		i++;
	}

	line[i] = '\0';
}
