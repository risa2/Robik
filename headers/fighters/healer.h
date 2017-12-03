#pragma once

class Healer: public Person, public HealingFighter
{
protected:
	bool Touch(Fighter& creature)
	{
		if(IsGood())
		{
			return GetPos()<=creature.GetPos()+size.x&&GetPos()+size.x+range>=creature.GetPos();
		}
		else
		{
			return GetPos()>=creature.GetPos()-size.x&&GetPos()-size.x-range<=creature.GetPos();
		}
	}
	DestructibleFighter* CanHeal(Arena& arena)
	{
		for(size_t i=0;i<arena.size();++i)
		{
			if(auto d=dynamic_cast<DestructibleFighter*>(arena[i]); d&&d->IsGood()==IsGood()&&Touch(*d)&&!d->IsHealthy())
			{
				return d;
			}
		}
		return nullptr;
	}
	bool HealIfPossible(Arena& arena)
	{
		interval.Continue();
		auto healable=CanHeal(arena);
		if(interval.IsElapsed()&&healable)
		{
			Heal(*healable);
			interval.Refresh();
			return true;
		}
		return healable!=nullptr;
	}
	bool MoveAfterAction(Arena& arena)
	{
		return !CanHeal(arena);
	}
	Interval interval;
	uint32 range;
public:
	Healer(SDL::Texture& img, uint32 pos, uint32 speed, bool good, uint32 health, uint32 power, uint32 interval, uint32 range, bool flying)
		:Person(img, pos, speed, good, health, flying), HealingFighter(power), interval(interval), range(range){}
	virtual void Action()override
	{
		if(!HealIfPossible(arena))
		{
			GoForward();
		}
	}
	virtual void DrawOn(SDL::Renderer& rend, SDL::Point dst_pos)override
	{
        Person::DrawOn(rend, dst_pos);
	}
	virtual unique_ptr<Fighter> Clone()override
	{
		return unique_ptr<Fighter>(new remove_reference_t<decltype(*this)>(*this));
	}
};