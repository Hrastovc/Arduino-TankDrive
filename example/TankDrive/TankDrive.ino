/*___________________________________________________________________________________________________________________________________________________________________
 * This library was written for easy implementation of tank style driving into your Arduino project.
 * This example program in conbination with 4 BTS7960 chips can be used as an costum high voltage and high power ESC (up to 45V and 43A).
 * ___________________________________________________________________________________________________________________________________________________________________
 * Connection diagram:
 *              Arduino   |   BTS7960 module from ebay (IBT_2)
 * ---------------------------------------------------------------------
 * Module #1:             |
 *                  +5V ----> Vcc
 *                  GND <---- GND
 *           analog PIN <---- R_IS  //not required, not yet implemented
 *           analog PIN <---- L_IS  //not required, not yet implemented
 *   digital pin or +5V ----> R_EN  //enables the chips high side stage
 *   digital pin or +5V ----> L_EN  //enables the chips low side stage
 *   left motor forward ----> RPWM  //forward PWM signal
 *  left motor backward ----> LPWM  //backward PWM signal
 *                        |
 *  Module #2:            |
 *                  +5V ----> Vcc
 *                  GND <---- GND
 *           analog PIN <---- R_IS  //not required, not yet implemented
 *           analog PIN <---- L_IS  //not required, not yet implemented
 *   digital pin or +5V ----> R_EN  //enables the chips high side stage
 *   digital pin or +5V ----> L_EN  //enables the chips low side stage
 *  right motor forward ----> RPWM  //forward PWM signal
 * right motor backward ----> LPWM  //backward PWM signal
 *                        |
 * ---------------------------------------------------------------------
 * ___________________________________________________________________________________________________________________________________________________________________
 * Functions:
 *    - Signal(contactor pin);        This function returns signal info (0 --> "no signal", 1 --> "OK signal"),
 *                                    "contactor pin" can be used for a contactor of a powerstage ("no signal" -- > "contactor off", "OK signal" --> "contactor on").
 *    - setValues(CH num, CH val);    This function sets CH values, "CH num" range 1 to 2 and "CH val" range from -255 to 255.
 *    - getValues();                  This function reads PWM RC values. You have to connect RC PWM signals to pins to "CH_1 pin" and "CH_2 pin"
 *    - Drive();                      This function analyses x and y joystick coordinators' and generates PWM outputs
 * ___________________________________________________________________________________________________________________________________________________________________
 */

#include "Tank.h"

       //(RC PWM sig, RC PWM sig,            PWM pin,             PWM pin,             PWM pin,              PWM pin,     min and max pulse length in us,     min and max pulse length in us,    center pos threshold);
       //(  CH_1 pin,   CH_2 pin, left motor forward, left motor backward, right motor forward, right motor backward, ch1 min pulse in, ch1 max pulse in, ch2 min pulse in, ch2 max pulse in, center position (10-20));
Tank tank(         4,          7,                  3,                   5,                   6,                    9,             1000,             2000,             1000,             2000,                      10); 

void setup(){
  while(!tank.Signal(8)); //Waits for a signal
}

void loop(){
  tank.getValues();       //reads PWM RC signal from specified pins
  if(tank.Signal(8)){     //gets signal info
    tank.Drive();         //analyses x and y joystick coordinators and generates PWM outputs
  }
}
