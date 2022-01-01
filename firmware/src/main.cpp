#include <Arduino.h>
#include <sensor.h>
#include <rotary.h>
#include <menu.h>
#include <button.h>

#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

Menu menu;
Sensor sensor(4, 2);
Rotary encoder(26, 27);
Adafruit_SSD1306 display(128, 64, &Wire);
TaskHandle_t displayHandle;
TaskHandle_t inputHandle;

[[noreturn]] void displayThread(void* m)
{
    // Menu m = *(Menu*)menu;

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setTextSize(1, 2);
    display.setTextColor(SSD1306_WHITE);
    display.display();
    while (true)
    {
      std::vector<String> items = menu.getMenu();

      int start = 0;
      int end = items.size();

      if(items.size() > 3) {
        start  = menu.index() - 1;
        if (start < 0) start = 0;
        end = menu.index() + 2;
        if(end > menu.index()-1) end = menu.index()-1;
      }
      int row = 0;
      for(int i = start; i < items.size(); i++){
        display.setCursor(0, row*20);
        display.println(items[i]);
        row++;
      }
        display.display();
        vTaskDelay(pdMS_TO_TICKS(200));
        display.clearDisplay();
    }
}

[[noreturn]] void inputThread(void *encoder)
{
  Rotary enc = *(Rotary*)encoder;
  enc.begin(true, false);

  Button button(&menu);
  button.begin(25);
  
  while (true)
  {
    button.tick();

    unsigned char result = enc.process();
    if (result)
    {
      if (result == DIR_CW) menu.next();
      else menu.previous();
    }

    vTaskDelay(pdMS_TO_TICKS(2));
  }
}


void setup() {
  Serial.begin(115200);

  vTaskDelay(pdMS_TO_TICKS(100));
  if (xTaskCreatePinnedToCore(displayThread, "display", 2048,
                              (static_cast<void *>(&menu)), 1,
                              &displayHandle, 0) != pdPASS){
    Serial.println("ERROR: Encoder task dont created.");
    Serial.flush();
    esp_deep_sleep_start();
  }

  vTaskDelay(pdMS_TO_TICKS(100));
  if (xTaskCreatePinnedToCore(inputThread, "Input", 2048,
                              (static_cast<void *>(&encoder)), 1,
                              &inputHandle, 1) != pdPASS)
  {
    Serial.println("ERROR: Input task dont created.");
    Serial.flush();
    esp_deep_sleep_start();
  }
}


void loop() {}
  //button.tick();

 // vTaskDelay(pdMS_TO_TICKS(1000));
  //Serial.print("mm:\t");
  //Serial.println(sensor.getMillimetersOfMercury() , 2);
  //Serial.print("psi:\t");
  //Serial.println(sensor.getPsi() , 2);