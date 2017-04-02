#pragma once

class Interval
{
private:
	uint32 interval, left;
public:
	void Continue()
	{
		if(left>0)
		{
			--left;
		}
	}
	void Refresh()
	{
		left=interval;
	}
	bool IsElapsed()
	{
		return left==0;
	}
	bool WasRefreshed()
	{
		return left==interval;
	}
	Interval(uint32 interval):interval(interval), left(interval-1){}
};