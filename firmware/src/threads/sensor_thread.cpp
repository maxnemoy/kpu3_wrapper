#include "threads.h"

[[noreturn]] void sensorThread(void *kpuData)
{
  KpuData kpu = *(KpuData*)kpuData;
  
  while (true)
  {
    kpu.menu->setValue(PSI_VALUE_ITEM, kpu.sensor->getPsi());
    kpu.menu->setValue(MMoM_VALUE_ITEM, kpu.sensor->getMillimetersOfMercury());

    vTaskDelay(pdMS_TO_TICKS(2));
  }
}
