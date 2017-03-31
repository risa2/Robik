#pragma once

class AttackingFighter: public virtual Fighter
{
protected:
	uint32 damage;
	void Attack(Fighter& enemy)
	{
        enemy.BeAttacked(*this, damage);
	}
public:
	AttackingFighter(uint32 damage): damage(damage){}
};