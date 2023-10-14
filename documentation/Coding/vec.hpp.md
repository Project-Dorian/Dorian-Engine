---
aliases:
  - <drn/vec.hpp>
---
# `#include <drn/vec.hpp>`

this is a fundamental library for the majority of the Dorian engine. This is where most of the math is performed through.

Name | Type | Description
--|--|--
`ZERO_VECTOR` | macro | General macro for a zero vector. Works with any size vector
`drn::Vec3<T>` | template struct | A basic template structure for 3D vectors
`drn::Vec2<T>` | template struct | A basic template structure for 2D vectors

## `struct drn::Vec2<class T>`
A basic template structure for 2D vectors in C++. This is a foundational data type for the majority of the game engine.
$$\vec{v}=\langle x, y \rangle,\space x, y \in \text{T}$$
```cpp
drn::Vec2<T> v = {(T)X, (T)Y};
```
X and Y default to 0, however it is preferred to use the `ZERO_VECTOR` Definition to represent $\vec{0}$.

Property | Type | Description
--|--|--
`X` | `T` | the X coordinate property
`Y` | `T` | the Y coordinate property
`operator+(drn::Vec2<T> u)` | `drn::Vec2<T>` | returns $\vec{v}+\vec{u}$
`operator-(drn::Vec2<T> u)` | `drn::Vec2<T>` | returns $\vec{v}-\vec{u}$
`operator*(T a)` | `drn::Vec2<T>` | returns $a\vec{v}$
`Dot(drn::Vec2<T> u)` | `T` | return the dot product of $\vec{v}\cdot\vec{u}$
`Cross(drn::Vec2<T> u)` | `T` | return the cross product of $\vec{v}\times\vec{u}$ in scalar form
`length()` | `float` | returns $\mid \vec{v} \mid$

### `T drn::Vec2<T>.Cross(drn::Vec2<T> u)`
returns the cross product of this vector, and vector $\vec{u}$

Mathematical representation of a scalar cross product with vectors of $\mathbb{R}^2$.
$$
let\space\vec{u}=\langle u_x,u_y\rangle,\space\vec{v}=\langle v_x,v_y\rangle; u_x,u_y,v_x,v_y\in\mathbb{R}
$$
$$
\vec{v}\times\vec{u}=\begin{vmatrix}
v_x&v_y\\u_x&u_y
\end{vmatrix}
=v_xu_y-v_yu_x
$$

## `struct drn::Vec3<class T>`
A basic template structure for 3D vectors in C++. This is a foundational data type for the 3D graphics of the game engine.
$$\vec{v}=\langle x, y, z\rangle,\space x, y, z \in \text{T}$$
```cpp
drn::Vec2<T> v = {(T)X, (T)Y};
```
X, Y, and Z default to 0, however it is preferred to use the `ZERO_VECTOR` Definition if you need $\vec{0}$.

Property | Type | Description
--|--|--
`X` | `T` | the X coordinate property
`Y` | `T` | the Y coordinate property
`Z` | `T` | the Z coordinate property
`operator+(drn::Vec3<T> u)` | `drn::Vec3<T>` | returns $\vec{v}+\vec{u}$
`operator-(drn::Vec3<T> u)` | `drn::Vec3<T>` | returns $\vec{v}-\vec{u}$
`operator*(T a)` | `drn::Vec3<T>` | returns $a\vec{v}$
`Dot(drn::Vec3<T> u)` | `T` | return the dot product of $\vec{v}\cdot\vec{u}$
`Cross(drn::Vec3<T> u)` | `drn::Vec3<T>` | return the cross product of $\vec{v}\times\vec{u}$ in scalar form
`length()` | `float` | returns $\mid \vec{v} \mid$

### `T drn::Vec3<T>.Cross(drn::Vec3<T> u)`
returns the cross product of this vector, and vector $\vec{u}$

Mathematical representation of a traditional cross product with vectors of $\mathbb{R}^3$.
$$
let\space\vec{u}=\langle u_x,u_y,u_z\rangle,\space\vec{v}=\langle v_x,v_y,v_z\rangle; u_x,u_y,u_z,v_x,v_y,v_z\in\mathbb{R}
$$
$$
\vec{v}\times\vec{u}=\begin{vmatrix}
\hat{i} & \hat{j} & \hat{k} \\
v_x & v_y & v_z \\
u_x & u_y & u_z
\end{vmatrix}
=\langle v_yu_z-v_zu_y, -(v_xu_z-v_zu_x), v_xu_y-v_yu_x\rangle
$$