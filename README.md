# Ray Tracing Simulation with SDL2

This project demonstrates a basic ray-tracing simulation using SDL2. It visualizes rays originating from a light source, checks for intersections with circular objects, and displays the result. Below is a detailed explanation of the code and the mathematical concepts involved, including relevant formulas.

---
## Check out the simulation in action:
![Simulation in Action](./RayTracing 2024-12-29 22-17-01.gif)


## Compilation and Execution

### Compilation
```bash
g++ -o RayTracing main.cpp -lSDL2 -lm
```

### Execution
```bash
./RayTracing
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

### 2. Ray Representation

A ray is a semi-infinite line that starts from a point and extends in one direction. The parametric equations of a ray starting at \((x_0, y_0)\) with an angle \(\theta\) are:

\[
x = x_0 + t \cos(\theta)
\]
\[
y = y_0 + t \sin(\theta)
\]

Where:
- \(t\): A positive parameter that moves the point along the ray.
- \(\cos(\theta), \sin(\theta)\): Trigonometric functions that determine the direction of the ray.

In the simulation, \(t\) is incremented step by step to trace the path of the ray.

---

### 3. Intersection of a Ray and a Circle

To determine if a ray intersects a circle, we check whether the ray’s path satisfies the circle equation. Substituting the ray’s parametric equations into the circle equation, we get:

\[
\left( x_0 + t \cos(\theta) - x_c \right)^2 + \left( y_0 + t \sin(\theta) - y_c \right)^2 = r^2
\]

Expanding and rearranging this quadratic equation in terms of \(t\):

\[
a t^2 + b t + c = 0
\]

Where:
- \(a = \cos^2(\theta) + \sin^2(\theta) = 1\) (by the Pythagorean identity).
- \(b = 2 \left( \cos(\theta) (x_0 - x_c) + \sin(\theta) (y_0 - y_c) \right)\)
- \(c = (x_0 - x_c)^2 + (y_0 - y_c)^2 - r^2\)

The discriminant of this quadratic equation, \(\Delta = b^2 - 4ac\), determines the intersection:
- \(\Delta > 0\): Two intersection points.
- \(\Delta = 0\): Tangent to the circle (one intersection point).
- \(\Delta < 0\): No intersection.

In our simulation, the rays terminate upon intersection.

---

### 4. Trigonometry in Ray Generation

To evenly distribute rays around the light source, the angles are divided uniformly:

\[
\theta_i = \frac{i}{N} \times 2\pi, \quad i = 0, 1, 2, \ldots, N-1
\]

Where:
- \(N\): Total number of rays.
- \(\theta_i\): Angle of the \(i\)-th ray.

The rays are then computed using their parametric equations.

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









