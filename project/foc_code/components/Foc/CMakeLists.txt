set(component_srcs 	"Foc_init.c" "AS5600.c")

idf_component_register(SRCS "${component_srcs}"
                       INCLUDE_DIRS "include"
                       PRIV_INCLUDE_DIRS ""
                       PRIV_REQUIRES "driver" "main"
                       REQUIRES "")
