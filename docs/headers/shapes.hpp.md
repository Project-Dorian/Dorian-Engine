---
aliases:
  - <drn/math/shapes.hpp>
---
# `#include <drn/math/shapes.hpp>`

This is a mathematic header file that focuses primarily on shape generation, and other graph theory algorithms. This focuses more on 2D and 3D shape generation such as basic polygons, but there will be more to be considered in the future.

Name | Type | Description
--|--|--
`PolygonVerts2D(int s)` | drn::Vec2\<float>* function | Generates an array of vertices for a basic 2D shape 
`PolygonEdges2D(int s)` | int* function | Generates the OpenGL edges of a basic 2D shape

## Mathematics
This was not possible to write code for without mathematically conceptualizing the information. Here's what to understand.

### 2D Polygons
let $G(s)=(V(s), E(s))$ be a graph functions, where $s\in\mathbb{Z}$ is the number of sides.
$|V(s)|=s+1$ because we need to consider a center vertex to draw the polygon with triangles.

let $V(s)$ an array of vertices where $V(s)_n\in\mathbb{R}^2$

When generating 2D polygons, I came to realize it is basically just making a circle with less vertices. Therefore, to generate the positions of vertices, we use the following:
$$
V(s)_0=\vec{0}, V(s)_n=\biggl\langle\cos\left(\frac{n2\pi}{s}\right),\sin\left(\frac{n2\pi}{s}\right)\biggr\rangle
$$

As for the edges, we can use the following adjacency matrix to generate the edges:
$$
E(s)=\begin{bmatrix}
0 & 1 & 1 & 1 & 1 & 0 & ... & 1 & 1 \\
1 & 0 & 1 & 0 & 0 & 0 & ... & 0 & 1 \\
1 & 1 & 0 & 1 & 0 & 0 & ... & 0 & 0 \\
1 & 0 & 1 & 0 & 1 & 0 & ... & 0 & 0 \\
1 & 0 & 0 & 1 & 0 & 1 & ... & 0 & 0 \\
\vdots & \vdots & \vdots & \vdots & \vdots & \vdots & & \vdots & \vdots \\
1 & 1 & 0 & 0 & 0 & 0 & ... & 1 & 0 
\end{bmatrix}
$$
All edges need to be connected to the center. Thats what is happening on the top row, and the very left column, excluding $E(s)_{0\,0}$
> Example: Adjacency matrix of a pentagon made of triangles
> $$
E(5)=\begin{bmatrix}
0 & 1 & 1 & 1 & 1 & 1 \\
1 & 0 & 1 & 0 & 0 & 1 \\
1 & 1 & 0 & 1 & 0 & 0 \\
1 & 0 & 1 & 0 & 1 & 0 \\
1 & 0 & 0 & 1 & 0 & 1 \\
1 & 1 & 0 & 0 & 1 & 0
\end{bmatrix}
$$
in the end, we can also notate $E(s)=\{\{v_0, v_1\}, \{v_0, v_2\}, ... \{v_0, v_s\}\} \cup \{\{v_1, v_2\}, \{v_2, v_3\}, ... \{v_{s-1}, v_s\}, \{v_s, v_1\}\}$

finally, we can generate faces with the following cycle walks:
$$
let\space i\in\mathbb{Z}, 0<s<s,
W(s)_i=0\{0,i\}i\{i,i+1\}(i+1)\{i+1, 0\}0
$$
where the final walk goes as following:
$$
W(s)_s=0\{0,s\}s\{s,1\}1\{1,0\}0
$$

## `drn::Vec2<float>* PolygonVerts2D(int s)`
This function generates and returns the vertices of a 2D polygon made of triangles based on the number of sides input.