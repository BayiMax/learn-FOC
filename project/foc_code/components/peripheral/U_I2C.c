/**
 * @file U_I2C.c
 * @author {白秉鑫}-{bbx20010518@outlook.com}
 * @brief
 * @version 0.1
 * @date 2023-04-09
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "U_I2C.h"
#include "main.h"

#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"

#define I2C_SDA_Pin 4 // I2C SDA
#define I2C_SCL_Pin 5 // I2C SCL

#define WRITE_BIT I2C_MASTER_WRITE  /*!< I2C 主 写 */
#define READ_BIT I2C_MASTER_READ    /*!< I2C 主 读 */
#define I2C_MASTER_TX_BUF_DISABLE 0 /*!< 主机不需要缓冲区 */
#define I2C_MASTER_RX_BUF_DISABLE 0 /*!< 主机不需要缓冲区 */
#define ACK_CHECK_EN 0x1            /*!< I2C主端检查从端ack*/
#define ACK_CHECK_DIS 0x0           /*!< I2C主端不检查从端ack */
#define ACK_VAL 0x0                 /*!< 使能ack */
#define NACK_VAL 0x1                /*!< 关闭ack */

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
static esp_err_t I2C_Read(i2c_port_t i2c_num, uint8_t addr, uint8_t reg, uint8_t *buf, uint8_t len)
{
  int ret = 0;
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, (addr << 1) | WRITE_BIT, ACK_CHECK_EN);
  i2c_master_write_byte(cmd, reg, ACK_CHECK_EN);
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, (addr << 1) | READ_BIT, ACK_CHECK_EN);
  while (len)
  {
    if (len == 1)
    {
      i2c_master_read_byte(cmd, buf, NACK_VAL);
    }
    else
    {
      i2c_master_read_byte(cmd, buf, ACK_VAL);
    }
    len--;
    buf++;
  }
  i2c_master_stop(cmd);
  ret = i2c_master_cmd_begin(i2c_num, cmd, 100 / portTICK_RATE_MS);
  i2c_cmd_link_delete(cmd);
  if (ret == ESP_ERR_TIMEOUT)
  {
    MY_DEBUG("error!ret:%x.", ret);
  }
  return ret;
}
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
static esp_err_t I2C_Write(i2c_port_t i2c_num, uint8_t addr, uint8_t reg, uint8_t *buf, uint8_t len)
{
  uint8_t i;
  int ret = 0;
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, (addr << 1) | WRITE_BIT, ACK_CHECK_EN);
  i2c_master_write_byte(cmd, reg, ACK_CHECK_EN);
  for (i = 0; i < len; i++)
  {
    i2c_master_write_byte(cmd, buf[i], ACK_CHECK_EN);
  }
  i2c_master_stop(cmd);
  ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_RATE_MS);
  i2c_cmd_link_delete(cmd);
  if (ret == ESP_ERR_TIMEOUT)
  {
    MY_DEBUG("error!ret:%d.", ret);
  }
  return ret;
}
/**
 * @brief AS5600 I2C初始化
 *
 * @return esp_err_t
 */
esp_err_t I2C1_init(void)
{
  // 初始化控制结构体
  myi2c.Read = I2C_Read;
  myi2c.Write = I2C_Write;
  // 初始化控制结构体
  int i2c_master_port = 0; // 选择I2C0
  i2c_config_t conf = {
      .mode = I2C_MODE_MASTER,             // 选择I2C模式
      .sda_io_num = I2C_SDA_Pin,           // SDA引脚
      .sda_pullup_en = GPIO_PULLUP_ENABLE, // 使能上拉
      .scl_io_num = I2C_SCL_Pin,           // SCl引脚
      .scl_pullup_en = GPIO_PULLUP_ENABLE, // 使能上拉
      .master.clk_speed = 400000,          // I2C频率  400k
  };
  esp_err_t err = i2c_param_config(i2c_master_port, &conf);
  if (err != ESP_OK)
  {
    return err;
  }
  // 初始化I2C驱动
  return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}