#include <Arduino.h>
#include <sensor.h>
#include <rotary.h>

#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "OneButton.h"

OneButton button(25, true);
Sensor sensor(4, 2);
Rotary encoder(26, 27);
Adafruit_SSD1306 display(128, 64, &Wire);
TaskHandle_t displayHandle;
TaskHandle_t inputHandle;

[[noreturn]] void displayThread(void*)
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setTextSize(3, 5);
    display.setTextColor(SSD1306_WHITE);
    display.display();
    int counter = 1; 
    while (true)
    {
        display.setCursor(20, 10);
        display.println(counter);
        display.display();
        vTaskDelay(pdMS_TO_TICKS(1000));
        display.clearDisplay();
        counter++;
    }
}

[[noreturn]] void inputThread(void *encoder)
{
  Rotary enc = *(Rotary *)encoder;
  enc.begin(true, false);
  Serial.println("Start input thread");
  int counter = 0;
  while (true)
  {
    unsigned char result = enc.process();

    if (result)
    {
      if (result == DIR_CW)
      {
        counter++;
        Serial.println(counter);
      }
      else
      {
        counter--;
        Serial.println(counter);
      }
    }

    vTaskDelay(pdMS_TO_TICKS(2));
  }
}

// This function will be called when the button1 was pressed 1 time (and no 2. button press followed).
void click1() {
  Serial.println("Button 1 click.");
} // click1


// This function will be called when the button1 was pressed 2 times in a short timeframe.
void doubleclick1() {
  Serial.println("Button 1 doubleclick.");
} // doubleclick1


// This function will be called once, when the button1 is pressed for a long time.
void longPressStart1() {
  Serial.println("Button 1 longPress start");
} // longPressStart1


// This function will be called often, while the button1 is pressed for a long time.
void longPress1() {
  Serial.println("Button 1 longPress...");
} // longPress1


// This function will be called once, when the button1 is released after beeing pressed for a long time.
void longPressStop1() {
  Serial.println("Button 1 longPress stop");
} 

void setup() {
  Serial.begin(115200);

  button.attachClick(click1);
  button.attachDoubleClick(doubleclick1);
  button.attachLongPressStart(longPressStart1);
  button.attachLongPressStop(longPressStop1);
  button.attachDuringLongPress(longPress1);


  vTaskDelay(pdMS_TO_TICKS(100));
  if (xTaskCreatePinnedToCore(displayThread, "display", 2048,
                              nullptr, 1,
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

void loop() {
  button.tick();
  vTaskDelay(pdMS_TO_TICKS(10));
  //Serial.print("mm:\t");
  //Serial.println(sensor.getMillimetersOfMercury() , 2);
  //Serial.print("psi:\t");
  //Serial.println(sensor.getPsi() , 2);
}