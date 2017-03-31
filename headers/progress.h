#pragma once

class Progress
{
private:
	uint32 i=0;
	const uint32 loops, sleeptime;
public:
	Progress(uint32 loops, uint32 sleeptime):loops(loops), sleeptime(sleeptime){}
	uint32 GetLoops()const noexcept
	{
		return loops;
	}
	void Next()noexcept
	{
		++i;
		SDL::Wait(sleeptime);
	}
	bool End()const noexcept
	{
		return i>=loops;
	}
	operator uint32()const noexcept
	{
		return i;
	}
};