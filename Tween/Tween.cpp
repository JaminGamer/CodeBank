#include "stdafx.h"

Tween::Tween()
{
}

Tween::Tween(float min, float range, float timeSpan) :
	m_StartingValue(min),
	m_Range(range),
	m_EndTime(timeSpan)
{
}

Tween::~Tween()
{
}

void Tween::SetTween(TweenFunc function)
{
	m_pTweenFunction = function;
}

float Tween::Tick(double a_Deltatime)
{
	m_ElapsedTime += a_Deltatime;
	return m_pTweenFunction(m_StartingValue, m_Range, m_ElapsedTime, m_EndTime);
}

void Tween::Reset()
{
	Reset(m_StartingValue, m_Range, m_EndTime);
}

void Tween::Reset(float min, float range, float time)
{
	m_ElapsedTime = 0.0f; // reset timer
	m_StartingValue = min;
	m_Range = range;
	m_EndTime = time;
}