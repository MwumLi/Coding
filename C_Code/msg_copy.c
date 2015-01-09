#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/msg.h>

/*
 * 使用消息队列实现读取指定文本到屏幕
 * */
#define LINES 80

typedef struct  MSG_STRUCT{
	long type;
	char msg[LINES];
}MSG_STRUCT;


int main(int argc, const char *argv[])
{
	int			src_fd;
	int			msg_id;
	int			fd;
	int			n;
	int			ret;

	MSG_STRUCT	msg1;
	MSG_STRUCT  msg2;

	if(argc != 2) {
		printf("Usage:%s filemame\n", argv[0]);
		return 1;
	}

	src_fd = open(argv[1], O_RDONLY);
	msg_id = msgget(111, IPC_CREAT|0600);

	fd = fork();

	if(fd == 0) {
		while(1) {
			memset(&msg1, 0, sizeof(MSG_STRUCT));
			msg1.type = 1;
			n = read(src_fd, msg1.msg, LINES-1);
			if(n <= 0)			
			  break;
			msgsnd(msg_id, (struct msgbuf *)&msg1, sizeof(MSG_STRUCT), 0);
		}
		memset(&msg1, 0, sizeof(MSG_STRUCT));
		msg1.type = 1;
		strcpy(msg1.msg, "over");
		msgsnd(msg_id, (struct msgbuf *)&msg1, sizeof(MSG_STRUCT), 0);
		exit(1);
	} else if(fd > 0) {
		while(1) {
			msg2.type = 1;
			ret=msgrcv(msg_id, (struct msgbuf *)&msg2, sizeof(MSG_STRUCT), 1, 0);
			if(ret != -1)  {
				if(strcmp(msg2.msg, "over") != 0)
					printf("%s", msg2.msg);
				else break;
			}
		}	
	}


	close(src_fd);

	return 0;
}
