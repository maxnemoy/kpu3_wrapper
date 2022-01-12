#ifndef _THREADS_H
#define _THREADS_H
// подключение необходимых заголовков
#include "kpu_data.h"
// объявления потока управления дисплеем
[[noreturn]] void displayThread(void* kpuData);
// объявления потока обработки пользовательского ввода
[[noreturn]] void inputThread(void *kpuData);
// объявления потока обработки данных с датчика давления
[[noreturn]] void sensorThread(void *kpuData);
// объявления потока рабочего состояния
[[noreturn]] void workThread(void *kpuData);
// объявления потока таймера
[[noreturn]] void timerThread(void *kpuData);

#endif