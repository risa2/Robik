#pragma once

class ProgressOfZombieKilling
{
private:
	SDL::Font font=SDL::Font("font.ttf", 20);
	uint32 killed=0;
	ZombieCreator& zombies;
public:
	ProgressOfZombieKilling(ZombieCreator& zom):zombies(zom){}
    void IncreaseKilled(uint32 newkilled)
    {
    	killed+=newkilled;
    }
    bool YouWin()
    {
    	return killed==zombies.TotalZombies();
    }
    void DrawOn(SDL::Renderer& rend, SDL::Rect dst)
    {
    	rend.Draw(SDL::Rect(dst.Position(), dst.w*killed/zombies.TotalZombies(), dst.h), SDL::Color::Cyan());
    	rend.Draw(SDL::Rect(dst.Position()+SDL::Point(dst.w*killed/zombies.TotalZombies(), 0), dst.w-dst.w*killed/zombies.TotalZombies(), dst.h), SDL::Color::Black());
		auto progresstext=to_string(killed*100/zombies.TotalZombies())+"%";
		rend.Draw(font, progresstext, SDL::Color::White(), SDL::Point((rend.GetOutputSize().w-font.TextSize(progresstext).w)/2,0));
    }
};