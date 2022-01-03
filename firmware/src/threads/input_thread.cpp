#include "threads.h"

[[noreturn]] void inputThread(void *kpuData)
{
  KpuData kpu = *(KpuData*)kpuData;
    
  while (true)
  {
    kpu.button->tick();

    kpu.menu->updateData();

    unsigned char result = kpu.encoder->process();
    if (result)
    {
      if (result == DIR_CW) kpu.menu->next();
      else kpu.menu->previous();
    }

    vTaskDelay(pdMS_TO_TICKS(2));
  }
}