
// Windows includes
#include <windows.h>
#include <shlwapi.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <ctype.h>

// Vulkan includes
#define VK_USE_PLATFORM_WIN32_KHR
#define VK_NO_PROTOTYPES
#include "vulkan/vulkan.h"
#include "vulkan/vk_platform.h"


// lib includes
#define STB_TRUETYPE_IMPLEMENTATION
#include "../lib/stb_truetype.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../lib/stb_image_write.h"



// My includes
#include <stdint.h>
#include "source.h"


LRESULT CALLBACK MainWindowCallback(HWND Window,
                                    UINT Message,
                                    WPARAM wParam,
                                    LPARAM lParam)
{
    u32 virtual_key = wParam;
    u32 key_state = lParam;
    
    switch(Message)
    {
        case WM_CLOSE:
        {
            app.running = false;
        } break;
        
        case WM_DESTROY:
        {
            app.running = false;
        } break;
        
        case WM_KEYDOWN:
        {
            bool was_down = ((key_state & (1 << 30)) != 0);
            bool is_down  = ((key_state & (1 << 31)) == 0);
            
            if(virtual_key == VK_UP)
            {
                if(is_down)
                    ScrollUp(viewer.scroll_speed);
            }
            else if(virtual_key == VK_DOWN)
            {
                if(is_down)
                    ScrollDown(viewer.scroll_speed);
            }
            
            else if(virtual_key == VK_PRIOR)
            {
                if(is_down)
                    ScrollUp(viewer.jump_speed);
            }
            else if(virtual_key == VK_NEXT)
            {
                if(is_down)
                    ScrollDown(viewer.jump_speed);
            }
            
            if(was_down != is_down)
            {
                if(virtual_key == VK_ESCAPE)
                {
                    if(is_down)
                    {
                        ODS("Quitting the program\n");
                        ODS("Total images processed: %d\n", viewer.processed_image_count);
                        PostQuitMessage(0);
                    }
                }
                
                else if(virtual_key == 'Q')
                {
                    if(is_down)
                    {
                        data.display_overlay = !data.display_overlay;
                    }
                }
                else if(virtual_key == VK_HOME)
                {
                    if(is_down)
                    {
                        viewer.scroll_y = viewer.scroll_min;
                    }
                }
                else if(virtual_key == VK_END)
                {
                    if(is_down)
                    {
                        viewer.scroll_y = viewer.scroll_max;
                    }
                }
            }
        }
        
        default:
        {
            
        } break;
    }
    
    return DefWindowProc(Window, Message, wParam, lParam);
}


int CALLBACK WinMain(HINSTANCE Instance,
                     HINSTANCE PrevInstance,
                     LPSTR CommandLine,
                     int ShowMode)
{
    u32 vk_dir_len = 100;
    app.vk_sdk_path = (char *)calloc(vk_dir_len, sizeof(char));
    GetEnvironmentVariable("vulkan_sdk", app.vk_sdk_path, vk_dir_len);
    ODS("Found Vulkan SDK path: %.*s\n", vk_dir_len, app.vk_sdk_path);
    
    //// --- --- --- Preliminary setup --- --- ---
    data.RECORD         = true;     // If this is true...
    data.record_frames  = 20;  //  change this from 0. Or it will close immediately :)
    viewer.image_folder = String("D:/'Your folder of choice here!'/");
    // Example: viewer.image_folder = String("../screenshots/");  // Better use '/' these slashes, and don't forget the final one :)
    //// --- --- ---
    
    
    
    viewer.thread_main = GetCurrentThread();
    InitializeCriticalSection(&crit_sec);
    
    TimerSetup();
    TimerStart();
    
    app.instance = Instance;
    COLORREF color = 0x00000000;
    WindowClassRegister(MainWindowCallback, Instance,
                        color, app.class_name);
    WindowCreate(app.class_name, app.window_name, Instance);
    
    
    // --- Vulkan preparations ---
    LoadEnums();
    LoadInfos();
    
    VulkanPrepare();
    // ---
    
    
    
    // --- Data preparations ---
    DataPrepare();
    
    data.target_fps = 60.0f;
    
    data.target_frametime = 1.0f / data.target_fps;
    
    r64 us_per_s = 1000000.0;
    r64 ms_per_s = 1000.0;
    
    data.time_framestart = TimerRead();
    data.time_active = TimerRead();
    data.time_warmup = TimerElapsedFrom_ms(data.time_start);
    
    
    // --- Message Pump ---
    MSG msg;
    while(app.running)
    {
        PeekMessage(&msg, 0, 0, 0, PM_REMOVE);
        if(msg.message == WM_QUIT)
            app.running = false;
        else
        {
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }
        
        ODS(" --- Frame %3d begins --- \n", data.frame_counter);
        
        Process();
        
        Render();
        
        Present();
        
        if(data.RECORD)
        {
            if(data.frame_counter < data.record_frames)
                AddScreenshotToLL(data.acquired_index, data.frame_counter);
            if(viewer.screenshots_recorded == data.record_frames)
                exit(0);
        }
        
        r64 frame_presleep = TimerElapsedFrom_ms(data.time_framestart);
        ODS("Frame %d presleep time: %f", data.frame_counter, frame_presleep);
        
        // wait here
        r64 frame_elapsed = TimerElapsedFrom_s(data.time_framestart);
        r64 sleep_time = frame_elapsed;
        if(sleep_time < data.target_frametime)
        {
            // if sleep is granular, then sleep
            if(data.ms_granular)
            {
                u32 sleep_for_ms = (u32)(ms_per_s * (data.target_frametime - frame_elapsed));
                if(sleep_for_ms > 0)
                    Sleep(sleep_for_ms);
            }
            
            // if not, then spinlock with no shame
            while(sleep_time < data.target_frametime)
                sleep_time = TimerElapsedFrom_s(data.time_framestart);
        }
        // ---
        
        ODS(" --- Frame %3d ends --- \n", data.frame_counter);
        data.frame_counter++;
        PadDebugOutput(5);
        
        data.dt = TimerElapsedFrom_s(data.time_framestart);
        data.time_framestart = TimerRead();
    }
    
    vkUnmapMemory(vk.device, viewer.view_memory);
    if(data.RECORD)
    {
        vkUnmapMemory(vk.device, data.screenshot_memory);                                                 
    }
    
    PadDebugOutput(20);
    TimerShutdown();
    
    return 0;
    // ---
}