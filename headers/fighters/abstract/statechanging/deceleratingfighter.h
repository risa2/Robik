#pragma once

class DeceleratingFighter: public virtual Fighter
{
protected:
	SpeedState sstate;
	void Decelerate(Fighter& enemy)
	{
		enemy.BeDecelerated(*this, sstate);
	}
public:
	DeceleratingFighter(SpeedState sstate): sstate(sstate){}
};