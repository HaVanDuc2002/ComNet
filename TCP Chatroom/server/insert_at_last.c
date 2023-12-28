#include "common.h"

extern server_db *head;

int insert_at_last(server_db **head, const char *msg, const char *pass, int sock)
{
	//Create node
	server_db *new = (server_db*)malloc(sizeof(server_db));

	//Validation
	if (new == NULL)
	{
		return FAILURE;
	}

	//Search for username only if we are registering user


	strcpy(new->username, msg);
	strcpy(new->password, pass);

	new->cl_num = sock;
	//Check for list empty or not
	if (*head == NULL)
	{
		new->cl_num = sock;
		*head = new;

		return SUCCESS;
	}


	server_db *temp = *head;
	while (temp->link)
	{
	
		temp = temp->link;
	}
	temp->link = new;
	return SUCCESS;
}
