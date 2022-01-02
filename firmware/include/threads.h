#ifndef _THREADS_H
#define _THREADS_H

#include "kpu_data.h"

[[noreturn]] void displayThread(void* kpuData)
{
    KpuData kpu = *(KpuData*)kpuData;

    kpu.display->begin(SSD1306_SWITCHCAPVCC, 0x3C);
    kpu.display->clearDisplay();
    kpu.display->setTextSize(1, 2);
    kpu.display->setTextColor(SSD1306_WHITE);
    kpu.display->display();
    while (true)
    {
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
        kpu.display->display();
        vTaskDelay(pdMS_TO_TICKS(200));
        kpu.display->clearDisplay();
    }
}


[[noreturn]] void inputThread(void *kpuData)
{
  KpuData kpu = *(KpuData*)kpuData;
  kpu.encoder->begin(true, false);
  kpu.button->begin(25);
  
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

[[noreturn]] void sensorThread(void *kpuData)
{
  KpuData kpu = *(KpuData*)kpuData;
  
  while (true)
  {
    kpu.menu->setValue(PSI_VALUE_ITEM, kpu.sensor->getPsi());
    kpu.menu->setValue(MMoM_VALUE_ITEM, kpu.sensor->getMillimetersOfMercury());

    vTaskDelay(pdMS_TO_TICKS(300));
  }
}

#endif