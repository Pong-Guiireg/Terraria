#ifndef PHYSICS_H
#define PHYSICS_H

#include <raylib.h>
#include <stdbool.h>

// Déclaration anticipée pour éviter les dépendances circulaires
struct World;  // Supprimé le typedef ici pour éviter le conflit

bool checkCollision(Rectangle a, Rectangle b);
bool checkWorldCollision(Rectangle hitbox, struct World *world, Vector2 *correction);

#endif // PHYSICS_H
