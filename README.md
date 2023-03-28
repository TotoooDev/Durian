# Durian

A wannabe 2D game engine

## Lua functions you can call

### Logging

- `Durian_LogInfo`
- `Durian_LogWarn`
- `Durian_LogError`

### Component manipulation

- Transform component
    - `Durian_AttachTransform`
    - `Durian_DetachTransform`
- Sprite component
    - `Durian_AttachSprite`
    - `Durian_DetachSprite`
- Sound emitter component
    - `Durian_AttachSoundEmitter`
    - `Durian_DetachSoundEmitter`
    - `Durian_SoundLoad`
    - `Durian_SoundPlay`
    - `Durian_SoundVolume` (doesn't work according to the comments in my code, didn't test it though)

### Scene

- `Durian_GetEntityByName`

### Events

- Keyboard
    - `Durian_EventKeyDown`
    - `Durian_EventKeyUp`
- Mouse
    - `Durian_EventMouseMoved`
    - `Durian_EventMouseButtonDown`
    - `Durian_EventMouseButtonUp`
    - `Durian_EventMouseScrolled`
- Window
    - `Durian_EventWindowPos`
    - `Durian_EventWindowSize`

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
