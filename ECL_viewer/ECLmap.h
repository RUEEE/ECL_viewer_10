#pragma once
#include <cstdint>
struct InsFormat
{
	int32_t id;
	const char* ins_format;
};


const char* GetFormat(int version, int32_t id);