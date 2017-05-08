#include<stdio.h>
#include<mysql/mysql.h>

int main()
{
	MYSQL mysql;
	if(NULL == mysql_init(&mysql))
	{
		printf("mysql_init is fail\n");
		return -1;	
	}

	if(NULL==mysql_real_connect(&mysql,"localhost","root",
				"123456","mysql",0,NULL,0))
	{
		printf("mysql-real-connect is error1,%s\n",mysql_error(&mysql));
		return -1;
	}
	
	printf("connect sql is successful!\n");

	mysql_close(&mysql);

	int a=8;
	int b=9;
	printf("hello world,this is my first value1=%d,value2=%d",a,b);
	return 1;
}
