#include "threads.h"

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