// подключение необходимых заголовочных файлов
#include "threads.h"
// определение основного рабочего потока
[[noreturn]] void workThread(void *kpuData)
{
  KpuData kpu = *(KpuData*)kpuData;
  while (true)
  {
    // точка входа в основной цикл рабочей программы
    if(kpu.menu->getBoolValue(IS_RUN_ITEM) && !kpu.timer->isRun && kpu.menu->getFloatValue(CHANGES_ITEM) == 0.001f){
      // получение входных данных
      float currentMm = kpu.menu->getFloatValue(MMoM_VALUE_ITEM);
      float comppressLimit = kpu.menu->getFloatValue(C_LIMIT_ITEM);
      float vacuumLimit = kpu.menu->getFloatValue(V_LIMIT_ITEM);
      float difference = kpu.menu->getFloatValue(CHANGES_ITEM);
      bool isVacuumMode = kpu.menu->getBoolValue(IS_VACUUM_ITEM);
      //управление мотором
      if(isVacuumMode){
        if(currentMm > vacuumLimit){
          kpu.motor->start(240);
          continue;
        } else {
          kpu.motor->stop();
        }
      } else {
        if(currentMm < comppressLimit){
          kpu.motor->start(240);
          continue;
        } else {
          kpu.motor->stop();
        }
      }
      //запуск таймера при нагнетании/разряжении давления
      if(!kpu.timer->isRun && difference == 0.001f){
        // обновление лимитов на фактически показания датчика
        if(isVacuumMode){
          kpu.menu->setValue(V_LIMIT_ITEM, currentMm);
        } else {
          kpu.menu->setValue(C_LIMIT_ITEM, currentMm);
        }
        kpu.timer->start();
      }
    }
    //передача управления другому патоку
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}