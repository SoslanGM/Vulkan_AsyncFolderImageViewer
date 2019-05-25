# Vulkan_AsyncFolderImageViewer
Asynchronious Vulkan-based thumbnail-generating image viewer.

Requirements:
- Vulkan SDK and Runtime drivers.

How to build:
- cd into the code directory and launch build.bat. That's it :)

How to use:
- In the source.cpp, in WinMain(), type in the folder of interest.
- Scroll through the folder with up/down arrows(scrolling up and down), PageUp/PageDown(faster scrolling) and Home/End keys(beginning and end of currently opened images in the folder).
- Also included is the screenshot generation feature(more on it below).

How it works:
after looking into your folder via win32 API functions, it forms a list of images, and then works through it with three(four with screenshots) threads:
- disk thread opens the images and leaves its pixels in a linked list;
- thumb thread picks the pixels up, stages them to GPU and blits them into a smaller thumbnail image, cleaning the pixels
 up after the disk thread;
- main thread renders available thumbnail images, and scrolls through them; with screenshots enabled, it also captures the end
 result of the frame and puts its pixels into another LL
- again, if screenshots are enabled, fourth thread picks entries from it and writes them to disk, into a dedicated folder.
