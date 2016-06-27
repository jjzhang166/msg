#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>

#define _PATH_ "."
#define _PROJ_ID_ 0x5666
#define _BLOCK_SIZE_ 1024
#define _SERVER_ID_ 1
#define _CLIENT_ID_ 2
struct msgbuf
{
	long mtype;
	char mtext[_BLOCK_SIZE_];
};


int comm_msg_queue(int flag);
int creat_msg_queue();
int msg_queue_recv(int msg_id,int recv_type,char buf[]);
int destroy_msg_queue(int msg_id);
int msg_queue_send(int msg_id,const char* message,long type);
int get_msg_queue();



