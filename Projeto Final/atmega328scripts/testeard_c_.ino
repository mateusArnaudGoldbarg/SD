#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"
#include <util/delay.h>
#define F_CPU 16000000UL


int contador = 0;
int contador2 = 0;
bool flag1 = false;

int main(void){
  Serial.begin(9600);

//=============================================
    OCR1A = 0x61D;

    TCCR1B |= (1 << WGM12);

    TCCR1A |= (1 << WGM12);

    TIMSK1 |= (1 << OCIE1A);

    TCCR1B |= (1 << CS12) | (1 << CS10);


//=============================================


  sei();
  
  char ad_valor = 0;
  unsigned char *chptr;
  ADMUX |= 0b01000000;  //AVCC como referência, ADLAR = 0, MUX = 0000 (ADC0 como entrada);
  ADCSRA |= 0b10000111;
  
  DDRB |= 0b00000000;
  PORTB |= 0b11111111;
  DDRD = 0b11111111;
  PORTD = 0b00000000;
  int Loop = 0;
  while(1){
    ADCSRA |= 0b10000111;

    ADMUX  &= 0b11110000;
    ADMUX  |= 0b00000000;
    ADCSRA |= 0b01000000;
    while(!(ADCSRA & 0b00010000));    
    ad_valor = ADC/8;
    chptr = (unsigned char *) &ad_valor;
    //Serial.println(ad_valor);
    UART_write(ad_valor);
    UART_write_txt("\n");
    //Serial.println(PINB);
    if(!(PINB & (1<<PB2))){
      UART_write_txt("E\n");
      PORTD |= (1<<PD4); 
      _delay_ms(5);    
    }
    else if(!(PINB & (1<<PB3))){
      UART_write_txt("D\n");
      PORTD |= (1<<PD5); 
      _delay_ms(5);
    }
    else{
      //UART_write_txt("O\n");
      PORTD = 0b00000000;
      //_delay_ms(20);
    }
    _delay_ms(20);
    if(Loop >= 200){
      Loop = 0;
    }
    Loop++;
  }
}

ISR(TIMER1_COMPA_vect){
  if(flag1 == false){
    contador++;
  }
  if(flag1 == true){
    contador2++;
  }
  
  if(contador >= 80 && flag1 == false){
    UART_write_txt("Nathan\n");
    contador = 0;
    flag1 = true;
  }
  if(contador2 >= 40 && flag1 == true){
    UART_write_txt("xau\n");
    contador2 = 0;
    flag1 = false;
  }
  
}
