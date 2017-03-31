#pragma once

class ReversingFighter: public virtual Fighter
{
protected:
	void Reverse(Fighter& enemy)
	{
		enemy.BeReversed(*this);
	}
public:
	ReversingFighter()=default;
};