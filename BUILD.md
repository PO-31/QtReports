# Building instruction
## Step 1: Unpackaging.

+ Clone the project or download release from repo.
+ Unpackage archive in the directory of QtReports.

## Step 2: Building.
There are 2 ways to build the project, and if it's needed to set version, then set its value in "QTREPORTS_VERSION" variable.

### Method 1. With using QtCreator:
+ In the root of QtReports open "QtReports.pro" file with QtCreator.
+ To Coverage support set "BUILD_COVERAGE" variable value to "TRUE".
+ Press "Build" (Hammer button) to build the whole project.
+ If necessary to build only certain module, press Right Mouse Key on module's project in project browser and select "Build <i>Module_Name</i>"

### Method 2. With using Qmake:
+ Launch terminal and go to directory of required module.
+ Input qmake [-spec "<i>Using_compiler</i>"] "CONFIG += <i>Building_type_(release,debug,coverage,etc.)</i>" <i>Module_Project_File</i>.pro.
+ After generation of Makefile call make [-j<i>ThreadsNum</i>].

# Usage
Built library will be in "build/lib" directory, public headers - "qtreports/include".

For using library with Qmake project string "LIB += -lqtreports" must be set in project file, and set "LIB += <i>Library_Path</i>" and "INCLUDEPATH += <i>Headers_Path</i>" if necessary.