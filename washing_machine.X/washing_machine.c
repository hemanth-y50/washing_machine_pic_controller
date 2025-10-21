/*
 * File:   washing_machine.c
 * Author: yenug
 *
 * Created on 24 June, 2025, 10:42 PM
 */


#include"main.h"
extern unsigned char reset_flag;
extern unsigned char operational_mode;
char *washing_program[] = {
    "Daily",
    "Heavy",
    "Dedicates",
    "Whites",
    "Stain wash",
    "EcoCottons",
    "Woolens",
    "Bed sheets",
    "Rinse + Dry",
    "Dry only",
    "Wash only",
    "Aqua store"
};
char *water_level[] = {
    "Auto",
    "Low",
    "Medium",
    "High",
    "Max"
};
unsigned char program_no = 0;
unsigned char level = 0;
unsigned char sec, min;
unsigned int total_time, wash_time, rinse_time, spin_time, time;

void power_on_screen(void) {

    for (unsigned char i = 0; i < 16; i++) {
        // your code here
        clcd_putch(BLOCK, LINE1(i));

        __delay_ms(100);
    }

    clcd_print("powering on", LINE2(3));
    clcd_print("washing machine", LINE3(1));

    for (unsigned char i = 0; i < 16; i++) {
        // your code here
        clcd_putch(BLOCK, LINE4(i));
        __delay_ms(100);
    }

    __delay_ms(2000);


}

void clear_screen(void) {

    clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
    __delay_us(500);


}

void washing_program_display(unsigned char key) {
    if (reset_flag == RESET_WASH_PROGRAM_SCREEN) {

        clear_screen();
        reset_flag = RESET_NOTHING;

    }
    if (key == SW4) {
        clear_screen();
        program_no++;
        if (program_no == 12) {
            program_no = 0;
        }
    }
    clcd_print("Washing Program", LINE1(1));
    clcd_print("*", LINE2(0));
    if (program_no <= 9) {

        clcd_print(washing_program[program_no], LINE2(1));
        clcd_print(washing_program[program_no + 1], LINE3(1));
        clcd_print(washing_program[program_no + 2], LINE4(1));

    } else if (program_no == 10) {

        clcd_print(washing_program[program_no], LINE2(1));
        clcd_print(washing_program[program_no + 1], LINE3(1));
        clcd_print(washing_program[0], LINE4(1));

    } else if (program_no == 11) {

        clcd_print(washing_program[program_no], LINE2(1));
        clcd_print(washing_program[0], LINE3(1));
        clcd_print(washing_program[1], LINE4(1));

    }


}

void water_level_screen(unsigned char key) {

    if (reset_flag == RESET_WATER_LEVEL_SCREEN) {
        clear_screen();
        reset_flag = RESET_NOTHING;
    }

    if (key == SW4) {
        clear_screen();
        level++;
        if (level == 5) {
            level = 0;
        }
    }
    clcd_print("WATER_LEVEL:", LINE1(0));
    clcd_print("*", LINE2(0));


    clcd_print(water_level[level], LINE2(1));
    clcd_print(water_level[(level + 1) % 5], LINE3(1));
    clcd_print(water_level[(level + 2) % 5], LINE4(1));




}

void start_stop_screen(unsigned char key) {

    if (reset_flag == RESET_START_STOP_SCREEN) {
        clear_screen();
        reset_flag = RESET_NOTHING;
    }

    clcd_print("Press Switch:", LINE1(1));
    clcd_print("SW5:START", LINE2(1));
    clcd_print("SW6:STOP", LINE3(1));
    if (key == SW5) {
        operational_mode = START_SCREEN;
        reset_flag = RESET_START_PROGRAM;

    } else if (key == SW6) {

        operational_mode = WASHING_PROGRAM_SCREEN;
        reset_flag = RESET_WASH_PROGRAM_SCREEN;
    }

}

void start_screen(unsigned char key) {
    
   
    if (reset_flag == RESET_START_PROGRAM) {

        clear_screen();
        reset_flag = RESET_NOTHING;

    }
    clcd_print("prog:", LINE1(0));
    clcd_print(washing_program[program_no], LINE1(6));
    clcd_print("time:", LINE2(0));
    clcd_putch(min / 10 + '0', LINE2(6));
    clcd_putch(min % 10 + '0', LINE2(7));
    clcd_putch(':', LINE2(8));
    clcd_putch(sec / 10 + '0', LINE2(9));
    clcd_putch(sec % 10 + '0', LINE2(10));

    total_time = time = min * 60 + sec;

    wash_time = (int) (total_time * 0.46);
    rinse_time = (int) (total_time * 0.12);
    spin_time = (int) (total_time * 0.42);
    __delay_ms(1000);
    TMR2ON = 1;
    FAN = ON;
    
    reset_flag = RESET_UNKNOW_SCREEN;
    operational_mode = UPDATE_CYCLE_PHASE;


    //TMR2IF = 0;





}

void pause(unsigned char key){
    
     
   
    __delay_ms(100);
    
     if (key == SW5) {
                    TMR2ON = ON;
                    FAN = ON;
                    operational_mode = UPDATE_CYCLE_PHASE;

                }
    
}


