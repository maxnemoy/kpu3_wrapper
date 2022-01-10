#include "threads.h"

[[noreturn]] void timerThread(void *kpuData)
{
  KpuData kpu = *(KpuData*)kpuData;
  
  while (true)
  {
    if(kpu.timer->isRun){
        kpu.timer->tick();
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}