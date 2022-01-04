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
      if(!kpu.menu->getBoolValue(IS_RUN_ITEM)){ //show menu
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
      } else { //show run mode 
      ////////////
      //// 10 | 10
      //// exit
        kpu.display->setCursor(0, 0);
        if(kpu.menu->getBoolValue(IS_VACUUM_ITEM)){
          kpu.display->println(kpu.menu->getFloatValue(V_LIMIT_ITEM));
        }else{
          kpu.display->println(kpu.menu->getFloatValue(C_LIMIT_ITEM));
        }
        kpu.display->setCursor(0, 20);
        kpu.display->println("LIMIT");
        kpu.display->setCursor(40,0);
        kpu.display->println("|");
        kpu.display->setCursor(40,20);
        kpu.display->println("|");
        kpu.display->setCursor(60, 0);
        kpu.display->println(kpu.menu->getFloatValue(MMoM_VALUE_ITEM));
        kpu.display->setCursor(60, 20);
        kpu.display->println("CURRENT");
      }
      
      kpu.display->display();
      vTaskDelay(pdMS_TO_TICKS(200));
      kpu.display->clearDisplay();
    }
}