#include "common.h"

extern pthread_mutex_t mutex;
extern int clients[20];
extern int n;
extern server_db *head, *head1;

void sendtoall(char *msg,int curr)
{
	int i;
	server_db *temp = head1;
	server_db *temp1 = head1;
	char *user= NULL;

	pthread_mutex_lock(&mutex);

	while(temp)
	{
		if (temp->cl_num != curr)
		{
			send(temp->cl_num, msg, strlen(msg), 0);
		}
		temp = temp->link;
	}
	pthread_mutex_unlock(&mutex);
}

