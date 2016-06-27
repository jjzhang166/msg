#include "comm.h"

int comm_msg_queue(int flag)
{
	key_t _key=ftok(_PATH_,_PROJ_ID_);
	if(_key<0)
	{
		perror("ftok");
		return -1;
	}
	int msg_id=msgget(_key,flag);
	if(msg_id<0)
	{
		perror("msgget");
		return -1;
	}
	return msg_id;
}

int creat_msg_queue()
{
	umask(0);
	return comm_msg_queue(IPC_CREAT |IPC_EXCL |0666);
}

int get_msg_queue()
{
	return comm_msg_queue(IPC_CREAT);
}

int msg_queue_send(int msg_id,const char* message,long type)
{
	struct msgbuf msg;
	msg.mtype=type;
	strcpy(msg.mtext,message);
	if(msgsnd(msg_id,&msg,sizeof(msg.mtext),0)<0)
	{
		perror("msgsnd");
		return -1;
	}
	return 0;
}

int msg_queue_recv(int msg_id,int recv_type,char buf[])
{
	struct msgbuf msg;
	if(msgrcv(msg_id,&msg,sizeof(msg.mtext),recv_type,0)<0)
	{
		perror("msgrcv");
		return -1;
	}
	strcpy(buf,msg.mtext);
	return 0;
}

int destroy_msg_queue(int msg_id)
{
	if(msgctl(msg_id,IPC_RMID,NULL)<0)
	{
		perror("msgct");
		return -1;
	}
	else
	{
		printf("remove success\n");
	}
	return 0;
}
