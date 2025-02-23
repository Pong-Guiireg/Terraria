# 🎮 Terraria Remake

<div align="center">
  <img src="assets/Logo.png" alt="Logo" width="200"/>

  [![Raylib](https://img.shields.io/badge/raylib-4.5.0-orange.svg)](https://www.raylib.com/)
  [![Language](https://img.shields.io/badge/language-C-yellow.svg)]()
</div>

## 📋 Table des Matières
- [🚀 Installation](#-installation)
- [🎯 Fonctionnalités](#-fonctionnalités)
- [🛠️ Technologies](#️-technologies)
- [📚 Documentation](#-documentation)

## 🚀 Installation

### Prérequis
- GCC/Clang
- Make
- [Raylib](https://www.raylib.com/): Une bibliothèque simple et facile à utiliser pour le développement de jeux

### Compilation

```bash
make
```

## 🎯 Fonctionnalités

### Menu Principal
- Interface utilisateur intuitive
- Options de configuration
- Système de sauvegarde (à venir)

### Options
- Configuration des touches :
  ```c
  options_t options = {
      .sound_volume = 0.5f,
      .music_volume = 0.5f,
      .move_up = KEY_Z,
      .move_down = KEY_S,
      .move_left = KEY_Q,
      .move_right = KEY_D,
      .jump = KEY_SPACE
  };
  ```
- Réglages audio
- Interface AZERTY/QWERTY

## 🛠️ Technologies

### Raylib
- Version: 4.5.0
- [Documentation officielle](https://www.raylib.com/cheatsheet/cheatsheet.html)
- Fonctionnalités utilisées:
  - Gestion des fenêtres
  - Entrées clavier/souris
  - Rendu 2D
  - Audio (à venir)

### Structure du Projet

```bash
.
├── Makefile
├── assets/
│ └── Dirt.png
├── include/
│ ├── button.h
│ ├── menu.h
│ ├── options.h
│ ├── sliders.h
│ └── types.h
└── src/
├── main.c
├── menu.c
├── button.c
└── options/
├── options.c
└── sliders.c
```

## 📚 Documentation

### Guides et Ressources
- [Guide d'installation de Raylib](https://github.com/raysan5/raylib/wiki)
- [Tutoriels Raylib](https://www.raylib.com/examples.html)

### Architecture
Le projet suit une architecture modulaire :
- `menu.c`: Gestion du menu principal
- `button.c`: Système de boutons interactifs
- `options/`: Configuration et personnalisation
  - `options.c`: Menu des options
  - `sliders.c`: Composants UI pour les réglages

---
<div align="center">
  Créé avec ❤️ par Guireg
</div>
