#include "common.h"

int search_list(server_db **head, const char *msg, const char *pass)
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
				if(strcmp(temp->password, pass) == 0)
				{
					return SUCCESS;
				}
				else
				{
					return FAILURE;
				}
			}
			else
			{
				return FAILURE;
			}
			temp = temp->link;
		}
}
