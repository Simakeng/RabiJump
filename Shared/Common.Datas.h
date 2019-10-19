#pragma once
#ifndef _CSTDINT_
#include <cstdint>
#endif // ! _CSTDINT_

namespace Common {
	struct PackageHeader
	{
		uint32_t rabi = 'Rabi';
		uint32_t pack_size;
		uint32_t pack_id;
		uint32_t sha256;
	};
}