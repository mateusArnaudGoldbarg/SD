

void UART_init();							
unsigned char UART_read();					
void UART_write(unsigned char);				
void UART_msg(char*);						

void UART_init()
{
	DDRD |= (1<<1);							
	DDRD &= ~(1<<0);						
	UCSR0A = (0<<TXC0)|(0<<U2X0)|(0<<MPCM0);
	UCSR0B = (1<<RXCIE0)|(0<<TXCIE0)|(0<<UDRIE0)|(1<<RXEN0)|(1<<TXEN0)|(0<<UCSZ02)|(0<<TXB80);
	UCSR0C = (0<<UMSEL01)|(0<<UMSEL00)|(0<<UPM01)|(0<<UPM00)|(0<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00)|(0<<UCPOL0);
	UBRR0 = 103;								
}

unsigned char UART_read(){
	if(UCSR0A&(1<<7)){			
		return UDR0;			
	}
	else
	return 0;
}

void UART_write(unsigned char caracter){
	while(!(UCSR0A & (1<<UDRE0)));   
	UDR0 = caracter;           
}

void UART_write_txt(char* cadena){			
	while(*cadena !=0x00){				
		UART_write(*cadena);			
		cadena++;						
										
	}
}
