#ifndef __Helpers_H__
#define __Helpers_H__

#define MyAssert assert

void OutputMessage(const char* message, ...);

void CheckForGLErrors();

char* DeepCopyString(const char* original);
char* LoadFile(const char* filename);
void WriteStringToFile(char* filename, char* string);

int RandomNumber() { return rand(); };

//float RandomNumberInRange(float min, float max) { return ((rand()) / (RAND_MAX / (max - min)) + min); };

static int g_UniqueID = 0;
static int UniqueID() { return g_UniqueID++; };

#endif //__Helpers_H__