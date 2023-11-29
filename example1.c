#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h> 

void setVideoMode(unsigned char mode) {
    union REGS inregs, outregs;
    inregs.h.ah = 0x00;  // Set video mode function
    inregs.h.al = mode;  // Mode 13h
    int86(0x10, &inregs, &outregs);
}

void setPixel(int x, int y, unsigned char color) {
    union REGS inregs, outregs;
    inregs.h.ah = 0x0C;     // Set pixel function
    inregs.h.al = color;    // Color value
    inregs.x.cx = x;        // X-coordinate
    inregs.x.dx = y;        // Y-coordinate
    int86(0x10, &inregs, &outregs);
}

int main() {
    int x, y, z;
    unsigned char color;

    setVideoMode(0x13); // Set Mode 13h

    for (y = 0; y < 200; y++) {
        for (x = 0; x < 320; x++) {
            color = color % 256;  // Generate a random color value
            z++;
            setPixel(x, y, color);
            if (z == 10){
            color = rand();
                z = 0;
            }
        }
    }

    getch(); // Wait for a key press before exiting

    setVideoMode(0x03); // Set text mode

    return 0;
}