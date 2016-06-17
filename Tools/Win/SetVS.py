#coding: utf-8

__author__ = 'King'

import os
import re
import sys

class SetVS:
  def __init__(self, path):
    self.projPath = path
    self.file = ''
  def readFile(self):
    file = open(self.projPath, 'r+')
    self.file = file.read()
    file.close()
  def writeFile(self):
    libAndInclude = """
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
    <IncludePath>D:\Projects\OpenGL\LearningOpenGL\Libs\Includes;$(IncludePath)</IncludePath>
    <LibraryPath>D:\Projects\OpenGL\LearningOpenGL\Libs\</LibraryPath>
  </PropertyGroup>
    """
    link = """
  <AdditionalDependencies>opengl32.lib;glfw3.lib;glew32s.lib;%(AdditionalDependencies)</AdditionalDependencies>
  </Link>
    """
    self.readFile()
    pattern = re.compile(r'<PropertyGroup />', re.S)
    rst = re.sub(pattern, libAndInclude, self.file)
    pattern = re.compile(r'(<Link>.*?</GenerateDebugInformation>\n\s+)</Link>', re.S)
    linkPrefix = re.findall(pattern, rst)[0]
    link = linkPrefix + link
    pattern = re.compile(r'<Link>.*?</GenerateDebugInformation>\n\s+(</Link>)', re.S)
    rst = re.sub(pattern, link, rst)
    file = open(self.projPath, 'w+')
    file.write(rst)
    file.close()

def MainFunc(path):
  vs = SetVS(path)
  vs.writeFile()

if __name__ == '__main__':
  if len(sys.argv) != 2:
    print 'Usage: SetVS.py path'.decode('utf-8')
  else:
    MainFunc(sys.argv[1])


