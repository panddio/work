#include<stdio.h>

#if 1
#include"My.h"
//#include </home/pc/work/example/math/mymath.h>
//#include "./math/mymath.h"
#include "mymath.h"

void main()
{
	int a,b,c;
	char sub[]="hello";
	//printf("please input three numbers\n");

	//scanf("%d %d %d", &a,&b,&c);
	Bubbing_Methed(sub);

}

#endif

#if 0
int main(int argc, char *argv[])
{

	char a1 = '*';
	char a2[20] = "abcdef";
	unsigned short int b1 = 0x5a;
	int b2 = -30;
	long int b3 = 040;
	float c = 3.14f;
	double d = 3.1415936535898;
	double e = 314e-2;

	printf("a1=%c,%d\n",a1,sizeof(a1));
	printf("a2=%s,%d\n",a2,sizeof(a2));
	printf("b1=%x,%d\n",b1,sizeof(b1));
	printf("b2=%d,%d\n",b2,sizeof(b2));
	printf("b3=%o,%d\n",b3,sizeof(b3));
	printf("c=%.2f,%d\n",c,sizeof(c));
	printf("d=%.10f,%d\n",d,sizeof(d));
	printf("e=%e,%d\n",e,sizeof(e));
	return 0;
}
#endif

#if 0
void main()
{
	signed char n = -10;//1000 1010
	signed char m = 0x40 & ( n >> 1 );
	         // 0100 0000 & (1100 0101)= 0100 0000 =64
	unsigned char mm =0x82;
    mm >>=8;
	printf("%d\n",n);
	printf("%d\n",m);
	printf("%d\n",mm);
}
#endif
