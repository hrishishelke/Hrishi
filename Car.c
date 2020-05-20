#include<reg51.h>
sbit doorp=P2^0;
sbit doorn=P2^1;
sbit rs=P2^5;
sbit rw=P2^6;
sbit en=P2^7;
void lcddat(unsigned char);
void lcdcmd(unsigned char);
void lcddis(unsigned char *);
void lcd_init();
void serial_init();
void check();
void delay();
void mdelay();
unsigned char rfid[12],v1;
void main()
{
doorp=doorn=0;
serial_init();
lcd_init();
lcddis("RFID BASED CAR");
lcdcmd(0xc0);
lcddis("PARKING SYSTEM");
mdelay();
lcdcmd(0x01);
while(1)
{
lcdcmd(0x01);
lcddis("SWIPE your card");
for(v1=0;v1<12;v1++)
{
while(RI==0);
rfid[v1]=SBUF;
RI=0;
SBUF=rfid[v1];
while(TI==0);
TI=0;
}
check();
}
}

void check()
{
if(rfid[0]=='1'&&rfid[1]=='A' &&rfid[2]=='3'&&rfid[3]=='4'&&rfid[4]=='6'&&rfid[5]=='5'&&rfid[6]=='B'&&rfid[7]=='8'&&rfid[8]=='9'&&rfid[9]=='3'&&rfid[10]=='5'&&rfid[11]=='6')
{
lcdcmd(0x01);
lcddis("Association member");
lcdcmd(0xc0);
lcddis("Sharma -slot 101");
delay();
delay();
lcdcmd(0x01);
doorp=1;doorn=0;
lcddis("Door OPENING");
lcdcmd(0xc0);
lcddis("ALLOW INSIDE");
mdelay();
doorp=0;doorn=0;
delay();
lcdcmd(0x01);
doorp=0;doorn=1;
lcddis("DOOR CLOSING");
mdelay();
doorp=0;doorn=0;
}

else if(rfid[0]=='3'&&rfid[1]=='2'&&rfid[2]=='4'&&rfid[3]=='5'&&rfid[4]=='F'&&rfid[5]=='R'&&rfid[6]=='6'&&rfid[7]=='7'&&rfid[8]=='8'&&rfid[9]=='6'&&rfid[10]=='A'&&rfid[11]=='1')	
	{
lcdcmd(0x01);
lcddis("Association member");
lcdcmd(0xc0);
lcddis("Khan -slot 405");
delay();
delay();
lcdcmd(0x01);
doorp=1;doorn=0;
lcddis("Door OPENING");
lcdcmd(0xc0);
lcddis("ALLOW INSIDE");
mdelay();
doorp=0;doorn=0;
delay();
lcdcmd(0x01);
doorp=0;doorn=1;
lcddis("DOOR CLOSING");
mdelay();
doorp=0;doorn=0;
}
else if(rfid[0]=='1'&&rfid[1]=='4'&&rfid[2]=='5'&&rfid[3]=='6'&&rfid[4]=='7'&&rfid[5]=='8'&&rfid[6]=='H'&&rfid[7]=='A'&&rfid[8]=='3'&&rfid[9]=='4'&&rfid[10]=='E'&&rfid[11]=='C')
{
lcdcmd(0x01);
lcddis("Association member");
lcdcmd(0xc0);
lcddis("Reddy -slot 103");
delay();
delay();
lcdcmd(0x01);
doorp=1;doorn=0;
lcddis("Door OPENING");
lcdcmd(0xc0);
lcddis("ALLOW INSIDE");
mdelay();
doorp=0;doorn=0;
delay();
lcdcmd(0x01);
doorp=0;doorn=1;
lcddis("DOOR CLOSING");
mdelay();
doorp=0;doorn=0;
}
else
{
lcdcmd(0x01);
lcddis("OUTSIDE PERSON");
lcdcmd(0xc0);
lcddis("NO SLOT FOR YOU");
mdelay();
}
}

void serial_init()
{
SCON=0x50;
TMOD=0x20;
TH1=-3;
TR1=1;
}

void lcd_init()
{
lcdcmd(0x38);//initialises crystal 5x7 matrix
lcdcmd(0x01);//clear screen
lcdcmd(0x10);//shift cursor position to right
lcdcmd(0x0c); //display on cursor off
lcdcmd(0x80); // start display from 1 st line
}

void lcdcmd(unsigned char val)
{
P1=val;
rs=0;
rw=0;
en=1;
delay();
en=0;
}
void delay()
{
unsigned int v5;
for(v5=0;v5<6000;v5++);
}

void mdelay()
{
	unsigned int v6,v7;
	for(v6=0;v6<2;v6++)
	{
		for(v7=0;v7<60000;v7++);
	}
	
}

void lcddis(unsigned char *s)
{
unsigned char w;
for(w=0;s[w]!='\0';w++)
{
lcddat(s[w]);
}
}

void lcddat(unsigned char val)
{
P1=val;
rs=1;
rw=0;
en=1;
delay();
en=0;
}