# Vulkan_AsyncFolderImageViewer
Asynchronious Vulkan-based thumbnail-generating image viewer.

Requirements:
- Vulkan SDK and Runtime drivers.

How to build:
- launch build.bat in the code directory. That's it :)

How to use:
- in the source.cpp, in WinMain(), type in the folder of interest.
- Also included is the screenshot generation feature[more on it below].

How it works:
- after looking into your folder via win32 API, it works through each image it finds with three[four with screenshots] threads - 
  disk thread opens the images and leaves its pixels in a linked list;
  thumb thread picks the pixels up, stages them to GPU and blits them into a smaller thumbnail image, cleaning the pixels
 up after the disk thread;
  main thread renders available thumbnail images, and scrolls through them; [with screenshots enabled, it captures the end
 result and puts it into another LL];
  [where a fourth thread picks entries from it and writes them to disk, into a dedicated folder.]
