# Set up Qt 6.4 & OpenCV 4.7.0

## Qt

### 1- Download Files

```
1 - Download Qt 6.4 from Qt installer
make sure I am choosing mingw64 from the tools and inside the qt version
```

```
2- Download OpenCV 4.7.0 from
https://opencv.org/releases/
uncompress the files to any folder you like
```

```
3-Download cmake-gui from
https://cmake.org/download/
set up the program
make sure you check the "add to system enviroments for all user check box"
```


### 2- Set up system enviroment

```
Go to C:\Qt\6.4.2\mingw_64\bin
Copy the path
Put it in System Enviroments
Make sure you make at the top of the list
```

```
Go to C:\Qt\Tools\mingw1120_64\bin
Copy the path
Put it in System Enviroments
Make sure you make at the top of the list put under the above path
```


### 3- Compiling OpenCV

```
Go to <Your openCV Directory>
you will find 2 folders "sources" & "build"
create folder "release"
```

open cmake-gui

```
where is the source code: <Your openCV Directory>\sources
where to build the binaries:  <Your openCV Directory>\release
```

Then click Configure, let cmake create the build directory, and choose the following settings:

```
Specify the generator for this project: MinGW Makefiles
Specify native compilers, next
Compilers C: D:\Qt\Tools\Tools\mingw1120_64\bin\gcc.exe
Compilers C++: D:\Qt\Tools\Tools\mingw1120_64\bin\g++.exe
Finish
```

```
Check the box [X]WITH_QT
Check the box [X]WITH_OPENGL
```

```
Uncheck the box []ENABLE_PRECOMPILED_HEADERS if checked
```

make sure that the qt looks likes like this 

```
QT_MAKE_EXECUTABLE to C:\Qt\6.4.2\mingw_64\bin\qmake.exe
Qt5Concurrent_DIR to C:\Qt\6.4.2\mingw_64\lib\cmake\Qt5Concurrent
Qt5Core_DIR to C:\Qt\6.4.2\mingw_64\lib\cmake\Qt6Core
Qt5Gui_DIR to C:\Qt\6.4.2\mingw_64\lib\cmake\Qt6Gui
Qt5Test_DIR to C:\Qt\6.4.2\mingw_64\lib\cmake\Qt6Test
Qt5Widgets_DIR to C:\Qt\6.4.2\mingw_64\lib\cmake\Qt6Widgets
Qt5OpenGL_DIR to C:\Qt\6.4.2\mingw_64\lib\cmake\Qt6OpenGL
CMAKE_BUILD_TYPE to Release or RelWithDebInfo if not set up
OPENCV_VS_VERSIONINFO_SKIP=1 if found
```

if not set them up & then click configure again Then click generate

if they are okay click generate only

```
cd  <Your openCV Directory>\release
shift & right click
show more (if you are windows 11)
open powershell here

mingw32-make -j 12 (if your pc has 8 cores processor)
mingw32-make install
```

```
add  <Your openCV Directory>\release\bin to system enviroment
add  C:\Qt\Tools\QtCreator\bin to system enviroments
```


open new Qt project, make sure you select qmake as your build system
and in the .pro file add
```

INCLUDEPATH +=  <Your openCV Directory>\release\install\include

LIBS += -L<Your openCV Directory>\release\lib \
    -lopencv_calib3d470 \
    -lopencv_core470 \
    -lopencv_features2d470 \
    -lopencv_flann470 \
    -lopencv_highgui470 \
    -lopencv_imgproc470 \
    -lopencv_imgcodecs470 \
    -lopencv_photo470 \
    -lopencv_stitching470 \
    -lopencv_ts470 \
    -lopencv_video470 \
    -lopencv_videoio470 \
```




