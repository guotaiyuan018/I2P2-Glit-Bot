#ifndef DATACENTER_H_INCLUDED
#define DATACENTER_H_INCLUDED
#include <vector>
#include <list>
#include "Hero.h"
#include "Bullet.h"

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

private:
    std::list<Hero *> heroSet;
    std::vector<Bullet *> bulletSet;
};
extern DataCenter *const DC;

#endif
