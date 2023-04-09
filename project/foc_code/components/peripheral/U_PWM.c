/**
 * @file U_PWM.c
 * @author {白秉鑫}-{bbx20010518@outlook.com}
 * @brief
 * @version 0.1
 * @date 2023-04-09
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "U_PWM.h"
#include "main.h"

#define IN1 6
#define IN2 7
#define IN3 8

// 引脚注释
// mtck in1 6
// in2 7 mtdo
//  in3 8

//  en 10

static void Pwm_init(void)
{
  mypwm.Set_duty = Set_duty;

  // 定时器配置
  ledc_timer_config_t pwm_timer = {
      .speed_mode = LEDC_SPEED_MODE_MAX,
      .timer_num = LEDC_TIMER_0,
      .duty_resolution = LEDC_TIMER_13_BIT,
      .freq_hz = 1000,           // f (频率)
      .clk_cfg = LEDC_AUTO_CLK}; // 自动
  ESP_ERROR_CHECK(ledc_timer_config(&pwm_timer));

  // 通道配置
  ledc_channel_config_t pwm_channel_1 = {
      .speed_mode = LEDC_SPEED_MODE_MAX, // 速度
      .channel = 0,                      // 通道
      .timer_sel = LEDC_TIMER_0,         // 定时器选择
      .intr_type = LEDC_INTR_DISABLE,    //?
      .gpio_num = IN1,                   // IO口选择
      .duty = 0,                         // Set duty to 0%
      .hpoint = 0};
  ESP_ERROR_CHECK(ledc_channel_config(&pwm_channel_1));
} 

/**
 * @brief 设置输出占空比
 *
 * @param duty 占空比值
 */
static void Set_duty(uint32_t duty)
{
  ledc_set_duty(LEDC_SPEED_MODE_MAX, PWM_OUT_1, duty);
}
