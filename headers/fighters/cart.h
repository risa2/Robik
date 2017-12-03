#pragma once

class Cart: public RangeFighter, public AttackingFighter, public VisualFighter, public LocatedFighter, public NonNeutralFighter
{
private:
	uint32 range;
	bool end=false;
public:
	Cart(SDL::Texture& img, uint32 pos, uint32 speed, bool good, uint32 damage, uint32 range)
		:RangeFighter(0), AttackingFighter(damage), VisualFighter(img), LocatedFighter(pos, speed), NonNeutralFighter(good), range(range){}
	virtual void Action()override
	{
        GoForward();
        for(size_t i=0;i<arena.size();++i)
		{
			if(auto d=dynamic_cast<DestructibleFighter*>(arena[i]); d&&d->IsGood()!=IsGood()&&Touch(*d))
			{
				end=true;
			}
		}
	}
	virtual void DrawOn(SDL::Renderer& rend, SDL::Point dst_pos)
	{
        if(end)
		{
			rend.Draw(SDL::Rect(dst_pos.x+pos, dst_pos.y, range, size.y), SDL::Color(255,128,0));
		}
		else
		{
			VisualFighter::DrawOn(rend, dst_pos+SDL::Point(pos, 0));
		}
	}
	virtual bool IsAlive()const noexcept override
	{
		return !end;
	}
	~Cart()
	{
		RangeFighter::range=range;
		for(size_t i=0;i<arena.size();++i)
		{
			if(auto d=dynamic_cast<DestructibleFighter*>(arena[i]); d&&d->IsGood()!=IsGood()&&Touch(*d))
			{
				Attack(*d);
			}
		}
	}
	virtual unique_ptr<Fighter> Clone()override
	{
		return unique_ptr<Fighter>(new remove_reference_t<decltype(*this)>(*this));
	}
};