#ifndef MAIN_H
#define MAIN_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <malloc.h>
#include <cstdlib>
#include <iostream>

/*任务头文件*/
#include <thread>
#include <freertos/FreeRTOS.h>
#include "freertos/event_groups.h"
#include <freertos/task.h>
#include <chrono>
#include <sstream>
/*任务头文件*/

#include "esp_log.h"
#include "gpio_cxx.hpp"
#include "sdkconfig.h"
#include "esp_system.h"
#include "spi_flash_mmap.h"
#include "esp_log.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_err.h"
/**
 * @brief Debug 输出
 *
 */
#define MY_DEBUG(format, ...) printf("<B:%d-%s>:" format "\n", __LINE__, __func__, ##__VA_ARGS__)

/*任务优先级划分*/
#define Prio_AS5600 3
#define Prio_LED 10
/*任务优先级划分*/

#endif /* MAIN_H */
