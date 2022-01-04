#include "threads.h"

[[noreturn]] void workThread(void *kpuData)
{
  KpuData kpu = *(KpuData*)kpuData;
  
  while (true)
  {
    if(kpu.menu->getBoolValue(IS_RUN_ITEM)){
      float currentMm = kpu.menu->getFloatValue(MMoM_VALUE_ITEM);
      float comppressLimit = kpu.menu->getFloatValue(C_LIMIT_ITEM);
      float vacuumLimit = kpu.menu->getFloatValue(V_LIMIT_ITEM);
      bool isVacuumMode = kpu.menu->getBoolValue(IS_VACUUM_ITEM);
      if(isVacuumMode){
        if(currentMm > vacuumLimit){
          kpu.motor->start(1); //TODO: setup speed
        } else {
          kpu.motor->stop();
        }
      } else {
        if(currentMm < comppressLimit){
          kpu.motor->start(1);// TODO: setup speed
        } else {
          kpu.motor->stop();
        }
      }
    }
    
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}