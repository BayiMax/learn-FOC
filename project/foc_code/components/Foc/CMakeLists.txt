set(component_srcs 	 "AS5600.c")
# "foc.cpp"
idf_component_register(SRCS "${component_srcs}"
                       INCLUDE_DIRS "include"
                       )
