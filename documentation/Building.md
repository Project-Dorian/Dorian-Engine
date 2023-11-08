The general process that the project builder will go through each file is as followed:
1. Take the file (although it can have any file extension, it is really just a json file)
2. Generate a temporary .cpp file using the information given
3. add important information to the `shared.hpp` file to be shared between other files

# Shared.hpp
Shared.hpp is a file that is called from any file. It includes the following non CPP files: scenes, scripts, animations, and assets.