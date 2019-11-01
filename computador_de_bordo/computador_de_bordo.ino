#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"

#define piscaE PB2
#define piscaD PB3

#define set_bit(Y,bit_x)(Y|=(1<<bit_x)) //ativa o bit x da variável Y (coloca em 1)
#define clr_bit(Y,bit_x)(Y&=~(1<<bit_x)) //limpa o bit x da variável Y (coloca em 0)
#define cpl_bit(Y,bit_x)(Y^=(1<<bit_x)) //troca o estado do bit x da variável Y
#define tst_bit(Y,bit_x)(Y&(1<<bit_x)) //testa o bit x da variável Y (retorna 0 ou 1)




  uint16_t ad_valor = 0;
  uint16_t ad_velocidade = 0;
  uint16_t ad_nivel = 0;
  int contador = 0;
  int contador2 = 0;
  bool ligou1 = false;
  uint8_t velocidade;
  uint8_t nivel;
  unsigned char *chptr;
  unsigned char *chptr2;

  
  int main(){

  Serial.begin(9600);
  uint16_t count;

//====================================== Setando timer 1 ===========================================
    OCR1A = 0x61D;

    TCCR1B |= (1 << WGM12);
    // Mode 4, CTC on OCR1A
    TCCR1A |= (1 << WGM12);

    TIMSK1 |= (0 << OCIE1A);
    //Set interrupt on compare match

    TCCR1B |= (1 << CS12) | (1 << CS10);
    // set prescaler to 1024 and start the timer


//===================================================================================================

  
  
  ADMUX |= 0b01000000;  //AVCC como referência, ADLAR = 0, MUX = 0000 (ADC0 como entrada);
  DDRD |= 0b11111111;

  DDRB |= 0b00000000;

  ADCSRA |= 0b10000111;
  //ADCSRA |= (1<< ADIE);
  
  sei();
  count = 0;
  while(1){

    ADCSRA |= 0b10000111;


    ADMUX  &= 0b11110000;
    ADMUX  |= 0b00000000;
    ADCSRA |= 0b01000000;
    while(!(ADCSRA & 0b00010000));    
    ad_valor = ADC; 

    if(ad_valor > 200){
      TIMSK1 |= (1 << OCIE1A);
    if(ad_valor >650){
      velocidade = ad_velocidade*127/1023;
      chptr = (unsigned char *) &velocidade;
    }
    

      
    
      if(ligou1 == true){

        nivel = ad_nivel*127/1023;
        chptr2 = (unsigned char *) &nivel;
        //UART_write(*chptr2);
          Serial.println(ad_nivel);
        

        
          PORTD = (1<<PD7);
          if((tst_bit(PINB,piscaD))){ // ascende o pisca direito
            if (contador2 > 5){
              PORTD = 0b10010000;  
            } else{
              PORTD = 0b10000000;
            }
            
          }
          if((tst_bit(PINB,piscaE))){ // ascende o pisca esquerdo
            if (contador2 > 5){
              PORTD = 0b10100000;  
            } else{
              PORTD = 0b10000000;
            }
            
          }

    ADMUX  &= 0b11110000;
    ADMUX  |= 0b00000001;
    ADCSRA |= 0b01000000;
    while(!(ADCSRA & 0b00010000));
    ad_velocidade = ADC;  

    ADMUX  &= 0b11110000;
    ADMUX  |= 0b00000010;
    ADCSRA |= 0b01000000;
    while(!(ADCSRA & 0b00010000));
    ad_nivel = ADC; 
          
      }
      
    } else if(ad_valor <= 200){
      TIMSK1 |= (0 << OCIE1A);
      ligou1 = false;
      PORTD = 0b00000000;
    }

    while(ad_valor<=200){
      ADMUX  &= 0b11110000;
      ADMUX  |= 0b00000000;
      ADCSRA |= 0b01000000;
      while(!(ADCSRA & 0b00010000));    
      ad_valor = ADC; 
    }     
  }
}


ISR(TIMER1_COMPA_vect){
  contador++;
  contador2++;
  if(contador >= 10){
    ligou1 = true;
    if(ad_valor > 650){
    //UART_write(*chptr);
    Serial.println(ad_velocidade);
  }
  }
  if(contador2 == 10){
    contador2 = 0;
  }
}
