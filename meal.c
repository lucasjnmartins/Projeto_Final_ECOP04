#include "meal.h"
#include "rtc.h"
#include "keypad.h"
#include "lcd.h"
#include "bits.h"
#include <string.h>

void mealFigure() {
    char food[48] = {
        0b00000, 0b00000, 0b00000, 0b00000, 0b00001, 0b00010, 0b00100, 0b01000,
        0b00000, 0b00000, 0b00010, 0b10101, 0b01000, 0b00101, 0b10000, 0b01001,
        0b00000, 0b00000, 0b00000, 0b00000, 0b10000, 0b01000, 0b00100, 0b00010,
        0b01111, 0b01110, 0b01100, 0b01100, 0b01110, 0b01111, 0b01111, 0b00000,
        0b11111, 0b01110, 0b00000, 0b00000, 0b01110, 0b11111, 0b11111, 0b00000,
        0b11110, 0b01110, 0b00110, 0b00110, 0b01110, 0b11110, 0b11110, 0b00000
    };
    lcdInit();
    lcdCommand(0x40);

    for (char i = 0; i < 48; i++) {
        lcdData(food[i]);
    }
    //Envia cada uma das linhas em ordem
    for (char i = 0; i < 16; i++) {
        lcdCommand(CLR);
        lcdCommand(L0 + i);
        lcdData(0);
        lcdData(1);
        lcdData(2);
        lcdCommand(L1 + i);
        lcdData(3);
        lcdData(4);
        lcdData(5);
        for (int j = 0; j < 20000; j++);
    }

    for (char i = 0; i < 5; i++) {
        if (i % 2 == 0) {
            lcdCommand(CLR);
            lcdCommand(0x80);
            lcdData(0);
            lcdData(1);
            lcdData(2);
            lcdCommand(0xC0);
            lcdData(3);
            lcdData(4);
            lcdData(5);

            lcdCommand(0x86);
            lcdData('H');
            lcdData('o');
            lcdData('r');
            lcdData('a');
            lcdData(' ');
            lcdData('d');
            lcdData('a');
            lcdCommand(0xC7);
            lcdData('r');
            lcdData('a');
            lcdData('c');
            lcdData('a');
            lcdData('o');
        } else {
            lcdCommand(CLR);
        }
        for (int j = 0; j < 30000; j++);
    }

}

void printHour(char pos, char hour[3], char minute[3]) {
    lcdCommand(pos);
    lcdData(hour[0]);
    lcdData(hour[1]);
    lcdData(':');
    lcdData(minute[0]);
    lcdData(minute[1]);
}

void printDaysSelected(char dia){
    for(char i=0; i<7; i++){
        if(bitTst(dia, i)){
            lcdCommand(L1 + 1 + 2*i);
            lcdData(223);
        }else{
            lcdData(' ');
        }
    }
}

void changeHours(char hora[3], char add) {
    if (add == 0) {
        if (hora[1] == '0') {
            if (hora[0] == '0') {
                hora[0] = '2';
                hora[1] = '3';
            } else {
                hora[1] = '9';
                hora[0]--;
            }
        } else {
            hora[1]--;
        }
    } else {
        if (hora[1] == '9') {
            hora[0]++;
            hora[1] = '0';
        } else if (hora[0] == '2' && hora[1] == '3') {
            hora[0] = '0';
            hora[1] = '1';
        } else {
            hora[1]++;
        }
    }
}

void changeMinutes(char minuto[3], char add) {
    if (add == 0) {
        if (minuto[1] == '0') {
            if (minuto[0] == '0') {
                minuto[0] = '5';
                minuto[1] = '9';
            } else {
                minuto[1] = '9';
                minuto[0]--;
            }
        } else {
            minuto[1]--;
        }
    } else {
        if (minuto[1] == '9') {
            if (minuto[0] == '5') {
                minuto[0] = '0';
                minuto[1] = '0';
            } else {
                minuto[0]++;
                minuto[1] = '0';
            }
        } else {
            minuto[1]++;
        }
    }
}

void newTime(signed char pos) {
    char msg[16];

    lcdCommand(CLR);
    lcdCommand(L0);
    strcpy(msg, "Nova refeicao: ");
    for (char j = 0; j < 15; j++) {
        lcdData(msg[j]);
    }

    lcdCommand(L1);
    lcdCommand(0xC0);
    strcpy(msg, "Hora: ");
    for (char j = 0; j < 6; j++) {
        lcdData(msg[j]);
    }
    printHour(0xCA ,hora, minuto);
    if(pos == 0){
        lcdCommand(0xC0 + 9);
        lcdCommand(ON);
    }else if(pos == 1){
        lcdCommand(0xC0 + 12);
        lcdCommand(ON);
    }
}

void newDay(signed char pos){
    char msg[16];

    lcdCommand(CLR);
    lcdCommand(L0);
    
    strcpy(msg, " D S T Q Q S S ");
    for (char j = 0; j < 15; j++) {
        lcdData(msg[j]);
    }
    
    printDaysSelected(dia);
    lcdCommand(ON);
    lcdCommand((char)(L1 + 1 + pos*2));
}