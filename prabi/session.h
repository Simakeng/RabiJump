#pragma once
#include "os.h"
#include <functional>

#ifndef _SESSION_HEADER_
#define _SESSION_HEADER_

struct Session
{
	uint32_t remote;
	uint32_t sid;

	friend struct std::hash<Session>;
};

namespace std
{
	template<>
	struct hash<Session>
	{
	public:
		std::size_t operator() (const Session& t) const { return t.sid; }
	};
}

#endif //!_SESSION_HEADER_