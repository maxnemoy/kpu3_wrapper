#pragma once

#include "Arduino.h"

#define DIR_NONE 0x0
#define DIR_CW 0x10
#define DIR_CCW 0x20

class Rotary
{
  public:
    Rotary(char, char);
    unsigned char process();
    void begin(bool internalPullup=true, bool flipLogicForPulldown=false);
  private:
    unsigned char state;
    unsigned char pin1;
    unsigned char pin2;
    unsigned char inverter;
};
 

//////


#define R_START 0x0
#define R_CW_FINAL 0x1
#define R_CW_BEGIN 0x2
#define R_CW_NEXT 0x3
#define R_CCW_BEGIN 0x4
#define R_CCW_FINAL 0x5
#define R_CCW_NEXT 0x6

const unsigned char ttable[7][4] = {
  // R_START
  {R_START,    R_CW_BEGIN,  R_CCW_BEGIN, R_START},
  // R_CW_FINAL
  {R_CW_NEXT,  R_START,     R_CW_FINAL,  R_START | DIR_CW},
  // R_CW_BEGIN
  {R_CW_NEXT,  R_CW_BEGIN,  R_START,     R_START},
  // R_CW_NEXT
  {R_CW_NEXT,  R_CW_BEGIN,  R_CW_FINAL,  R_START},
  // R_CCW_BEGIN
  {R_CCW_NEXT, R_START,     R_CCW_BEGIN, R_START},
  // R_CCW_FINAL
  {R_CCW_NEXT, R_CCW_FINAL, R_START,     R_START | DIR_CCW},
  // R_CCW_NEXT
  {R_CCW_NEXT, R_CCW_FINAL, R_CCW_BEGIN, R_START},
};

Rotary::Rotary(char _pin1, char _pin2) {
  pin1 = _pin1;
  pin2 = _pin2;
  state = R_START;
  inverter = 0;
}

void Rotary::begin(bool internalPullup, bool flipLogicForPulldown) {
  if (internalPullup){
    pinMode(pin1,INPUT_PULLUP);
    pinMode(pin2,INPUT_PULLUP);
  }else{
    pinMode(pin1, INPUT);
    pinMode(pin2, INPUT);
  }
  inverter = flipLogicForPulldown ? 1 : 0;
}

unsigned char Rotary::process() {
  unsigned char pinstate = ((inverter ^ digitalRead(pin2)) << 1) | (inverter ^ digitalRead(pin1));
  state = ttable[state & 0xf][pinstate];
  return state & 0x30;
}