#include "common.h"
/*#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdlib.h>*/
pthread_mutex_t mutex;
int clients[20];
int n=0;
int flag  = 0;
/*typedef struct node
{
	char username[20];
	char password[5];
	short cl_num;
	struct node *link;
}server_db;*/
/*
   typedef struct node1
   {
   short cl_num;
   char cl_name[20];
   struct node1 *link;
   }active_cl;
 */
server_db *head = NULL, *head1 = NULL;
/*int search_list(server_db **head, const char *msg, const char *pass, int mode);
int insert_at_last(server_db **head, const char *msg, const char *pass);
void sendtoall(char *msg,int curr)
{
	int i;
	pthread_mutex_lock(&mutex);
	for(i = 0; i < n; i++) 
	{
		if(clients[i] != curr) 
		{
			if(send(clients[i],msg,strlen(msg),0) < 0) 
			{
				printf("sending failure \n");
				continue;
			}
		}
	}
	pthread_mutex_unlock(&mutex);
}*/
/*int authentication(int sock)
{
	server_db user;
	char msg[20];
	char pass[5];
	int len;
	while (1)
	{
		send(sock, "1.Register\n2.Login\n3.Logout",28,0);
		recv(sock, msg, 20, 0);
		switch (msg[0])
		{
			case '1': 
				send(sock, "enter username: ",17,0);
				len = recv(sock, msg, 20, 0);
				msg[len] = '\0';
				//Need to search user first and then proceed
				search_list(&head, msg, NULL, 1);


				send(sock, "Enter Password: ",17,0);
				len = recv(sock, pass, 5, 0);
				pass[len] = '\0';

				if ((insert_at_last(&head, msg, pass)) == 0)
				{
					send(sock, "User already present",21,0);
				}
				else
				{
					send(sock, "Registered",11,0);
				}
				break;

			case '2': 
				send(sock, "enter username: ",17,0);
				len = recv(sock, msg, 20, 0);
				msg[len] = '\0';
				//Need to search user first and then proceed
				send(sock, "Enter Password: ",17,0);
				len = recv(sock, pass, 5, 0);
				pass[len] = '\0';
				if (search_list(&head, msg, pass, 2))
				{
					send(sock, "Login success",14,0);

					//Insert the logged in user in 2nd list
					insert_at_last(&head1, msg, pass);
					return 1;
				}
				send(sock, "Login Failed",13,0);
				break;

			default:
				send(sock, "Wrong option",13,0);
		}
	}

}*/
/*void *recvmg(void *client_sock)
{
	int status;
	int sock = *((int *)client_sock);
	char msg[500];
	int len;
	status = authentication(sock);
	if (status == 1)192.168.43.207
	{	
		while((len = recv(sock,msg,500,0)) > 0) 
		{
			msg[len] = '\0';
			sendtoall(msg,sock);
		}
	}
//	char info[300] = ""
}*/

/*int search_list(server_db **head, const char *msg, const char *pass, int mode)
{
	if(*head == NULL)
	{
		return 1;
	}
	
	   if((strcmp((*head)->username, msg) == 0) && (mode == 2))
	   {
	   if(strcmp((*head)->password, pass) == 0)
	   {
	   return 1;
	   }
	   }
	 
	server_db *temp = *head;
	while(temp)
	{
		if(strcmp((temp)->username, msg) == 0)
		{
			if(mode == 2)
			{
				if(strcmp((temp)->password, pass) == 0)
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
			else
			{
				return 0;
			}
		}
		temp = temp->link;
	}
	return 1;
}*/

/*int insert_at_last(server_db **head, const char *msg, const char *pass)
{
	//Create node
	server_db *new = malloc(sizeof(server_db));

	//Validation
	if (new == NULL)
	{
		return 0;
	}
	//	new->data = data;
	//	new->link = NULL;

	//Search for username only if we are registering user


	strcpy(new->username, msg);
	strcpy(new->password, pass);

	//Check for list empty or not
	if (*head == NULL)
	{
		new->cl_num = 1;
		*head = new;

		return 1;
	}


	//Take a temporary pointer
	server_db *temp = *head;
	int number;
	//Traverse till last node
	while (temp->link)
	{
		number = temp->cl_num;
		temp = temp->link;

	}
	temp->link = new;
	new->cl_num = ++number;
	return 1;
}*/


int main()
{

	struct sockaddr_in ServerIp;
	pthread_t recvt;
	int sock=0 , Client_sock=0;

	ServerIp.sin_family = AF_INET;
	ServerIp.sin_port = htons(1234);
	ServerIp.sin_addr.s_addr = inet_addr("127.0.0.1");
	sock = socket( AF_INET , SOCK_STREAM, 0 );
	if( bind( sock, (struct sockaddr *)&ServerIp, sizeof(ServerIp)) == -1 )
		printf("cannot bind, error!! \n");
	else
		printf("Server Started\n");

	if( listen( sock ,20 ) == -1 )
		printf("listening failed \n");

	while(1)
	{
		if( (Client_sock = accept(sock, (struct sockaddr *)NULL,NULL)) < 0 )
		{
			printf("accept failed  \n");
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
