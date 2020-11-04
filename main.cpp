#include <iostream>
#include <fstream>
#include <memory>
#include <array>

#include "objsdl/objsdl.h"

using namespace std;

#include "headers/bank.h"
#include "headers/progress.h"
#include "headers/arena.h"

using ImageList=array<SDL::Texture, 20>;
using FighterList=array<unique_ptr<Fighter>, 16>;

#include "headers/level.h"
#include "headers/zombiecreator.h"
#include "headers/progressofkilling.h"
#include "headers/shopwithsoliders.h"
#include "headers/graphicoutput.h"
#include "headers/sound.h"
#include "headers/music.h"
#include "headers/end.h"

Arena Fighter::arena;

int main(int argc, char** argv)try
{
	if(argc<2)
	{
		return 0;
	}
	SDL::Init _i;
	Music music("sound\\music.wav");
	Sound killedZombieSound("sound\\killedzombie.wav");
	Level level{ifstream(argv[1])};
	Progress progress=level.GetProgressObject();

	SDL::Window screen("Robík vs Zombíci", SDL::Rect(40, 40, Fighter::lenght, GraphicOutput::height));
	GraphicOutput out(screen);

	ImageList images={
		out.LoadImg("img\\robik.png"),
		out.LoadImg("img\\gate.png"),
		out.LoadImg("img\\shoot.png"),
		out.LoadImg("img\\horse.png"),
		out.LoadImg("img\\child.png"),
		out.LoadImg("img\\archer.png"),
		out.LoadImg("img\\healer.png"),
		out.LoadImg("img\\cat.png"),
		out.LoadImg("img\\knight.png"),
		out.LoadImg("img\\businessman.png"),
		out.LoadImg("img\\cart.png"),
		out.LoadImg("img\\zombiearcher.png"),
		out.LoadImg("img\\zombiehealer.png"),
		out.LoadImg("img\\icezombie.png"),
		out.LoadImg("img\\zombie.png"),
		out.LoadImg("img\\obr.png"),
		out.LoadImg("img\\runner.png"),
		out.LoadImg("img\\zombiebird.png"),
		out.LoadImg("img\\businesszombie.png"),
		out.LoadImg("img\\zombieshoot.png")
	};
	constexpr uint32 zombie_start=Fighter::lenght-Fighter::size.x;
	FighterList fighters={
		make_unique<SwordFighter>(images[3], 0, 10, true, 100, 10, 1, 0, false),//Pes
		make_unique<Decelerator>(images[4], 0, 2, true, 100, 20, SpeedState(SpeedState::Enum::Slow, 50), false),
		make_unique<Archer>(images[5], 0, 1, true, 100, 10, 150, false, make_unique<Shoot>(images[2], 0, 5, true)),
		make_unique<Healer>(images[6], 0, 1, true, 100, 50, 40, 80, false),//Lekar
		make_unique<SwordFighter>(images[7], 0, 1, true, 200, 50, 4, 50, false),//Risa
		make_unique<SwordFighter>(images[8], 0, 1, true, 2000, 20, 1, 0, false),//Rytir
		make_unique<Reverser>(images[9], 0, 1, true, 100, 100, 100, false),
		make_unique<Cart>(images[10], 0, 10, true, 500, 200),

		make_unique<Archer>(images[11], zombie_start, 1, false, 100, 20, 150, false, make_unique<Shoot>(images[19], 0, 10, false)),
		make_unique<Healer>(images[12], zombie_start, 1, false, 100, 50, 40, 80, false),
		make_unique<Decelerator>(images[13], zombie_start, 1, false, 150, 20, SpeedState(SpeedState::Enum::Slow, 100), false),
		make_unique<SwordFighter>(images[14], zombie_start, 2, false, 100, 10, 1, 0, false),
		make_unique<SwordFighter>(images[15], zombie_start, 1, false, 500, 350, 60, 20, false),
		make_unique<Runner>(images[16], zombie_start, 15, 100, 100, false),
		make_unique<SwordFighter>(images[17], zombie_start, 2, false, 50, 10, 1, 0, true),
		make_unique<Reverser>(images[18], zombie_start, 1, false, 50, 100, 100, false)
	};
	Fighter::arena.AddFighter(make_unique<Robik>(images[0], 0, 5, 1000, 20, 1, 0, make_unique<Shoot>(images[2], 0, 10, true), 20, 200, GraphicOutput::arenaPos));
	Fighter::arena.AddFighter(make_unique<Gate>(images[1], 1000, 0, true));
	Bank bank(10000);
	ShopWithSoliders shop(bank, images, fighters, {
		{0,  500},
		{1,  500},
		{2,  500},
		{3, 1500},
		{4, 2000},
		{5, 3000},
		{6, 2000},
		{7, 2000}});
	ZombieCreator zombies(fighters, level, progress.GetLoops());
	KillingProgress killed(zombies);
	while(!SDL::events::Quit())
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
		shop.AddMoney(1+newkilled*100);
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
	SDL::MessageBox::Show("Chyba", exc.what());
}