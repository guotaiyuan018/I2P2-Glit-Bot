#ifndef DATACENTER_H_INCLUDED
#define DATACENTER_H_INCLUDED
#include <vector>
#include <list>
#include "Hero.h"
#include "Bullet.h"
#include "Monster.h"
#include "Boss.h"

class DataCenter
{
public:
    std::list<Hero *> &get_Hero()
    {
        return heroSet;
    }

    std::vector<Bullet *> &get_Bullet()
    {
        return bulletSet;
    }
    std::vector<Monster *> &get_Monster()
    {
        return monsterSet;
    }
    std::list<Boss *> &get_Boss()
    {
        return bossSet;
    }

private:
    std::list<Hero *> heroSet;
    std::vector<Bullet *> bulletSet;
    std::vector<Monster *> monsterSet;
    std::list<Boss *> bossSet;
};
extern DataCenter *const DC;

#endif
