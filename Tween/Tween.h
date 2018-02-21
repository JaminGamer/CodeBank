#ifndef __Tween_H__
#define __Tween_H__

typedef float (*TweenFunc) (float startvalue, float valuerange, double timepassed, double totaltime);

class Tween
{
public:
	Tween();
	Tween(float min, float range, float timeSpan);
	~Tween();

	void SetTween(TweenFunc function);

	float Tick(double a_Deltatime);
	void Reset();
	void Reset(float min, float range, float time);

	float Progress() { return m_pTweenFunction(m_StartingValue, m_Range, m_ElapsedTime, m_EndTime); };

private:
	TweenFunc m_pTweenFunction = nullptr;
	float m_StartingValue = 0.0f;
	float m_Range = 0.0f;
	float m_ElapsedTime = 0.0f;
	float m_EndTime = 0.0f;
};

#endif //!__Tween_H__
