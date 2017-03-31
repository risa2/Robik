#pragma once

class LocatedFighter: virtual public Fighter
{
protected:
	uint32 pos, speed;
public:
	LocatedFighter(uint32 pos, uint32 speed):pos(pos), speed(speed){}
	uint32 GetPos()const noexcept
	{
        return pos;
	}
	bool GoLeft()
	{
		if(pos!=0)
		{
			pos=(pos<=speed)?0:pos-speed;
			return true;
		}
		else
		{
			return false;
		}
	}
	bool GoRight()
	{
		if(pos!=Fighter::lenght-Fighter::size.w)
		{
			pos=(pos+speed>=Fighter::lenght-Fighter::size.w)?Fighter::lenght-Fighter::size.w:pos+speed;
			return true;
		}
		else
		{
			return false;
		}
	}
	bool GoForward()noexcept
	{
        return IsGood()?GoRight():GoLeft();
	}
	bool GoBackwards()noexcept
	{
        return IsGood()?GoLeft():GoRight();
	}
};