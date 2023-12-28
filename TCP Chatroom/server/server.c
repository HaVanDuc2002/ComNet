#include "common.h"

#define PORT	5000
pthread_mutex_t mutex;
int clients[20];
int n=0;
server_db *head = NULL, *head1 = NULL;


int main()
{

	struct sockaddr_in ServerIp;
	pthread_t recvt;
	int sock=0 , Client_sock=0;

	ServerIp.sin_family = AF_INET;
	ServerIp.sin_port = htons(PORT);
	ServerIp.sin_addr.s_addr = inet_addr("127.0.0.1");
	sock = socket( AF_INET , SOCK_STREAM, 0 );
	if( bind( sock, (struct sockaddr *)&ServerIp, sizeof(ServerIp)) == -1 )
		perror("Cannot bind, error!! \n");
	else
		perror("Server Started\n");

	if( listen( sock ,20 ) == -1 )
		perror("Listening failed \n");

	while(1)
	{
		if( (Client_sock = accept(sock, (struct sockaddr *)NULL,NULL)) < 0 )
		{
			perror("Accept failed  \n");
		}

		pthread_mutex_lock(&mutex);

		clients[n]= Client_sock;
		n++;
		// creating a thread for each client 
		pthread_create(&recvt,NULL,(void *)recvmg,&Client_sock);

		pthread_mutex_unlock(&mutex);
	}
	return 0; 

}
