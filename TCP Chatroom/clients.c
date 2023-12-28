#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>


#define MAX_LENGHT      1024
#define PORT		5000
char msg[MAX_LENGHT];
pthread_mutex_t mutex;

void *recvmg(void *my_sock)
{
    int sock = *((int *)my_sock);
    int len;
    // client thread always ready to receive message
    while((len = recv(sock,msg,MAX_LENGHT,0)) > 0) {
        msg[len] = '\0';
        pthread_mutex_lock(&mutex);
        printf("\n");
        fputs(msg,stdout);
        pthread_mutex_unlock(&mutex);
    }
}

int main(){
    pthread_t recvt;
    int len;
    int sock;
    char send_msg[MAX_LENGHT] = {'\0'};
    struct sockaddr_in ServerIp;
    char client_name[100];
    sock = socket( AF_INET, SOCK_STREAM,0);
    ServerIp.sin_port = htons(PORT);
    ServerIp.sin_family= AF_INET;
    ServerIp.sin_addr.s_addr = inet_addr("127.0.0.1");
    if( (connect( sock ,(struct sockaddr *)&ServerIp,sizeof(ServerIp))) == -1 )
        perror("\n Connection to socket failed \n");
	
	recv(sock, send_msg, MAX_LENGHT, 0);
	printf("Server:  %s", send_msg);
       	memset(send_msg, 0, MAX_LENGHT);
       	fgets(send_msg,MAX_LENGHT,stdin);
       	send(sock,send_msg,strlen(send_msg), 0);
	recv(sock, send_msg, MAX_LENGHT, 0);
	printf("%s", send_msg);
    //creating a client thread which is always waiting for a message
    pthread_create(&recvt,NULL,(void *)recvmg,&sock);
    pthread_mutex_init(&mutex,NULL);
	
    //ready to read a message from console
    while(1) 
    {
        fflush(stdin);
        fgets(send_msg,MAX_LENGHT,stdin);
        pthread_mutex_lock(&mutex);
        printf("You: %s", send_msg);
        pthread_mutex_unlock(&mutex);
        len = send(sock,send_msg,strlen(send_msg), 0);
        memset(send_msg, '\0', MAX_LENGHT);
        if(len < 0) 
            perror("\n Message not sent \n");
            
    }

    //thread is closed
    pthread_join(recvt,NULL);
    close(sock);
    return 0;
}
