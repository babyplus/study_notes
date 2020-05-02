#include <mcs51/8051.h>
#include <stdint.h>

void delay(uint16_t i)
{
	while(i--);
}

void main(void)
{
    while(1) {
        P0 = 0x0f;
        P1 = 0xf0;
        P3 = 0xff;
        delay(200);
        P0 = 0xf0;
        P1 = 0xff;
        P3 = 0x0f;
        delay(200);
    }
}
