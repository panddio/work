#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <fcntl.h>
#include "sqlite3.h"
#include "uart_debug.h"


typedef struct _msg
{
	long type;
	char msg[32];
}MSG;

/*********************************************************************
*功能:	URL的解码
*参数:	result: URL的解码结果；
		url_src：URL的编码
*返回值:URL的解码结果地址
*********************************************************************/
char *url_decode(char *result, const char *url_src)
{
	const char *src = url_src;
	char *dst = result;
	while(*src)
	{
		if(*src == '%')
		{
			char tmp[3];
			tmp[0] = src[1];
			tmp[1] = src[2];
			tmp[2] = 0;
			*dst = strtoul(tmp, NULL, 16);
			src += 2;
		}
		else if(*src=='+')
		{
			*dst=strtoul("20",NULL,16);
		}
		else
			{
				*dst = *src;
			}
		dst++;
		src++;
	}
	*dst = 0;
	return result;
}

/*****************************************************
*功能：查询的结果以表格的形式显示
*参数：db:数据库句柄，
*
*****************************************************/
void display_table(sqlite3 *db, char *cmd)
{
    uart_debug(0, "cmd", cmd);
	char **result = NULL;
	char *errmsg =NULL;
	int row = 0;
	int col =0;
	int ret=sqlite3_get_table(db, cmd, &result, &row, &col,&errmsg);
	
	if(ret==1)
	{
		printf("%s:",errmsg);
	}
	if(row ==0 && col ==0)
	{
		printf("未找到信息！");
	}
	else{
		printf("<table id=\"customers\">");
		int i=0;int j=0;
		for(i=0;i<row+1;i++)
		{
		   if(i==0){
				printf("<tr bgcolor=\"#8A2BE2\"><th>");
		   }
		   if(i%2==0 && i!=0){//表头
				printf("<tr class=\"alt\"><td>");
		   }
		   if(i%2==1){
				printf("<tr><td>");
		   }
		  
		   for(j=0;j<col;j++){  //列
				printf("%s",result[i*col+j]);

				if(j+1==col){
					printf("</td></tr>");
				}
				else{
					if(i==0){
						printf("</th><th>");
					}
					else{
						printf("</td><td>");
					}
				}
		   }
		   int k = i;
		   if(k==row){
				printf("</table>");
			}
		 }
		sqlite3_free_table(result);	
	}		
}
// 1: 新卡注册
// 2：注销旧卡
// 3：查询信息
// 4：更新信息
int main(int argc, char *argv[])
{
	// cgi程序里，printf(), 实际上是给web服务器发送内容，不是打印到屏幕上
	printf("content-type:text/html\n\n");	
	
	char data[1024] = "";
	char *psrc = NULL;

	uart_debug(0, "I' am cgi!", "OK");
	psrc = getenv("QUERY_STRING");
	if(NULL == psrc)
	{
		printf("error");
		return 0;
	}
	
	url_decode(data, psrc);
	uart_debug(0, "AAA", data);
	// 打开数据库
	sqlite3 *db = NULL;
	int ret = sqlite3_open("../db/admin.db",&db);
	if(ret != SQLITE_OK){
		printf("Open db failed!\n");
		exit(-1);
	}
	
	char *errmsg = NULL;
	char cmd[256] = "";     // 操作数据库的命令
	const char *sql = cmd;
	
	int i = 0;
	char *pdata[6] = {NULL};
	
	pdata[i] = strtok(data, ":");
	while(pdata[i++] != NULL && i<6){
		pdata[i] = strtok(NULL, ":");
	}
	
	switch(data[0])
	{
		case '1':
		{	
			char cardid[32]= ""; //	卡号		
			int agentID = 0;     // 工号
			int msgid;
			key_t key;
			MSG send, recv;			
			
			key = ftok("../",10);                  // 获取key 值
			msgid = msgget(key, IPC_CREAT | 0777); // 打开或创建消息队列
			if(msgid == -1)  //出错退出
			{
				perror("");
				exit(-1);
			}	
			
			bzero(recv.msg, sizeof(recv.msg));
			bzero(send.msg, sizeof(send.msg));
			recv.type = (long)('C');
			send.type = (long)('R');
			strcpy(send.msg, "register");
		
			msgsnd(msgid, &send, sizeof(send) - sizeof(long), 0);
			//printf("send ok");
			uart_debug(0, "send", "OK");
			msgrcv(msgid, &recv, sizeof(recv) - sizeof(long), recv.type, 0);
			
			uart_debug(0, "recv", "OK");
			//printf("recv ok");
			if(strcmp(recv.msg, "failed") != 0){
				agentID = atoi(pdata[2]);
				strcpy(cardid, recv.msg);
				
				sprintf(cmd, "insert into stuff values(%d,'%s','%s','%s');", agentID, pdata[1], cardid, pdata[3]);
				uart_debug(0, "register", cmd);
				ret = sqlite3_exec(db,sql,NULL,NULL,&errmsg);
				if(ret != SQLITE_OK)
				{
					printf("Err: %s\n", errmsg);
					exit(-1);
				}				
				printf("注册成功");
			}
			else{
				printf("注册失败");
			}
			break;		
		}
		case '2':
		{
			int agentID = 0; // 工号
			uart_debug(0, "agentID", pdata[1]);
			agentID = atoi(pdata[1]);
			
			sprintf(cmd, "delete from stuff where id=%d;", agentID);
			
			ret = sqlite3_exec(db,sql,NULL,NULL,&errmsg);
			if(ret != SQLITE_OK){
				printf("Err: %s\n", errmsg);
				exit(-1);
			}	
			else{
				printf("注销成功");
			}		
			break;
		}
		case '3':
		{
			char **result = NULL;
			int row = 0; // 行
			int col = 0; // 列

			uart_debug(0, "type", pdata[1]);
			uart_debug(0, "text", pdata[2]);
			if(strcmp(pdata[1], "name") == 0){
				sprintf(cmd, "select * from stuff_record where name='%s';", pdata[2]);				
			}
			else if(strcmp(pdata[1], "cardid") == 0){
				sprintf(cmd, "select * from stuff_record where rfid='%s';", pdata[2]);
			}
			else if(strcmp(pdata[1], "agentID") == 0){
				sprintf(cmd, "select * from stuff_record where id='%s';", pdata[2]);				
			}
			else if(strcmp(pdata[1], "all") == 0){
				strcpy(cmd, "select * from stuff_record;");			
			}			
			else{
				
			}
			printf("query$");// 数据头部
			display_table(db, sql);

#if 0			
			ret = sqlite3_get_table(db,sql,&result,&row, &col, &errmsg);
			if(ret != SQLITE_OK){
				printf("err: %s\n", errmsg);
				exit(-1);
			}
			printf("query$");// 数据头部
			
			
			for(int i=0;i<row+1;i++){
				for(int j=0;j<col;j++){
					printf("%s  ",result[i*col+j]);
				}
				printf("#"); // 行分割标识
			}
	
			sqlite3_free_table(result);	
#endif			
			break;
		}
		case '4':
		{		
			if(strcmp(pdata[2], "name") == 0){
				sprintf(cmd, "update stuff set name='%s' where name='%s';", pdata[3], pdata[1]);
			}
			else if(strcmp(pdata[2], "sex") == 0){
				sprintf(cmd, "update stuff set sex='%s' where name='%s';", pdata[3], pdata[1]);
			}
			else if(strcmp(pdata[2], "agentID") == 0){
				int agentID = 0;
				agentID = atoi(pdata[3]);
				
				sprintf(cmd, "update stuff set id=%d where name='%s';", agentID, pdata[1]);
			}
			else if(strcmp(pdata[2], "cardid") == 0){
				sprintf(cmd, "update stuff set rfid='%s' where name='%s';", pdata[3], pdata[1]);
			}
			else{
				printf("类型错误");
				exit(-1);
			}
			
			ret = sqlite3_exec(db,sql,NULL,NULL,&errmsg);
			if(ret != SQLITE_OK){
				printf("Err: %s\n", errmsg);
				exit(-1);
			}	
			else{
				printf("更新成功");
			}
			
			break;
		}
		default:
			printf("出错");
	}
	sqlite3_close(db);
	return 0;
}