/*
 * File:   main.c
 * Author: yenug
 *
 * Created on 24 June, 2025, 10:09 PM
 */


#include "main.h"

#pragma config WDTE = OFF
unsigned char operational_mode = WASHING_PROGRAM_SCREEN;
unsigned char reset_flag = RESET_WASH_PROGRAM_SCREEN;

static void init_config(void) {
    init_clcd();
    init_digital_keypad();
    init_timer2();
    GIE = 1;
    PEIE = 1;
    //buzzer ,fan are output
    BUZZER_DDR = 0;
    FAN_DDR = 0;
    
    
    BUZZER = OFF;
    FAN = OFF;



}

void main(void) {
    init_config();
    unsigned char key;
    clcd_print("press key5 to", LINE1(1));
    clcd_print("power on", LINE2(5));
    clcd_print("washing machine", LINE3(1));


    while (1) {
        key = read_digital_keypad(STATE);
        if (key == SW5) {
            break;
        }
        __delay_ms(20);
    }


    clear_screen();
    power_on_screen();



    while (1) {

        key = read_digital_keypad(STATE);
        for (unsigned int delay = 1000; delay--;);


        for (unsigned int delay = 300; delay--;);
        if (key == LPSW4 && operational_mode == WASHING_PROGRAM_SCREEN) {
            operational_mode = WATER_LEVEL_SCREEN;
            reset_flag = RESET_WATER_LEVEL_SCREEN;


        } else if (key == LPSW4 && operational_mode == WATER_LEVEL_SCREEN) {
            operational_mode = START_STOP_SCREEN;
            reset_flag = RESET_START_STOP_SCREEN;
            set_time();


        }



        switch (operational_mode) {
            case WASHING_PROGRAM_SCREEN:
                washing_program_display(key);
                break;
            case WATER_LEVEL_SCREEN:
                water_level_screen(key);
                break;
            case START_STOP_SCREEN:
                start_stop_screen(key);
                break;
            case START_SCREEN:
                start_screen(key);
                break;
            case UPDATE_CYCLE_PHASE:
                //for (unsigned int delay = 1000; delay--;);
                update_cycle_phase(key);
                break;
            case PAUSE:
                pause(key);
                break;
        }


    }
    return;
}
