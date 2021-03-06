#pragma once

class StoppableFighter: public virtual Fighter
{
protected:
	SpeedState speedstate;
public:
    StoppableFighter():speedstate(){}
	void DrawOn(SDL::Renderer& rend, SDL::Point dst_pos)
	{
		auto sstate=speedstate.GetState();
		if(sstate!=SpeedState::Enum::Ok)
		{
			rend.Draw(SDL::Rect(dst_pos.x, dst_pos.y, Fighter::size), sstate==SpeedState::Enum::Sleeping?SDL::Color(255,0,255):SDL::Color(0,0,255));
		}
	}
	void Continue()
	{
		speedstate.Continue();
	}
	SpeedState::Enum GetState()
	{
		return speedstate.GetState();
	}
	virtual void BeDecelerated(Fighter&, SpeedState newstate)
	{
		if(newstate>speedstate)
		{
			speedstate=newstate;
		}
	}
};