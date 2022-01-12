// подключение необходимых заголовочных файлов
#include "threads.h"

// определение потока управления дисплеем
[[noreturn]] void displayThread(void* kpuData)
{
    KpuData kpu = *(KpuData*)kpuData;
    // подготовка дисплея к работе
    kpu.display->begin(SSD1306_SWITCHCAPVCC, 0x3C);
    kpu.display->clearDisplay();
    kpu.display->setTextSize(1, 2);
    kpu.display->setTextColor(SSD1306_WHITE);
    kpu.display->display();
    while (true)
    {
      if(!kpu.menu->getBoolValue(IS_RUN_ITEM)){ // отображаем основное меню
        std::vector<String> items = kpu.menu->getMenu();
        int start = 0;
        int end = items.size();
        if(items.size() > 3) {
          start  = kpu.menu->index() - 1;
          if (start < 0) start = 0;
          end = kpu.menu->index() + 2;
          if(end > kpu.menu->index()-1) end = kpu.menu->index()-1;
        }
        int row = 0;
        for(int i = start; i < items.size(); i++){
          kpu.display->setCursor(0, row*20);
          kpu.display->println(items[i]);
          row++;
        }
      } else { // иначе отображаем рабочее меню
        kpu.display->setCursor(0, 0);
        //
        if(!kpu.timer->isRun && kpu.menu->getFloatValue(CHANGES_ITEM) == 0.001f){ // отображаем лимит давления/разряжения
          if(kpu.menu->getBoolValue(IS_VACUUM_ITEM)){
            kpu.display->println(kpu.menu->getFloatValue(V_LIMIT_ITEM));
          }else{
            kpu.display->println(kpu.menu->getFloatValue(C_LIMIT_ITEM));
          }
          kpu.display->setCursor(0, 20);
          kpu.display->println("LIMIT");
        } else { // иначе выводим разницу в измерениях
          kpu.display->println(kpu.menu->getFloatValue(CHANGES_ITEM));
          kpu.display->setCursor(0, 20);
          kpu.display->println("diff");
        }
        // отрисовка таймера
        if (kpu.timer->isRun) {
          kpu.display->clearDisplay();
          kpu.display->setCursor(0, 00);
          kpu.display->println(kpu.timer->getCurrent());
          kpu.display->setCursor(0, 20);
          kpu.display->println("SECOND");
        }
        // отрисовка текущего давления
        kpu.display->setCursor(60,0);
        kpu.display->println("|");
        kpu.display->setCursor(60,20);
        kpu.display->println("|");
        kpu.display->setCursor(70, 0);
        kpu.display->println(kpu.menu->getFloatValue(MMoM_VALUE_ITEM));
        kpu.display->setCursor(70, 20);
        kpu.display->println("CURRENT");
        // отрисовка строки выхода в главное меню
        kpu.display->setCursor(0, 50);
        kpu.display->println("double click to exit");
      }
      // отображение информации на дисплее
      kpu.display->display();
      // передача управления другому потоку
      vTaskDelay(pdMS_TO_TICKS(200));
      // очистка дисплея
      kpu.display->clearDisplay();
    }
}