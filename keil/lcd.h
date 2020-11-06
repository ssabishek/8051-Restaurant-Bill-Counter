#define lcd P2

sbit rs = P3^0;
sbit rw = P3^1;
sbit en = P3^2;



static int loc=0;


void lcd_init();
void lcd_cmd(unsigned char);
void lcd_dat(unsigned char);
void msdelay(unsigned char);
void lcd_string(unsigned char *);


void lcd_cursor(){
	loc=0;
}

void lcd_cust(){
	loc=12;
}

//lcd initialization

void lcd_init()
{
	lcd_cmd(0x80);//force cursor to the begining
	lcd_cmd(0x38);//use 2 lines and 5x2 matrix 8bitdata
	lcd_cmd(0x01);//clear screen
	lcd_cmd(0x0c);//display on cursor off
	lcd_cmd(0x06);//increment cursor
	
}

// send commands

void lcd_cmd(unsigned char ch)
{
	lcd = ch;
	rs = 0;
	rw = 0;
	en = 1;
	msdelay(20);
	en = 0;
	
}

// send data

void lcd_dat(unsigned char ch)
{
	lcd = ch;
	rs = 1;
	rw = 0;
	en = 1;
	msdelay(20);
	en = 0;
}

// delay

void msdelay(unsigned char t)
{
	unsigned int i, j;
	for(i = 0; i < t; i++)
	for(j = 0; j < 1275; j++);//1ms delay
}
void lcd_head(unsigned char *p)
{
	
	while(*p != '\0')
	{
		lcd_dat(*p);
			p++;
		
	}
}


// send a string of data

void lcd_string(unsigned char *p)
{
	
	while(*p != '\0')
	{
		loc++;
		lcd_dat(*p);
		 if(loc>13) {  // this is the logic that we move text to left side after we reached at 
			lcd_cmd(0x18);  // location 8fh which is last address on lcd in  first line
 }	p++;
		
	}
}