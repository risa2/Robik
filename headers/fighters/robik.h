#pragma once

#include <stdexcept>

class Robik: public TouchFighter, public Shooter, public Person
{
private:
	const uint32 arenapos;
public:
	Robik(SDL::Texture& img, uint32 pos, uint32 speed, uint32 health, uint32 damage, uint32 interval, uint32 range, unique_ptr<Shoot> shoot, uint32 shootinterval, uint32 shootrange, uint32 arenapos)
		:TouchFighter(damage, interval, range), Shooter(shootinterval, shootrange, func::Move(shoot)), Person(img, pos, speed, true, health, false), arenapos(arenapos){}
	virtual void Action()override
	{
		reversed=false;
		if(!IsHealthy())
		{
			++health;
		}
		if((SDL::Cursor::PressedButtons()&SDL::MouseButtonMask::Left)!=SDL::MouseButtonMask::None&&func::Ordered<uint32,uint32,uint32>(arenapos, SDL::Cursor::Position().y, arenapos+size.h))
		{
			if(uint32(SDL::Cursor::Position().x)>pos+size.w/2)
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