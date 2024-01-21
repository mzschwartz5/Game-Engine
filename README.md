# Game-Engine
A home-grown bundle of graphics, physics, and gameplay engines, using with OpenGL and written in C++. 

Currently a work-in-progress.

Next milestone:
- Collision response and rigidbody dynamics

Previous milestones:
- Static collision detection of convex polytopes via GJK method
- Basic rendering engine: https://mattzschwartz.web.app/blog/Game%20Engine%20Part%20I:%20Rendering%20a%20Cube

Future milestones:
- Model loading
- Advanced rendering and lighting
- Level creation / loading 

Developer dependencies / requirements:
- jinja2 for Glad generator (`pip3 install jinja2`)

Steps to build / run (tested on MacOS with clang compiler and vscode)
- Configure:
(for me, this happens automatically when I save the CMakeLists.txt file, but this is the command being run:
```/opt/homebrew/bin/cmake --no-warn-unused-cli -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/clang -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++ -S/Users/matthewschwartz/Game-Engine -B/Users/matthewschwartz/Game-Engine/build -G "Unix Makefiles"```
)

- Build: from the build directory, run `make`
- Execute: run the exectutable, `./GameEngineExecutable`