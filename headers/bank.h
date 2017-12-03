#pragma once

class Bank
{
private:
	uint32 money;
	const uint32 capacity;
public:
	Bank(uint32 cap, uint32 startmoney=0):money(startmoney), capacity(cap){}
	void AddMoney(uint32 money)
	{
		this->money=std::min(this->money+money, capacity);
	}
	bool Pay(uint32 price)
	{
		if(price>money)
		{
			return false;
		}
		else
		{
			money-=price;
			return true;
		}
	}
	void DrawOn(SDL::Renderer& rend, const SDL::Rect& dst, uint16 section, SDL::Color col=SDL::Color::Yellow())
	{
		rend.Draw(dst, SDL::Color(0,0,0,0));
		rend.Draw(SDL::Rect(dst.Position(), dst.w*money/capacity, dst.h), col);
        rend.DrawBorder(dst, SDL::Color::White());
        for(size_t i=section;i<capacity;i+=section)
		{
            rend.Draw(SDL::Line(SDL::Point(dst.x+dst.w*i/capacity, dst.y), SDL::Point(dst.x+dst.w*i/capacity, dst.y+dst.h-1)), SDL::Color::White());
		}
	}
};