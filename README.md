# Durian

A wannabe 2D game engine

## Want to build Durian from source?

### For Windows users

Clone the repository, run GenerateProjects.bat and a solution will be created for you. 

Open the solution and hit the build button (make sure you build in Distribution mode)

### For Linuwux users

First you'll need to install a few depedencies:
- sdl2
- glew

You'll also need to compile Lua from source since the pre-compiled binaries from their website are dynamically-linked and I can't figure out how to put that in premake :(

Once you've compiled Lua, place the ``liblua.a`` file in the ``libs/linux`` folder.

Clone the repository, open a terminal and run ``./GenerateProjects.sh``, then ``make config=distribution`` to build in distribution mode. You can also build in debug mode with ``make config=debug``.
