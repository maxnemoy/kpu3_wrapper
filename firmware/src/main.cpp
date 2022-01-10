#include <Arduino.h>
#include <threads.h>

KpuData data = KpuData();

TaskHandle_t displayHandle;
TaskHandle_t inputHandle;
TaskHandle_t sensorHandle;
TaskHandle_t workHandle;
TaskHandle_t timerHandle;

void setup() {
  Serial.begin(115200);
  
  data.begin();
  
  //init display thread on 0 core
  vTaskDelay(pdMS_TO_TICKS(100));
  if (xTaskCreatePinnedToCore(displayThread, "Display", 2048,
                              (static_cast<void *>(&data)), 1,
                              &displayHandle, 0) != pdPASS){
    Serial.println("ERROR: Display task dont created.");
    Serial.flush();
    esp_deep_sleep_start();
  }

  //init input thread on 1 core
  vTaskDelay(pdMS_TO_TICKS(100));
  if (xTaskCreatePinnedToCore(inputThread, "Input", 2048,
                              (static_cast<void *>(&data)), 1,
                              &inputHandle, 1) != pdPASS)
  {
    Serial.println("ERROR: Input task dont created.");
    Serial.flush();
    esp_deep_sleep_start();
  }

  //init sensor thread on 1 core
  vTaskDelay(pdMS_TO_TICKS(100));
  if (xTaskCreatePinnedToCore(sensorThread, "Sensor", 2048,
                              (static_cast<void *>(&data)), 1,
                              &sensorHandle, 1) != pdPASS)
  {
    Serial.println("ERROR: Sensor task dont created.");
    Serial.flush();
    esp_deep_sleep_start();
  }

  //init work thread on 1 core
  vTaskDelay(pdMS_TO_TICKS(100));
  if (xTaskCreatePinnedToCore(workThread, "Work", 2048,
                              (static_cast<void *>(&data)), 1,
                              &workHandle, 1) != pdPASS)
  {
    Serial.println("ERROR: Work task dont created.");
    Serial.flush();
    esp_deep_sleep_start();
  }

  //init timer thread on 1 core
  vTaskDelay(pdMS_TO_TICKS(100));
  if (xTaskCreatePinnedToCore(timerThread, "Timer", 2048,
                              (static_cast<void *>(&data)), 1,
                              &timerHandle, 1) != pdPASS)
  {
    Serial.println("ERROR: Timer task dont created.");
    Serial.flush();
    esp_deep_sleep_start();
  }
}


void loop(){};