# OpenGL starter

This is a starter project for a cmake OpenGL, GLFW, glad project. There are a lot of things you need to initialize and write to create a simple OpenGL project. This repository tries to help start an OpenGL project.

## Building

In order to build, you need to install the requirements to build GLFW and glad from source.
As of right now, glad requires Jinja2 python package, and GLFW requires multiple packages and libraries to be installed. See [Compiling GLFW](https://www.glfw.org/docs/latest/compile.html) for details.

After the requirements are installed, run the following commands in this repository.
```
cmake .
cmake --build .
```

Then, you can run the application.
```
./opengl_starter
```

## References

These references can be relevant to this project.
* [GLFW](https://www.glfw.org/),
* [glad](https://github.com/Dav1dde/glad/),
* tutorials by Victor Gordan [repository](https://github.com/VictorGordan/opengl-tutorials), [videos](https://www.youtube.com/playlist?list=PLPaoO-vpZnumdcb4tZc4x5Q-v7CkrQ6M-),
* tutorials by Joey de Vries [repository](https://github.com/JoeyDeVries/LearnOpenGL), [website](https://learnopengl.com),
* tutorials by Opengl-tutorials [repository](https://github.com/opengl-tutorials/ogl), [website](https://www.opengl-tutorial.org/),
* tutorials by GamesWithGabe [repository](https://github.com/codingminecraft/MinecraftCloneForYoutube/), [videos](https://www.youtube.com/playlist?list=PLtrSb4XxIVbodGYZZVzC1PAZfwckrXp_X).
