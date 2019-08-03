/*
 * GccApplication1.c
 *
 * Created: 7/26/2019 7:50:14 PM
 * Author : SHUBHAM
 */ 
//F_CPU 8000000UL
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#define BAUD 9600
#define BAUDRATE 51
float kp;
float kd;
float ki;
                         
void uart_init(void)
{
	UBRR0H = (BAUDRATE>>8);
	UBRR0L = BAUDRATE;
	UCSR0B = (1<<RXEN)|(1<<TXEN);
	UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);  
}

void uart_transmit(char data)
{
	while(!(UCSR0A & (1<< UDRE)));
	UDR0 = data;
}

char uart_receive (void)
{
	while (!( UCSR0A & (1<<RXC0)));
	return UDR0;
}

void usart_transmit_string(char *str)
{

	while(*str > 0)
	{
		
		uart_transmit(*str);
		str++;
	}
}


int main(void)
{
	//char character='a';
	uart_init();	
    /* Replace with your application code */
    
	mpu6050_init();
	float pitch = 0;
	//int intdata=179;
	char data[10] ;
	int16_t ax = 0;
	int16_t ay = 0;
	int16_t az = 0;
	int16_t gx = 0;
	int16_t gy = 0;
	int16_t gz = 0;
	
	float x=0,y=0,z=0;
	char res[10];
	
	while (1)
	{
		mpu6050_getRawData(&ax, &ay, &az, &gx, &gy, &gz);
		//itoa(ax,data,10);
		//itoa(ay,data,10);
		//itoa(az,data,10);
		x=(float)ax/16384;
		y=(float)ay/16384;
		z=(float)ay/16384;
		//usart_transmit_string(data);
		pitch=(atan(x/(sqrt(pow(y,2)+pow(z,2)))))*(1260/22.0);
		dtostrf(pitch,10,2,res);
		//usart_transmit_string(data);
		//usart_transmit_string("     ");
		usart_transmit_string(res);
		usart_transmit_string("     ");
		//uart_transmit('a');
		//_delay_ms(50);
		pid(pitch);
	}
}


void pid(float pitch)
{
	
		float current_pitch = 0,last_error = 0,error ,target_pitch = 0,derivative,integral=0,output;
		current_pitch = pitch ;
		error = target_pitch - current_pitch ;
		integral=integral+error;
		derivative = error - last_error ;
		output = (kp*error)+ (kd*derivative) + (ki*integral);
		
		output=(output/90)*255;
		
		if(abs(output)>255)
		{
			output=255;
		}
		
		if (pitch>0)
		{
			usart_transmit_string("forward");
		}
		else
		{	
			usart_transmit_string("backward");
		}
		
		last_error = error ;
	
}

