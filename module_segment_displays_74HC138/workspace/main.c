#include <mcs51/8051.h>
#include <stdint.h>

#define _A 0x80
#define _B 0x40
#define _C 0x20
#define _D 0x10
#define _E 0x08
#define _F 0x04
#define _G 0x02
#define _H 0x01
#define N(x,code) uint8_t n##x = code;

void delay(uint16_t i)
{
	while(i--);
}

void main(void)
{
    N(0, _E|_F|_A|_B|_C)
    N(1, _E|_F|_A|_B|_C|_D|_H)
    N(2, 0x00)
    N(3, _E|_F|_A|_B|_C|_D|_G)
    N(4, _F|_A|_B|_C|_D|_G)
    N(5, _A|_B|_C)
    N(6, _A|_F|_G|_C|_D)
    N(7, _A|_B|_C)
    uint8_t j[8] = {n0,n1,n2,n3,n4,n5,n6,n7};
    uint8_t i = 0;
    while(1)
    {
        for(i=0;i<8;i++){
            P0 = j[i];
            P2 = i;
            delay(50);
        }
    }
}
