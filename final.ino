#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


uint16_t ad_valor = 0;

uint16_t count = 0;

int main(){
  Serial.begin(9600);

    //1 SEGUNDO PARA CONTADOR A
    OCR1A = 15625;
    //O MENTOR TEMPO POSSÍVEL PARA O CONTADOR B (DEPENDE DO CONTADOR A PARA COMEÇAR A CONTAR)
    OCR1B = 0;

    //CTC B ATIVADO
    TCCR1B |= (1 << WGM12);
    
    //CTC A ATIVADO
    TCCR1A |= (1 << WGM12);

    //INTERRUÇÃO A COMEÇA DESABILITADO
    TIMSK1 |= (0 << OCIE1A);

    //PRESCALER DE 1024
    TCCR1B |= (1 << CS12)|(1 << CS10);

  //AVCC COMO REFERÊNCIA, ADLAR = 0, MUX = 0000
  ADMUX |= 0b01000000;  

  //ENABLE ADC COM CLOCK DE 128
  ADCSRA |= 0b10000111;

  DDRB |= 0b00011100;
  PORTB |= 0b00000001;

  DDRD |= 0b11111111;
  PORTD |= 0b00000000;
  sei();

  while(1){
    ADCSRA |= 0b01000000;

    //LIGA O RADAR
    if(!(PINB & 0b00000001)){ 
      
        
      while(1){
        ADCSRA |= 0b11000111;
        ad_valor = ADC;

        //PULSOS PARA CARREGAR O CAPACITOR
        for(int i = 0; i <= 10; i++){
          PORTD = 0b11000000;
          _delay_ms(1);
          PORTD = 0b00000000;
          _delay_ms(1);
          
        }
        Serial.println(ad_valor);

        //VALOR PRÓXIMO DA TENSÃO MÁXIMA PARA PODER HABILITAR O PRIMEIRO CONTADOR
        if((ADMUX == 0b01000000) and ad_valor >= 845){ 
              TIMSK1 |= (1 << OCIE1A);
        }

        //ASCENDE A LUZ SE PASSAR ABAIXO DE 5 SEGUNDOS
        if((ADMUX == 0b01000000) and count >1 and count <=5){ 
              PORTB = 0b00010000;
              count = 0;
              TIMSK1 = (0 << OCIE1B);  

        //NÃO ASCENDE A LUZ SE PASSAR ACIMA DE 5 SEGUNDOS      
        } else if((ADMUX == 0b01000000) and count >5){
              PORTB = 0b00000000;
              count = 0;
              TIMSK1 = (0 << OCIE1B);  
        }

      }
    } 
  }
} 


//PRIMEIRA INTERRUÇÃO
ISR(TIMER1_COMPA_vect){
  //APAGA LUZ DO ANTIGO INFRATOR
  PORTB = 0b00000000;
  
  //SE HOUVER DIMINUIÇÃO DE TENSÃO NA PRIMEIRA BOBINA
  //A INTERRUPÇÃO B É HABILITADA E O ADMUX É
  //ALTERADO PARA FAZER A LEITURA DO PINO A1
  if((ADMUX == 0b01000000) and ad_valor < 844){ 
       ADMUX = 0b01000001;
       ADCSRA |= 0b10000111; 
       TIMSK1 |= (1 << OCIE1B);  
        }

   //SE HOUVER DIMINUIÇÃO DE TENSÃO NA SEGUNDA BOBINA
   //O ADMUX É ALTERADO PARA FAZER A LEITURA DO A0
   if((ADMUX == 0b01000001) and ad_valor < 60){
       ADMUX = 0b01000000;
       ADCSRA |= 0b10000111;
       
}
}

//SEGUNDA INTERRUPÇÃO
//CONTARÁ 5 SEGUNDOS
ISR(TIMER1_COMPB_vect){
  count++;
}
