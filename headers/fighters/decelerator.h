#pragma once

class Decelerator: public DeceleratingFighter, public Person, public RangeFighter
{
protected:
	bool lastaction=false;
	bool DecelerateIfPossible()
	{
		return FindEnemies<StoppableFighter>([&](StoppableFighter& f){Decelerate(f);}, true);
	}
public:
	Decelerator(SDL::Texture& img, uint32 pos, uint32 speed, bool good, uint32 health, uint32 range, SpeedState state, bool flying)
		:DeceleratingFighter(state), Person(img, pos, speed, good, health, flying), RangeFighter(range){}
	virtual void DrawOn(SDL::Renderer& rend, SDL::Point dst_pos)override
	{
		Person::DrawOn(rend, dst_pos);
		if(lastaction)
		{
			RangeFighter::DrawOn(rend, dst_pos);
			lastaction=false;
		}
	}
	virtual void Action()override
	{
		if(DecelerateIfPossible())
		{
			lastaction=true;
			GoBackwards();
		}
		else
		{
			GoForward();
		}
	}
	virtual unique_ptr<Fighter> Clone()override
	{
		return unique_ptr<Fighter>(new remove_reference_t<decltype(*this)>(*this));
	}
};