#include <lpc214x.h>
#include <stdio.h>

#define RS 0x10000
#define RW 0x20000
#define EN 0x40000

void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_initialize(void);
void lcd_display(void);
void lcd_display2(void);
void lcd_display3(void);
void LCD4_Convert(unsigned char);
void lcd_clear(void);
const unsigned char cmd[4] = {0x28, 0x0c, 0x06, 0x01};
unsigned char msg[] = {"Gear1"};
unsigned char msg2[] = {"Gear2"};
unsigned char msg3[] = {"Gear3"};
   int gear = 0;
int main()
{
  PINSEL1 = 0;
  PINSEL0 = 0X00000000;
  IO0DIR = 0xFFFF0000;
  lcd_initialize();
  while (1)
  {
    if (!(IO0PIN & (1 << 12)))
    {
		if(!(IO0PIN & (1 << 15)))
		{
			gear = gear + 1;
      		lcd_clear();  
			  if(gear == 1)
			  {																				    
			  	lcd_display();
				IO0SET = 0x00000800; 
			  }   // Clear the LCD
			  else if(gear == 2)
			  {
			  	lcd_display2();
				IO0SET = 0x00000800; 
			  } 
			  else if(gear == 3)
			  {
			  	lcd_display3();
				IO0SET = 0x00000800; 
			  } 
			  else
		    	{
		      	lcd_clear(); 
		    	}
		}
		else if(!(IO0PIN & (1 << 13)))
		{
			gear = gear - 1;
      		lcd_clear();  
			  if(gear == 1)
			  {
			  	lcd_display();
				IO0SET = 0x00000800; 
			  }   // Clear the LCD
			  else if(gear == 2)
			  {
			  	lcd_display2();
				IO0SET = 0x00000800; 
			  } 
			  else if(gear == 3)
			  {
			  	lcd_display3();
				IO0SET = 0x00000800; 
			  } 
			  else
		    	{
		      	lcd_clear(); 
		    	}
		}
		 else
		    	{
		      	lcd_clear(); 
		    	}

    }
    
	else
    {
      lcd_clear(); 
    }
  }
}

void delay(unsigned int n)
{
  unsigned int i, j;
  for (i = 0; i < n; i++)
    for (j = 0; j < 12000; j++)
      ;
}

void lcd_cmd(unsigned char data)
{
  IOCLR0 |= RS; //0x1000; //RS
  IOCLR0 |= RW; //0x2000; //RW
  LCD4_Convert(data);
}

void lcd_initialize(void)
{
  int i;
  for (i = 0; i < 4; i++)
  {
    IOCLR0 = 0xF << 19; //IOCLR 0/1
    lcd_cmd(cmd[i]);
    delay(15);
  }
}

void lcd_data(unsigned char data)
{
  IOSET0 |= RS; //0x1000; //RS
  IOCLR0 |= RW; //0x2000; //RW
  LCD4_Convert(data);
}

void lcd_display(void)
{
  char i;
  /* first line message */
  lcd_cmd(0x80);
  delay(15);
  i = 0;
  while (msg[i] != '\0')
  {
    delay(5);
    lcd_data(msg[i]);
    i++;
  }

  delay(1000);
}

void lcd_display2(void)
{
  char i;
  /* first line message */
  lcd_cmd(0x80);
  delay(15);
  i = 0;
  while (msg2[i] != '\0')
  {
    delay(5);
    lcd_data(msg2[i]);
    i++;
  }

  delay(1000);
}

void lcd_display3(void)
{
  char i;
  /* first line message */
  lcd_cmd(0x80);
  delay(15);
  i = 0;
  while (msg3[i] != '\0')
  {
    delay(5);
    lcd_data(msg3[i]);
    i++;
  }

  delay(1000);
}

void LCD4_Convert(unsigned char c)
{
  if (c & 0x80)
    IOSET0 = 1 << 22;
  else
    IOCLR0 = 1 << 22;
  if (c & 0x40)
    IOSET0 = 1 << 21;
  else
    IOCLR0 = 1 << 21;
  if (c & 0x20)
    IOSET0 = 1 << 20;
  else
    IOCLR0 = 1 << 20;
  if (c & 0x10)
    IOSET0 = 1 << 19;
  else
    IOCLR0 = 1 << 19;
  IOSET0 = EN;
  delay(8);
  IOCLR0 = EN;
  if (c & 0x08)
    IOSET0 = 1 << 22;
  else
    IOCLR0 = 1 << 22;
  if (c & 0x04)
    IOSET0 = 1 << 21;
  else
    IOCLR0 = 1 << 21;
  if (c & 0x02)
    IOSET0 = 1 << 20;
  else
    IOCLR0 = 1 << 20;
  if (c & 0x01)
    IOSET0 = 1 << 19;
  else
    IOCLR0 = 1 << 19;
  IOSET0 = EN;
  delay(8);
  IOCLR0 = EN;
}

void lcd_clear(void)
{
  lcd_cmd(0x01); // Command to clear the display
  delay(15);
}
