#pragma once
#include <stdint.h>

static void __generate_table();

uint32_t crc32(const void* buf, size_t len, uint32_t init);
