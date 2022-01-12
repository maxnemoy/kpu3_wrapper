// подключение необходимых заголовочных файлов
#include "threads.h"

// определение потока получающего данные с датчика давления
[[noreturn]] void sensorThread(void *kpuData)
{
  KpuData kpu = *(KpuData*)kpuData;
  while (true)
  {
    // запрос и сохранение данных
    kpu.menu->setValue(PSI_VALUE_ITEM, kpu.sensor->getPsi());
    kpu.menu->setValue(MMoM_VALUE_ITEM, kpu.sensor->getMillimetersOfMercury());
    // передача управления другому потоку
    vTaskDelay(pdMS_TO_TICKS(2));
  }
}
