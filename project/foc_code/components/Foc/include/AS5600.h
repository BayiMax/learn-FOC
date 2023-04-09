/**
 * @file AS5600.h
 * @author {白秉鑫}-{bbx20010518@outlook.com}
 * @brief
 * @version 0.1
 * @date 2023-04-09
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef _AS5600_H
#define _AS5600_H

#include "main.h"
#include "U_I2C.h"

typedef struct AS5600
{
  // 角度值
  float Raw_angel;
  // 圈数
  float turns_num;
  /**
   * @brief 获取原始角度数据
   *
   * @return float
   */
  float (*Get_Raw_angel)(void);
} _AS5600;

_AS5600 my_as5600;
/**
 * @brief 初始化
 *
 */
void AS5600_init(void);
/**
 * @brief AS5600 任务
 *
 * @param pvParameters
 */
void AS5600_Task(void *pvParameters);

#endif /* _AS5600_H */
