#pragma once

class SpeedState
{
private:
	uint8 state:2;//0-nic, 1-pomaly, 2-spici
	uint32 time:30;
public:
	enum class Enum:uint8{Ok=0,Slow=1,Sleeping=2};
	constexpr SpeedState():state(0),time(0){}
	constexpr SpeedState(Enum state, uint32 time):state(uint8(state)), time(time){}
	bool operator<(SpeedState second)
	{
        return state<second.state||(state==second.state&&time<second.time);
	}
	bool operator>(SpeedState second)
	{
        return state>second.state||(state==second.state&&time>second.time);
	}
	void Sleep(uint32 newtime)
	{
		*this=SpeedState(Enum::Sleeping, newtime);
	}
	void Slow(uint32 newtime)
	{
		*this=SpeedState(Enum::Slow, newtime);
	}
	Enum GetState()
	{
		return state==0?Enum::Ok:(state==1?Enum::Slow:Enum::Sleeping);
	}
	void Continue()
	{
		if(time!=0)
		{
			--time;
		}
		if(time==0)
		{
			state=0;
		}
	}
};