#pragma once

class TouchFighter: public RangeFighter, public AttackingFighter
{
private:
	bool AttackEnemies()
	{
		return FindEnemies<DestructibleFighter>([&](DestructibleFighter& x){Attack(x);}, false);
	}
protected:
	Interval interval;
	bool AttackIfPossible()
	{
		interval.Continue();
		if(interval.IsElapsed())
		{
			if(AttackEnemies())
			{
				interval.Refresh();
				return true;
			}
		}
		return false;
	}
	bool MoveAfterAction()
	{
		return !FindEnemy<DestructibleFighter>()&&!AtEnd();
	}
public:
	TouchFighter(uint32 damage, uint32 interval, uint32 range)
		:RangeFighter(range), AttackingFighter(damage), interval(interval){}
	virtual void Action()override
	{
		AttackIfPossible();
	}
	virtual void DrawOn(SDL::Renderer& rend, SDL::Point dst_pos)override
	{
        if(interval.WasRefreshed())
		{
			RangeFighter::DrawOn(rend, dst_pos);
		}
	}
};

class SwordFighter: public TouchFighter, public Person
{
public:
    SwordFighter(SDL::Texture& img, uint32 pos, uint32 speed, bool good, uint32 health, uint32 damage, uint32 interval, uint32 range, bool flying)
		:TouchFighter(damage, interval, range), Person(img, pos, speed, good, health, flying){}
	virtual void Action()override
	{
		TouchFighter::Action();
		if(MoveAfterAction())
		{
			GoForward();
		}
	}
	virtual void DrawOn(SDL::Renderer& rend, SDL::Point dst_pos)override
	{
		Person::DrawOn(rend, dst_pos);
        TouchFighter::DrawOn(rend, dst_pos);
	}
	virtual unique_ptr<Fighter> Clone()override
	{
		return unique_ptr<Fighter>(new remove_reference_t<decltype(*this)>(*this));
	}
};