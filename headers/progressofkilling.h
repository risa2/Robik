#pragma once

class KillingProgress
{
private:
	SDL::Font font=SDL::Font("font.ttf", 20);
	uint32 killed=0;
	const uint32 zombies;
public:
	KillingProgress(ZombieCreator& zombies):zombies(zombies.TotalZombies()){}
    void IncreaseKilled(uint32 newkilled)
    {
    	killed+=newkilled;
    }
    bool YouWin()
    {
    	return killed==zombies;
    }
    void DrawOn(SDL::Renderer& rend, SDL::Rect dst)
    {
    	rend.Draw(SDL::Rect(dst.Position(), dst.w*killed/zombies, dst.h), SDL::Color::Cyan());
    	rend.Draw(SDL::Rect(dst.Position()+SDL::Point(dst.w*killed/zombies, 0), dst.w-dst.w*killed/zombies, dst.h), SDL::Color::Black());
		auto progresstext=to_string(killed*100/zombies)+"%";
		rend.Draw(font, progresstext, SDL::Color::White(), SDL::Point((rend.GetOutputSize().x-font.TextSize(progresstext).x)/2, 0));
    }
};