void update_cycle_phase(unsigned char key) {
    
    
    
    if (reset_flag == RESET_UNKNOW_SCREEN) {
        clear_screen();
        reset_flag = RESET_NOTHING;
    }
door_check();
 //   __delay_ms(100);

    if (key == SW6) {
        TMR2ON = 0;
        FAN = OFF;
        operational_mode = PAUSE;
    }
    
    
    total_time = min * 60 + sec;


    clcd_print("__program:", LINE1(0));


    if (program_no <= 7) {
        if (total_time >= (time - wash_time)) {
            clcd_print("wash", LINE1(10));
        } else if (total_time >= (time - wash_time - spin_time)) {
            clcd_print("rinse", LINE1(10));
        } else {
            clcd_print("spin", LINE1(10));
        }
    } else if (program_no == 8) {
        if (total_time >= (time - (unsigned char) (0.4 * time))) {
            clcd_print("rinse", LINE1(10));
        } else {
            clcd_print("spin", LINE1(10));
        }
    } else if (program_no == 9) {
        clcd_print("spin", LINE1(10));
    } else {
        clcd_print("wash", LINE1(10));
    }

    clcd_print("TIME:", LINE2(0));
    clcd_putch(min / 10 + '0', LINE2(6));
    clcd_putch(min % 10 + '0', LINE2(7));
    clcd_putch(':', LINE2(8));
    clcd_putch(sec / 10 + '0', LINE2(9));
    clcd_putch(sec % 10 + '0', LINE2(10));
    clcd_print("S5:START", LINE3(0));
    clcd_print(" S6:PAUSE", LINE4(0));
    if (min == 0 && sec == 0) {
        clear_screen();
        FAN = OFF;
        BUZZER = ON;
        clcd_print("program completed", LINE1(0));
        clcd_print("REMOVE CLOTHS", LINE2(0));
        BUZZER = OFF;
        __delay_ms(3000);
        operational_mode = WASHING_PROGRAM_SCREEN;
        reset_flag = RESET_WASH_PROGRAM_SCREEN;


    }

}
void door_check(){
    if (RB0 == 0){
        FAN=OFF;
        TMR2ON=OFF;
        BUZZER=ON;
        clear_screen();
        clcd_print("door is ",LINE1(0));
        clcd_print("OPENED ",LINE2(0));
        clcd_print("PLEASE CLOSE",LINE3(0));
        while(RB0 == 0){
            ;
        }
        FAN=ON;
        TMR2ON=ON;
        BUZZER=OFF;
        clear_screen();
        clcd_print("__program:", LINE1(0));
        clcd_print("TIME:", LINE2(0));
        clcd_print("S5:START", LINE3(0));
    clcd_print(" S6:PAUSE", LINE4(0));
        
        
        
    }
}

void set_time(void) {
    switch (program_no) {
        case 0: //Daily
            switch (level) {
                case 1:
                    min = 0;
                    sec = 33;
                    break;
                case 0:
                case 2:
                    min = 0;
                    sec = 41;
                    break;
                case 3:
                case 4:
                    min = 0;
                    sec = 45;
                    break;
            }
            break;
        case 1:
            switch (level) {
                case 1:
                    min = 0;
                    sec = 43;
                    break;
                case 0:
                case 2:
                    min = 0;
                    sec = 50;
                    break;
                case 3:
                case 4:
                    min = 0;
                    sec = 57;
                    break;
            }
            break;
        case 2:
            switch (level) {
                case 1:
                case 0:
                case 2:
                    min = 0;
                    sec = 26;
                    break;
                case 3:
                case 4:
                    min = 0;
                    sec = 31;
                    break;
            }
            break;
        case 3:
            switch (level) {
                case 1:
                case 0:
                case 2:
                case 3:
                case 4:
                    min = 1;
                    sec = 16;
                    break;
            }
            break;
        case 4:
            switch (level) {
                case 1:
                case 0:
                case 2:
                case 3:
                case 4:
                    min = 1;
                    sec = 36;
                    break;
            }
            break;
        case 5:
            switch (level) {
                case 1:
                case 0:
                case 2:
                    min = 0;
                    sec = 31;
                    break;
                case 3:
                case 4:
                    min = 0;
                    sec = 36;
                    break;
            }
        case 6:
            switch (level) {
                case 1:
                case 0:
                case 2:
                case 3:
                case 4:
                    min = 0;
                    sec = 29;
                    break;
            }
            break;
        case 7:
            switch (level) {
                case 1:
                    min = 0;
                    sec = 46;
                    break;
                case 0:
                case 2:
                    min = 0;
                    sec = 53;
                    break;
                case 3:
                case 4:
                    min = 0;
                    sec = 60;
                    break;
            }
            break;
        case 8:
            switch (level) {
                case 1:
                    min = 0;
                    sec = 18;
                    break;
                case 0:
                case 2:
                case 3:
                case 4:
                    min = 0;
                    sec = 20;
                    break;
            }
            break;
        case 9:
            switch (level) {
                case 1:
                case 0:
                case 2:
                case 3:
                case 4:
                    min = 0;
                    sec = 6;
                    break;
            }
            break;
        case 10:
            switch (level) {
                case 1:
                    min = 0;
                    sec = 16;
                    break;
                case 0:
                case 2:
                    min = 0;
                    sec = 21;
                    break;
                case 3:
                case 4:
                    min = 0;
                    sec = 26;
                    break;
            }
            break;
        case 11:
            switch (level) {
                case 1:
                case 0:
                case 2:
                case 3:
                case 4:
                    min = 0;
                    sec = 6;
                    break;
            }
            break;

















    }




}

