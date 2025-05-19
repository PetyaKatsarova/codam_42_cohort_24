#include <stdio.h>

int main() {
    unsigned char val = 48; // 48=0
    int bit = 1;

    // Stel een paar bits in met een lus en laat het resultaat zien
    for (int i = 0; i < 8; i++) {
        val += bit; 
        printf("Bit = %d,  val = %d (ASCII: %c)\n", bit, val, val);
        bit <<= 1; // 2,4,8,16,64,128,0 (unsigned char max_val=255, overflow to 0)
    }

    return 0;
}