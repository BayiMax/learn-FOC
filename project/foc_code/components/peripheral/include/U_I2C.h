/**
 * @file U_I2C.h
 * @author {白秉鑫}-{bbx20010518@outlook.com}
 * @brief
 * @version 0.1
 * @date 2023-04-09
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef U_I2C_H
#define U_I2C_H

#include "main.h"

typedef struct
{
  /**
   * @brief I2C读数据
   *
   * @param i2c_num I2C选择
   * @param addr 器件地址
   * @param reg 寄存器地址
   * @param buf 数据缓冲区
   * @param len 数据长度
   * @return esp_err_t 函数状态
   */
  esp_err_t (*Read)(i2c_port_t i2c_num, uint8_t addr, uint8_t reg, uint8_t *buf, uint8_t len);
  /**
   * @brief I2C写数据
   *
   * @param i2c_num I2C选择
   * @param addr 器件地址
   * @param reg 寄存器地址
   * @param buf 数据缓冲区
   * @param len 数据长度
   * @return esp_err_t 函数状态
   */
  esp_err_t (*Write)(i2c_port_t i2c_num, uint8_t addr, uint8_t reg, uint8_t *buf, uint8_t len);
} _UI2C;

_UI2C myi2c;

esp_err_t I2C1_init(void);

#endif /* U_I2C_H */
