#pragma once

class ShopWithSoliders
{
private:
	using Ally=pair<size_t, uint32>;
	Bank bank;
	ImageList& images;
	FighterList& fighters;
	DynArr<Ally> allies;
	bool BuyAlly(Arena& arena, Ally& ally)
	{
		if(bank.Pay(ally.second))
		{
			arena.AddFighter(fighters[ally.first]->Clone());
			return true;
		}
		return false;
	}
public:
	ShopWithSoliders(Bank bank, ImageList& images, FighterList& fighters, const DynArr<Ally>& allies)
		:bank(bank), images(images), fighters(fighters), allies(func::Move(allies)){}
	void Purchase(Arena& arena, SDL::Point pos)
	{
		static bool pressed=false;
		if((SDL::Cursor::PressedButtons()&SDL::MouseButtonMask::Left)!=SDL::MouseButtonMask::None)
		{
			if(!pressed)
			{
				pressed=true;
				auto clickpos=SDL::Cursor::Position();
				if(func::Ordered(pos.y,clickpos.y,pos.y+Fighter::size.h)&&func::Ordered<uint32, uint32, uint32>(pos.x, clickpos.x,pos.x+Fighter::size.w*allies.size()))
				{
					BuyAlly(arena, allies[clickpos.x/Fighter::size.w]);
				}
			}
		}
		else
		{
			pressed=false;
		}
	}
	void AddMoney(uint32 money)
	{
		bank.AddMoney(money);
	}
	void DrawOn(SDL::Renderer& rend, SDL::Rect dst, uint16 section, SDL::Color col=SDL::Color::Yellow())
	{
		bank.DrawOn(rend, dst, section, col);
		SDL::Rect rect(dst.Position()+SDL::Point(0,30), Fighter::size);
		for(size_t i=0;i<allies.size();++i)
		{
			rend.Draw(fighters[allies[i].first]->GetImage(), nullptr, &rect);
			rect.x+=rect.w;
		}
		rend.Draw(SDL::Line(SDL::Point(0, dst.y+Fighter::size.h+30-1), SDL::Point(Fighter::lenght,dst.y+Fighter::size.h+30-1)), SDL::Color::Black());
	}
};