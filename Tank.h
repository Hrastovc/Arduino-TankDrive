/*
  TankDrive.h - Library for driving tank RC models.
  Created by Hrastovc, March 4, 2016.
*/
#ifndef Tank_h
#define Tank_h

#include "Arduino.h"

class Tank
{
  public:
    Tank (byte _chPIN_1, byte _chPIN_2, byte _left_motor_forward, byte _left_motor_backward, byte _right_motor_forward, byte _right_motor_backward, int _chPulse_min1, int _chPulse_max1, int _chPulse_min2, int _chPulse_max2, byte _eps);
    boolean Signal(byte contactor);
    void Drive();
    void getValues();
    void setValues(byte i, int val);
  private:
    void Motors (byte val_left_motor_forward, byte val_left_motor_backward, byte val_right_motor_forward, byte val_right_motor_backward);
    int backward_A;
    int backward_B;
    int PWMch[3];
    unsigned int PWMabs[3];
    unsigned int ch[3];
    byte chPIN[3];
    byte left_motor_forward;
    byte left_motor_backward;
    byte right_motor_forward;
    byte right_motor_backward;
    int chPulse_min[3];
    int chPulse_max[3];
    byte eps;
    boolean signal_info;
};

#endif
