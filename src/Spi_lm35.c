#define F_CPU 16000000UL

#include <mega328p.h>
#include <delay.h>
#include <stdint.h>
 unsigned int i;

void SPI_init(void)
{
    DDRB |= (1<<3) | (1<<5) | (1<<2);   // MOSI, SCK, LATCH
    SPCR = (1<<SPE) | (1<<MSTR);        // Enable SPI Master
}


void SPI_send(uint8_t data)
{
    SPDR = data;
    while (!(SPSR & (1<<SPIF)));
}


void send_16bit(uint8_t digit, uint8_t segment)
{
    PORTB &= ~(1<<2);    // LATCH LOW

    SPI_send(digit);
    SPI_send(segment);

    PORTB |= (1<<2);     // LATCH HIGH
}


void ADC_init(void)
{
    DDRC &= ~(1<<0);        // PC0 input

    ADMUX = (1<<REFS0);     // AVCC reference, ADC0

    ADCSRA = (1<<ADEN)
           | (1<<ADPS2)
           | (1<<ADPS1)
           | (1<<ADPS0);    // Prescaler 128
}

unsigned int ADC_read(void)
{
    ADCSRA |= (1<<ADSC);
    while (ADCSRA & (1<<ADSC));

    return ADCW;    
}


unsigned int read_temperature(void)
{
    unsigned int adc = ADC_read();
    unsigned long temp = (unsigned long)adc * 500;
    temp /= 1023;
    return (unsigned int)temp;
}


unsigned char seg_code[10] =
{
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};


void display_number(unsigned int number)
{
    unsigned char d1,d2,d3,d4;

    if(number > 9999) number = 9999;

    d1 = number / 1000;
    d2 = (number / 100) % 10;
    d3 = (number / 10) % 10;
    d4 = number % 10;

    send_16bit(0b1110, seg_code[d1]);
    delay_ms(2);

    send_16bit(0b1101, seg_code[d2]);
    delay_ms(2);

    send_16bit(0b1011, seg_code[d3]);
    delay_ms(2);

    send_16bit(0b0111, seg_code[d4]);
    delay_ms(2);
}


void main(void)
{
    SPI_init();
    ADC_init();

    while(1)
    {
        unsigned int temperature = read_temperature();

        for( i=0; i<50; i++)
        {
            display_number(temperature);
        }
    }
}