#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define set_bit(Y,bit_x)(Y|=(1<<bit_x)) //ativa o bit x da variável Y (coloca em 1)
#define clr_bit(Y,bit_x)(Y&=~(1<<bit_x)) //limpa o bit x da variável Y (coloca em 0)
#define cpl_bit(Y,bit_x)(Y^=(1<<bit_x)) //troca o estado do bit x da variável Y
#define tst_bit(Y,bit_x)(Y&(1<<bit_x)) //testa o bit x da variável Y (retorna 0 ou 1)

#define pinLigar PB1
#define pinPulso PD6
#define pin_tone 10

const byte npulse = 3;
const bool sound = true;


uint16_t ad_valor = 0;
uint16_t valmax = 0;
uint16_t valmin = 0;
int minval = 0;
int maxval = 1023;

const int nmeas=256;  //measurements to take
long int sumsum=0; //running sum of 64 sums 
long int skip=0;   //number of skipped sums
long int diff=0;        //difference between sum and avgsum
long int flash_period=0;//period (in ms) 
long unsigned int prev_flash=0; //time stamp of previous flash
long unsigned int sum=0;
uint16_t count = 0;

int main(){
  Serial.begin(9600);

    OCR1A = 15625;
    OCR1B = 0;
    
    TCCR1B |= (1 << WGM12);
    // Mode 4, CTC on OCR1A
    TCCR1A |= (1 << WGM12);

    TIMSK1 |= (0 << OCIE1A);
    //Set interrupt on compare match

    TCCR1B |= (1 << CS12)|(1 << CS10);
    // set prescaler to 1024 and start the timer

    
  
  ADMUX |= 0b01000000;  //AVCC como referência, ADLAR = 0, MUX = 0001 (ADC1 como entrada);
  ADCSRA |= 0b10000111;// Enable do adc, Escalonador de Clock em 128;

  DDRB |= 0b00011100;
  PORTB |= 0b00000001;

  DDRC |= 0b00000000;
  DDRD |= 0b11111111;
  PORTD |= 0b00000000;
  sei();

  while(1){
    ADCSRA |= 0b01000000;
    
    if((PINB & 0b00000001)){            //Liga o Sistema
      Serial.println("Ligado");
        
      while(1){
        ADCSRA |= 0b11000111;
        //while (!(ADCSRA & 0b00010000));
        ad_valor = ADC;
        
        for(int i = 0; i <= 10; i++){
          PORTD = 0b11000000;
          _delay_ms(1);
          PORTD = 0b00000000;
          _delay_ms(1);
          
        }
        Serial.println(ad_valor);

         
        if((ADMUX == 0b01000000) and ad_valor >= 844){ 
              TIMSK1 |= (1 << OCIE1A);
        }
        if((ADMUX == 0b01000001) and ad_valor < 52){
            
        }

        if((ADMUX == 0b01000000) and count >1 and count <=5){ 
              PORTB = 0b00010000;
              count = 0;
              TIMSK1 = (0 << OCIE1B);  
        } else if((ADMUX == 0b01000000) and count >5){
              PORTB = 0b00000000;
              count = 0;
              TIMSK1 = (0 << OCIE1B);  
        }

      }
    } else{
      Serial.println("Desligado"); 
    }
  }
} 



ISR(TIMER1_COMPA_vect){
  PORTB = 0b00000000;
  if((ADMUX == 0b01000000) and ad_valor < 841){ 
       ADMUX = 0b01000001;
       ADCSRA |= 0b10000111; 
       TIMSK1 |= (1 << OCIE1B);  
        }
   if((ADMUX == 0b01000001) and ad_valor < 51){
       ADMUX = 0b01000000;
       ADCSRA |= 0b10000111;
       
}
}

ISR(TIMER1_COMPB_vect){
  count++;
}
