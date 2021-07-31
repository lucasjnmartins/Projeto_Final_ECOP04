#include "lcd.h"
#include "showNow.h"
#include "meal.h"

void showNow(char posTime, char time[10], char posDate, char date[10], char posDay, char day){
    lcdCommand(CLR);

    switch(day - 48){
        case 0:
            printDay("dom", posDay);
            break;
        case 1:
            printDay("seg", posDay);
            break;
        case 2:
            printDay("ter", posDay);
            break;
        case 3:
            printDay("qua", posDay);
            break;
        case 4:
            printDay("qui", posDay);
            break;
        case 5:
            printDay("sex", posDay);
            break;
        case 6:
            printDay("sab", posDay);
            break;
    }
    
    lcdCommand(posDate);
    for(char i=0; i<8; i++){
        lcdData(date[i]);
    }
    
    lcdCommand(posTime);
    for(char i=0; i<8; i++){
        lcdData(time[i]);
    }     
}

void printDay(char dia[4], char pos){
    lcdCommand(pos);
    for(char i=0; i<3; i++){
        lcdData(dia[i]);
    }
}



