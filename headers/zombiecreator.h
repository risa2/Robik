#pragma once

class ZombieCreator
{
private:
	const Level& level;
	FighterList& fighters;
	uint32 zombiecount;
public:
	ZombieCreator(FighterList& fighters, const Level& level, uint32 loops)
		:level(level), fighters(fighters), zombiecount(level.TotalZombies(loops)){}
	vector<unique_ptr<Fighter>> AllNew(uint32 loop)
	{
		vector<unique_ptr<Fighter>> created;
		for(auto& index:level.AllNew(loop))
		{
            created.push_back(fighters[index]->Clone());
		}
		return func::Move(created);
	}
	uint32 TotalZombies()const noexcept
	{
		return zombiecount;
	}
};