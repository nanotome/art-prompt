# art-prompt
Desktop app to generate prompts for art practice

## Quick Start

You will need CMake to build the code. If you're using Windows, you need Visual Studio 2017 in addition to CMake.

First, clone the code:

```sh
git clone https://github.com/gnerkus/art-prompt.git --recursive
cd art-prompt
```

### C++ API

For macOS or Linux or Windows Subsystem for Linux (WSL):

```sh
mkdir build
cd build
cmake ..
make
```

For Windows:

```sh
mkdir build
cd build
cmake .. -G"Visual Studio 15 2017 Win64"
MSBuild ArtPrompt.sln /p:Configuration=Release
```
