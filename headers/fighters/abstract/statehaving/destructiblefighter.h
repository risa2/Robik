#pragma once

class DestructibleFighter: public virtual Fighter
{
protected:
	bool flying;
	uint32 health;
	const uint32 maxhealth;
    DestructibleFighter(uint32 health, bool flying):flying(flying), health(health), maxhealth(health){}
public:
	virtual void BeAttacked(Fighter& attacker, uint32 damage)noexcept
	{
		if(flying)
		{
			if(auto d=dynamic_cast<DestructibleFighter*>(&attacker))
			{
				if(!d->IsFlying())
				{
					return;
				}
			}
		}
		health=(health<=damage)?0:health-damage;
	}
	virtual void BeHealed(Fighter&, uint32 power)noexcept
	{
		health=(health+power>=maxhealth)?maxhealth:health+power;
	}
    bool IsFlying()const noexcept
	{
    	return flying;
    }
    virtual bool IsAlive()const noexcept override
	{
		return health!=0;
	}
	bool IsHealthy()
	{
		return health==maxhealth;
	}
	void DrawOn(SDL::Renderer& rend, SDL::Point dst_pos)
	{
		rend.Draw(SDL::Rect(dst_pos.x, flying?dst_pos.y+Fighter::size.h-1:dst_pos.y, Fighter::size.w*health/maxhealth, 1), SDL::Color::Green());
		rend.Draw(SDL::Rect(dst_pos.x+Fighter::size.w*health/maxhealth, flying?dst_pos.y+Fighter::size.h-1:dst_pos.y, Fighter::size.w-Fighter::size.w*health/maxhealth, 1), SDL::Color::Red());
	}
};