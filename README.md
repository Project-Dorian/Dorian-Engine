# Dorian Engine

<img src="https://badgen.net/badge/icon/typescript?icon=typescript&label" />
<img src="https://badgen.net/badge/icon/C++?icon=terminal&label" />
<img src="https://badgen.net/badge/icon/npm?icon=npm&label" />

The Dorian Engine is a flexible C++ and Lua based game engine to make 2D and, more importantly, 2.5D games. The interface allows you to either work alone effortlessly, or if you wish to work with a team, you can host the game on one computer, and develop on multiple computers through a web based workspace.

## Development
You will need the following skills for development:
- MinGW/GCC (g++)
- git
- SDL2
- luaJIT

```sh
git clone ___
cd ___
make build_engine
```

## Testing
you can run the tests after via `make run_test FILE={TestName}` which takes `tests/{TestName}.cpp`, and compiles it with the game engine, then runs it as a test.