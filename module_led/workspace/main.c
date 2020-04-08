#include <mcs51/8051.h>
#include <stdint.h>

#define led P0

void delay(uint16_t i)
{
	while(i--);
}

void main(void)
{
    while(1){
        led= 0x01;
        delay(50000);
        uint8_t i = 0;
        for (i=0;i<8;i++){
            P0= 0x01<<i;
            delay(50000);
        }
    }
}
