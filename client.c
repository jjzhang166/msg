#include "comm.h"

int main()
{
	int msg_id=get_msg_queue();
	if(msg_id<0)
	{
		exit(1);
	}
	char buf[_BLOCK_SIZE_];
	printf("%d\n",msg_id);
	while(1)
	{
		fflush(stdout);
		printf("please input: ");
		memset(buf,'\0',sizeof(buf));
		gets(buf);
		if(msg_queue_send(msg_id,buf,_CLIENT_ID_)<0)
		{
			printf("sned fail\n");
			exit(1);
		}
		memset(buf,'\0',sizeof(buf));
		if(msg_queue_recv(msg_id,_SERVER_ID_,buf)<0)
		{
			printf("recv fail\n");
			exit(1);
		}
		else
		{
			if(strcmp(buf,"quie")==0)
			{
				printf("server quit\n");
				break;
			}
			printf("server: %s\n",buf);
		}
	}
	destroy_msg_queue(msg_id);
	return 0;
}
