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
	
	// 获取在浏览器端以GET方法输入的数据
	// 之前是这样做的，url="/cgi-bin/_cgi2.cgi?1:0"， open("GET",url,true)，
	// 获取的内容为 "?" 后面的内容，即为 data = "1:0";
	
	db = (char *)getenv("QUERY_STRING");
	if(NULL == db)
	{
		printf("error");
		return 0;
	}
	
	// cgi程序里，printf(), 实际上是给web服务器发送内容，不是打印到屏幕上
	// 但是，下面这句话，不会打印到网页上，这句话的作用，指明CGI给web服务器传输的文本格式为html
	// 如果不指明CGI给web服务器传输的文本格式，后期printf()是不能给web服务器传递信息
	printf("content-type:text/html\n\n");
	
	printf("#%s#",db);
	return 0;
}