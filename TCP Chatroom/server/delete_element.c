#include "common.h"

int delete_element(server_db **head, int sock)
{
	//Assigning the head value to a temporary pointer variable
	server_db *temp  = *head;
	server_db *past = NULL;
/*	//Check if list is empty
	if (*head == NULL)
	{
		return LIST_EMPTY;
	}*/

	//Check for first node
	if ((*head)->cl_num == sock)
	{
		*head = temp -> link;
		free(temp);
		return SUCCESS;
	}


	//Traversing till n_data is reached
	while (temp)
	{
		if (temp->cl_num == sock)
		{
			printf("CL_num: %d\nsock: %d\n", temp->cl_num, sock);
			past->link = temp->link;
			free(temp);
			return SUCCESS;
		}
		past = temp;
		temp = temp->link;
	}
	return 0;
}
