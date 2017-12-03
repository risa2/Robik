#pragma once

class RangeFighter: public virtual Fighter
{
protected:
	uint32 range;
	bool Touch(Fighter& creature)
	{
		return IsGood()?
			int32(GetPos()-size.x)<=int32(creature.GetPos())&&GetPos()+size.x+range>=creature.GetPos():
			GetPos()+size.x>=creature.GetPos()&&GetPos()-range<=creature.GetPos()+size.x;
	}
	bool AtEnd()
	{
		return IsGood()?GetPos()+size.x+size.x+range>=lenght:int32(GetPos())-size.x-range<=0;
	}
	template<typename T, typename Fn>
	bool FindEnemies(Fn callback, bool one)
	{
		bool action=false;
		for(size_t i=0;i<arena.size();++i)
		{
			if(auto o=dynamic_cast<T*>(arena[i]); o&&o->IsGood()!=IsGood()&&Touch(*o))
			{
				callback(*o);
				action=true;
				if(one)
				{
					break;
				}
			}
		}
		return action;
	}
	template<typename T>
	bool FindEnemy()
	{
		return FindEnemies<T>([](T&){}, true);
	}
public:
	RangeFighter(uint32 range)
		:range(range){}
	virtual void DrawOn(SDL::Renderer& rend, SDL::Point dst_pos)override
	{
        rend.Draw(SDL::Rect(GetPos()+(IsGood()?dst_pos.x+size.x:dst_pos.x-range), dst_pos.y+size.y/2-1, range, 2), SDL::Color::Blue());
	}
};