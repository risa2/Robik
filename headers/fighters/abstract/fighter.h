#pragma once

class Fighter
{
public:
	virtual void BeAttacked(Fighter& attacker, uint32 damage){}
	virtual void BeHealed(Fighter& healer, uint32 power){}
	virtual void BeReversed(Fighter& reverser){}
	virtual void BeDecelerated(Fighter& decelerator, SpeedState newstate){}
	constexpr static SDL::Point size=SDL::Point(80,80);
	constexpr static uint32 lenght=16*size.x;
	static Arena arena;
	virtual ~Fighter(){}
	virtual bool IsAlive()const noexcept=0;
	virtual uint32 GetPos()const noexcept=0;
	virtual bool IsGood()const noexcept=0;
	virtual bool IsReversed()const noexcept=0;
	virtual unique_ptr<Fighter> Clone()=0;
	virtual void Action()=0;
	virtual void DrawOn(SDL::Renderer& rend, SDL::Point dst_pos){}
	virtual SDL::Texture& GetImage()const noexcept=0;
};
constexpr SDL::Point Fighter::size;