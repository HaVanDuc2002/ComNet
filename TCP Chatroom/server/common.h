#ifndef COMMON_H
#define COMMON_H

#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct node
{
	char username[20];
	char password[20];
	short cl_num;
	struct node *link;
}server_db;

#define SUCCESS 1
#define FAILURE 0

/*pthread_mutex_t mutex;
int clients[20];
int n=0;

server_db *head = NULL, *head1 = NULL;*/

int authentication(int sock);
server_db *search_sock(server_db **head, int sock);
void *recvmg(void *client_sock);
void sendtoall(char *msg,int curr);
int search_list(server_db **head, const char *msg, const char *pass, int mode);
int insert_at_last(server_db **head, const char *msg, const char *pass, int sock);
int delete_element(server_db **head, int sock);



#endif
