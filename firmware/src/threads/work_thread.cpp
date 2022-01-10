#include "threads.h"

[[noreturn]] void workThread(void *kpuData)
{
  KpuData kpu = *(KpuData*)kpuData;
  
  while (true)
  {
    //compress
    if(kpu.menu->getBoolValue(IS_RUN_ITEM) && !kpu.timer->isRun && kpu.menu->getFloatValue(CHANGES_ITEM) == 0.001f){
      float currentMm = kpu.menu->getFloatValue(MMoM_VALUE_ITEM);
      float comppressLimit = kpu.menu->getFloatValue(C_LIMIT_ITEM);
      float vacuumLimit = kpu.menu->getFloatValue(V_LIMIT_ITEM);
      float difference = kpu.menu->getFloatValue(CHANGES_ITEM);
      bool isVacuumMode = kpu.menu->getBoolValue(IS_VACUUM_ITEM);

      if(isVacuumMode){
        if(currentMm > vacuumLimit){
          kpu.motor->start(240); //TODO: setup speed
          continue;
        } else {
          kpu.motor->stop();
        }
      } else {
        if(currentMm < comppressLimit){
          kpu.motor->start(240);// TODO: setup speed
          continue;
        } else {
          kpu.motor->stop();
        }
      }
      
      //run timer 
      if(!kpu.timer->isRun && difference == 0.001f){
        if(isVacuumMode){
          kpu.menu->setValue(V_LIMIT_ITEM, currentMm);
        } else {
          kpu.menu->setValue(C_LIMIT_ITEM, currentMm);
        }
        kpu.timer->start();
      }
    }
    
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}