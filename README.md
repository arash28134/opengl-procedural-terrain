# Opengl Procedural Terrain Generator (Windows and Linux)
Project I did back in 9th grade for our computer class (Still under development...)
## Getting started
You can either build the project or download a pre-built binary (Windows & Linux) from [Releases](https://github.com/arash28134/opengl-procedural-terrain/releases) section.

### Prerequisites
- **CMake**: Make sure you have CMake installed on your system. You can download it from [cmake.org](https://cmake.org/download/) on Windows or use your package manager on Linux.
- **vcpkg**: Follow the instructions in Microsoft's [vcpkg documentation](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-powershell) to install vcpkg.

### Building the Project

1. **Clone the repository**
   ```sh
   git clone https://github.com/arash28134/opengl-procedural-terrain.git
   cd opengl-procedural-terrain
   ```

2. **Configure CMake**
   
   Change CMAKE_TOOLCHAIN_FILE to your root vcpkg installation directory.
   ```sh
   cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
   ```
   (You can also set the VCPKG_ROOT environment variable to your vcpkg directory and run CMake without the toolchain file argument. the first method is more recommended)

3. **Build**
   ```sh
   cmake --build build
   ```

### Installing Dependencies (if not using vcpkg integrate/toolchain file)
If you haven't integrated vcpkg with CMake using the toolchain file or the VCPKG_ROOT environment variable, you can install dependencies using the following command:

   ```
   vcpkg install glfw3 glew glm
   ```

## License
This software is provided in the hope that it will be useful to the public. It is released into the public domain, meaning that it is free to use, modify, and distribute for any purpose, without any restrictions or obligations. Please refer to [LICENSE](LICENSE) for details.