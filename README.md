# LearningOpenGL

## 学习 OpenGL
https://learnopengl-cn.readthedocs.io/zh/latest/

## 准备工作

### Windows

    1. 安装 CMake。
    2. 下载 GLFW 源码并用CMake，选择相应的编译器并编译拿到其中的 .lib 文件。
    3. 新建 Project 后，在 Tools/Win 文件夹中用 SetVS.py 设置一下。

### Mac OS X

参考以下三篇文章：

    http://blog.csdn.net/u011327476/article/details/44014579
    http://blog.csdn.net/mingzznet/article/details/42266225
    http://aiplay.github.io/2016/03/14/2016-01-08-mac-config-opengl/
    
当然其中也有不太准确的地方。

    1. 安装 CMake
    2. 下载 GLFW 源码并用 CMake，选择 Unix 编译。
    3. 在编译好的文件夹中 make && make install。
    4. 在 build-setting 中的 header search paths 加入 `/usr/local/include` ，在 Library search paths 加入 `/usr/local/lib` 。
    5. 在 Link Binary With Libraries 中添加CoreVideo, IOKit, Cocoa, OpenGL, GLUT, libglfw3.a
    6. GLEW 下载源码，并`sudo make GLEW_DEST=/usr/local` && `sudo make GLEW_DEST=/usr/local install`，耐心等待。
    7. Always Search User Paths 调整为 Yes。
    8. 在 Link Binary With Libraries 中添加libGLEW.a。
    9. 配置 SOIL（引用aiplay）：下载好该库的代码后，需要自己再编译一下。进入projects/makefile目录，新建立 obj 目录，并修改makefile文件，在CXXFLAGS增加”-m64”选项，即 CXXFLAGS = -O2 -s -Wall -m64 。然后在makefile目录执行 make 和 sudo make install ，将lib目录新生成的libSOIL.a库文件增加到xcode的链接库中。

其中也许有的步骤没必要，现在知识不足，先这样吧。
