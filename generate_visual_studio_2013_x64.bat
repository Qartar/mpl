@echo off
:: Inline comments: %"..."% resolves to an empty variable, line continue with caret
cmake -G "Visual Studio 12 2013 Win64"      %"Set the generator to Visual Studio 2013 x64"% ^
      -H.                                   %"Set the source directory to the current directory"% ^
      -B.\_cmake                            %"Set the build directory to the _cmake subfolder"% ^
      -DCMAKE_INSTALL_PREFIX="_install"     %"Set the install directory to the _install subfolder"% ^
      %*                                    %"Pass additional command line arguments to CMake"%

@echo on
