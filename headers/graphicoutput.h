#pragma once

class GraphicOutput
{
private:
	SDL::Renderer rend;
public:
	constexpr static int width=Fighter::lenght, killedPos=0, killedHeight=30,
		bankPos=killedPos+killedHeight, bankHeight=30,
		alliesPos=bankPos+bankHeight, alliesHeight=Fighter::size.y,
		arenaPos=alliesPos+alliesHeight, arenaHeight=Fighter::size.y,
		height=arenaPos+arenaHeight;
	GraphicOutput(SDL::Window& screen):rend(screen){}
	void Show(KillingProgress& killed, Bank& bank, ShopWithSoliders& allies, Arena& arena)
	{
		rend.Repaint(SDL::Color(255,255,160));
		killed.DrawOn(rend, SDL::Rect(0, killedPos, width, killedHeight));
		bank.DrawOn(rend, SDL::Rect(0, bankPos, Fighter::lenght, bankHeight), 500);
		allies.DrawOn(rend, SDL::Point(0, alliesPos));
		arena.DrawOn(rend, SDL::Point(0, arenaPos));
		rend.Show();
	}
	operator SDL::Renderer&()
	{
		return rend;
	}
};