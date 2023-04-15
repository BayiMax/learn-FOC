/*
 *                        _oo0oo_
 *                       o8888888o
 *                       88" . "88
 *                       (| -_- |)
 *                       0\  =  /0
 *                     ___/`---'\___
 *                   .' \\|     |// '.
 *                  / \\|||  :  |||// \
 *                 / _||||| -:- |||||- \
 *                |   | \\\  - /// |   |
 *                | \_|  ''\---/''  |_/ |
 *                \  .-\__  '-'  ___/-. /
 *              ___'. .'  /--.--\  `. .'___
 *           ."" '<  `.___\_<|>_/___.' >' "".
 *          | | :  `- \`.;`\ _ /`;.`/ - ` : | |
 *          \  \ `_.   \_ __\ /__ _/   .-` /  /
 *      =====`-.____`.___ \_____/___.-`___.-'=====
 *                        `=---='
 *
 *
 *      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *            佛祖保佑     永不宕机     永无BUG
 */

/**
 * @file u_led.c
 * @author {白秉鑫}-{bbx20010518@outlook.com}
 * @brief
 * @version 0.1
 * @date 2023-04-10
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "u_led.h"

_U_LED myled;

/**
 * @brief 根据当前分辨率计算对应的计数值
 *
 * @param value 占空比
 * @return uint16_t
 */
static uint16_t calc(float value)
{
  // ((2^13)-1)*50% --> 50%的占空比
  return (8191 * value);
}

/**
 * @brief Set the Led object
 *
 * @param value led 亮度 百分比
 */
static void set_Led(float value)
{
  ledc_set_duty(LEDC_LOW_SPEED_MODE, 0, calc(value));
  ledc_update_duty(LEDC_LOW_SPEED_MODE, 0);
}

void led_init(void)
{
  myled.set_Led = set_Led;

  // 定时器配置
  ledc_timer_config_t led_timer = {
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .timer_num = LEDC_TIMER_0,
      .duty_resolution = LEDC_TIMER_13_BIT,
      .freq_hz = 1000,           // f (频率)
      .clk_cfg = LEDC_AUTO_CLK}; // 自动
  ESP_ERROR_CHECK(ledc_timer_config(&led_timer));

  // 通道配置
  ledc_channel_config_t led_channel = {
      .speed_mode = LEDC_LOW_SPEED_MODE, // 速度
      .channel = 0,                      // 通道
      .timer_sel = LEDC_TIMER_0,         // 定时器选择
      .intr_type = LEDC_INTR_DISABLE,    //?
      .gpio_num = 3,                     // IO口选择
      .duty = 0,                         // Set duty to 50%
      .hpoint = 0};
  ESP_ERROR_CHECK(ledc_channel_config(&led_channel));
}
/**
 * @brief AS5600 任务
 *
 * @param pvParameters
 */
void Led_Task(void *pvParameters)
{
  float lum = 0.1;
  int flag = 0;
  while (1)
  {
    if (flag)
    {
      lum += 0.02;
      if (lum >= 0.9)
        flag = 0;
    }
    if (flag == 0)
    {
      lum -= 0.02;
      if (lum <= 0.1)
        flag = 1;
    }

    myled.set_Led(lum);

    vTaskDelay(25 / portTICK_PERIOD_MS);
  }
}
