The goal of the Dorian Game Engine is to make the development of 2.5D games easier, while keeping the skills of making a high quality game available.

# Game Engine Hierarchy
Although the game engine relies on fundamental modules, you will realize that you do not need to include some of these libraries as they are being used by other libraries such as the main library relying on graphics, or graphics just straight up relying on the vector library. The hierarchy is shown below. 

```nomnoml
[vec]->[graphics]

[dorian (main)]->[graphics]
[dorian (main)]->[ui]

[graphics]->[ui]

[animation]
```

# How to use
