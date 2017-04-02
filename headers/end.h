#pragma once

bool End(Arena& arena, bool win)
{
	return win||arena.DeadRobik(0)||arena.DeadGate(1);
}
void Message(Arena& arena)
{
	if(arena.DeadRobik(0)||arena.DeadGate(1))
	{
		SDL::MessageBox::Show("Konec hry", "Prohra!");
	}
	else
	{
		SDL::MessageBox::Show("Konec hry", "Výhra!");
	}
}