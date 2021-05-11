# 3D-Visualizer_st
a 3D-visualizer for .st file generated in project autoknit(https://github.com/textiles-lab/autoknit) and my personal project Scan2knit(https://github.com/ZiniuLu/Scan2knit)

## Image

![1](image/1.JPG)

![2](image/2.JPG)



## Install

1. install libigl at first
2. install `3D-Visualizer_st` and generate `.sln` file

```bash
git clone https://github.com/ZiniuLu/Scan2knit.git
mkdir build
cd build
cmake-gui ..
```

3. open `.sln` file in Visual Studio 2019
4. set `3D-Visualizer_st` as Startup project
5. Build & Run

## Usage

1. copy .st file into directory `./data/`
2. change the path of `.st` file in the `main` function

For example:

```c++
std::string path = "../data/teddy3.st";
```

