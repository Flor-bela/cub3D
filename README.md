*This project has been created as part of the 42 curriculum by medel-ca and fda-roch.*

## Description

cub3D is a faux 3D game engine inspired by the 90s *Wolfenstein 3D*, written in C using the **MiniLibX** graphical library. This project parses a `.cub` file as a 2D grid map into an immersive 3D perspective using ray-casting algorithms.

### Custom Ray-casting Implementation

AQUI HABLAR EN QUE CONSISTE EL RAY-CASTING


#### The Angular Approach (our method)
While many ray-casting tutorials (such as Lodev) use a Vector Plane approach, we used the **Angular Method** for ray generation.

Instead of using a moving camera plane vector, we the player's view orientation as a continuous floating-point angle in radians (`p_angle`). For each vertical column `i` across the `WIDTH` ($1920$), we step through target angles stored inside `start_angle[i]`.

1. **Ray Vector Derivation:**
   For every column, the horizontal and vertical components of the ray are extracted directly via basic trigonometric functions:
   $$\text{ray\_dir\_x} = \cos(\text{ray\_angle})$$
   $$\text{ray\_dir\_y} = \sin(\text{ray\_angle})$$
   The grid delta metrics (`delta_dist_x` and `delta_dist_y`) represent the distance the ray must travel to cross a full grid boundary ($TILE\_SIZE = 64$) and are initialized using:
   $$\Delta\text{dist}_x = \left| \frac{1}{\cos(\text{ray\_angle})} \right|, \quad \Delta\text{dist}_y = \left| \frac{1}{\sin(\text{ray\_angle})} \right|$$

2. **Digital Differential Analysis (DDA):**
   Using `perform_dda`, the ray steps incrementally across grid intersections. Variables `side_dist_x` and `side_dist_y` track accumulated distance bounds. The traversal advances column-by-column along the shortest dimensional vector until a map grid barrier (`'1'`) is intersected.

3. **Fish-Eye Correction:**
   Because our rays radiate outward at equal angular steps from a central point, computing raw Euclidean distance produces radial lens distortion (flat walls appear curved). To maintain a flat projection plane, we isolate the perpendicular distance by flattening the ray against the player's focal direction vector:
   $$\text{corrected\_dist} = \text{euclidean\_dist} \times \cos(\text{ray\_angle} - \text{player\_angle})$$

4. **Wall Texture Mapping:**

  (VER DE NUEVO ESTA PARTE)

   The intersection axis (`side = 0` for vertical, `side = 1` for horizontal) with the directional step flags (`step_x` / `step_y`) to determine the orientation of the wall (**North**, **South**, **East**, or **West**). 
   The horizontal texture coordinate (`texx`), from raw `.xpm` source files into the frame rendering.

### Key Features
- **Sliding Collision System:** Independent axis checking using a player boundaries threshold (`PLAYER_RADIUS` = 10) to support fluid movement when close to the walls.
- **Minimap:** Toggleable ($2D$) map showing wall grids, player position, and live projection ray casting beams.

## Instructions

### Prerequisites
(CONTINUAR AQUI)

**MiniLibX** dependencies (X11 / Xshm / Xlib).

### Compilation

 `make`

 `make re`


### Execution

For example:

`./cub3D maps/map.cub`


### Controls
**W / S**: Move forward / backward.

**A / D**: Move left / right.

**Left Arrow / Right Arrow**: Rotate camera view perspective.

**M**: Toggle Mouse mode.

**N**: Toggle Minimap.

**ESC / Window Close (X)**: Exits the game.

## Resources

#### Raycasting:

- [Lode's Computer Graphics Tutorial](https://lodev.org/cgtutor/raycasting.html)
- https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/
- https://42-fran-byte-f94097.gitlab.io/docs/cub3d/cub3d-approach-es/#/
- https://hackmd.io/@nszl/H1LXByIE2
- https://devabdilah.medium.com/3d-ray-casting-game-with-cub3d-7a116376056a


#### AI Usage