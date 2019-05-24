:: Paste your ffmpeg path instead in the next line. Mine was "C:/Program Files/ffmpeg/bin/ffmpeg.exe", so
::  "C:/Program Files/ffmpeg/bin/ffmpeg.exe" -framerate 60 -i "../screenshots/screenshot_%%05d.png" -c:v libx264 -pix_fmt yuv420p out.mp4

%ffmpeg_path% -framerate 60 -i "../screenshots/screenshot_%%05d.png" -c:v libx264 -pix_fmt yuv420p out.mp4
