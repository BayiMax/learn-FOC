#include <stdio.h>
#include "u_led.h"
#include "driver/ledc.h"

U_LED myled;


/**
 * @brief 根据当前分辨率计算对应的计数值
 *
 * @param value 占空比
 * @return uint16_t
 */
static uint16_t calc(float value) {
    // ((2^13)-1)*50% --> 50%的占空比
    return (8191 * value);
}

/**
 * @brief Set the Led object
 *
 * @param value led 亮度 百分比
 */
static void set_Led(float value) {
    ledc_set_duty(LEDC_LOW_SPEED_MODE, static_cast<ledc_channel_t>(0), calc(value));
    ledc_update_duty(LEDC_LOW_SPEED_MODE, static_cast<ledc_channel_t>(0));
}

void led_init(void) {
    myled.set_Led = set_Led;

    // 定时器配置
    ledc_timer_config_t led_timer = {
            .speed_mode = LEDC_LOW_SPEED_MODE,
            .duty_resolution = LEDC_TIMER_13_BIT,
            .timer_num = LEDC_TIMER_0,
            .freq_hz = 1000,           // f (频率)
            .clk_cfg = LEDC_AUTO_CLK}; // 自动
    ESP_ERROR_CHECK(ledc_timer_config(&led_timer));

    // 通道配置
    ledc_channel_config_t led_channel = {
            .gpio_num = 3,                     // IO口选择
            .speed_mode = LEDC_LOW_SPEED_MODE, // 速度
            .channel = static_cast<ledc_channel_t>(0),                      // 通道
            .intr_type = LEDC_INTR_DISABLE,    //?
            .timer_sel = LEDC_TIMER_0,         // 定时器选择
            .duty = 0,                         // Set duty to 50%
            .hpoint = 0};
    ESP_ERROR_CHECK(ledc_channel_config(&led_channel));
}

/**
 * led_任务
 */
void Led_thread() {
    float lum = 0.1;
    int flag = 0;

    while (true) {
        if (flag) {
            lum += 0.02;
            if (lum >= 0.9)
                flag = 0;
        }
        if (flag == 0) {
            lum -= 0.02;
            if (lum <= 0.1)
                flag = 1;
        }

        myled.set_Led(lum);
        std::this_thread::sleep_for((const std::chrono::milliseconds) 25);
//        vTaskDelay(25 / portTICK_PERIOD_MS);
    }
}
