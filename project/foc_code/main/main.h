/**
 * @file main.h
 * @author {白秉鑫}-{bbx20010518@outlook.com}
 * @brief
 * @version 0.1
 * @date 2023-03-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef _MAIN_H
#define _MAIN_H

/**
 * @file main.h
 * @author {白秉鑫}-{bbx20010518@outlook.com}
 * @brief
 * @version 0.1
 * @date 2023-03-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <malloc.h>

#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_err.h"
/*drive*/
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "driver/ledc.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
/*drive*/
/*user*/
#include "foc_init.h"
/*user*/

/**
 * @brief Debug 输出
 *
 */
#define MY_DEBUG(format, ...) printf("<B:%d-%s>:" format "\n", __LINE__, __func__, ##__VA_ARGS__)

/*任务优先级划分*/
#define Priority_AS5600 3
#define Priority_LED 10
/*任务优先级划分*/

#endif /* _MAIN_H */
