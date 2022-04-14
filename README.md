# Installation

Box currently requires:
 * bash shell
 * git
 * cmake version 3.0 or higher

## MacOS dependencies
Install xcode command line tools (if it doesn't work try install full xcode):

    xcode-select --install

Install homebrew ([brew.sh](https://brew.sh)), then:

    brew install git git-lfs cmake libsndfile
    
## Ubuntu / Debian dependencies
    sudo apt install build-essential git git-lfs cmake libsndfile1-dev libassimp-dev libasound-dev libxrandr-dev libopengl-dev libxinerama-dev libxcursor-dev libxi-dev

## Creating a new project based on allotemplate
On a bash shell:

    git clone https://github.com/wang-edward/box.git
    cd box
    ./init.sh

This will prepare the project as a fresh git repository and will add allolib and al_ext as submodules.

## How to compile / run
The src/ folder contains the initial main.cpp starter code.

On a bash shell you can run:

    ./configure.sh
    ./run.sh

This will configure and compile the project, and run the binary if compilation is successful.

Alternatively, you can open the CMakeLists.txt proeject in an IDE like VS Code, Visual Studio or Qt Creator and have the IDE manage the configuration and execution of cmake.

You can also generate other IDE projects through cmake.

## How to perform a distclean
If you need to delete the build,

    ./distclean.sh

should recursively clean all the build directories of the project including those of allolib and its submodules.
