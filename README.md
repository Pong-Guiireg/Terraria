## 🧪 Détails d'implémentation

### 📷 Système de caméra
La caméra suit le joueur de manière fluide et respecte les limites du monde :

```c
void update_camera(void)
{
    // Récupérer les dimensions du joueur
    float player_width = player_instance.hitbox.width;
    float player_height = player_instance.hitbox.height;
    // Centrer la caméra sur le joueur
    camera_offset.x = player_instance.position.x - SCREEN_WIDTH / 2 + player_width / 2;
    camera_offset.y = player_instance.position.y - SCREEN_HEIGHT / 2 + player_height / 2;
    // Limiter aux bords du monde
    camera_offset.x = clamp(camera_offset.x, 0, WORLD_WIDTH BLOCK_SIZE - SCREEN_WIDTH);
    camera_offset.y = clamp(camera_offset.y, 0, WORLD_HEIGHT BLOCK_SIZE - SCREEN_HEIGHT);
}
```

### 📦 Gestion des entités
Les entités sont stockées dans un tableau et sont mises à jour dans l'ordre :

```c
void update_entities(void)
{
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        if (entities[i] != NULL)
            entities[i]->update();
    }
}
```

### 🏔️ Plateformes en l'air
Les plateformes volantes sont générées de manière à paraître naturelles :

```c
int platformWidth = 3 + rand() % 8;

// Générer la plateforme avec support
for (int px = 0; px < platformWidth; px++) {
    world->blocks[x + px][platformHeight] = BLOCK_GRASS;

    // Support sous la plateforme (comme un petit îlot)
    for (int py = 1; py < 2 + rand() % 2; py++) {
        if (platformHeight + py < WORLD_HEIGHT) {
            world->blocks[x + px][platformHeight + py] = BLOCK_DIRT;
        }
    }
}
```

### 🏃‍♂️ Physique de saut et gravité
Le système de saut utilise un modèle physique simple avec gravité :

```c
void playerJump(Player *player)
{
    if (!player->isFalling)
    {
        player->velocity.y = -JUMP_FORCE;
        player->isJumping = true;
    }
}

void applyGravity(Player *player)
{
    player->velocity.y += GRAVITY;
    player->velocity.x *= 0.8f;  // Friction horizontale

    // Limiter la vitesse de chute
    if (player->velocity.y > 15.0f)
        player->velocity.y = 15.0f;
}
```

### 🎯 Optimisation du rendu
Seuls les blocs visibles à l'écran sont rendus pour optimiser les performances :

```c
void render_world(void)
{
    // Calculer les limites visibles du monde
    int start_x = (int)(camera_offset.x / BLOCK_SIZE);
    int start_y = (int)(camera_offset.y / BLOCK_SIZE);
    int end_x = start_x + (SCREEN_WIDTH / BLOCK_SIZE) + 2;
    int end_y = start_y + (SCREEN_HEIGHT / BLOCK_SIZE) + 2;

    // Limiter les indices
    start_x = clamp(start_x, 0, WORLD_WIDTH - 1);
    start_y = clamp(start_y, 0, WORLD_HEIGHT - 1);
    end_x = clamp(end_x, 0, WORLD_WIDTH);
    end_y = clamp(end_y, 0, WORLD_HEIGHT);

    // Dessiner uniquement les blocs visibles
    for (int x = start_x; x < end_x; x++) {
        for (int y = start_y; y < end_y; y++) {
            // ...
        }
    }
}
```

## 🔍 Aperçu technique

### ⚙️ Architecture
Le projet utilise une architecture modulaire où chaque composant (joueur, monde, physique) est indépendant. Cette approche facilite la maintenance et l'ajout de nouvelles fonctionnalités.

### 🧩 Modules principaux
- **Joueur** : Gère les entrées utilisateur, les mouvements et l'état du joueur
- **Monde** : S'occupe de la génération et du stockage du monde
- **Physique** : Détecte et résout les collisions
- **Rendu** : Affiche le monde et le joueur à l'écran

### 🔄 Boucle de jeu
La boucle principale suit le modèle classique :
1. Traiter les entrées utilisateur
2. Mettre à jour l'état du jeu
3. Rendre la scène

```c
void runGameLoop(Game *game)
{
    while (!WindowShouldClose() && game->running)
    {
        handleInput(game);
        updateGame(game);
        render_game();
    }
}
```

## 👏 Remerciements
- [Raylib](https://www.raylib.com/) pour la bibliothèque graphique simple et puissante
- [Terraria](https://terraria.org/) pour l'inspiration du jeu original
