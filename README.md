# Langton's Ant

A visualization of a turmite Turing machine with Langton's Ant ruleset using OpenCV.

## Install  
* On Linux, navigate to the project directory.
* Enter 'cmake .' to create Makefile.
* Enter 'make' to compile the code.

## Parameters
$ [program] [string: language/commands] [steps]

## Example Commands
./langton LR 1000000

![](/img/LR.png)

./langton RL 1000000

![](/img/RL.png)

./langton RLR 4000000

![](/img/RLR.png)

./langton LLRR 1000000

![](/img/LLRR.png)

./langton LRRRRRLLR 40000000

![](/img/LRRRRRLLR.png)

./langton LLRRRLRLRLLR 4000000

![](/img/LLRRRLRLRLLR.png)

### Required Packages:
* GCC 4.4.x or later
* CMake 2.6 or higher
* GTK+2.x or higher, including headers (libgtk2.0-dev)
* pkg-config
* ffmpeg or libav development packages: libavcodec-dev, libavformat-dev, libswscale-dev
* libtbb2 libtbb-dev
* libdc1394 2.x
* libjpeg-dev, libpng-dev, libtiff-dev, libjasper-dev, libdc1394-22-dev

#### OpenCV:
https://github.com/opencv/opencv

http://docs.opencv.org/2.4/doc/tutorials/introduction/linux_install/linux_install.html

### Further Readings:
https://en.wikipedia.org/wiki/Langton%27s_ant

http://mathworld.wolfram.com/LangtonsAnt.html
