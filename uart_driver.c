#include<lpc21xx.h>
void uart0_init(unsigned int baud)
{
	int pclk,res=0;
	if(VPBDIV==0)
		pclk=15000000;
	else if(VPBDIV==0x1)
		pclk=60000000;
	else if(VPBDIV==0x2)
		pclk=30000000;
	res=pclk/(16*9600);
	PINSEL0|=0X5;
	U0LCR=0X83;
	U0DLL=(res&0xff);
	U0DLM=(res>>8)&0xff;
	U0LCR=0X03;
}
#define THRE ((U0LSR>>5)&1)
void uart0_tx(unsigned int data)
{
	U0THR=data;
	while(THRE==0);
	}
#define RDR (U0LSR&1)
	unsigned char uart0_rx()
	{
		while(RDR==0)
			return U0RBR;
	}
void uart0_string(char *ptr)
{
	while(*ptr!='\0')
	{
		uart0_tx(*ptr);
			ptr++;
	}
}

void uart0_integer(int num)
{
	int a[10],i;
	if(num==0)
	{
		uart0_tx('0');
	}
	if(num<0)
	{
		num=-num;
		uart0_tx('-');
	}
	i=0;
	while(num>0)
	{
		a[i]=num%10+48;
		num=num/10;
		i++;
	}
	for(i=i-1;i>=0;i--)
	{
		uart0_tx(a[i]);
	}
}
