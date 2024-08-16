#include "freertos/FreeRTOS.h" // IWYU pragma: export
#include "freertos/task.h"
#include <Arduino.h>

#include <print.h>

namespace global {
char out_buf[256];
}

void myTask1(void *pvParam) {
  printf("[TASK 1] launched\n");
  unsigned int counter = 0;
  while (1) {
    printf("[TASK 1] counter = %u\n", counter++);
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}

void myTask2(void *pvParam) {
  printf("[TASK 2] launched\n");
  unsigned int counter = 0;
  while (1) {
    printf("[TASK 2] counter = %u\n", counter++);
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin();
  // Wait for serial monitor to startup.
  delay(1000);

  TaskHandle_t pxHandle1;
  TaskHandle_t pxHandle2;

  printf("[ MAIN ] Launching Task 1\n");
  xTaskCreatePinnedToCore(myTask1, "Task 1", 2048, NULL, 1, &pxHandle1, 1);

  printf("[ MAIN ] Launching Task 2\n");
  xTaskCreatePinnedToCore(myTask2, "Task 2", 2048, NULL, 2, &pxHandle2, 1);

  printf("[ MAIN ] All tasks launched\n");

  // vTaskDelay(1000 / portTICK_PERIOD_MS);

  // Suspend Task 1
  if (pxHandle1 != NULL) {
    vTaskSuspend(pxHandle1);
    printf("[ MAIN ] Task 1 suspended\n");
  }

  vTaskDelay(2000 / portTICK_PERIOD_MS);

  vTaskResume(pxHandle1);
  printf("[ MAIN ] Task 1 resumed\n");

  vTaskDelay(2000 / portTICK_PERIOD_MS);

  vTaskSuspend(pxHandle1);
  printf("[ MAIN ] Task 1 suspended\n");

  vTaskSuspend(pxHandle2);
  printf("[ MAIN ] Task 2 suspended\n");
}

void loop() {}
