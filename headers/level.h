#pragma once

class Level
{
public:
	class Rule
	{
	private:
		uint32 divisor;
		uint32 modus;
		size_t index;
	public:
		Rule(uint32 divisor=1, uint32 modus=1, size_t index=0)
			:divisor(divisor), modus(modus), index(index) {}
		bool IsTrue(uint32 value)const
		{
			return value%divisor==modus;
		}
		size_t GetIndex()const
		{
			return index;
		}
		uint32 TrueCount(uint32 loops)const
		{
            return (loops-modus)/divisor+1;
		}
		friend istream& operator>>(istream& in, Rule& rule)
		{
			return in>>rule.divisor>>rule.modus>>rule.index;
		}
	};
private:
	DynArr<Rule> rules;
	uint32 loops, sleeptime;
public:
	Progress GetProgressObject()const
	{
		return Progress(loops, sleeptime);
	}
	DynArr<size_t> AllNew(uint32 value)const
	{
		DynArr<size_t> result;
		for(auto& rule:rules)
		{
			if(rule.IsTrue(value))
			{
				result.push_back(rule.GetIndex());
			}
		}
		return result;
	}
	uint32 TotalZombies(uint32 loops)const
	{
		uint32 zombies=0;
		for(auto& rule:rules)
		{
			zombies+=rule.TrueCount(loops);
		}
		return zombies;
	}
	Level(istream&& in)
	{
		in>>loops>>sleeptime;
		while(in&&in.peek()!='|')
		{
			rules.resize(rules.size()+1);
			in>>rules.back();
		}
		in.ignore(1);
	}
};