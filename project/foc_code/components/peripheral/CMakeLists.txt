set(peripheral_srcs "U_i2C.c" "U_PWM.c" "u_led.c" "u_adc.c")

idf_component_register(SRCS "${peripheral_srcs}"
                       INCLUDE_DIRS "include"
                       PRIV_INCLUDE_DIRS ""
                       PRIV_REQUIRES "driver" "main"
                       REQUIRES "")
