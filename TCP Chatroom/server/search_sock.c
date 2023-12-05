#include "common.h"


server_db *search_sock(server_db **head, int sock)
{
	if(*head == NULL)
	{
		return NULL;
	}
	server_db *temp = *head;
	while(temp)
	{
		if(temp->cl_num == sock)
		{
			return temp;
		}
		temp = temp->link;
	}
	return NULL;
}

