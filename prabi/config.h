#pragma once
#include <cstdint>
class Config 
{
public:
	Config();
	~Config();
	
	bool IsStop();
	bool IsStartRabiJumpServer();
	bool IsStartRabiJumpClient();
	const char* GetRabiJumpAddress();
	uint16_t GetRabiJumpPort();
private:
	bool stop;
};

extern Config globalConfig;