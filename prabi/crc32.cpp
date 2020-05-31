#include "crc32.h"

uint32_t __crc_table[256];

void __generate_table()
{
	const uint32_t polynomial = 0xEDB88320;
	for (uint32_t i = 0; i < 256; i++)
	{
		uint32_t c = i;
		for (size_t j = 0; j < 8; j++)
		{
			if (c & 1) {
				c = polynomial ^ (c >> 1);
			}
			else {
				c >>= 1;
			}
		}
		__crc_table[i] = c;
	}
}

uint32_t crc32(const void* buf, size_t len, uint32_t init)
{

	static bool __table = false;
	if (!__table) 
	{
		__generate_table();
		__table = true;
	}

	uint32_t c = init ^ 0xFFFFFFFF;
	const uint8_t* u = static_cast<const uint8_t*>(buf);
	for (size_t i = 0; i < len; ++i)
	{
		c = __crc_table[(c ^ u[i]) & 0xFF] ^ (c >> 8);
	}
	return c ^ 0xFFFFFFFF;
}