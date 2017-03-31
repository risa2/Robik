#pragma once

#include <typeinfo>

class Fighter;

enum class Survive: uint8
{
	Robik, Zombies, Both
};
class Arena
{
private:
	using Array=containers::DynArr<unique_ptr<Fighter>>;
	Array fighters;
	bool active=true;
public:
	Arena()=default;
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
	Survive GetState();
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
			if(!fighters[i]->IsGood()&&dynamic_cast<DestructibleFighter*>(fighters[i].get())&&!fighters[i]->IsReversed())
			{
				++money;
			}
			fighters.erase(i);
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
Survive Arena::GetState()
{
	struct
	{
		uint8 robik:1, zombies:1, gate:1;
	} isAlive= {0,0,0};
	for(auto& creature:fighters)
	{
		if(typeid(*creature)==typeid(Robik))
		{
			isAlive.robik=1;
		}
		else if(typeid(*creature)==typeid(Gate))
		{
			isAlive.gate=1;
		}
		else if(!creature->IsGood()&&dynamic_cast<DestructibleFighter*>(creature.get()))
		{
			isAlive.zombies=1;
		}
	}
	return isAlive.robik&&isAlive.gate?
				(isAlive.zombies?
					Survive::Both:
					Survive::Robik):
				Survive::Zombies;
}