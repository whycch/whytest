/*********************************************************************
由于协会开发板数据端口与1602数据手册数据端口相反
1602数据手册端口 D0     D1    D2    D3      D4      D5      D6      D7 
对应I/O口		 P^0	P^1	  P^2	P^3 	P^4 	P^5 	P^6 	P^7
协会开发板数据口 P^7	P^6	  P^5	P^4 	P^3 	P^2 	P^1 	P^0

所以用第32行八位数据反向排列
也可以用一下函数
unsigned char Convert(unsigned char In_Date)
{
    unsigned char i, Out_Date = 0, temp = 0;
    for(i=0; i<8; i++)
    {
        temp = (In_Date >> i) & 0x01;
        Out_Date |= (temp << (7 - i));
    }
    return Out_Date;
}


**********************************************************************/

#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar code table[]="We are SPMT";					   //第一行显示的内容
uchar code table2[]="A super team";				   	  //第二行显示的内容	 
sbit lcd_en=P0^2;									  //使能端	 E
sbit lcd_rw=P0^1;									  //读/写数据口
sbit lcd_rs=P0^0;									  

void delay(uint z)									  //延时函数
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

void write_com(uchar com)							  //写命令函数
{
	//uchar xx;
	lcd_rs=0;
	//xx=com;
	//P0=((xx<<7)&0x80)|((xx<<5)&0x40)|((xx<<3)&0x20)|((xx<<1)&0x10)|((xx>>7)&0x01)|((xx>>5)&0x02)|((xx>>3)&0x04)|((xx>>1)&0x08);
	P1=com;
	delay(5);
	lcd_en=1;
	delay(5);
	lcd_en=0;

}

void write_date(uchar date)							//写数据函数
{
	//uchar xx;
	lcd_rs=1;
	//xx=date;
	//P0=((xx<<7)&0x80)|((xx<<5)&0x40)|((xx<<3)&0x20)|((xx<<1)&0x10)|((xx>>7)&0x01)|((xx>>5)&0x02)|((xx>>3)&0x04)|((xx>>1)&0x08);
	P1=date;
	delay(5);
	lcd_en=1;
	delay(5);
	lcd_en=0;

}

void init()											  //初始话函数
{
	 lcd_rw=0;
	 lcd_en=0;
	 write_com(0x38);
	 write_com(0x0c);
	 write_com(0x06);
	 write_com(0x01);

}

void display()										   //显示部分
{
	uchar num,num2;
	write_com(0x80+0x03);								 //第一行显示位置
	for(num=0;num<11;num++)								 //第一行显示内容
		write_date(table[num]);

	 write_com(0x80+0x42);								  //第二行显示位置
	 	for(num2=0;num2<12;num2++)						   //第二行显示内容
			write_date(table2[num2]);

}

void main()
{
	 init();
	display();
	 while(1);
}