# Arduino-TankDrive
___________________________________________________________________________________________________________________________________________________________________
This library was written for easy implementation of tank style driving into your Arduino project.
This example program in conbination with 4 BTS7960 chips can be used as an costum high voltage and high power ESC (up to 45V and 43A).
___________________________________________________________________________________________________________________________________________________________________
Functions:
   - Signal(contactor pin);        This function returns signal info (0 --> "no signal", 1 --> "OK signal"),
                                   "contactor pin" can be used for a contactor of a powerstage ("no signal" -- > "contactor off", "OK signal" --> "contactor on").
   - setValues(CH num, CH val);    This function sets CH values, "CH num" range 1 to 2 and "CH val" range from -255 to 255.
   - getValues();                  This function reads PWM RC values. You have to connect RC PWM signals to pins to "CH_1 pin" and "CH_2 pin"
   - Drive();                      This function analyses x and y joystick coordinators' and generates PWM outputs
___________________________________________________________________________________________________________________________________________________________________