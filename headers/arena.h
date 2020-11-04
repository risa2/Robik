#pragma once

#include <typeinfo>

class Fighter;

class Arena
{
private:
	using Array=vector<unique_ptr<Fighter>>;
	Array fighters;
	bool active=true;
public:
	Arena():fighters(){}
	void AddFighter(unique_ptr<Fighter> fighter)
	{
		fighters.push_back(func::Move(fighter));
	}
	template<template<typename>typename T>void AddFighters(T<unique_ptr<Fighter>> fighters)
	{
		for(auto& fighter:fighters)
		{
            AddFighter(func::Move(fighter));
		}
	}
	uint32 Clean();
	void DrawOn(SDL::Renderer& draw, SDL::Point pos);
	void Actions();
	inline bool DeadRobik(size_t index);
	inline bool DeadGate(size_t index);
	size_t size()const noexcept
	{
		return fighters.size();
	}
	Fighter* operator[](size_t i)
	{
		return fighters[i].get();
	}
};

#include "speedstate.h"
#include "interval.h"
#include "fighters.h"

uint32 Arena::Clean()
{
	uint32 money=0;
	for(size_t i=0; i<fighters.size(); ++i)
	{
		if(!fighters[i]->IsAlive())
		{
			if(auto d=dynamic_cast<DestructibleFighter*>(fighters[i].get()); d&&!fighters[i]->IsGood()&&!fighters[i]->IsReversed())
			{
				++money;
			}
			fighters.erase(fighters.begin()+i);
			--i;
		}
	}
	return money;
}
void Arena::Actions()
{
	active=!active;
	for(size_t i=0; i<fighters.size(); ++i)
	{
		if(auto x=dynamic_cast<StoppableFighter*>(fighters[i].get()))
		{
			x->Continue();
			if(x->GetState()!=SpeedState::Enum::Sleeping&&(x->GetState()!=SpeedState::Enum::Slow||active))
			{
				fighters[i]->Action();
			}
		}
		else
		{
			fighters[i]->Action();
		}
	}
}
void Arena::DrawOn(SDL::Renderer& draw, SDL::Point pos)
{
	for(size_t i=0; i<fighters.size(); ++i)
	{
		fighters[i]->DrawOn(draw, pos);
	}
}
inline bool Arena::DeadRobik(size_t index)
{
	return !dynamic_cast<Robik*>(fighters[index].get());
}
inline bool Arena::DeadGate(size_t index)
{
	return !dynamic_cast<Gate*>(fighters[index].get());
}