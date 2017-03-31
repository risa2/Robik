#pragma once

class Shoot: public RangeFighter, public AttackingFighter, public VisualFighter, public LocatedFighter, public NonNeutralFighter
{
protected:
	bool end=false;
public:
	Shoot(SDL::Texture& img, uint32 pos, uint32 damage, bool good)
		:RangeFighter(0), AttackingFighter(damage), VisualFighter(img), LocatedFighter(pos, 60), NonNeutralFighter(good){}
	virtual void Action()override
	{
		if(FindEnemies<DestructibleFighter>([&](DestructibleFighter& x){Attack(x);}, true)||AtEnd())
		{
			end=true;
		}
		else
		{
			GoForward();
		}
	}
	virtual bool IsAlive()const noexcept override
	{
		return !end;
	}
	virtual void DrawOn(SDL::Renderer& rend, SDL::Point dst_pos)override
	{
		VisualFighter::DrawOn(rend, dst_pos+SDL::Point(pos, 0));
	}
	unique_ptr<Fighter> BeShooted(Fighter& archer)
	{
		pos=archer.GetPos();
		return unique_ptr<Fighter>(Clone());
	}
	virtual unique_ptr<Fighter> Clone()override
	{
		return unique_ptr<Fighter>(new remove_reference_t<decltype(*this)>(*this));
	}
};