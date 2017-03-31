#pragma once

bool End(Survive who, bool lastzombies)
{
	return lastzombies&&who!=Survive::Both;
}
void Message(Survive gamestate)
{
	if(gamestate==Survive::Zombies)
	{
		SDL::MessageBox::Show("Konec hry", "Prohra!");
	}
	if(gamestate==Survive::Robik)
	{
		SDL::MessageBox::Show("Konec hry", "Výhra!");
	}
}