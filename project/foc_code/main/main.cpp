#include <esp_pthread.h>
#include "main.h"
#include "u_led.h"

/**
 * 创建线程
 * @param name 线程名
 * @param core_id 线程使用内核ID
 * @param stack 可用堆栈大小
 * @param prio 线程优先级
 * @return
 */
static esp_pthread_cfg_t create_config(const char *name, int core_id, int stack, int prio) {
    auto cfg = esp_pthread_get_default_config();
    cfg.thread_name = name;//线程名
    cfg.pin_to_core = core_id;//内核ID
    cfg.stack_size = stack;//可用堆栈大小
    cfg.prio = prio;//线程优先级
    return cfg;
}

/**
 * 初始化
 */
void All_init() {
    led_init();
}

extern "C" void app_main(void) {
    auto cfg = esp_pthread_get_default_config();
    All_init();

    cfg = create_config("led_tack", 0, 512, Prio_LED);
    cfg.inherit_cfg = true;
    esp_pthread_set_cfg(&cfg);
    std::thread led_tack(Led_thread);

    while (1) {

        std::stringstream ss;
        ss << "core id: " << xPortGetCoreID()
           << ", prio: " << uxTaskPriorityGet(nullptr)
           << ", minimum free stack: " << uxTaskGetStackHighWaterMark(nullptr) << " bytes.";
        ESP_LOGI(pcTaskGetName(nullptr), "%s", ss.str().c_str());
//        MY_DEBUG("runing...");

        std::this_thread::sleep_for((const std::chrono::seconds) 1);
//        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
