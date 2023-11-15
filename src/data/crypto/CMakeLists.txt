# SPDX-FileCopyrightText: Chris Rizzitello <sithlord48@gmail.com>
# SPDX-License-Identifier: CC0-1.0
add_library(CRYPTO OBJECT aes.c aes.h)
set_target_properties(CRYPTO PROPERTIES POSITION_INDEPENDENT_CODE ON)
