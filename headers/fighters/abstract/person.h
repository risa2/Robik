#pragma once

class Person: public DestructibleFighter, public StoppableFighter, public VisualFighter, public NonNeutralFighter, public LocatedFighter
{
public:
	Person(SDL::Texture& img, uint32 pos, uint32 speed, bool good, uint32 health, bool flying)
		:DestructibleFighter(health, flying), VisualFighter(img), NonNeutralFighter(good), LocatedFighter(pos, speed){}
	virtual void DrawOn(SDL::Renderer& rend, SDL::Point dst_pos)override
	{
        StoppableFighter::DrawOn(rend, dst_pos+SDL::Point(GetPos(), 0));
        DestructibleFighter::DrawOn(rend, dst_pos+SDL::Point(GetPos(), 0));
        VisualFighter::DrawOn(rend, dst_pos+SDL::Point(GetPos(),0));
	}
};