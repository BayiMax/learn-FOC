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
#include "u_pwm.h"
#include "main.h"

#define IN1_io 6
#define IN2_io 7
#define IN3_io 8

// 引脚注释
// mtck in1 6
// in2 7 mtdo
//  in3 8
//  en 10

_U_PWM mypwm = {
    .IN1_channel = 1,
    .IN2_channel = 2,
    .IN3_channel = 3};

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
 * @brief 设置输出占空比
 *
 * @param duty 占空比值
 */
static void Set_duty(const ledc_channel_t channel, float duty)
{
    ledc_set_duty(LEDC_LOW_SPEED_MODE, channel, calc(duty));
    ledc_update_duty(LEDC_LOW_SPEED_MODE, channel);
}

/**
 * @brief pwm初始化
 *
 */
void Pwm_init(void)
{
    mypwm.Set_duty = Set_duty;

    // 定时器配置
    ledc_timer_config_t pwm_timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_1,
        .duty_resolution = LEDC_TIMER_13_BIT,
        .freq_hz = 1000,           // f (频率)
        .clk_cfg = LEDC_AUTO_CLK}; // 自动
    ESP_ERROR_CHECK(ledc_timer_config(&pwm_timer));

    // 通道配置
    ledc_channel_config_t pwm_channel_1 = {
        .speed_mode = LEDC_LOW_SPEED_MODE, // 速度
        .channel = mypwm.IN1_channel,      // 通道
        .timer_sel = LEDC_TIMER_1,         // 定时器选择
        .intr_type = LEDC_INTR_DISABLE,    //?
        .gpio_num = IN1_io,                // IO口选择
        .duty = 0,                         // Set duty to 0%
        .hpoint = 0};
    ESP_ERROR_CHECK(ledc_channel_config(&pwm_channel_1));
    // 通道配置
    ledc_channel_config_t pwm_channel_2 = {
        .speed_mode = LEDC_LOW_SPEED_MODE, // 速度
        .channel = mypwm.IN2_channel,      // 通道
        .timer_sel = LEDC_TIMER_1,         // 定时器选择
        .intr_type = LEDC_INTR_DISABLE,    //?
        .gpio_num = IN2_io,                // IO口选择
        .duty = 0,                         // Set duty to 0%
        .hpoint = 0};
    ESP_ERROR_CHECK(ledc_channel_config(&pwm_channel_2));
    // 通道配置
    ledc_channel_config_t pwm_channel_3 = {
        .speed_mode = LEDC_LOW_SPEED_MODE, // 速度
        .channel = mypwm.IN3_channel,      // 通道
        .timer_sel = LEDC_TIMER_1,         // 定时器选择
        .intr_type = LEDC_INTR_DISABLE,    //?
        .gpio_num = IN3_io,                // IO口选择
        .duty = 0,                         // Set duty to 0%
        .hpoint = 0};
    ESP_ERROR_CHECK(ledc_channel_config(&pwm_channel_3));
}
