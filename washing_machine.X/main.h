/* 
 * File:   main.h
 * Author: yenug
 *
 * Created on 24 June, 2025, 10:52 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#include <xc.h>
#include "clcd.h"
#include "digital_keypad.h"
#include"timers.h"
#include "washing_machine.h"

#define WASHING_PROGRAM_SCREEN     0x01
#define WATER_LEVEL_SCREEN         0x02
#define START_STOP_SCREEN          0x03
#define START_SCREEN               0x04
#define UPDATE_CYCLE_PHASE         0x05
       
#define RESET_WASH_PROGRAM_SCREEN  0x11
#define RESET_NOTHING              0xFF
#define RESET_WATER_LEVEL_SCREEN  0x22
#define RESET_START_STOP_SCREEN   0x33
#define RESET_START_PROGRAM       0x44
#define RESET_UNKNOW_SCREEN       0x55
#define PAUSE                     0x66

#define FAN_DDR              TRISC2
#define BUZZER_DDR           TRISC1

#define BUZZER             RC1
#define FAN                RC2

#define ON             1
#define OFF             0









#endif	/* MAIN_H */

