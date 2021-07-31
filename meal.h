/* 
 * File:   meal.h
 * Author: Usuario
 *
 * Created on July 15, 2021, 7:30 PM
 */

#ifndef MEAL_H
#define	MEAL_H
 
    char hora[3] = {'0', '0', '\0'}, minuto[3] = {'0', '0', '\0'}, dia;
    
    void mealFigure();
    void chooseMeal(char *dia, char hora[10]);
    void changeHours(char hora[3], char add);
    void changeMinutes(char minuto[3], char add);
    void changeDays(char dia, char add);
    void printDaysSelected(char dia);
    void newTime(signed char pos);
    void newDay(signed char pos);
    
#endif	/* MEAL_H */

