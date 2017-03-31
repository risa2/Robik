#pragma once

class RangeFighter: public virtual Fighter
{
protected:
	uint32 range;
	bool Touch(Fighter& creature)
	{
		return IsGood()?
			int32(GetPos()-size.w)<=int32(creature.GetPos())&&GetPos()+size.w+range>=creature.GetPos():
			GetPos()+size.w>=creature.GetPos()&&GetPos()-range<=creature.GetPos()+size.w;
	}
	bool AtEnd()
	{
		return IsGood()?GetPos()+size.w+size.w+range>=lenght:int32(GetPos())-size.w-range<=0;
	}
	template<typename T, typename Fn>
	bool FindEnemies(Fn callback, bool one)
	{
		bool action=false;
		for(size_t i=0;i<arena.size();++i)
		{
			if(auto o=dynamic_cast<T*>(arena[i]))
			{
				if(o->IsGood()!=IsGood()&&Touch(*o))
				{
					callback(*o);
					action=true;
					if(one)
					{
						break;
					}
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
	RangeFighter(uint32 range):range(range){}
	virtual void DrawOn(SDL::Renderer& rend, SDL::Point dst_pos)override
	{
        rend.Draw(SDL::Rect(GetPos()+(IsGood()?dst_pos.x+size.w:dst_pos.x-range), dst_pos.y+size.h/2-1, range, 2), SDL::Color::Blue());
	}
};