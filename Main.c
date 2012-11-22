//============================================================================//
//==                                                                        ==//
//==                         K-Junior Main Template                         ==//
//==                                                                        ==//
//============================================================================//
#include "KJunior.h"
#include "HemLinCam.h"
#include "Basic_functions.h"


#define  MUTE          0
#define  SOUND_LA     22
#define  LIMIT       500
#define  SLEEP_TIME  500

//----------------------------------------------------------------------------//
// Main program  




                       //
//----------------------------------------------------------------------------//
#separate
void main(void)
{
  //--- Initialization
  KJunior_init();
  HemLinCam_Init();
  unsigned int32 loopcontrol = 54;

  //_______________________________ Main loop __________________________________
  while (1)
  {
    // Test if a Serial Command was received and execute the selected function
    if((SerialCommandOK==1) && (Enable_RS232_Control==1)) SerialCommandHandler();

    //--------------------------------------------------------------------------
    //      ***  ADD YOUR CODE HERE (replace the following lines)  ***
    //--------------------------------------------------------------------------
 
 
   unsigned int32 before = KJunior_get_time();
   sleep_ms(4000);
   fprintf(USB, "sleep 4s : %Ld \r\n", (int32)KJunior_get_time() - before);
   
   rotate_no_move(10, 5);
   
   before = KJunior_get_time();
   sleep_ms(15000);
   fprintf(USB, "sleep 15s : %Ld  \r\n", (int32)KJunior_get_time() - before);
   
  }//end while true
  
}//end main 
