#ifndef _THREADS_H
#define _THREADS_H

#include "kpu_data.h"

[[noreturn]] void displayThread(void* kpuData);

[[noreturn]] void inputThread(void *kpuData);

[[noreturn]] void sensorThread(void *kpuData);

[[noreturn]] void workThread(void *kpuData);

#endif