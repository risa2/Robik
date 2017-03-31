#pragma once

class Shooter: public RangeFighter
{
private:
	bool AttackEnemies()
	{
		return FindEnemies<DestructibleFighter>([&](DestructibleFighter&){arena.AddFighter(shoot->BeShooted(*this));}, true);
	}
protected:
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
	Interval interval;
	unique_ptr<Shoot> shoot;
public:
	Shooter(uint32 interval, uint32 range, unique_ptr<Shoot> shoot):RangeFighter(range), interval(interval), shoot(func::Move(shoot)){}
	Shooter(const Shooter& second):RangeFighter(range), interval(second.interval), shoot(dynamic_cast<Shoot*>(second.shoot->Clone().release())){}
	virtual void Action()override
	{
		AttackIfPossible();
	}
};
class Archer: public Shooter, public Person
{
public:
	Archer(SDL::Texture& img, uint32 pos, uint32 speed, bool good, uint32 health, uint32 interval, uint32 range, bool flying, unique_ptr<Shoot> shoot)
			:Shooter(interval, range, func::Move(shoot)), Person(img, pos, speed, good, health, flying){}
	virtual void DrawOn(SDL::Renderer& rend, SDL::Point dst_pos)override
	{
		Person::DrawOn(rend, dst_pos);
		RangeFighter::DrawOn(rend, dst_pos);
	}
	virtual void Action()override
	{
		Shooter::Action();
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