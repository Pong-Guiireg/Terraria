#ifndef GLOBAL_H
#define GLOBAL_H

#include "player.h"
#include "world.h"

// Variables globales partagées entre les modules
extern Player player_instance;
extern World world_instance;

#endif // GLOBAL_H
