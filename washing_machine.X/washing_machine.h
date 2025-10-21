/* 
 * File:   washing_machine.h
 * Author: yenug
 *
 * Created on 24 June, 2025, 10:43 PM
 */

#ifndef WASHING_MACHINE_H
#define	WASHING_MACHINE_H

void power_on_screen(void);
void clear_screen(void);
void washing_program_display(unsigned char key);
void water_level_screen(unsigned char key);
void start_stop_screen(unsigned char key);
void start_screen(unsigned char key);
void set_time(void);
void update_cycle_phase(unsigned char key);
void pause(unsigned char key);
void door_check(void);


#endif	/* WASHING_MACHINE_H */

