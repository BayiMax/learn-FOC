/**
 * @file AS5600.c
 * @author {白秉鑫}-{bbx20010518@outlook.com}
 * @brief
 * @version 0.1
 * @date 2023-04-09
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "AS5600.h"
#include "main.h"

#include "U_I2C.h"

#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"

// AS5600原地址 7位
#define AS5600_ADDR 0x36
// 分辨率设置
#define AS5600_RESOLUTION 4096 // 12bit Resolution

#define AS5600_RAW_ANGLE_REGISTER 0x0C

/**
 * @brief 获取原始角度数据
 *
 * @return float
 */
static float Get_Raw_Angle(void)
{
  uint16_t value1 = 0;
  float raw_angle;
  uint8_t buffer[2] = {0};

  myi2c.Read(I2C_NUM_0, AS5600_ADDR, AS5600_RAW_ANGLE_REGISTER, buffer, 2);

  value1 = ((uint16_t)buffer[0] << 8) | (uint16_t)buffer[1]; // 一共就11位 注意

  raw_angle = ((int)value1 & 0b0000111111111111) * 360.0 / 4096.0;
  return raw_angle;
}
/**
 * @brief AS5600 初始化
 *
 */
void AS5600_init(void)
{
  my_as5600.Get_Raw_angel = Get_Raw_Angle;
  // my_as5600.Raw_angel = 0;
  // my_as5600.turns_num = 0;
}
/**
 * @brief AS5600 任务
 *
 * @param pvParameters
 */
void AS5600_Task(void *pvParameters)
{
  while (1)
  {
    my_as5600.Raw_angel = my_as5600.Get_Raw_angel();
    vTaskDelay(2 / portTICK_PERIOD_MS);
  }
}