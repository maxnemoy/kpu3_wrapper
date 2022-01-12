// подключение необходимых заголовочных файлов
#include "rotary.h"
// Определение конструктора
Rotary::Rotary(char _pin1, char _pin2) {
  pin1 = _pin1;
  pin2 = _pin2;
  state = R_START;
  inverter = 0;
}
// определение инициализации инкрементного энкодера
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
// определение функции проверки состояния инкрементного энкодера
unsigned char Rotary::process() {
  unsigned char pinstate = ((inverter ^ digitalRead(pin2)) << 1) | (inverter ^ digitalRead(pin1));
  state = ttable[state & 0xf][pinstate];
  return state & 0x30;
}