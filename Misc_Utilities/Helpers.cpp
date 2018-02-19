#include "pch.h"

char* DeepCopyString(const char* original)
{
	return _strdup(original);
	//char* copy = new char[strlen(original) + 1]; // memory allocation
	//memcpy(copy, original, strlen(original) + 1);

	//return copy;
}

