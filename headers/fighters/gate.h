#pragma once

class Gate: public DestructibleFighter, public VisualFighter, public LocatedFighter, public NonNeutralFighter
{
public:
	Gate(SDL::Texture& img, uint32 health, uint32 pos, bool good)
		:DestructibleFighter(health, false), VisualFighter(img), LocatedFighter(pos,0), NonNeutralFighter(good){}
	virtual void Action()override
	{
		reversed=false;
	}
	void DrawOn(SDL::Renderer& rend, SDL::Point dst_pos)
	{
		VisualFighter::DrawOn(rend, dst_pos+SDL::Point(pos, 0));
        DestructibleFighter::DrawOn(rend, dst_pos+SDL::Point(pos, 0));
	}
	virtual unique_ptr<Fighter> Clone()override
	{
		return unique_ptr<Fighter>(new remove_reference_t<decltype(*this)>(*this));
	}
};