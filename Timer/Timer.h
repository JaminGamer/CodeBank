#ifndef __TIMER_H__
#define __TIMER_H__

// Simplified time management.
// Pretty basic implementation so far but is intended
// to be expanded upon in the future.

// Possible feature/functionality addition: CallBacks
// Use a CallBack* to notify listeners of timer expiry,
// or trigger a function.

class Timer
{
public:
	Timer();
    virtual ~Timer();

	void Reset(double a_TimeLength); // start
	bool Tick(double a_Deltatime); // update

	bool HasCompleted() { return m_HasCompleted; };
	// void SetCallBack(CallBack* callback) { m_CallBack = callback;};
	// void CallBack(...); // build a universal function callback pointer if possible
private:
	void CheckIfCompleted();
	bool m_HasCompleted = false;
	float m_ElapsedTime = 0.0f;
	float m_TimeLength = FLT_MAX;

	// CallBack* m_CallBack = nullptr;
};

#endif //__TIMER_H__
