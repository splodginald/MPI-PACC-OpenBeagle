# MPI-PACC-OpenBeagle
Builds and installs OpenBeagle libraries and examples with optional build/install of MPI and PACC binaries, libraries and includes on Linux systems. This includes the building of the mpi hpc libraries and examples.

Includes bash scripts for build\install and heavy hacking of OpenBeagele's CMakeLists.txt file!

Includes instructions for build\install without administrator permissions.
Source Files
------------

This repository containes files from the following sources:
* [mpich-3.2](http://www.mpich.org/static/downloads/3.2/mpich-3.2.tar.gz)
* [OpenBEAGLE-4.0.0-alpha2-Source](https://code.google.com/p/beagle/downloads/detail?name=OpenBEAGLE-4.0.0-alpha2-Source.tar.gz)
* [pacc-1.4.1-Source](https://sourceforge.net/projects/pacc/files/latest/download)

Installing the source code and build environment.
-------------------------------------------------
There are two options here.
* Cloning the git repository to a directory of your choice (__strongly reccomended__).
* Unzipping an archive to a directory of your choice.

##### Cloning the git repository to a directory of your choice.
In the terminal, navigate to a directory of your choice and run:
git clone https://github.com/splodginald/MPI-PACC-OpenBeagle.git
The source files will be in a subdirectory of your choosen directory.
Example:
My home directory is /home/david
if I navigate to /home/david in the terminal and run:
git clone https://github.com/splodginald/MPI-PACC-OpenBeagle.git
The source code is now in:
/home/david/MPI-PACC-OpenBeagle

##### Unzipping an archive to a directory of your choice.
Go to https://github.com/splodginald/MPI-PACC-OpenBeagle
Click on the "Download ZIP" button.
Extract the .zip file to directory of your choice.
The source files will be in a subdirectory of your choosen directory.
Example:
My home directory is /home/david
If I extract the archive to /home/david
the source code is now in:
/home/david/MPI-PACC-OpenBeagle-master
