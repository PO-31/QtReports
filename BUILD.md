# Building instruction
## Step 1: Unpackaging.

+ Clone the project or download release from repo.
+ Unpackage archive in the directory of QtReports.

## Step 2: Building.
Собрать проект можно несколькими способами, но если необходимо указать версию собираемой библиотеки, то необходимо задать переменную среды QTREPORTS_VERSION.

### Method 1. With using QtCreator:
+ In the root of QtReports open "QtReports.pro" file with QtCreator.
+ To Coverage support set "BUILD_COVERAGE" variable value to "TRUE".
+ Press "Build" (Hammer button) to build the whole project.
+ If necessary to build only certain module, press Right Mouse Key on module's project in project browser and select "Build Module_Name"

### Method 2. With using Qmake:
+ Launch terminal and go to directory of required module.
+ Input qmake [-spec "Using_compiler"] "CONFIG += Building_type_(release,debug,coverage,etc.)" Module_Project_File.pro.
+ After generation of Makefile call make [-jThreadsNum].

# Usage
Built library will be in "build/lib" directory, public headers - "qtreports/include".

For using library with Qmake project string "LIB += -lqtreports" must be set in project file, and set "LIB += Library_Path" and "INCLUDEPATH += Headers_Path" if necessary.