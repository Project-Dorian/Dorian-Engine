---
aliases:
  - <drn/boolArray.hpp>
---
# `#include <drn/boolArray.hpp>`

The Goal of boolArray.hpp is to optimize bit management for boolean arrays as much as possible. Due to memory stored in groups of 8, each `drn::BoolArray` has a size of 8*size bits.

Name | Type | Description
--|--|--
`drn::BoolArray` | class | The standard boolean array

## `class drn::BoolArray`

```cpp
drn::BoolArray A(ui8 size);
```

Name | Type | Description
--|--|--
`BoolArray(ui8 size)` | Constructor | The Constructor used to create a Boolean Array of size `8*size`
`binary()` | char* | Returns the binary form of the data
`ascii()` | char* | Returns the binary data as characters
`on(unsigned long long i)` | bool | assigns 1 to the bit and returns it
`off(unsigned long long i)` | bool | assigns 0 to the bit and returns it
`operator[](unsigned long long i)` | bool | returns the ith index of the bool array.
`operator=(std::string data)` | Operator | Assigns the information stored in the Boolean Array

### `BoolArray(ui8 size)`

### `binary()`

### `ascii()`

### `on(unsigned long long i)`

### `off(unsigned long long i)`

### `operator[](unsigned long long i)`

### `operator=(unsigned long long i)`
