#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"

#define BUTTON_GPIO 0

#define IDENTIFIER "Group 8:\n1. Pham Tan Luc - 1914089\n2. Ho Nguyen Duc Tam - 1915020\n3. Pham Quang Son - 1914973\n4. Vu Nhat Nam - 1911660\n"

short key_code = 0;

void init_system()
{
    key_code = 0;

    // button
    gpio_pad_select_gpio(BUTTON_GPIO);
    gpio_set_direction(BUTTON_GPIO, GPIO_MODE_INPUT);
}

void monitor_task(void *pvParameter)
{
    while (1)
    {
        printf(IDENTIFIER);
        vTaskDelay(5000 / portTICK_RATE_MS);
    }
}

void buttton_task(void *pvParameter)
{

    while (1)
    {
        if (gpio_get_level(BUTTON_GPIO) == 1)
        {
            key_code++;
        }
        else
        {
            key_code = 0;
        }

        vTaskDelay(10 / portTICK_RATE_MS);
    }
}

void is_button_pressed(void *pvParameter)
{
    while (1)
    {
        if (key_code == 1)
        {
            printf("ESP32\n");
        }

        vTaskDelay(50 / portTICK_RATE_MS);
    }
}

void app_main()
{
    xTaskCreate(&monitor_task, "monitor_task", 1024, NULL, 5, NULL);
    xTaskCreate(&buttton_task, "buttton_task", 1024, NULL, 5, NULL);
    xTaskCreate(&is_button_pressed, "is_button_pressed", 1024, NULL, 5, NULL);
    vTaskStartScheduler();
}