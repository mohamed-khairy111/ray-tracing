# Ray Tracing Simulation with SDL2

This project demonstrates a basic ray-tracing simulation using SDL2. It visualizes rays originating from a light source, checks for intersections with circular objects, and displays the result. Below is a detailed explanation of the code and the mathematical concepts involved, including relevant formulas.

---


## Compilation and Execution

### Compilation
```bash
 g++ -Llib -o ray raytracing.cpp -lSDL2
```

### Execution
```bash
./ray.exe
```

---

## Features
- **Dynamic Light Source**: A movable light source controlled by mouse motion.
- **Shadow Simulation**: Rays stop when intersecting an obstacle (circle).
- **Basic Rendering**: Uses SDL2 to render circles and rays.

---

## Code Breakdown

### Constants and Macros
- `WIDTH` and `HEIGHT`: Define the window dimensions.
- `COLOR_WHITE`, `COLOR_BLACK`, `COLOR_RAY`: Represent different colors used for rendering.
- `M_PI`: Defines the value of pi for trigonometric calculations.
- `RAYS_NUMBER`: Determines the number of rays to be emitted from the light source.

### Structs
1. **`Circle`**: Represents a circular object with coordinates `(x, y)` and radius `r`.
2. **`Ray`**: Represents a ray with a starting position `(x_start, y_start)` and an angle `angle`.

---

## Functions and Their Role

### `FillCircle`
This function renders a filled circle on the SDL surface.
- Loops through a square bounding box around the circle.
- Uses the circle equation to check if each pixel lies inside.

### `generate_Rays`
Generates an array of rays originating from the center of a circle.
- Divides \(360^\circ\) (or \(2\pi\) radians) into equal segments.
- Initializes rays with starting positions and angles.

### `FillRays`
Simulates and renders rays until they intersect an object or leave the screen.
- Advances each ray in small steps using the parametric equations.
- Stops when the ray satisfies the circle equation or moves out of bounds.

---









