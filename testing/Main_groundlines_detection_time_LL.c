#include "../KJunior.h"
#include "tv_remote_calibration.h"
#include "core.h"
#include "positionment.h"
#include "find_barcode.h"
#include "avoid_obstacles.h"
#include "tv_remote_calibration.h"
#include "../basic_functions.h"

#define BC_TIMEOUT (1000) //deux minutes


void main(void)
{ 
   
   // Initialization
   KJunior_init () ;
   HemLinCam_Init (); // currently all this does is sleeping for 1 second...
   KJunior_config_tv_remote_control (ENABLE);// Init camera settings and TV remote control
   
   /*while(1){
      find_barcode(1000 * 120);
      sleep_s(2);
   }*/
   //calibration
   calibrate_thresholds();
   //calibrate_camera();
   while (KJunior_get_tv_data() != TV_POWER);
   
   move_forward();
   
   while (1)
   {
      if((SerialCommandOK == 1) && (Enable_RS232_Control == 1))                    // Test if a Serial Command was received ...
         SerialCommandHandler();
      
      //while(1)
      debug();
      
      if (black_detected()) 
      {
         fprintf(USB, "        BLACK DETECTED\r\n");
         normal_state = 0;
         move_forward();
         
         //position straight in the axis of the black line
         if(!do_positioning()){
             normal_state = 1;
             continue;
         }

        //turns left or right depending on the line
      unsigned int8 direction = do_rotation_based_on_line();
       
        //if something went wrong, stops
      if(direction == -1){
         normal_state = 1;
         continue;
      }

       
      stop();
      unsigned int8 barcode = find_barcode(BC_TIMEOUT);
      if( barcode > 0 ){
         fprintf(USB, "PLAYING MUSIC N°%d", barcode);      
      }else{
         fprintf(USB, "TIMEOUT BARCODE N°%d", barcode);      
      }  
         
       //signed int8 bc = find_barcode();
       sleep_ms(800);
       do_rotation_back(direction);
       normal_state = 1;
       //avoids obstacles ignoring black until black is under the robot
       avoid_black_lines();
       
       sleep_s(1);
      
      } else {
         avoid_obstacles();        
      } // end if black_detected()
      
      sleep_ms(100);
      
   } // end while
} // end main
