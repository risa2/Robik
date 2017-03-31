#pragma once

class HealingFighter: public virtual Fighter
{
protected:
	uint32 power;
	void Heal(Fighter& ally)
	{
        ally.BeHealed(*this, power);
	}
public:
	HealingFighter(uint32 power): power(power){}
};