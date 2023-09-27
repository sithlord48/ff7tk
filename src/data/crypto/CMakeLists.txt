add_library(CRYPTO OBJECT aes.c aes.h)
set_target_properties(CRYPTO PROPERTIES POSITION_INDEPENDENT_CODE ON)
