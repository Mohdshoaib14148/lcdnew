#include <avr/io.h>
#include<util/delay.h>

#define MrLcdsCrib				PORTB
#define DataDir_MrLcdsCrib		DDRB
#define MrLcdsControl			PORTD
#define DataDir_MrLcdsControl	DDRD
#define LightSwitch	5                      // ENABLE on PD5 5 of arduino
#define ReadWrite	7                      // R/W on PD7    7 of arduino  
#define BiPolarMood	2					   // RS on PD2     2 of arduino

void Check_If_MrLcd_isbusy(void);
void Peek_A_Boo(void);
void Send_A_Command(unsigned char command);
void Send_A_Character(unsigned char character);

int main(){
	DataDir_MrLcdsControl |= 1<<LightSwitch | 1<<ReadWrite | 1<<BiPolarMood;  //initialising the lcd
	_delay_ms(15);
	Send_A_Command(0x01);      			// clearing the screen
	_delay_ms(2);
	Send_A_Command(0x28);               // 4 bit mode
	_delay_us(50);
	Send_A_Command(0b00001110);         // controlling cursor and display
	_delay_us(50);
	Send_A_Character(0x53);  // S
	Send_A_Character(0x68);  // h
	Send_A_Character(0x6F);  // o
	Send_A_Character(0x61);  // a
	Send_A_Character(0x69);  // i
	Send_A_Character(0x62);  // b
	_delay_ms(2000);         // delay between names
	Send_A_Command(0x01);    // clearing screen
	_delay_ms(2);
	Send_A_Character(0x56);  // V
	Send_A_Character(0x69);  // i
	Send_A_Character(0x6B);  // k
	Send_A_Character(0x61);  // a
	Send_A_Character(0x73);  // s
	
}

void Check_If_MrLcd_isbusy(void)
{
	DataDir_MrLcdsCrib=0;
	MrLcdsControl |= 1<<ReadWrite;
	MrLcdsControl &= ~(1<<BiPolarMood);
	while(MrLcdsCrib>=0x80)
	{
		Peek_A_Boo();
	}
	DataDir_MrLcdsCrib=0xff;
	
}


void Peek_A_Boo()
{
	MrLcdsControl |= 1<<LightSwitch;
	asm volatile ("nop");
	asm volatile ("nop");
	MrLcdsControl &= ~(1<<LightSwitch);
}


void Send_A_Command(unsigned char command)
{
	void Check_If_MrLcd_isbusy();
	MrLcdsCrib = command;
	MrLcdsControl &= ~(1<<ReadWrite | 1<<BiPolarMood); // R/W = Write, RS = command mode
	Peek_A_Boo();
	MrLcdsCrib=0;	
}



void Send_A_Character(unsigned char character)
{
	void Check_If_MrLcd_isbusy();
	MrLcdsCrib = character;
	MrLcdsControl &= ~(1<<ReadWrite);  		//R/W = Write
	MrLcdsControl |= (1<<BiPolarMood);		// RS = character mode receiving character and displaying
	Peek_A_Boo();
	MrLcdsCrib=0;	
}


