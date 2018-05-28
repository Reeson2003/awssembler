# AWSSEMBLER #

## Description ##
Awssembler is the educational project that is java application that uses
C++ dll library with inline assembly under the hood.

## Build ##
### Native code ###
To build .dll file use Microsoft Visual Studio. Win32 configuration supported only.
- Create new empty project
- Open Project > properties > general and select dll project type
- Project > properties > C/C++ > general and add to **Additional Include Directories**
path to your JDK **include** directory and **subfolders** and path to project **native**
directory
- add files under **native** directory into VS project as existing files
- build VS project and go under project directory to check that .dll file appeared
- copy .dll file into **src/dist/lib** and rename it to ***awssembler.dll***

### Application ###
To build and run application needs to be JDK x86 installed and **JAVA_HOME**
variable in **PATH**.
- run gradlew.bat

## Run ##
- go under **build/distributions**
- unzip **awssembler.zip**
- run **bin/awssembler.bat**
- enjoy
