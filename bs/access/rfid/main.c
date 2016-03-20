#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <pthread.h>
#include <sys/select.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <time.h>
#include "sqlite3.h"
#include "uart_init.h"


typedef struct _msg
{
	long type;
	char msg[32];
}MSG;

static int cgi_flag = 0;

void *pthread_select_cgi(void *arg)
{
	int msgid = (int)arg;	
	MSG recv;
	
	recv.type = (long)('R');  // 接受数据类型
	
	while(1)
	{
		if(!cgi_flag){
			bzero(&recv.msg, sizeof(recv.msg));
			msgrcv(msgid, &recv,sizeof(recv) - sizeof(long), recv.type, 0);
			
			if(strcmp(recv.msg, "register") == 0){
				printf("recv from cgi\n");
				cgi_flag = 1;		
			}			
		}
		usleep(200000);
	}
}

void rfid_read_cardid(int uart_fd, char *rfid, int length)
{
	int i;
	
	for(i=0;i<length;i++)
	{
		read(uart_fd, rfid+i, 1);
	}
}

char *rfid_cardid_change(char *rfid, int length, char *cardid)
{
	int i;
	char buf[5] ="";
	
	for(i=0;i<length;i++)
	{
		sprintf(buf,"%02x", rfid[i]);
		strcat(cardid, buf);		
	}
	
	return cardid;
}

void get_locatime(char *newtime)
{
	time_t rawtime;
    struct tm * timeinfo;
	time (&rawtime);
	
	timeinfo=localtime(&rawtime);
	//asctime(timeinfo);  //转为便准的ASCII时间格式
	
	sprintf(newtime,"%4d-%02d-%02d  %02d:%02d:%02d\n",
			timeinfo->tm_year+1900,timeinfo->tm_mon+1,timeinfo->tm_mday,
			timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);	
}

int rfid_join_db(sqlite3 *db,char *cardid,char *newtime)
{
	char *errmsg = NULL;
	char buf[256] = "";
	const char *sql = buf;
	
	sprintf(buf,"insert into record values(\'%s\',\'%s\');",cardid, newtime);
	int ret = sqlite3_exec(db,sql,NULL,NULL,&errmsg);
	
	if(ret != SQLITE_OK)
	{
		printf("Err: %s\n", errmsg);
		return -1;
	}
	
	return 0;
}

void rfid_card_print(char *rfid, int length)
{
	int i;
	
	printf("rfid card number:\n\t");
	for(i=0;i<length;i++)
	{
		printf("0x%02x ", rfid[i]);
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	int msgid, ret;
	key_t key;
	MSG send;
	pthread_t pth_cgi;

	key = ftok("../",10);                  // 获取key 值
	msgid = msgget(key, IPC_CREAT | 0777); // 打开或创建消息队列
	if(msgid == -1)  //出错退出
	{
		perror("");
		exit(-1);
	}
	
	sqlite3 *db = NULL;
	ret = sqlite3_open("../db/admin.db",&db);
	if(ret != SQLITE_OK){
		printf("Open db failed!\n");
		exit(-1);
	}
	
	int uart_fd = uart_init("/dev/ttyUSB0"); // 打开串口设备文件
	
	// 创建一个监听是否有新卡注册的进程
	pthread_create(&pth_cgi, NULL, pthread_select_cgi, (void *)msgid); 
	pthread_detach(pth_cgi);

	while(1)
	{
		char rfid[5] = "";
		char cardid[32] = "";

		
		char newtime[64] = "";
		rfid_read_cardid(uart_fd, rfid, sizeof(rfid));	
		rfid_cardid_change(rfid, sizeof(rfid), cardid); // 把卡号转换成字符串
		rfid_card_print(rfid, 5);
		printf("cardid=%s\n",cardid);
		if(!cgi_flag){		
			get_locatime(newtime);
			rfid_join_db(db, cardid, newtime);
		}
		else{			
			send.type = (long)('C');
			bzero(send.msg, sizeof(send.msg));
			strcpy(send.msg, cardid);
			
			msgsnd(msgid, &send, sizeof(send) - sizeof(long), 0);
			cgi_flag = 0;
		}
	}
	
	uart_uninit(uart_fd);
	sqlite3_close(db);
	return 0;
}



