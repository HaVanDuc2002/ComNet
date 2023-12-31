#include "common.h"

extern int clients[20];
extern int n;
extern server_db *head, *head1;


int authentication(int sock)
{
	server_db user;
	char msg[30];
	char pass[20];
	int len, i;
	while (1)
	{
		send(sock, "1.Register 2.Login \n",28,0);
		recv(sock, msg, 30, 0);
		switch (msg[0])
		{
			case '1': 
				memset(msg, '\0', 30);
				memset(pass, '\0', 20);
				send(sock, "Enter username: \n",20,0);
				len = recv(sock, msg, 20, 0);
				msg[len] = '\0';
				//Need to search user first and then proceed
				int ret = search_list(&head, msg, NULL,1);
				if(ret == SUCCESS)
				{
					send(sock, "Enter Password: \n",20,0);
					len = recv(sock, pass, 20, 0);
					pass[len] = '\0';
					printf("Server received : %s\n", pass);

					if ((insert_at_last(&head, msg, pass, sock)) == FAILURE)
					{
						send(sock, "User already present\n",25,0);
					}
					else
					{
						send(sock, "Registered! Press 2 to login\n",30,0);
					}
				}
				memset(msg, '\0', 20);
				memset(pass, '\0', 5);
				break;

			case '2': 
				memset(msg, '\0', 20);
				memset(pass, '\0', 20);
				send(sock, "Enter username: \n",20,0);
				len = recv(sock, msg, 20, 0);
				msg[len] = '\0';
				printf("Server received : %s\n", msg);
				//Need to search user first and then proceed
				send(sock, "Enter Password: \n",17,0);
				len = recv(sock, pass, 20, 0);
				printf("length %d Server received : %s\n", len, pass);
				pass[len] = '\0';
				if (search_list(&head, msg, pass,2))
				{
					send(sock, "Login successfully\n",20,0);

					insert_at_last(&head1,msg, pass, sock);
					return 1;
				}
				
				send(sock, "Login Failed\n",20,0);
				return 0;
				memset(msg, '\0', 20);
				memset(pass, '\0', 5);
				break;
			default:
				send(sock, "Wrong option\n",14,0);
		}	{

	}
	}

}

