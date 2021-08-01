#include "start.h"
#include "lcd.h"
#include "keypad.h"
#include "rtc.h"
#include "bits.h"
#include "meal.h"
#include "list.h"
#include "showNow.h"
#include "pwm.h"
#include "adc.h"
#include <pic18f4520.h>

void main() {
    TRISA = 0x00;
    TRISB = 0x0f;
    TRISC = 0x00;
    TRISE = 0x00;
    PORTC = 0x00;
    PORTE = 0x00;
    PORTA = 0x00;
    PORTB = 0x00;
    lcdInit();
    pwmInit();
    kpInit();
    listInit();
    char str[2];
    signed char op = -1, flagOp = -1, contDay;
    volatile unsigned char tecla;
    unsigned char pwm = 0, posMeal = 0, water = 0, meal = 0;
    unsigned int cont = 0, aux;



    for (;;) {
        for (;;) { //Esperando para ligar
            kpDebounce();
            if (tecla != kpRead()) {
                tecla = kpRead();
                if (bitTst(tecla, 0)) {
                    welcome();
                    op = 0;
                    break;
                }
            }
            for (int k = 0; k < 1000; k++);
        }


        //Ligado
        for (;;) {
            kpInit();
            kpDebounce();
            if (tecla != kpRead()) {
                tecla = kpRead();

                ////////////////////////////////// DESLIGA A ESTACAUM ////////////////////////////////////////////
                if (bitTst(tecla, 0)) {
                    op = -1;
                    pwmSet(0);
                    PORTCbits.RC0 = 0;
                    PORTEbits.RE0 = 0;
                    PORTB = 0;
                    lcdCommand(CLR);
                    bye();
                    break;
                }


                ///////////////////////////// MUDA OS MENUS ////////////////////////////////////////
                if (bitTst(tecla, 3)) {
                    op++;

                    //op = 0 mostra as horas e o dia atuais
                    if (op == 0) {
                        cont = 0;
                    }

                    //Entra no local para adicionar alarme
                    if (op == 1) {
                        flagOp = -1;
                        newTime(flagOp);
                    }

                    //Mostra as refeicoes ja inseridas
                    if (op == 2) {
                        posMeal = 0;
                        hora[0] = '0';
                        hora[1] = '0';
                        minuto[0] = '0';
                        minuto[1] = '0';
                        dia = 0;
                        lcdCommand(OFF);
                        lcdInit();
                    }

                    //permite a mudanca do pwm e o mostra na tela
                    if (op == 3) {
                        showPWM(pwm);
                    }

                    //reinicia
                    if (op == 4) {
                        op = 0;
                    }
                }


                ///////////////////////////////////// TECLA 2 ///////////////////////////////////////////                
                if (bitTst(tecla, 7)) {
                    if (op == 1) {
                        flagOp++;
                        if (flagOp > 2) {
                            insertMeal(dia, hora, minuto);

                            hora[0] = '0';
                            hora[1] = '0';
                            minuto[0] = '0';
                            minuto[1] = '0';
                            dia = 0;
                            lcdCommand(OFF);
                            flagOp = -1;
                            lcdInit();
                            newTime(flagOp);
                        }
                        lcdCommand(CLR);

                        newTime(flagOp);
                        if (flagOp == 2) {
                            newDay(contDay);
                        }
                    }
                    
                    //TECLA 2
                    if (op == 2) {
                        removeMeal(posMeal);
                        if(posMeal == dispo){
                            posMeal--;
                        }
                    }
                }


                ///////////////////////////// TECLA 2 //////////////////////////////////////////
                if (bitTst(tecla, 2)) {
                    //Ajusta as horas
                    if (op == 1 && flagOp == 0) {
                        changeHours(hora, 0);
                        newTime(flagOp);
                    }

                    //Ajusta os minutos
                    if (op == 1 && flagOp == 1) {
                        changeMinutes(minuto, 0);
                        newTime(flagOp);
                    }

                    //Ajusta os dias da semana
                    if (op == 1 && flagOp == 2) {
                        bitFlp(dia, contDay);
                        printDaysSelected(dia);
                        lcdCommand(ON);
                        lcdCommand((char) (L1 + 1 + contDay * 2));
                    }
                    
                    //TECLA 4
                    if (op == 2) {
                        if (dispo == 0) {
                            lcdCommand(CLR);
                            lcdCommand(L0);
                            char msg1[16] = "Sem refeicoes!  ";
                            for (char i = 0; i < 16; i++)
                                lcdData(msg1[i]);
                        }
                    } else {
                        if (posMeal > 0) {
                            posMeal--;
                        } else {
                            posMeal = dispo - 1;
                        }
                    }
                }


                ///////////////////////////////////// TECLA 6 /////////////////////////////////////////////////
                if (bitTst(tecla, 6)) {
                    //muda horas
                    if (op == 1 && flagOp == 0) {
                        changeHours(hora, 1);
                        newTime(flagOp);
                    }

                    //muda minutos
                    if (op == 1 && flagOp == 1) {
                        changeMinutes(minuto, 1);
                        newTime(flagOp);
                    }

                    //muda dias
                    if (op == 1 && flagOp == 2) {
                        contDay++;
                        if (contDay > 6) {
                            contDay = 0;
                        }
                        newDay(contDay);
                    }
                    
                    //TECLA 5
                    if (op == 2) {
                        if (dispo == 0) {
                            lcdCommand(CLR);
                            lcdCommand(L0);
                            char msg1[16] = "Sem refeicoes!  ";
                            for (char i = 0; i < 16; i++) {
                                lcdData(msg1[i]);
                            }
                        } else {
                            if (posMeal < (dispo - 1)) {
                                posMeal++;
                            } else {
                                posMeal = 0;
                            }
                        }
                    }
                }

                // Simula que o pote de racao ficou vazio ///
                if (bitTst(tecla, 1)) {
                    bitClr(PORTB, 4);
                    bitClr(PORTB, 5);
                    meal = 0;
                }
                if (bitTst(tecla, 5)) {
                    bitClr(PORTB, 6);
                    bitClr(PORTB, 7);
                    water = 0;
                }
            }

            /////////////////////////////// ATUALIZACOES DOS MENUS //////////////////////////////////////

            if (cont % 2000 == 0) {
                rtc_r();
                turnIntoTime(time, day);

                if (searchList(noTime)) {
                    PORTCbits.RC0 = 1;
                    if (!bitTst(PORTB, 5)) {
                        if (meal == 0) {
                            mealFigure();
                        }
                        meal++;
                    }
                }
                if (meal > 1 && meal < 4) {
                    bitSet(PORTB, 4);
                } else if (meal > 3) {
                    bitSet(PORTB, 5);
                    PORTCbits.RC0 = 0;
                }
            }

            if (cont % 1000 == 0) {
                if (water < 3) {
                    PORTEbits.RE0 = 1;
                }
                if(bitTst(PORTE, 0)) water++;

                if (water > 3 && water < 8) {
                    bitSet(PORTB, 6);
                } else if (water > 8) {
                    bitSet(PORTB, 7);
                    PORTEbits.RE0 = 0;
                }
            }

            //Mostra a hora atual se op = 0
            if (op == 0) {
                if (cont % 300 == 0) {
                    rtc_r();
                    showNow(0xC4, (char *) time, 0x87, (char *) date, 0x80, (char) day);
                }
            }

            if (op == 1) {
                if (cont % 4000 == 0) {
                    if (flagOp == 2) {
                        newDay(contDay);
                    } else {
                        newTime(flagOp);
                    }
                }
            }

            if ((op == 2) && (cont % 300 == 0)) {
                if (dispo == 0) {
                    lcdCommand(CLR);
                    lcdCommand(L0);
                    char msg1[18] = "Sem refeicoes.   ";
                    for (char i = 0; i < 16; i++) {
                        lcdData(msg1[i]);
                    }
                } else {
                    showMeals(posMeal);
                }
            }

            if (op == 3) {
                if (cont % 500 == 0) {
                    itoa(((adc_amostra(0) * 10) 
                            / 204), str);
                    pwm = (str[0] - 48)*20 + 
                            (str[1] - 48)*2;
                    pwmSet(pwm);
                    showPWM(pwm);
                }
            }

            if (cont % 4000 == 0) {
                cont = 4000;
            }
            cont--;
        }
    }
}
