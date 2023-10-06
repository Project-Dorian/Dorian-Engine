---
aliases:
  - <drn/vec.hpp>
---
`#include <drn/vec.hpp>`

this is a fundamental library for the majority of the Dorian engine. This is where most of the math is performed through.

Name | Type | Description
--|--|--
`ZERO_VECTOR` | macro | General macro for a zero vector. Works with any size vector
`drn::Vec3<T>` | template struct | A basic template structure for 3D vectors
`drn::Vec2<T>` | template struct | A basic template structure for 2D vectors

# `struct drn::Vec2<class T>`
A basic template structure for 2D vectors in C++. This is a foundational data type for the majority of the game engine. This can be mathematically presented as followed.
$$\vec{v}=\langle x, y \rangle,\space x, y \in \mathbb{T}$$
```cpp
template <class T>
struct drn::Vec2 {T X, T Y};
```
X and Y default to 0, but it is heavily unsuggested, because that is intended for the `ZERO_VECTOR` Definition.

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

## `T drn::Vec2<T>.Cross(drn::Vec2<T> u)`
returns the cross product of this vector, and vector $\vec{u}$

Mathematical representation of what is going on
$$
let\space\vec{u}=\langle u_x,u_y\rangle,\space\vec{v}=\langle v_x,v_y\rangle; u_x,u_y,v_x,v_y\in\mathbb{R}
$$
$$
\vec{v}\times\vec{u}=\begin{vmatrix}
v_x&v_y\\u_x&u_y
\end{vmatrix}
=v_xu_y-v_yu_x
$$