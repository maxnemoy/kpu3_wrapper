// подключение необходимых заголовочных файлов
#include "threads.h"

// определение потока получения пользовательского ввода
[[noreturn]] void inputThread(void *kpuData)
{
  KpuData kpu = *(KpuData *)kpuData;
  while (true)
  {
    // обновление состояния кнопки
    kpu.button->tick();
    // обновление меню
    kpu.menu->updateData();
    // запрос состояния инкрементного энкодера
    unsigned char result = kpu.encoder->process();
    if (result) {
      if (!kpu.menu->getBoolValue(IS_RUN_ITEM)) { // если мы находимся в основном меню
        if (result == DIR_CW) kpu.menu->next(); // переход к следующей строке меню
        else kpu.menu->previous(); // переход к предыдущей строке меню
      }
    }
    // передача управления другому потоку
    vTaskDelay(pdMS_TO_TICKS(2));
  }
}