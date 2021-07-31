#include "lcd.h"

void welcome(){
    char dog[48] = {
        0b00000, 0b00001, 0b00110, 0b01000, 0b10000, 0b10001, 0b10001, 0b10010,
        0b00000, 0b11111, 0b00000, 0b00000, 0b01010, 0b01010, 0b00000, 0b00000,
        0b00000, 0b10000, 0b01100, 0b00010, 0b00001, 0b10001, 0b10001, 0b01001,
        0b01010, 0b01010, 0b00110, 0b00010, 0b00010, 0b00001, 0b00000, 0b00000,
        0b01110, 0b00100, 0b00100, 0b00000, 0b10001, 0b01110, 0b11111, 0b01110,
        0b01010, 0b01010, 0b01100, 0b01000, 0b01000, 0b10000, 0b00000, 0b00000
    };
    
    lcdInit();
    lcdCommand(0x40);
    
    for(char i=0; i<48; i++){
        lcdData(dog[i]);
    }
    //Envia cada uma das linhas em ordem
    for(char i=16; i>0; i--){
        char aux1, aux2;
        lcdCommand(CLR);
        lcdCommand(L0 + i);
        lcdData(0);
        lcdData(1);
        lcdData(2);
        lcdCommand(L1+ i);
        lcdData(3);
        lcdData(4);
        lcdData(5);
        for(int j=0; j<20000; j++);
    }
    
    for(char i=0; i<5; i++){
        if(i%2 == 0){
            lcdCommand(CLR);
            lcdCommand(0x80);
            lcdData(0);
            lcdData(1);
            lcdData(2);
            lcdCommand(0xC0);
            lcdData(3);
            lcdData(4);
            lcdData(5);
            for(int j=0; j<20000; j++);
            lcdCommand(0x85);
            lcdData('B');
            lcdData('e');
            lcdData('m');
            lcdData(' ');
            lcdData('v');
            lcdData('i');
            lcdData('n');
            lcdData('d');
            lcdData('o');

            lcdCommand(0xC4);
            lcdData('a');
            lcdData(' ');
            lcdData(' ');
            lcdData('e');
            lcdData('s');
            lcdData('t');
            lcdData('a');
            lcdData('c');
            lcdData('a');
            lcdData('u');
            lcdData('m');   
        }else{
            lcdCommand(CLR);
        }
        for(int j=0; j<30000; j++);
    }
    for(int j=0; j<30000; j++);
}

void bye(){
    char dog[48] = {
        0b00000, 0b00001, 0b00110, 0b01000, 0b10000, 0b10001, 0b10001, 0b10010,
        0b00000, 0b11111, 0b00000, 0b00000, 0b01010, 0b01010, 0b00000, 0b00000,
        0b00000, 0b10000, 0b01100, 0b00010, 0b00001, 0b10001, 0b10001, 0b01001,
        0b01010, 0b01010, 0b00110, 0b00010, 0b00010, 0b00001, 0b00000, 0b00000,
        0b01110, 0b00100, 0b00100, 0b00000, 0b10001, 0b01110, 0b11111, 0b01110,
        0b01010, 0b01010, 0b01100, 0b01000, 0b01000, 0b10000, 0b00000, 0b00000
    };
    
    lcdInit();
    lcdCommand(0x40);
    
    for(char i=0; i<48; i++){
        lcdData(dog[i]);
    }
    //Envia cada uma das linhas em ordem
    for(char i=16; i>0; i--){
        lcdCommand(CLR);
        lcdCommand(0x80 + i);
        lcdData(0);
        lcdData(1);
        lcdData(2);
        lcdCommand(0xC0 + i);
        lcdData(3);
        lcdData(4);
        lcdData(5);
        for(int j=0; j<20000; j++);
    }
    
    for(char i=0; i<5; i++){
        if(i%2 == 0){
            lcdCommand(CLR);
            lcdCommand(0x80);
            lcdData(0);
            lcdData(1);
            lcdData(2);
            lcdCommand(0xC0);
            lcdData(3);
            lcdData(4);
            lcdData(5);
            for(int j=0; j<20000; j++);
            lcdCommand(0x87);
            lcdData('A');
            lcdData('t');
            lcdData('e');
            lcdData(' ');
            lcdData('a');
            
            lcdCommand(0xC6);
            lcdData('p');
            lcdData('r');
            lcdData('o');
            lcdData('x');
            lcdData('i');
            lcdData('m');
            lcdData('a');
                
        }else{
            lcdCommand(CLR);
        }
        for(int j=0; j<30000; j++);
    }
    for(int j=0; j<30000; j++);
    for(int j=0; j<30000; j++);
    lcdCommand(CLR);
}



