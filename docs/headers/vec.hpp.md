---
aliases:
  - <drn/math/vec.hpp>
---
# `#include <drn/math/vec.hpp>`

this is a fundamental library for the majority of the Dorian engine. This is where most of the math is performed through.
## Vectors Basics
$$
let\space \vec{u}=\langle u_1, u_2, ..., u_n\rangle, \vec{v}=\langle v_1, v_2, ..., v_n\rangle \in \mathbb{R^n},\space a\in \mathbb{R}
$$
### Adding/Subtracting Vectors
When Adding and Subtracting vectors, you just add the components.
$$
\vec{u}+\vec{v}=\langle u_1+v_1, u_2+v_2, ..., u_n+v_n\rangle
$$
### Multiplying a Vector with a Scalar
Although in the code you will have no choice but to place the scalar after the vector, you usually have the scalar number to the left. Either way, it should look something like this.
$$
a\vec{v}=\langle av_1, av_2, ..., av_n\rangle
$$
### Dot Product of Vectors
$$
\vec{u}\cdot\vec{v}=\sum^{n}_{i=1}u_iv_i
$$


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
This function returns the cross product of this vector, and vector $\vec{u}$. This is usually a vector that is orthogonal to both vectors.

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
`rotate(drn::Vec3<T> a)` | `drn::Vec3<T>` | returns a point rotated `a` radians around $\langle 0, 0, 0\rangle$

### `drn::Vec3<T> drn::Vec3<T>::Cross(drn::Vec3<T> u)`
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

### `drn::Vec3<T> drn::Vec3<T>::rotate(drn::Vec3<T> a)`
returns a point rotated `a` radians around $\langle 0, 0, 0\rangle$

Based on the matrix formula from [Wikipedia - 3D Projection](https://en.wikipedia.org/wiki/3D_projection), we multiply 3 matricies with the base vector.
$$
\begin{bmatrix}
1 & 0 & 0 \\
0 & cos(\theta_x) & sin(\theta_x) \\
0 & -sin(\theta_x) & cos(\theta_x)
\end{bmatrix}
\begin{bmatrix}
cos(\theta_y) & 0 & -sin(\theta_y) \\
0 & 1 & 0 \\
sin(\theta_y) & 0 & cos(\theta_y)
\end{bmatrix}
\begin{bmatrix}
cos(\theta_z) & sin(\theta_z) & 0 \\
-sin(\theta_z) & cos(\theta_z) & 0 \\
0 & 0 & 1
\end{bmatrix}
(\vec{a}-\vec{c})
$$