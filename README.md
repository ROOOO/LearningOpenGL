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

---
All the resources are came from http://tf3dm.com/ and http://learnopengl.com/.

---
### Logs

##### Jul 13, 2016, Wed.
 - 

##### Jul 12, 2016, Tue.
 - Chapter Framebuffers.

##### Jul 11, 2016, Mon.
 - Chapter Framebuffers.

##### Jul 10, 2016, Sun.
 - Chapter Depth testing.
 - Chapter Stencil testing.
 - Chapter Blending.
 - Chapter Face culling.

##### Jul 9, 2016, Sat.
 - Chapter Model Loading.

##### Jul 8, 2016, Fri.
 - Chapter Mesh.
 - Add Mesh Class.
 - Chapter Model.

##### Jul 7, 2016, Thur.
 - Exercises of Multiple Lights.
 - Chapter Assimp.

##### Jul 6, 2016
 - Chapter Multiple Lights.
 
##### Jul 5, 2016
 - Chapter Multiple Lights.

##### Jul 4, 2016
 - 4nd exercise of Lighting Maps, Lighting.

##### Jul 3, 2016
 - 2nd exercise of Lighting Maps, Lighting.
 - 3rd exercise of Lighting Maps, Lighting.

##### Jul 2, 2016
 - Chapter Lighting Maps, Lighting.

##### Jul 1, 2016
 - Exercises of Material, Lighting.

##### Jun 30, 2016
 - 3rd exercise of Basic Lighting.
 - 4nd exercise of Basic Lighting.
 - Chapter Material, Lighting.

##### Jun 29, 2016
 - Phong lighting.
 - Chapter Basic Lighting.
 - Enhance common settings.
 - 1st exercise of Basic Lighting.
 - 2nd exercise of Basic Lighting.

##### Jun 28, 2016
 - Chapter Lighting.

##### Jun 27, 2016
 - 1st exercise of Camera.
 - All the exercises of Getting Start.

##### Jun 26, 2016
 - 3rd exercise of Transformations.
 - Chapter Camera.
 - Add Camera Class.

##### Jun 25, 2016
 - 1st exercise of Transformations.
 - 2nd exercise of Transformations.
 - Chapter Coordinate System.

##### Jun 24, 2016
 - Add GLM.
 - Chapter Transformations.
 - Add Texture Class.

##### Jun 23, 2016
 - 3rd exercise of Textures.
 - 4nd exercise of Textures.

##### Jun 22, 2016
 - 2nd exercise of Textures.
 - 3rd exercise of Textures.
 - Add Texture Reader Class.

##### Jun 21, 2016
 - Add Common Setting Class.
 - 1st exercise of Textures.

##### Jun 20, 2016
 - Fix texture shaders bugs.
 - Ignore some files of Github.

##### Jun 19, 2016
 - Add SOIL libs.
 - Chapter Textures.

##### Jun 18, 2016
 - Shader Reader Class.
 - Chapter Shaders.
 - Exercises of Shaders.

##### Jun 17, 2016
 - 2nd Exercise of Create a window.
 - 3rd Exercise of Create a window.
 - Set up Visual Studio Project by Python.

##### Jun 16, 2016
 - EBO.
 - 1st Exercise of Create a window.

##### Jun 15, 2016
 - VAO and VBO.

##### Jun 14, 2016
 - Setting up environment.
 - Create a glfw window.
