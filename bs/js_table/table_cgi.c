#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "sqlite3.h"


int main(void)
{
	char *db = NULL;
	
	// ��ȡ�����������GET�������������
	// ֮ǰ���������ģ�url="/cgi-bin/_cgi2.cgi?1:0"�� open("GET",url,true)��
	// ��ȡ������Ϊ "?" ��������ݣ���Ϊ data = "1:0";
	
	db = (char *)getenv("QUERY_STRING");
	if(NULL == db)
	{
		printf("error");
		return 0;
	}
	
	// cgi�����printf(), ʵ�����Ǹ�web�������������ݣ����Ǵ�ӡ����Ļ��
	// ���ǣ�������仰�������ӡ����ҳ�ϣ���仰�����ã�ָ��CGI��web������������ı���ʽΪhtml
	// �����ָ��CGI��web������������ı���ʽ������printf()�ǲ��ܸ�web������������Ϣ
	printf("content-type:text/html\n\n");
	
	printf("#%s#",db);
	return 0;
}