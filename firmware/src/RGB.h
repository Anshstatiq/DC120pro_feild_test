
#include <stddef.h>                     
#include <stdbool.h>                    
#include <stdlib.h>                     
#include "definitions.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"



#define RGB_BUFFER_LENGTH   1               //MAximum buffer length of RGB LED.
#define RED                 0x00            //Define to state & write duty cycle to timer for red color. 
#define GREEN               0x01            //Define to state & write duty cycle to timer for green color. 
#define BLUE                0x02            //Define to state & write duty cycle to timer for blue color. 
#define YELLOW              0x03            //Define to state & write duty cycle to timer for yellow color. 
#define CYAN                0x04            //Define to state & write duty cycle to timer for cyan color. 
#define MAGENTA             0x05            //Define to state & write duty cycle to timer for magenta color. 
#define ORANGE              0x06            //Define to state & write duty cycle to timer for orange color. 
#define YELLOW_GREEN        0x07            //Define to state & write duty cycle to timer for yellow-green color. 
#define CYAN_GREEN          0x08            //Define to state & write duty cycle to timer for cyan-green color. 
#define CYAN_BLUE           0x09            //Define to state & write duty cycle to timer for cyan-blue color. 
#define BLUE_MAGENTA        0x0A            //Define to state & write duty cycle to timer for blue-magenta color. 
#define RED_MAGENTA         0x0B            //Define to state & write duty cycle to timer for red-magenta color. 
#define GREEN_BLINK         0x0C            //Define to state & write duty cycle to timer for green blink color.


/**Typedef structure QUEUE for SENDING data to HMI **/
typedef struct
{
uint8_t RGB1_DATA[RGB_BUFFER_LENGTH];   //Variable to store data which needs to send to HMI queue.
} RGB1_SEND_Q;


typedef struct
{
uint8_t RGB2_DATA[RGB_BUFFER_LENGTH];   //Variable to store data which needs to send to HMI queue.
} RGB2_SEND_Q;




void GREEN_BLUE( uint16_t Compare_0_Value ,uint16_t Compare_1_Value);
void RED_t( uint16_t Compare_0_Value);
