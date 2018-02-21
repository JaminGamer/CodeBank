#ifndef __Helpers_H__
#define __Helpers_H__

char* DeepCopyString(const char* original);

// seed rand()
int RandomNumber() { return rand(); };

//float RandomNumberInRange(float min, float max) { return ((rand()) / (RAND_MAX / (max - min)) + min); };

static int g_UniqueID = 0;
static int GetUniqueID() { return g_UniqueID++; };

// #define MyColor vec4
class MyColor
{
public:
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;

    MyColor()
    {
    }
    MyColor(unsigned char nr, unsigned char ng, unsigned char nb, unsigned char na)
    {
        r = nr;
        g = ng;
        b = nb;
        a = na;
    }
};

#endif //__Helpers_H__