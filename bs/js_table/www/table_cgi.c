#include <stdio.h>
#include <stdlib.h> //getenv()
#include <string.h>
#include "sqlite3.h"


int main(void)
{
	char *name = NULL;
	
	// ��ȡ�����������GET�������������
	// ֮ǰ���������ģ�url="/cgi-bin/_cgi2.cgi?1:0"�� open("GET",url,true)��
	// ��ȡ������Ϊ "?" ��������ݣ���Ϊ data = "1:0";
	
	name = (char *)getenv("QUERY_STRING");
	if(NULL == name)
	{
		printf("error");
		return 0;
	}
	
	// cgi�����printf(), ʵ�����Ǹ�web�������������ݣ����Ǵ�ӡ����Ļ��
	// ���ǣ�������仰�������ӡ����ҳ�ϣ���仰�����ã�ָ��CGI��web������������ı���ʽΪhtml
	// �����ָ��CGI��web������������ı���ʽ������printf()�ǲ��ܸ�web������������Ϣ
	printf("content-type:text/html\n\n");
	
	//printf("#%s#",name);
	//1.�����ݿ�
	sqlite3 *db = NULL;

	int ret = sqlite3_open(name, &db);
	if(ret != SQLITE_OK){
		printf("Cannot open");
	}
	printf("open ok");
	printf("next");
	return 0;
}