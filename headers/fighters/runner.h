#pragma once

class Runner: public AttackingFighter, public Person
{
public:
	Runner(SDL::Texture& img, uint32 pos, uint32 speed, uint32 health, uint32 damage, bool flying)
		:AttackingFighter(damage), Person(img, pos, speed, false, health, flying){}
	virtual void Action()override
	{
		GoForward();
		if(pos==0)
		{
			for(size_t i=0; i<arena.size(); ++i)
			{
				if(auto g=dynamic_cast<Gate*>(arena[i]))
				{
					Attack(*g);
				}
			}
		}
	}
	virtual void DrawOn(SDL::Renderer& rend, SDL::Point dst_pos)override
	{
		StoppableFighter::DrawOn(rend, dst_pos+SDL::Point(pos, 0));
		VisualFighter::DrawOn(rend, dst_pos+SDL::Point(pos, 0));
        DestructibleFighter::DrawOn(rend, dst_pos+SDL::Point(pos, 0));
	}
	virtual bool IsAlive()const noexcept override
	{
		return DestructibleFighter::IsAlive();
	}
	virtual unique_ptr<Fighter> Clone()override
	{
		return unique_ptr<Fighter>(new remove_reference_t<decltype(*this)>(*this));
	}
};