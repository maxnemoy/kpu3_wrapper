// подключение необходимых заголовочных файлов
#include <Arduino.h>
#include <threads.h>
// Определение объекта с данными и параметрами приложения.
KpuData data = KpuData();
// Объявление хендлеров для 
TaskHandle_t displayHandle;
TaskHandle_t inputHandle;
TaskHandle_t sensorHandle;
TaskHandle_t workHandle;
TaskHandle_t timerHandle;
// Функция инициализации 
void setup() {
  // Инициализация сериал интерфеса
  Serial.begin(115200);
  // Инициализация объекта данных.
  data.begin();
  // Инициализация потока управления дисплеем на 0 ядре микроконтроллера 
  vTaskDelay(pdMS_TO_TICKS(100));
  if (xTaskCreatePinnedToCore(displayThread, "Display", 2048,
                              (static_cast<void *>(&data)), 1,
                              &displayHandle, 0) != pdPASS){
    Serial.println("ERROR: Display task dont created.");
    Serial.flush();
    esp_deep_sleep_start();
  }
  // Инициализация потока обработки 
  // пользовательского ввода на 1 ядре микроконтроллера 
  vTaskDelay(pdMS_TO_TICKS(100));
  if (xTaskCreatePinnedToCore(inputThread, "Input", 2048,
                              (static_cast<void *>(&data)), 1,
                              &inputHandle, 1) != pdPASS)
  {
    Serial.println("ERROR: Input task dont created.");
    Serial.flush();
    esp_deep_sleep_start();
  }
  // Инициализация потока работы с драйвером 
  // датчика давления на 1 ядре микроконтроллера 
  vTaskDelay(pdMS_TO_TICKS(100));
  if (xTaskCreatePinnedToCore(sensorThread, "Sensor", 2048,
                              (static_cast<void *>(&data)), 1,
                              &sensorHandle, 1) != pdPASS)
  {
    Serial.println("ERROR: Sensor task dont created.");
    Serial.flush();
    esp_deep_sleep_start();
  }
  // Инициализация основного рабочего 
  // потока  на 1 ядре микроконтроллера 
  vTaskDelay(pdMS_TO_TICKS(100));
  if (xTaskCreatePinnedToCore(workThread, "Work", 2048,
                              (static_cast<void *>(&data)), 1,
                              &workHandle, 1) != pdPASS)
  {
    Serial.println("ERROR: Work task dont created.");
    Serial.flush();
    esp_deep_sleep_start();
  }
  // Инициализация потока таймера на 1 ядре микроконтроллера 
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
// Основной цикл не используется. Но обязателен для объявления.
void loop(){};