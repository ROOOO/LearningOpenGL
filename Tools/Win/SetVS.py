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
  def writeLibAndInclude(self):
    libAndInclude = """
    <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
    <IncludePath>D:\Projects\OpenGL\LearningOpenGL\Libs\Includes;$(IncludePath)</IncludePath>
    <LibraryPath>D:\Projects\OpenGL\LearningOpenGL\Libs\</LibraryPath>
  </PropertyGroup>"""
    pattern = re.compile(r'<PropertyGroup />', re.S)
    find = re.findall(pattern, self.file)
    if find == []:
      pattern = re.compile(r'(<PropertyGroup Label="UserMacros" />\n).*?(<PropertyGroup.*?</PropertyGroup>)', re.S)
      rst = re.sub(pattern, r'\1' + libAndInclude, self.file)
    else:
      rst = re.sub(pattern, libAndInclude, self.file)

    file = open(self.projPath, 'w+')
    file.write(rst)
    file.close()

  def writeLink(self):
    link = """
      <AdditionalDependencies>glew32s.lib;glfw3.lib;opengl32.lib;kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib;%(AdditionalDependencies)</AdditionalDependencies>
    </Link>"""
    pattern = re.compile(r'(<Link>.*?</GenerateDebugInformation>)(\n\s+)</Link>', re.S)
    find = re.findall(pattern, self.file)
    if find == []:
      pattern = re.compile(r'(<Link>.*?</GenerateDebugInformation>\n\s+)(<AdditionalDependencies>.*?</AdditionalDependencies>.*?</Link>)', re.S)
      rst = re.sub(pattern, r'\1' + link, self.file)
    else:
      rst = re.sub(pattern, r'\1' + link, self.file)
    file = open(self.projPath, 'w+')
    file.write(rst)
    file.close()

  def writeFile(self):
    self.readFile()
    self.writeLibAndInclude()
    # self.writeLink()

def MainFunc(path):
  vs = SetVS(path)
  vs.writeFile()

if __name__ == '__main__':
  if len(sys.argv) != 2:
    print 'Usage: SetVS.py path'.decode('utf-8')
  else:
    MainFunc(sys.argv[1])


