#include "common.h"

int search_list(server_db **head, const char *msg, const char *pass, int mode)
{
	if(*head == NULL)
	{
		return SUCCESS;
	}
	server_db *temp = *head;
	while(temp)
	{
		if(strcmp(temp->username, msg) == 0)
		{
			if(mode == 2)
			{
				if(strcmp(temp->password, pass) == 0)
				{
					return SUCCESS;
				}
				else
				{
					return FAILURE;
				}
			}
			else if(mode == 1)
			{
				return FAILURE;
			}
		}
		temp = temp->link;
	}
	return SUCCESS;
}
