/*program to design fullduplex msg queue(user 2)*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct msgbuf  //msg queue
{

	long mtype;
	char data[30];
};


int main()
{
	char s[30];

	struct msgbuf v1,v2;
	int id;

	id=msgget(4,IPC_CREAT|0644);  //opend msg queue with key 4
	if(id<0)
	{
		perror("msgget");
		return 0;
	}

	//		printf("%d\n",id);
	if(fork()==0)
	{//child//msg_rcv
		while(1)
		{
			msgrcv(id,&v1,sizeof(v1),2,0);  //recieving from user 1 parent data to user 2 child with mtype 2

			printf("\rstranger: %s\n",v1.data);
			printf("me: ");
			fflush(stdout);  //flushing output stream to print me 
		}
	}
	else
	{//parent//msg_snd 
		while(1)
		{
			v2.mtype=3;

			printf("me: ");
			scanf(" %[^\n]s",s);
			
			strcpy(v2.data,s);

			msgsnd(id,&v2,strlen(v2.data)+1,0);  //sending from user 2 parent data to user 1 child with mtype 3
			//perror("msgsnd");
		}
	}
}
