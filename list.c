#include "meal.h"
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"
#include "bits.h"
#include <string.h>
#include "list.h"

void turnIntoTime(char hora[10], char dia) {
    noTime.dia = 0;
    noTime.dia |= (1 << (dia - 48));

    for (char j = 0; j < 2; j++) {
        noTime.hora[j] = hora[j];
        noTime.minuto[j] = hora[j + 3];
    }
    noTime.fator = (noTime.hora[0] - 48)*600 + (noTime.hora[1] - 48)*60 + 
            (noTime.minuto[0] - 48)*10 + (noTime.minuto[1] - 48);
}

void listInit() {
    for (char j = 0; j < 16; j++) {
        meals[j].fator = -1000;
    }
}

boolean insertMeal(char dia, char hora[3], char minuto[3]) {
    int fator = (hora[0] - 48)*600 + (hora[1] - 48)*60 + (minuto[0] - 48)*10 + (minuto[1] - 48);
    char i = dispo;
    if (i > 15) {
        lcdCommand(CLR);
        char msg1[16] = "Limite atingido,";
        char msg2[16] = "Remova lanches. ";
        lcdCommand(L0);
        for (char j = 0; j < 16; j++) {
            lcdData(msg1[i]);
        }
        lcdCommand(L1);
        for (char j = 0; j < 16; j++) {
            lcdData(msg2[i]);
        }
        for (unsigned int j = 0; j < 65000; j++);
        for (unsigned int j = 0; j < 65000; j++);
        for (unsigned int j = 0; j < 65000; j++);
        return false;
    } else {
        char msg1[9] = "Refeicao";
        char msg2[9] = "inserida";

        lcdCommand(CLR);
        lcdCommand(L0 + 3);
        for (char j = 0; j < 8; j++) {
            lcdData(msg1[j]);
        }
        lcdCommand(L1 + 3);
        for (char j = 0; j < 8; j++) {
            lcdData(msg2[j]);
        }
        lcdData(i + 48);
        for (unsigned int j = 0; j < 65000; j++);
        for (unsigned int j = 0; j < 65000; j++);
        for (unsigned int j = 0; j < 65000; j++);

        meals[dispo].dia = dia;
        meals[dispo].fator = fator;
        strcpy(meals[dispo].hora, hora);
        strcpy(meals[dispo].minuto, minuto);
        meals[dispo].check = true;
        
        lcdCommand(CLR);
        lcdCommand(L0 + 5);
        lcdData(meals[dispo].hora[0]);
        lcdData(meals[dispo].hora[1]);
        lcdData(':');
        lcdData(meals[dispo].minuto[0]);
        lcdData(meals[dispo].minuto[1]);
        char dias[7] = {'D', 'S', 'T', 'Q', 'Q', 'S', 'S'};
        for (char j = 0; j < 7; j++) {
            if (bitTst(meals[dispo].dia, j)) {
                lcdCommand(L1 + 1 + 2 * j);
                lcdData(dias[j]);
            } else {
                lcdData(' ');
            }
        }
        dispo++;
        sortList();
        for (unsigned int j = 0; j < 65000; j++);
        for (unsigned int j = 0; j < 65000; j++);
        for (unsigned int j = 0; j < 65000; j++);
        for (unsigned int j = 0; j < 65000; j++);
        for (unsigned int j = 0; j < 65000; j++);
        for (unsigned int j = 0; j < 65000; j++);
        return true;
    }

    lcdCommand(CLR);
    char msg1[16] = "Falha!";
    lcdCommand(L0);
    for (char j = 0; j < 6; j++) {
        lcdData(msg1[j]);
    }
    for (unsigned int j = 0; j < 65000; j++);
    for (unsigned int j = 0; j < 65000; j++);
    for (unsigned int j = 0; j < 65000; j++);
    return false;
}

void showMeals(unsigned char pos) {
    char dias[7] = {'D', 'S', 'T', 'Q', 'Q', 'S', 'S'};

    if (pos < dispo) {
        lcdCommand(CLR);
        lcdCommand(L0 + 5);
        lcdData(meals[pos].hora[0]);
        lcdData(meals[pos].hora[1]);
        lcdData(':');
        lcdData(meals[pos].minuto[0]);
        lcdData(meals[pos].minuto[1]);
        lcdData(' ');
        lcdData(pos+48);

        for (char i = 0; i < 7; i++) {
            if (bitTst(meals[pos].dia, i)) {
                lcdCommand(L1 + 1 + 2 * i);
                lcdData(dias[i]);
            } else {
                lcdData(' ');
            }
        }
    }else{
        lcdCommand(CLR);
        lcdData(pos+48);
        lcdData('>');
        lcdData(dispo+48);
    }
}

void sortList(){
    noData aux;
    for(char i=0; i<dispo; i++){
        for(char j=0; j < dispo-1-i; j++){
            if(meals[j].fator > meals[j+1].fator){     
                aux = meals[j];
                meals[j] = meals[j+1];
                meals[j+1] = aux;               
            }
        }        
    }
}

boolean searchList(noData time){
    char lim = dispo, i = 0, aux;
    while(i < lim){
        aux = (lim + i) / 2;
        if(meals[aux].fator > time.fator){
            i = aux + 1;
        }else if(meals[aux].fator < time.fator){
            lim = aux - 1;
        }else if((meals[aux].fator == time.fator) && (meals[aux].dia & time.dia)){
            return true;
        }else{
            return false;
        }
    }
    return false;
}

void removeMeal(char pos) {
    for(char i = pos; i < dispo; i++){
        meals[i] = meals[i + 1];
    }
    dispo--;
    lcdCommand(CLR);
    char msg1[12] = "Refeicao   ";
    char msg2[12] = "removida.  ";
    
    lcdCommand(L0);
    for(char i=0; i < 11; i++){
        lcdData(msg1[i]);
    }
    
    lcdCommand(L1);
    for(char i=0; i < 11; i++){
        lcdData(msg2[i]);
    }
    
    for (unsigned int j = 0; j < 65000; j++);
    for (unsigned int j = 0; j < 65000; j++);
    for (unsigned int j = 0; j < 65000; j++);
}
