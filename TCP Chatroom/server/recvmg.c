#include "common.h"

extern server_db *head, *head1;

void *recvmg(void *client_sock)
{
	int status;
	int sock = *((int *)client_sock);
	char msg[500];
	int len, lenn;
	char user[200];
	status = authentication(sock);
	if (status == 1)
	{	
		while((len = recv(sock,msg,500,0)) > 0) 
		{

			msg[len] = '\0';

			//Search the sockfd to get the names
			server_db *name = search_sock(&head1, sock);
			if(name != NULL)
			{
				strcpy(user, name->username);
				len = strlen(user);
				user[len-1]=':';
				strcat(user, msg);
			}


			sendtoall(user,sock);
			//	sendtoall(msg,sock);
			
			printf("Msg : %s\n sock: %d\n", msg, sock);
			if(strncmp(msg, "logout", 6) == 0)
			{
				printf("Logout section\n");
				delete_element(&head1, sock);
				close(sock);
			}


		}
	}
}

