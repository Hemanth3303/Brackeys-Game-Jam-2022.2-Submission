# Brackeys-Game-Jam-2022.2-Submission
My submission to [Brackeys Game Jam 2022.2](https://itch.io/jam/brackeys-8)

## Dependencies
[glfw](https://www.glfw.org/): for windowing<br/>
[glad](https://glad.dav1d.de/): for accessing OpenGL functions<br>
[cglm](https://github.com/recp/cglm): for opengl maths<br>
[stb](https://github.com/nothings/stb): specifically [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h) for loading textures<br>
[collections-c](https://github.com/srdja/Collections-C): for data structures like dynamic arrays, queues, etc since C doesn't have any of those inbuilt<br>

## Build Instructions
This project used [premake5](https://premake.github.io/) to generate build files<br>
After installing premake5 and adding it to path, run: `premake5 --help` to see available options<br>
example:<br>
Run `premake5 gmake2` to generate makefiles<br>
Run `premake5 vs2022` to generate a visual studio 2022 solution<br>
