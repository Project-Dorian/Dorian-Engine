The goal of the Dorian Game Engine is to make the development of 2.5D games easier, while keeping the skills of making a high quality game available.

# Game Engine Header Hierarchy
Although the game engine relies on fundamental modules, you will realize that you do not need to include some of these libraries as they are being used by other libraries such as the main library relying on graphics, or graphics just straight up relying on the vector library. The hierarchy is shown below. 

```nomnoml
[vec]->[graphics]
[vec]->[dorian (main)]

[dorian (main)]->[ui]
[dorian (main)]->[scenes]

[scenes]->[luanode]

[graphics]->[ui]

[animation]
```

# The Engine Loop Structure

```nomnoml
[<start>start] -> [Scene Initialization]
[Scene Initialization] -> [SDL Updates]
[SDL Updates|Resize Check|Inputs|Window Reconfigure] -> [Scene Update]
[Scene Update] -> [Prepare OpenGL Data|Store Verticies/Indecies|Calculate Normals|Prepare Shaders]
[Prepare OpenGL Data] -> [Scene Draw]
[Scene Draw] -> [OpenGL Draw]
[OpenGL Draw] -> [SDL Updates]

[<reference>m_CurrentScene->Init()] -- [Scene Initialization]
[<reference>m_CurrentScene->Update()] -- [Scene Update]
[<reference>m_CurrentScene->Draw()] -- [Scene Draw]
```
Scene Initialization
- Calls `m_CurrentScene->init()` once to initialize the scene

SDL Updates
- See Above

Scene Update
- Calls `m_CurrentScene->Update()` to run any calculations needed before drawing

Prepare OpenGL Data
- Prepares Variables for inserting information into the OpenGL buffer

Scene Draw
- Calls `m_CurrentScene->Draw()` to pull drawing information
- This loads the OpenGL Renderer with any information required.

OpenGL Draw
- Actually draws the information recorded