#include <xc.h>
#include "timers.h"

void init_timer2(void)
{
    //timer2 control register
    
  
    /*
     * // prescalar as 1:1
     */
   // T2CKPS1 = 1;
   // T2CKPS0 = 1;
    
    
    //no of ticks in PR2
    PR2 = 250;
    TMR2IE = 1;
    
    
    // clear timer2 int flag
   // TMR2IF = 1;
    TMR2ON =0;
    
    
    
    
}
