/*
  TankDrive - Library for draving tank RC models.
  Created by Hrastovc, March 4, 2016.
*/
#include "Arduino.h"
#include "Tank.h"

Tank::Tank(byte _chPIN_1, byte _chPIN_2, byte _left_motor_forward, byte _left_motor_backward, byte _right_motor_forward, byte _right_motor_backward, int _chPulse_min1, int _chPulse_max1, int _chPulse_min2, int _chPulse_max2, byte _eps){

  chPIN[1] = _chPIN_1;
  chPIN[2] = _chPIN_2;
  left_motor_forward = _left_motor_forward;
  left_motor_backward = _left_motor_backward;
  right_motor_forward = _right_motor_forward;
  right_motor_backward = _right_motor_backward;
  chPulse_min[1] = _chPulse_min1;
  chPulse_max[1] = _chPulse_max1;
  chPulse_min[2] = _chPulse_min2;
  chPulse_max[2] = _chPulse_max2;
  eps = _eps;

  pinMode(_chPIN_1, INPUT);
  pinMode(_chPIN_2, INPUT);
  pinMode(left_motor_forward, OUTPUT);
  pinMode(left_motor_backward, OUTPUT);
  pinMode(right_motor_forward, OUTPUT);
  pinMode(right_motor_backward, OUTPUT);
}

void Tank::Drive(){
  if(ch[1]==0 || ch[2]==0) {
    Motors (0, 0, 0, 0);
  }else{
    if(PWMch[1]>-eps && PWMch[1]<eps && PWMch[2]>-eps && PWMch[2]<eps)
      Motors(0, 0, 0, 0);
      
    if(PWMch[1]<eps && PWMch[1]>-eps && PWMch[2]>eps)
      Motors(PWMabs[2], 0, PWMabs[2], 0);
      
    if(PWMch[1]<eps && PWMch[1]>-eps && PWMch[2]<-eps)
      Motors(0, PWMabs[2], 0, PWMabs[2]);
      
    if(PWMch[1]>eps && PWMch[2]<eps && PWMch[2]>-eps)
      Motors(0, PWMabs[1], PWMabs[1], 0);
      
    if(PWMch[1]<-eps && PWMch[2]<eps && PWMch[2]>-eps)
      Motors (PWMabs[1], 0, 0, PWMabs[1]);
      
    if(PWMch[1]>eps && PWMch[2]>eps && PWMabs[1]>PWMabs[2]+eps) 
      Motors(0, PWMabs[1]-PWMabs[2], PWMabs[1], 0);
      
    if(PWMch[1]>eps && PWMch[2]>eps && PWMabs[1]+eps<PWMabs[2])
      Motors(PWMabs[2]-PWMabs[1], 0, PWMabs[2], 0);
      
    if(PWMch[1]>eps && PWMch[2]>eps && PWMabs[1]-PWMabs[2]<2*eps && PWMabs[2]-PWMabs[1]<2*eps)
      Motors(0, 0, PWMabs[2], 0);
      
    if(PWMch[1]<-eps && PWMch[2]>eps && PWMabs[1]>PWMabs[2]+eps)
      Motors(PWMabs[1], 0, 0, PWMabs[1]-PWMabs[2]);
      
    if(PWMch[1]<-eps && PWMch[2]>eps && PWMabs[1]+eps<PWMabs[2])
      Motors(PWMabs[2], 0, PWMabs[2]-PWMabs[1], 0);
      
    if(PWMch[1]<-eps && PWMch[2]>eps && PWMabs[1]-PWMabs[2]<2*eps && PWMabs[2]-PWMabs[1]<2*eps)
      Motors(PWMabs[1], 0, 0, 0);
      
    if(PWMch[1]>eps && PWMch[2]<-eps && PWMabs[1]>PWMabs[2]+eps && PWMabs[2]<85)
      Motors(0, backward_A, backward_A, 0);
      
    if(PWMch[1]>eps && PWMch[2]<-eps && PWMabs[1]>PWMabs[2]+eps && PWMabs[2]>170)
      Motors(backward_B, 0, 0, backward_B);
      
    if(PWMch[1]>eps && PWMch[2]<-eps && PWMabs[1]+eps<PWMabs[2])
      Motors(0, PWMabs[1], 0, PWMabs[2]);
      
    if(PWMch[1]>eps && PWMch[2]<-eps && PWMabs[1]-PWMabs[2]<2*eps && PWMabs[2]-PWMabs[1]<2*eps)
      Motors(0, 0, 0, PWMabs[2]);
      
    if(PWMch[1]<-eps && PWMch[2]<-eps && PWMabs[1]>PWMabs[2]+eps && PWMabs[2]<85)
      Motors(backward_A, 0, 0, backward_A);
      
    if(PWMch[1]<-eps && PWMch[2]<-eps && PWMabs[1]>PWMabs[2]+eps && PWMabs[2]>170)
      Motors(0, backward_B, backward_B, 0);
      
    if(PWMch[1]<-eps && PWMch[2]<-eps && PWMabs[1]+eps<PWMabs[2])
      Motors(0, PWMabs[2], 0, PWMabs[1]);
      
    if(PWMch[1]<-eps && PWMch[2]<-eps && PWMabs[1]-PWMabs[2]<2*eps && PWMabs[2]-PWMabs[1]<2*eps)
      Motors(0, PWMabs[2], 0, 0);
  }
}

void Tank::getValues(){
  ch[1] = pulseIn(chPIN[1], HIGH);
  ch[2] = pulseIn(chPIN[2], HIGH);
  if(ch[1] == 0 || ch[2] == 0){
    signal_info = 0;
    PWMch[1] = 0;
    PWMch[2] = 0;
  }else{
    signal_info = 1;
    PWMch[1] = constrain(map(ch[1], chPulse_min[1], chPulse_max[1], -255, 255), -255, 255);
    PWMch[2] = constrain(map(ch[2], chPulse_min[2], chPulse_max[2], -255, 255), -255, 255);
    PWMabs[1] = abs(PWMch[1]);
    PWMabs[2] = abs(PWMch[2]);
    backward_A = constrain(((PWMabs[1]-PWMabs[2]-133) *2), 0, 255);
    backward_B = constrain(((PWMabs[1]-PWMabs[2]) *2), 0, 255);
  }
}

void Tank::setValues(byte i, int val){
  i = constrain(i, 1, 2);
  PWMch[i] = constrain(val, -255, 255);
}

void Tank::Motors (byte val_left_motor_forward, byte val_left_motor_backward, byte val_right_motor_forward, byte val_right_motor_backward) {
  analogWrite(left_motor_forward, val_left_motor_forward);
  analogWrite(left_motor_backward, val_left_motor_backward);
  analogWrite(right_motor_forward, val_right_motor_forward);
  analogWrite(right_motor_backward, val_right_motor_backward);
}

boolean Tank::Signal (byte contactor) {
  pinMode(contactor, OUTPUT);
  if(signal_info == 0){
    digitalWrite(contactor, LOW);
    return 0;
  }else{
    digitalWrite(contactor, HIGH);
    return 1;
  }
}
