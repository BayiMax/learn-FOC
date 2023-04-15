/**
 * @file u_adc.c
 * @author {白秉鑫}-{bbx20010518@outlook.com}
 * @brief
 * @version 0.1
 * @date 2023-04-10
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "u_adc.h"
#include "main.h"
#include "esp_adc_cal.h"

_U_ADC myadc;

#define ADC_EXAMPLE_ATTEN ADC_ATTEN_DB_11                // ADC衰减参数
#define ADC_EXAMPLE_CALI_SCHEME ESP_ADC_CAL_VAL_EFUSE_TP // 校准值类型

#define ADC_Channel1 ADC1_CHANNEL_0              // ADC通道
#define ADC_Channel2 ADC1_CHANNEL_1              // ADC通道
static esp_adc_cal_characteristics_t adc_chars1; // ADC初始化的结构体
/**
 * @brief 获取ADC的值
 *
 * @return int
 */
static float Get_adc1(void)
{
  float value = 0;
  float voltage = 0;
  for (int i = 0; i < 10; i++)
  {
    /* code */
    value += (float)adc1_get_raw(ADC_Channel1);
  }
  value = value / 10;
  printf("ADC value: %f", value);
  voltage = (float)esp_adc_cal_raw_to_voltage(value, &adc_chars1) / 1000;
  return voltage;
}
/**
 * @brief 获取ADC的值
 *
 * @return int
 */
static float Get_adc2(void)
{
  float value = 0;
  float voltage = 0;
  for (int i = 0; i < 10; i++)
  {
    /* code */
    value += (float)adc1_get_raw(ADC_Channel2);
  }
  value = value / 10;
  printf("ADC value: %f", value);
  voltage = (float)esp_adc_cal_raw_to_voltage(value, &adc_chars1) / 1000;
  return voltage;
}

/**
 * @brief
 *
 */
void adc_init(void)
{
  myadc.Get_adc1 = Get_adc1;
  myadc.Get_adc2 = Get_adc2;

  bool cali_enable = false;
  static const char *TAG = "ADC SINGLE";
  esp_err_t ret;
  /*ADC检查*/

  ret = esp_adc_cal_check_efuse(ADC_EXAMPLE_CALI_SCHEME);
  if (ret == ESP_ERR_NOT_SUPPORTED)
  {
    ESP_LOGW(TAG, "Calibration scheme not supported, skip software calibration");
  }
  else if (ret == ESP_ERR_INVALID_VERSION)
  {
    ESP_LOGW(TAG, "eFuse not burnt, skip software calibration");
  }
  /*描述ADC衰减特性*/
  else if (ret == ESP_OK)
  {
    cali_enable = true;
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_EXAMPLE_ATTEN, ADC_WIDTH_BIT_DEFAULT, 0, &adc_chars1);
  }
  else
  {
    ESP_LOGE(TAG, "Invalid arg");
  }
  /*配置ADC捕获宽度*/
  ESP_ERROR_CHECK(adc1_config_width(ADC_WIDTH_BIT_DEFAULT));
  ESP_ERROR_CHECK(adc1_config_channel_atten(ADC_Channel1, ADC_EXAMPLE_ATTEN));
  ESP_ERROR_CHECK(adc1_config_channel_atten(ADC_Channel2, ADC_EXAMPLE_ATTEN));
}
