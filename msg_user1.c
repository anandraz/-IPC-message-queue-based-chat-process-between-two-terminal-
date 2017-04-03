/*program to design fullduplex msg queue(user 1)*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct msgbuf  //msg queue structure
{

	long mtype;
	char data[10];
};


int main()
{
	char s[30];
	struct msgbuf v1,v2;
	int id;

	id=msgget(4,IPC_CREAT|0644);  //opened msg queue with key 4
	if(id<0)
	{
		perror("msgget");
		return 0;
	}

	//              printf("%d\n",id);

	if(fork())	
	{//parent//msg_snd
		while(1)
		{
			v1.mtype=2;

			printf("me: ");

			scanf(" %[^\n]s",s);
			
			strcpy(v1.data,s);

			msgsnd(id,&v1,strlen(v1.data)+1,0); /* sending user 1 parent data to user2 child process with mtype 2*/
			//perror("msgsnd");

		}
	}
	else
	{//child//msg_rcv

		while(1)
		{
			msgrcv(id,&v2,sizeof(v2),3,0);  /* recieving from user 2 parent data to user1 child process with mtype 3*/

			printf("\rstranger: %s\n",v2.data);
			printf("me: ");
			fflush(stdout); //flushing output stearm to print me 
		}
	}
}
