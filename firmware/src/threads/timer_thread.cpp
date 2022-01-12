// подключение необходимых заголовочных файлов
#include "threads.h"

// определение потока таймера
[[noreturn]] void timerThread(void *kpuData)
{
  KpuData kpu = *(KpuData*)kpuData;
  while (true)
  {
    // шаг таймера
    if(kpu.timer->isRun){
        kpu.timer->tick();
    }
    // передача управления другому потоку
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}