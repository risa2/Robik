#include <iostream>
#include <fstream>
#include <memory>

#include "print.h"
#include "dynarr.h"
#include "objsdl.h"
#include "nocopy.h"

using namespace std;
using containers::DynArr;

#include "headers/bank.h"
#include "headers/progress.h"
#include "headers/arena.h"

using ImageList=DynArr<SDL::Texture>;
using FighterList=DynArr<unique_ptr<Fighter>>;

#include "headers/level.h"
#include "headers/zombiecreator.h"
#include "headers/progressofkilling.h"
#include "headers/shopwithsoliders.h"
#include "headers/graphicoutput.h"
#include "headers/sound.h"
#include "headers/music.h"
#include "headers/end.h"

Arena Fighter::arena;

int main()try
{
	SDL::Init();
	Music music("sound\\music.wav");
	Sound killedZombieSound("sound\\killedzombie.wav");
	Level level(ifstream("levels"));
	Progress progress=level.GetProgressObject();

	SDL::Window screen("Robík vs Zombíci", SDL::Window::UndefinedPos, 30, Fighter::lenght, GraphicOutput::height);
	GraphicOutput out(screen);

	ImageList images={
		SDL::Texture::LoadImg("img\\robik.png", out),
		SDL::Texture::LoadImg("img\\gate.png", out),
		SDL::Texture::LoadImg("img\\shoot.png", out),
		SDL::Texture::LoadImg("img\\pes.png", out),
		SDL::Texture::LoadImg("img\\lukasek.png", out),
		SDL::Texture::LoadImg("img\\archer.png", out),
		SDL::Texture::LoadImg("img\\healer.png", out),
		SDL::Texture::LoadImg("img\\risa.png", out),
		SDL::Texture::LoadImg("img\\knight.png", out),
		SDL::Texture::LoadImg("img\\businessman.png", out),
		SDL::Texture::LoadImg("img\\cart.png", out),
		SDL::Texture::LoadImg("img\\zombiearcher.png", out),
		SDL::Texture::LoadImg("img\\zombiehealer.png", out),
		SDL::Texture::LoadImg("img\\icezombie.png", out),
		SDL::Texture::LoadImg("img\\zombie.png", out),
		SDL::Texture::LoadImg("img\\obr.png", out),
		SDL::Texture::LoadImg("img\\runner.png", out),
		SDL::Texture::LoadImg("img\\zombiebird.png", out),
		SDL::Texture::LoadImg("img\\businesszombie.png", out)
	};
	constexpr uint32 zombie_start=Fighter::lenght-Fighter::size.x;
	FighterList fighters={
		make_unique<SwordFighter>(images[3], 0, 10, true, 100, 10, 1, 0, false),//Pes
		make_unique<Decelerator>(images[4], 0, 2, true, 100, 20, SpeedState(SpeedState::Enum::Sleeping, 5), false),
		make_unique<Archer>(images[5], 0, 1, true, 100, 10, 150, false, make_unique<Shoot>(images[2], 0, 10, true)),
		make_unique<Healer>(images[6], 0, 1, true, 100, 50, 40, 80, false),//Lekar
		make_unique<SwordFighter>(images[7], 0, 1, true, 200, 50, 4, 50, false),//Risa
		make_unique<SwordFighter>(images[8], 0, 1, true, 2000, 20, 1, 0, false),//Rytir
		make_unique<Reverser>(images[9], 0, 1, true, 100, 100, 100, false),
		make_unique<Cart>(images[10], 0, 10, true, 500, 200),

		make_unique<Archer>(images[11], zombie_start, 1, false, 100, 20, 150, false, make_unique<Shoot>(images[2], 0, 10, false)),
		make_unique<Healer>(images[12], zombie_start, 1, false, 100, 50, 40, 80, false),
		make_unique<Decelerator>(images[13], zombie_start, 1, false, 150, 20, SpeedState(SpeedState::Enum::Slow, 100), false),
		make_unique<SwordFighter>(images[14], zombie_start, 2, false, 100, 10, 1, 0, false),
		make_unique<SwordFighter>(images[15], zombie_start, 1, false, 100, 400, 40, 50, false),
		make_unique<Runner>(images[16], zombie_start, 15, 100, 100, false),
		make_unique<SwordFighter>(images[17], zombie_start, 2, false, 50, 10, 1, 0, true),
		make_unique<Reverser>(images[18], zombie_start, 1, false, 50, 100, 100, false)
	};
	Fighter::arena.AddFighter(make_unique<Robik>(images[0], 0, 5, 1000, 20, 1, 0, make_unique<Shoot>(images[2], 0, 10, true), 20, 200, GraphicOutput::arenaPos));
	Fighter::arena.AddFighter(make_unique<Gate>(images[1], 1000, 0, true));
	Bank bank(7000, 0);
	ShopWithSoliders shop(bank, images, fighters, {
		{0,  350},
		{1,  350},
		{2,  700},
		{3, 1050},
		{4, 1400},
		{5, 2100},
		{6, 1400},
		{7, 1400}});
	ZombieCreator zombies(fighters, level, progress.GetLoops());
	KillingProgress killed(zombies);
	while(SDL::Event::NotQuit())
	{
		out.Show(killed, bank, shop, Fighter::arena);
		if(End(Fighter::arena, killed.YouWin()))
		{
			music.Stop();
			Message(Fighter::arena);
			break;
		}
		if(!progress.End())
		{
			Fighter::arena.AddFighters(zombies.AllNew(progress));
		}
		uint32 newkilled=Fighter::arena.Clean();
		killed.IncreaseKilled(newkilled);
		shop.AddMoney(1+newkilled);
		if(newkilled!=0)
		{
			killedZombieSound.Play();
		}
		Fighter::arena.Actions();
		shop.Purchase(Fighter::arena, SDL::Point(0, GraphicOutput::alliesPos+30));
		progress.Next();
	}
	return 0;
}
catch(SDL::Error& err)
{
	err.Show();
}
catch(exception& exc)
{
	cout<<exc.what()<<'\n';
}