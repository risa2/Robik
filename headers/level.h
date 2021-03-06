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
		Rule(uint32 divisor=1, uint32 modus=0, size_t index=0)
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
			in>>rule.divisor>>rule.modus>>rule.index;
			return in;
		}
	};
private:
	vector<Rule> rules;
	uint32 loops, sleeptime;
public:
	Progress GetProgressObject()const
	{
		return Progress(loops, sleeptime);
	}
	vector<size_t> AllNew(uint32 value)const
	{
		vector<size_t> result;
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
		while(in)
		{
			rules.resize(rules.size()+1);
			in>>rules.back();
		}
		rules.pop_back();
	}
};