#include "comm.h"

int main()
{
	int queue_id=creat_msg_queue();
	if(queue_id<0)
	{
		exit(1);
	}
	char buf[_BLOCK_SIZE_];
	printf("%d\n",queue_id);
	while(1)
		{
		memset(buf,'\0',sizeof(buf));
		if(msg_queue_recv(queue_id,_CLIENT_ID_,buf)<0)
		{
			printf("recv fail\n");
			exit(1);
		}
		else
		{
			if(strcmp(buf,"quit")==0)
			{
				printf("client quit\n");
				break;
			}
			printf("client: %s\n",buf);
		}
		printf("please input: ");
		fflush(stdout);
		memset(buf,'\0',sizeof(buf));
		gets(buf);
		if(msg_queue_send(queue_id,buf,_SERVER_ID_)<0)
		{
			printf("send fail\n");
			exit(1);
		}
	}
	destroy_msg_queue(queue_id);
return 0;
}
