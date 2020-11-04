#pragma once

#include <stdexcept>

class Robik: public TouchFighter, public Shooter, public Person
{
private:
	const uint32 arenapos;
	SDL::KeyboardState kb;
public:
	Robik(SDL::Texture& img, uint32 pos, uint32 speed, uint32 health, uint32 damage, uint32 interval, uint32 range, unique_ptr<Shoot> shoot, uint32 shootinterval, uint32 shootrange, uint32 arenapos)
		:TouchFighter(damage, interval, range), Shooter(shootinterval, shootrange, func::Move(shoot)), Person(img, pos, speed, true, health, false), arenapos(arenapos), kb(){}
	virtual void BeReversed(Fighter&)override{}
	virtual void Action()override
	{
		if(!IsHealthy())
		{
			++health;
		}
		if(kb.IsPressed(SDL::Scancode::Left)||kb.IsPressed(SDL::Scancode::Right))
		{
			if(kb.IsPressed(SDL::Scancode::Right))
			{
				GoRight();
			}
			else
			{
				GoLeft();
			}
			Shooter::interval.Continue();
			TouchFighter::interval.Continue();
		}
		else if(!TouchFighter::AttackIfPossible())
		{
			Shooter::AttackIfPossible();
		}
		else
		{
			Shooter::interval.Continue();
		}
	}
	virtual void DrawOn(SDL::Renderer& rend, SDL::Point dst_pos)override
	{
		Person::DrawOn(rend, dst_pos);
		TouchFighter::DrawOn(rend, dst_pos+SDL::Point(pos, 0));
	}
	virtual unique_ptr<Fighter> Clone()override
	{
		throw std::logic_error("Robik must be unique");
	}
};