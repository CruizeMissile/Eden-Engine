# Eden [![Build Status](https://travis-ci.org/CruizeMissile/Eden.svg?branch=master)](https://travis-ci.org/CruizeMissile/Eden) [![Build status](https://ci.appveyor.com/api/projects/status/99dlxhm5tfkie1ik/branch/master?svg=true)](https://ci.appveyor.com/project/CruizeMissile/eden/branch/master)

Eden is a cross platform c++ game engine. It is archetected around Entity-Component-System and a multi api renderer.

# Quick start
#### Note: Currently Eden is developed on windows and linux (manjaro/arch). Eden uses the lastest and greatest c++ 17 features.

### Windows
``` bash
$ git submodule update --init --recursive
$ cmake . -Bbuild -G "Visual Studio 15 2017 Win64"
$ cmake --build build
```

### Linux
``` bash
$ git submodule update --init --recursive
$ cmake . -Bbuild
$ cmake --build build
```

# In development
Eden is currently in development and is not feature complete.

# Dependencies
All Dependencies used under their respective licenses. Copyright is held by their respective owners.
* [Catch](https://github.com/philsquared/Catch)
* [Glew](http://glew.sourceforge.net)
* [Gsl](https://github.com/Microsoft/GSL)
* [Loguru](https://github.com/emilk/loguru)
* [Vulkan](https://www.khronos.org/vulkan/)
