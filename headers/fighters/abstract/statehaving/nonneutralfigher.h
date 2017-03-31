#pragma once

class NonNeutralFighter: public virtual Fighter
{
protected:
	bool good, reversed=false;
public:
	NonNeutralFighter(bool good):good(good){}
	virtual bool IsGood()const noexcept override
	{
		return good^reversed;
	}
	virtual bool IsReversed()const noexcept override
	{
		return reversed;
	}
	virtual void BeReversed(Fighter&)override
	{
		reversed=!reversed;
	}
};