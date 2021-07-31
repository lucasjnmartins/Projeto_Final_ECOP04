/* 
 * File:   list.h
 * Author: Usuario
 *
 * Created on July 20, 2021, 2:28 PM
 */

#ifndef LIST_H
#define	LIST_H

typedef enum {
    false, true
} boolean;

typedef struct {
    char dia, hora[3], minuto[3];
    boolean check;
    int fator;
} noData;
noData noTime;
noData meals[16];
char dispo = 0;

boolean insertMeal(char dia, char hora[3], char minuto[3]);
void removeMeal(char pos);
void turnIntoTime(char hora[10], char dia);
void listInit();
void showMeals(unsigned char pos);
void sortList();
void turnIntoTime(char hora[10], char dia);
boolean searchList(noData time);

#endif	/* LIST_H */

