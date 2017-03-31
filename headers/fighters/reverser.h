#pragma once

class Reverser: public ReversingFighter, public Person, public RangeFighter
{
protected:
	Interval interval;
	bool ReverseIfPossible()
	{
		interval.Continue();
		if(interval.IsElapsed())
		{
			if(FindEnemies<NonNeutralFighter>([&](NonNeutralFighter& x){Reverse(x);}, true))
			{
				interval.Refresh();
				return true;
			}
			return false;
		}
		return FindEnemy<NonNeutralFighter>();
	}
	bool MoveAfterAction()
	{
		return !FindEnemy<NonNeutralFighter>()&&!AtEnd();
	}
public:
    Reverser(SDL::Texture& img, uint32 pos, uint32 speed, bool good, uint32 health, uint32 interval, uint32 range, bool flying)
		:Person(img, pos, speed, good, health, flying), RangeFighter(range), interval(interval){}
	virtual void DrawOn(SDL::Renderer& rend, SDL::Point dst_pos)override
	{
		Person::DrawOn(rend, dst_pos);
		if(interval.WasRefreshed())
		{
			RangeFighter::DrawOn(rend, dst_pos);
		}
	}
	virtual void Action()override
	{
		ReverseIfPossible();
		if(MoveAfterAction())
		{
			GoForward();
		}
	}
	virtual unique_ptr<Fighter> Clone()override
	{
		return unique_ptr<Fighter>(new remove_reference_t<decltype(*this)>(*this));
	}
};