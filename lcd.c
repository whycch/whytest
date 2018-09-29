/*********************************************************************
����Э�Ὺ�������ݶ˿���1602�����ֲ����ݶ˿��෴
1602�����ֲ�˿� D0     D1    D2    D3      D4      D5      D6      D7 
��ӦI/O��		 P^0	P^1	  P^2	P^3 	P^4 	P^5 	P^6 	P^7
Э�Ὺ�������ݿ� P^7	P^6	  P^5	P^4 	P^3 	P^2 	P^1 	P^0

�����õ�32�а�λ���ݷ�������
Ҳ������һ�º���
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
uchar code table[]="We are SPMT";					   //��һ����ʾ������
uchar code table2[]="A super team";				   	  //�ڶ�����ʾ������	 
sbit lcd_en=P0^2;									  //ʹ�ܶ�	 E
sbit lcd_rw=P0^1;									  //��/д���ݿ�
sbit lcd_rs=P0^0;									  

void delay(uint z)									  //��ʱ����
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

void write_com(uchar com)							  //д�����
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

void write_date(uchar date)							//д���ݺ���
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

void init()											  //��ʼ������
{
	 lcd_rw=0;
	 lcd_en=0;
	 write_com(0x38);
	 write_com(0x0c);
	 write_com(0x06);
	 write_com(0x01);

}

void display()										   //��ʾ����
{
	uchar num,num2;
	write_com(0x80+0x03);								 //��һ����ʾλ��
	for(num=0;num<11;num++)								 //��һ����ʾ����
		write_date(table[num]);

	 write_com(0x80+0x42);								  //�ڶ�����ʾλ��
	 	for(num2=0;num2<12;num2++)						   //�ڶ�����ʾ����
			write_date(table2[num2]);

}

void main()
{
	 init();
	display();
	 while(1);
}