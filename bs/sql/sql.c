/* ************************************************************************
 *       Filename:  aql.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年09月22日 14时52分22秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#include <stdio.h>
#include <string.h>
#include "sqlite3.h"

#if 1

int main(int argc, char *argv[])
{
	//1.打开数据库
	char *name = "test.db";
	sqlite3 *db = NULL;

	int ret = sqlite3_open(name, &db);
	if(ret != SQLITE_OK){
		printf("Cannot open %s\n",name);
		return -1;
	}
	printf("--------OPEN_OK---------\n");
	
	//2.创建表
	const char *sql = NULL;
	char *errmsg = NULL;

	
	while(1)
	{
		char cmd[128]= "";
		printf("cmd: ");
		fflush(stdout);
		fgets(cmd, sizeof(cmd), stdin);
		cmd[strlen(cmd)-1] = 0;
		//printf("cmd:%s\n",cmd);
		
		if(strncmp(cmd,"select ", strlen("select ")) == 0){
		
			char **result = NULL;
			int nrow = 0;
			int col = 0;
			
			sql = cmd;
			ret = sqlite3_get_table(db,sql,&result,&nrow, &col, &errmsg);
			if(ret != SQLITE_OK){
				printf("err: %s\n", errmsg);
			}

			//printf("nrow=%d\n", nrow);
			//printf("col=%d\n", col);
			
			for(int i=0;i<nrow+1;i++){
				for(int j=0;j<col;j++){
					printf("%-8s  ",result[i*col+j]);
				}
				printf("\n");
			}	
			sqlite3_free_table(result);
		}
		if(strncmp(cmd,"create table", strlen("create table")) == 0){
			char table[64] = "";
			sscanf(cmd, "create table %[^ (]", table);
			printf("table=%s\n",table);
			
			if(strlen(table) != 0){
				char buf[128] = "drop table ";
				//
				strcat(buf, table);
				strcat(buf,";");	
				sql = buf;
				sqlite3_exec(db, sql, NULL, NULL, &errmsg);

				sql = cmd;
				ret = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
				if(ret != SQLITE_OK){
					printf("err: %s\n", errmsg);
				}				
			}
		}
		else if(strcmp(cmd,"exit") == 0)
		{
			//x.关闭数据库
			ret = sqlite3_close(db);
			if(ret != SQLITE_OK){
				printf("-----CLOSE_FALSE------\n");
				return -1;
			}
			printf("-----CLOSE_OK------\n");	
			break;		
		}
		else{

			sql = cmd;
			ret = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
			if(ret != SQLITE_OK){
				printf("err: %s\n", errmsg);
			}			
		}
	}
	
	return 0;
}

#elif 0
int callback(void *user_data, int n_column, char **column_value, char **column_name)
{
	printf("user_data=%s\n",(char *)user_data);
	printf("n_column=%d\n", n_column);
	
	for(int i=0;i<n_column;i++)
	{
		printf("%s\t",column_value[i]);
	}
	putchar('\n');
	return 0;
}

int main(int argc, char *argv[])
{
	//1.打开数据库
	char *name = "test.db";
	sqlite3 *db = NULL;

	int ret = sqlite3_open(name, &db);
	if(ret != SQLITE_OK){
		return -1;
	}
	printf("--------OPEN_OK---------\n");
	//2.创建表
	const char *sql = "drop table student;";
	char *errmsg = NULL;
	sqlite3_exec(db, sql, NULL,NULL,&errmsg);
	
	sql = "create table student(id int, name varchar(40), addr text);";
	ret = sqlite3_exec(db, sql, NULL,NULL,&errmsg);
	if(ret != SQLITE_OK){
		printf("err: %s\n", errmsg);
		return -1;
	}
	
	//3.插入数据
	sql = "insert into student values(1,'lucy','Beijing');";
	ret = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
	if(ret != SQLITE_OK){
		printf("err: %s\n", errmsg);
		return -1;
	}

	sql = "insert into student values(2,'petty','Shanghai');";
	ret = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
	if(ret != SQLITE_OK){
		printf("err: %s\n", errmsg);
		return -1;
	}
	
	//4.查看数据库的数据
#if 0
	sql = "select * from student;";
	ret = sqlite3_exec(db, sql, callback, "hehe", &errmsg);
	if(ret != SQLITE_OK){
		printf("err: %s\n", errmsg);
		return -1;
	}	
#else
	char **result = NULL;
	int nrow = 0;
	int col = 0;
	
	sql = "select *from student where addr='Beijing';";
	ret = sqlite3_get_table(db,sql,&result,&nrow, &col, &errmsg);
	if(ret != SQLITE_OK){
		printf("err: %s\n", errmsg);
		return -1;
	}

	printf("nrow=%d\n", nrow);
	printf("col=%d\n", col);
	
	for(int i=0;i<nrow+1;i++){
		for(int j=0;j<col;j++){
			printf("%s  ",result[i*col+j]);
		}
		printf("\n");
	}
	
	sqlite3_free_table(result);
#endif
	//x.关闭数据库
	ret = sqlite3_close(db);
	if(ret != SQLITE_OK){
		printf("-----CLOSE_FALSE------\n");
		return -1;
	}
	printf("-----CLOSE_OK------\n");

	return 0;
}
#endif

