#pragma once

class GraphicOutput
{
private:
	SDL::Renderer rend;
public:
	constexpr static int killedPos=0, killedHeight=30, alliesPos=killedPos+killedHeight,
			alliesHeight=Fighter::size.h+30, arenaPos=alliesPos+alliesHeight,
			arenaHeight=Fighter::size.h, height=arenaPos+arenaHeight;
	GraphicOutput(SDL::Window& screen):rend(screen){}
	void Show(ProgressOfZombieKilling& killed, ShopWithSoliders& allies, Arena& arena)
	{
		rend.Repaint(SDL::Color(255,255,160));
		killed.DrawOn(rend, SDL::Rect(0, killedPos, Fighter::lenght, killedHeight));
		allies.DrawOn(rend, SDL::Rect(0, alliesPos, Fighter::lenght, 30), 350);
		arena.DrawOn(rend, SDL::Point(0, arenaPos));
		rend.Show();
	}
	operator SDL::Renderer&()
	{
		return rend;
	}
};
constexpr int GraphicOutput::killedPos, GraphicOutput::killedHeight, GraphicOutput::alliesPos,
		GraphicOutput::alliesHeight, GraphicOutput::arenaPos, GraphicOutput::arenaHeight, GraphicOutput::height;