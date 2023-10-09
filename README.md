# Dorian Engine

The Dorian Engine is a flexible C++ and Lua based game engine to make 2D and, more importantly, 2.5D games. The interface allows you to either work alone effortlessly, or if you wish to work with a team, you can host the game on one computer, and develop on multiple computers through a web based workspace.

## Setup
You will need the following packages for development:
- MinGW/GNU compilers
- node.js (this is to access the interface and builder tools)
- git
- SDL2
- luaJIT

```sh
git clone ___
cd ___
npm install
npm run
```

From there, you will have two options. You can either edit the project via https://localhost:3000, or if you are working as a team locally, your team can edit with the ip address of the computer.

> ### Collaboration
> If you decide to locally collaborate, you are expected to test on a computer that you have easy access to. I would suggest connecting controllers to the testing computer to allow smooth gameplay. Although remote collaboration is possible, it may feel awkward to test.

### Setting Up External Libraries
Due to the libraries being compiled statically, some of these modules may not be available directly out of the box.

#### Lua
This engine was built with [LuaJIT](https://luajit.org/index.html). You should follow the instructions for how to setup the libraries, then place `lua51.dll` into `build/`, and you will place the following headers into `engine/include/`: `lauxlib.h`, `lua.h`, `lua.hpp`, `luajit.h`, `lualib.h`.
 