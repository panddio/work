#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>

struct termios options, oldoptions;
/*************************************************************
* ���ܣ�	���ڳ�ʼ������
* ������	�����豸�ļ����
* ����ֵ��	�����豸�ļ�������
**************************************************************/

int uart_init(int num)
{
	int fd = -1;
	
	char *serial_dev[] = {"/dev/s3c2410_serial0",
						"/dev/s3c2410_serial1",
						"/dev/s3c2410_serial2",
						"/dev/s3c2410_serial3",
						"/dev/ttyUSB0",
						"/dev/ttyUSB1"};
	fd = open(serial_dev[num], O_RDWR);
	tcgetattr(fd, &oldoptions);
	tcgetattr(fd, &options);
	
	cfsetispeed(&options, B115200);
	cfsetospeed(&options, B115200);

	options.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|IGNCR|ICRNL|IXON);
	
	options.c_cflag &= ~PARENB; //����żУ��λ
	options.c_cflag &= ~CSTOPB;	//ֹͣλΪ1λ
	options.c_cflag &= ~CSIZE;	
	options.c_cflag |= CS8;		//����λΪ8λ
	
	options.c_lflag &= ~(ICANON|ECHO|ECHOE|ISIG);
	tcsetattr(fd,TCSANOW,&options);
	return fd;
}


/*************************************************************
* ���ܣ�	���ڻָ�����
* ������	�����豸�ļ����
* ����ֵ��	�����豸�ļ�������
**************************************************************/

void uart_uninit(int fd)
{
	tcsetattr(fd,TCSANOW,&oldoptions);
}



/*************************************************************
* ���ܣ�	���ڷ����ַ���
* ������	uart_fd�������豸�ļ�������
			str�������͵��ַ�
* ����ֵ��	��
**************************************************************/
void uart_send_str(int uart_fd, char *str)
{
	write(uart_fd, str, strlen(str));
}


void uart_debug(int uart_id, char *head, char *debug_info)
{
	int uart_fd = uart_init(uart_id);
	uart_send_str(uart_fd, head);
	uart_send_str(uart_fd, "-------------->");
	uart_send_str(uart_fd, debug_info);
	uart_send_str(uart_fd, "\n");
	uart_uninit(uart_fd);
	close(uart_fd);
}

