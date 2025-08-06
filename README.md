# Cub3D - Raycasting Engine
[![42 School: Rank 4](https://img.shields.io/badge/42%20School-Rank%204-%2315bbbb)](https://www.42network.org/)

_The goal of this project was to create a simple Wolfenstein 3D-inspired 3D game engine, using raycasting. This is done by rendering a 3D representation of a 2D map, implementing player movement, walls, textures and collision detection, while using MiniLibX graphics library._

___


### Table of contents
[Usage](#usage) · [License](#license) · [References & further reading](#references--further-reading)

</br>

![demo](assets/cub3D.gif)

</br>

___

## Features

- Raycasting algorithm to render walls in a pseudo-3D perspective

- Texture mapping for different wall orientations

- Player movement with collision detection

- Camera rotation

- Configurable map parsing from `.cub` files

- Error handling and memory management

</br>

## Usage
### Setup and compilation

1. Clone repository
    ```bash
    git clone git@github.com:teresa-chow/42-cub3d.git cub3D
    ```

2. Go inside project directory and run `make bonus`
    ```bash
    cd cub3D
    make bonus
    ```

3. Execute `./cub3D_bonus` program
    ```bash
    ./cub3D_bonus path/to/map.cub
    ```

</br>

### Testing script
Includes a custom script to:

- Compile and run the project with sample maps (both valid and invalid)

- Check for memory leaks and error handling

- Validate edge cases (invalid maps, configurations, etc.)

```bash
./assets/test_leaks.sh
```

</br>

___

### Team

Carlos Teixeira [@Carlos688940](https://github.com/Carlos688940)

Teresa Chow (me)

</br>

### License
This work is published under the terms of [MIT License](./LICENSE).

</br>

#### References & further reading

- 42 Docs: [MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx.html)

- Lode's Computer Graphics Tutorial: [Flood Fill](https://lodev.org/cgtutor/floodfill.html)

- Lode's Computer Graphics Tutorial: [Raycasting](https://lodev.org/cgtutor/raycasting.html)

- 3DSage: [Make Your Own Raycaster](https://www.youtube.com/watch?v=gYRrGTC7GtA) [series]

</br></br>

[⬆ back to top](#cub3d---raycasting-engine)

deleteme
