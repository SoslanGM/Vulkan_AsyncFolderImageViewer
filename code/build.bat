@echo off

IF NOT EXIST ..\..\build mkdir ..\..\build
pushd ..\build

glslangValidator -V ..\code\viewer.vert -o viewer_vert.spv
glslangValidator -V ..\code\viewer.frag -o viewer_frag.spv

glslangValidator -V ..\code\overlay.vert -o overlay_vert.spv
glslangValidator -V ..\code\overlay.frag -o overlay_frag.spv

set vulkanInclude=%vulkan_sdk%\Include

set NAME=source
cl -I %vulkanInclude% -nologo -Zi "..\code\%NAME%.cpp" /link user32.lib gdi32.lib kernel32.lib shlwapi.lib winmm.lib

popd