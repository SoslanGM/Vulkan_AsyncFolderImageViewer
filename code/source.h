
//// --- HEADER
// - Data types
// - Debug facilities
// - Vector/matrix facilities
// - Dynamic function loading
// - Time functions
// - Win32 functions
// - File io
// - Tokenizer
// - Enum introspection
// - Renderstate management
// - String rendering
// - Vulkan function(interaction) abstraction
// - Screenshot facilities
// - Replay controls
// - Main controls
// --- --- ---




// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                                 DATA TYPES ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

// --- Standard type redefinitions ---

typedef int8_t   s8;
typedef int16_t  s16;
typedef int32_t  s32;
typedef int64_t  s64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float  r32;
typedef double r64;

// ---



// --- Special characters ---

char terminator  = '\0';
char newline     = '\n';
char carriageret = '\r';
char space       = ' ';
char dot         = '.';
char underscore  = '_';
char equals      = '=';
char semicolon   = ';';

char braceopen   = '{';
char braceclose  = '}';

// ---







// --- geometry

typedef struct vertex
{
    float x, y, z, w;
} vertex;

typedef struct vertex_uv
{
    float x, y, z, w;
    float u, v;
} vertex_uv;


typedef struct quad
{
    vertex v0;
    vertex v1;
    vertex v2;
    vertex v3;
} quad;
typedef struct quad_uv
{
    vertex_uv v0;
    vertex_uv v1;
    vertex_uv v2;
    vertex_uv v3;
} quad_uv;

// ---


// --- text stuff

typedef struct
{
    char *text;
    int length;
} string;
string *String(char *s)
{
    string *result = (string *)malloc(sizeof(string));
    
    result->length = strlen(s);
    result->text = (char *)malloc(sizeof(char) * (result->length+1));
    result->text[result->length] = '\0';
    memcpy(result->text, s, result->length);
    
    return result;
}

// --- images stuff

#define IMAGE_EXTENSION_COUNT 3
char *allowed_image_extensions[IMAGE_EXTENSION_COUNT] = { ".bmp", ".jpg", ".png" };

typedef struct
{
    VkImage image;
    s32 width;
    s32 height;
    
    VkSampler sampler;
    VkImageView imageview;
    VkDeviceMemory memory;
    u32 *pixels;
    u32 pixels_datasize;
} image_data;

typedef struct font_data
{
    // stb parameters
    stbtt_fontinfo fontinfo;
    stbtt_bakedchar *baked_chardata;
    
    r32 font_size;
    r32 scale;
    
    r32 ascent;
    r32 descent;
    r32 linegap;
    r32 v_advance;
    
    s32 first_char;
    s32 char_count;
    
    image_data atlas_data;
} font_data;

// ---



// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                           DEBUG FACILITIES ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

char ods_buf[2048];
#define ODS(...) \
_snprintf_s(ods_buf, sizeof(ods_buf), __VA_ARGS__); \
OutputDebugStringA(ods_buf);

void PadDebugOutput(u32 padsize)
{
    for(u32 i = 0; i < padsize; i++)
        OutputDebugStringA("\n");
}

void Assert(VkResult result, char *msg)
{
    if(result != VK_SUCCESS)
    {
        ODS("Result code: %d \n", result);
        ODS("ASSERT: %s \n", msg);
        
        int *base = 0;
        *base = 1;
    }
}
void Assert(bool flag, char *msg = "")
{
    if(!flag)
    {
        ODS("ASSERT: %s \n", msg);
        
        int *base = 0;
        *base = 1;
    }
}

// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////                    DEBUG FACILITIES ------ ------
// //////////////////////////////////////////////////////////////////////////////



// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                   VECTOR/MATRIX FACILITIES ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

// VECTOR3
typedef r32 *vector3;
vector3 Vector3()
{
    vector3 result = (r32 *)malloc(sizeof(r32) * 3);
    return result;
}
vector3 Vector3(r32 v0, r32 v1, r32 v2)
{
    vector3 result = (r32 *)malloc(sizeof(r32) * 3);
    result[0] = v0;
    result[1] = v1;
    result[2] = v2;
    return result;
}
// ---

// VECTOR4
typedef r32 *vector4;
r32 *Vector4()
{
    r32 *result = (r32 *)malloc(sizeof(r32) * 4);
    return result;
}

typedef r32 *matrix4;
r32 *Matrix4()
{
    r32 *result = (r32 *)malloc(sizeof(r32) * 16);
    for(u32 i = 0; i < 16; i++)
    {
        if(i % 5 == 0)
            result[i] = 1.0f;
        else
            result[i] = 0.0f;
    }
    return result;
}

vector4 Vector4(r32 x, r32 y, r32 z, r32 w)
{
    vector4 result = (r32 *)malloc(sizeof(r32) * 4);
    result[0] = x;
    result[1] = y;
    result[2] = z;
    result[3] = w;
    return result;
}

// ---

matrix4 Matrix4(r32 m0,  r32 m1,  r32 m2,  r32 m3,
                r32 m4,  r32 m5,  r32 m6,  r32 m7,
                r32 m8,  r32 m9,  r32 m10, r32 m11,
                r32 m12, r32 m13, r32 m14, r32 m15)
{
    matrix4 result = (r32 *)malloc(sizeof(r32) * 16);
    result[0]  = m0;
    result[1]  = m1;
    result[2]  = m2;
    result[3]  = m3;
    result[4]  = m4;
    result[5]  = m5;
    result[6]  = m6;
    result[7]  = m7;
    result[8]  = m8;
    result[9]  = m9;
    result[10] = m10;
    result[11] = m11;
    result[12] = m12;
    result[13] = m13;
    result[14] = m14;
    result[15] = m15;
    return result;
}
matrix4 Matrix4(r32 *m)
{
    matrix4 result = (r32 *)malloc(sizeof(r32) * 16);
    for(u32 i = 0; i < 16; i++)
        result[i] = m[i];
    return result;
}

matrix4 MultMM(matrix4 l, matrix4 r)
{
    matrix4 result = Matrix4();
    for(u32 i = 0; i < 4; i++)
    {
        u32 k;
        for(k = 0; k < 4; k++)
        {
            r32 sum = 0.0f;
            for(u32 j = 0; j < 4; j++)
                sum += l[4*i+j] * r[4*j+k];
            result[4*i+k] = sum;
        }
    }
    return result;
}

matrix4 GenerateTranslationMatrix(vector3 v)
{
    matrix4 result = Matrix4();
    
    result[3]  = v[0];
    result[7]  = v[1];
    result[11] = v[2];
    
    return result;
}

matrix4 GenerateOrthographicMatrix(u32 width, u32 height)
{
    r32 l = 0.0f;
    r32 r = (r32)width;
    r32 b = (r32)height;
    r32 t = 0.0f;
    r32 n = 1000.0f;
    r32 f = 0.0f;
    
    r32 o0  = 2.0f / (r-l);
    r32 o3  = - ((r+l) / (r-l));
    r32 o5  = 2.0f / (t-b);
    r32 o7  = - ((t+b) / (t-b));
    r32 o10 = -2.0f / (f-n);
    r32 o11 = - ((f+n) / (f-n));
    
    return Matrix4(o0,    0.0f,  0.0f,  o3,
                   0.0f,  o5,    0.0f,  o7,
                   0.0f,  0.0f,  o10,   o11,
                   0.0f,  0.0f,  0.0f,  1.0f);
}

// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////            VECTOR/MATRIX FACILITIES ------ ------
// //////////////////////////////////////////////////////////////////////////////



//// //// --- --- Data structures --- ---

// Application side of things
struct
{
    HINSTANCE instance;
    WNDCLASS window_class = {};
    HWND window = {};
    
    char *class_name  = "Window class name";
    char *window_name = "Window name";
    
    u32 screen_width  = GetSystemMetrics(SM_CXSCREEN);
    u32 screen_height = GetSystemMetrics(SM_CYSCREEN);
    u32 window_width  = 1280;
    u32 window_height = 720;
    RECT rect_client_area;
    
    char *vk_sdk_path;
    
    bool running = true;
} app;

// vulkan side of things
struct
{
    VkInstance instance;
    VkDebugUtilsMessengerEXT debug_messenger;
    VkPhysicalDevice gpu;
    VkSurfaceKHR surface;
    u32 queue_family_index;
    VkDevice device;
    VkQueue queue;
    VkQueue queue_thumb;
    
    VkFormat format;
    VkColorSpaceKHR colorspace;
    VkPresentModeKHR present_mode;
    
    VkExtent2D extent_client_area;
    VkSwapchainKHR swapchain;
    VkImage *swapchain_images;
    VkImageView *swapchain_imageviews;
    
    VkCommandPool command_pool;
    VkCommandPool command_pool_thumb;
    VkCommandBuffer command_buffer;
    VkCommandBuffer command_buffer_thumb;
    VkPhysicalDeviceMemoryProperties gpu_memprops;
    
    VkViewport viewport;
    VkRect2D scissor;
    VkFramebuffer *framebuffers;
    
    VkComponentMapping components;
    VkImageSubresourceRange color_sr;
    VkCommandBufferBeginInfo cb_bi;
    VkPipelineStageFlags stage_mask = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    
    VkFenceCreateInfo fence_ci;
    VkSemaphoreCreateInfo semaphore_ci;
    
    VkFence fence_acquisition_complete;
    VkFence fence_render_complete;
    
    VkFence fence_transit;
    VkFence fence_transit_processing;
    VkFence fence_blit;
    VkFence fence_stage;
} vk;

// our data
struct
{
    string *result_enum;
    string *format_enum;
    string *colorspace_enum;
    string *presentmode_enum;
    string *imagelayout_enum;
    string *pipeflags_enum;
    
    u32 image_count = 2;
    u32 acquired_index;
    
    bool display_overlay = true;
    
    matrix4 orthographic_matrix;
    matrix4 view_matrix;
    
    VkBuffer staging_buffer;
    VkDeviceMemory staging_memory;
    
    u32 vertex_binding = 0;
    
    u32 matrix_binding;
    VkBuffer matrix_buffer;
    VkDeviceMemory matrix_memory;
    
    VkBuffer obstacle_heightsbuf;
    VkDeviceMemory obstacle_heightsmemory;
    
    VkImage screenshot_image;
    VkDeviceMemory screenshot_memory;
    
    u32 frame_counter = 0;
    
    
    r32 distance = 0.0f;
    
    VkSemaphore semaphore_execution_complete;
    
    // --- time data ---
    bool ms_granular;
    u64 frequency;
    
    bool RECORD = false;
    u32 record_frames;
    
    r64 target_fps;
    r64 target_frametime;
    
    u64 time_start;      // start of the application
    u64 time_active;
    u64 time_framestart;
    
    r64 frametime;
    r64 dt;
    r64 time_warmup;    // roughly from start of app to frame display
    // ---
    
    HANDLE thr;
} data;

typedef struct
{
    u32 width;
    u32 height;
    u32 *pixels;
    u32 pixel_bytes;
} image_entry;

typedef struct
{
    u32 width;
    u32 height;
    u8 *pixels;
    u32 pixel_bytes;
    u32 index;
} screenshot_entry;
typedef struct
{
    VkImage        image;
    VkImageView    view;
    VkDeviceMemory memory;
    
    u32 width;
    u32 height;
    u32 *pixels;
    u32 pixel_bytes;
} viewer_image;
typedef struct
{
    VkImage        image;
    VkImageView    view;
    VkDeviceMemory memory;
    
    u32 width;
    u32 height;
} viewer_thumb;

typedef struct image_ll
{
    image_entry *ptr;
    image_ll *next;
} image_ll;
typedef struct screenshot_ll
{
    screenshot_entry *ptr;
    screenshot_ll *next;
} screenshot_ll;


struct
{
    u32 column_count = 6;
    r32 thumbnail_size  = (r32)app.window_width / (r32)column_count;
    
    u32 image_count;
    volatile u32 processed_image_count = 0;
    volatile u32 current_ready_image_count = 0;
    volatile u32 ready_image_count = 0;
    VkSampler sampler;
    
    bool scroll_up   = false;
    bool scroll_down = false;
    bool jump_up   = false;
    bool jump_down = false;
    
    r32 scroll_speed = 1000.0f;
    r32 jump_speed = scroll_speed * 10.0f;
    r32 crawl_speed = scroll_speed / 4.0f;
    
    r32 scroll_y = 0.0f;
    r32 scroll_min = 0.0f;
    r32 scroll_max = 0.0f;
    
    void *view_mapptr;
    matrix4 view;
    VkBuffer view_buffer;
    VkDeviceMemory view_memory;
    
    u32 total_memory;
    
    // --- images
    viewer_image *images;
    
    // --- thumbnails
    viewer_thumb *thumbs;
    
    string *image_folder;
    
    //// --- --- --- Threads --- --- ---
    HANDLE thread_main;
    HANDLE thread_disk;
    HANDLE thread_thumb;
    HANDLE thread_screenshot;
    
    // --- Image LL ---
    image_ll *image_head = NULL;
    screenshot_ll *screenshot_head = NULL;
    
    void *screenshot_mapptr;
    u32 screenshots_recorded = 0;
} viewer;



//// //// --- ---   --- ---





// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                DYNAMIC FUNCTION LOADING(?) ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#define DECLARE_FUNCTION_POINTER(Func) \
PFN_##Func Func = NULL;

#define LOAD_FUNCTION_POINTER_AND_ASSERT(Func) \
Func = (PFN_##Func) GetProcAddress (vulkanDLL, "" #Func ""); \
Assert(Func, "Unable to load function " #Func);

#define LOAD_EXTENSION_FUNCTION_POINTER_AND_ASSERT(Func, Inst) \
*(void **)&##Func = vkGetInstanceProcAddr(Inst, "" #Func); \
Assert(Func, "Unable to load extension function " #Func);


#define X(Func) DECLARE_FUNCTION_POINTER(Func)
#include "list_of_functions.h"
LIST_OF_FUNCTIONS
#include "list_of_ext_functions.h"
LIST_OF_EXT_FUNCTIONS
#undef X

// extraction of functions from the library and filling of function pointers
#define X(Func) LOAD_FUNCTION_POINTER_AND_ASSERT(Func)
void Vulkan_LoadInstanceFunctions()
{
    HMODULE vulkanDLL = LoadLibrary("vulkan-1.dll");
    Assert(vulkanDLL, "! Can't load Vulkan.\n");
    
    LIST_OF_FUNCTIONS
}
#undef LIST_OF_FUNCTIONS
#undef X

// loading of extension functions and filling of their pointers
#define X(Func) LOAD_EXTENSION_FUNCTION_POINTER_AND_ASSERT(Func, instance)
void Vulkan_LoadExtensionFunctions(VkInstance instance)
{
    LIST_OF_EXT_FUNCTIONS
}
#undef LIST_OF_EXT_FUNCTIONS
#undef X

// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////            DYNAMIC FUNCTION LOADING ------ ------
// //////////////////////////////////////////////////////////////////////////////



// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                            TIME FUNCTIONS  ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#define MS_GRANULARITY 1

void TimerSetup()
{
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    data.frequency = freq.QuadPart;
    
    data.ms_granular = (timeBeginPeriod(MS_GRANULARITY) == TIMERR_NOERROR);
}

void TimerShutdown()
{
    if(data.ms_granular)
        timeEndPeriod(MS_GRANULARITY);
}

void TimerStart()
{
    LARGE_INTEGER L;
    QueryPerformanceCounter(&L);
    data.time_start = L.QuadPart;
}

u64 TimerRead()
{
    LARGE_INTEGER L;
    QueryPerformanceCounter(&L);
    
    u64 time = L.QuadPart;
    return time;
}

r64 TimerElapsedFrom(u64 prev, u64 mult)
{
    LARGE_INTEGER L;
    QueryPerformanceCounter(&L);
    
    u64 curr = L.QuadPart;
    u64 diff = curr - prev;
    r64 result = (r64)(diff * mult) / (r64)data.frequency;
    
    return result;
}
r64 TimerElapsedFrom_s(u64 prev)
{
    return TimerElapsedFrom(prev, 1.0);
}
r64 TimerElapsedFrom_ms(u64 prev)
{
    u64 ms_to_s = 1000.0;
    return TimerElapsedFrom(prev, ms_to_s);
}
r64 TimerElapsedFrom_us(u64 prev)
{
    u64 us_to_s = 1000000.0;
    return TimerElapsedFrom(prev, us_to_s);
}
r64 TimerElapsedFrom_ns(u64 prev)
{
    r64 ns_to_m = 1000000000.0;
    return TimerElapsedFrom(prev, ns_to_m);
}

string *TimerString(r64 t_us)
{
    r64 us_to_ms = 1000.0;
    r64 ms_to_s  = 1000.0;
    r64 s_to_m   = 60.0;
    r64 m_to_h   = 60.0;
    
    u32 m  = (u64)(t_us / (us_to_ms * ms_to_s * s_to_m));
    u32 s  = (u32)(t_us / (us_to_ms * ms_to_s)) % 60;
    u32 ms = (u32)((u32)(t_us / us_to_ms) % (u32)us_to_ms);
    
    char *format = "%02dm:%02ds.%03dms";
    u32 size = 100;
    char *buf = (char *)malloc(size);
    snprintf(buf, size, format, m, s, ms);
    
    return String(buf);
}

// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////                      TIME FUNCTIONS ------ ------
// //////////////////////////////////////////////////////////////////////////////



// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                           WIN32 FUNCTIONS  ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

void WindowClassRegister(WNDPROC callback, HINSTANCE instance,
                         COLORREF color, char *class_name)
{
    HBRUSH brush = CreateSolidBrush(color);
    
    app.window_class.style         = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
    app.window_class.lpfnWndProc   = callback;
    app.window_class.hInstance     = instance;
    app.window_class.lpszClassName = class_name;
    app.window_class.hCursor       = LoadCursor(NULL, IDC_ARROW);
    app.window_class.hbrBackground = brush;
    
    if(!RegisterClassA(&app.window_class))
        OutputDebugStringA("! Register class failed\n");
    else
        OutputDebugStringA("> Window class registered\n");
}

void WindowCreate(char *class_name, char *window_name,
                  HINSTANCE instance)
{
    app.rect_client_area.left   = 0;
    app.rect_client_area.top    = 0;
    app.rect_client_area.right  = app.window_width  + 16;
    app.rect_client_area.bottom = app.window_height + 37;
    u32 style = WS_OVERLAPPEDWINDOW|WS_VISIBLE;
    
    u32 cx = (app.screen_width  - app.window_width)/2;
    u32 cy = (app.screen_height - app.window_height)/2;
    u32 width  = app.rect_client_area.right;
    u32 height = app.rect_client_area.bottom;
    
    app.window = CreateWindowExA(0,
                                 class_name,
                                 window_name,
                                 style,
                                 cx, cy,
                                 width, height,
                                 0,
                                 0,
                                 instance,
                                 0);
    
    if(!app.window)
        OutputDebugStringA("! Window creation failed\n");
    else
        OutputDebugStringA("> Window created\n");
    
    GetClientRect(app.window, &app.rect_client_area);
    
    vk.extent_client_area.width  = app.rect_client_area.right;
    vk.extent_client_area.height = app.rect_client_area.bottom;
}

u32 CountFolderFiles(char *dir)
{
    u32 file_count = 0;
    
    WIN32_FIND_DATA filedata;
    HANDLE findfile;
    DWORD dwError;
    
    findfile = FindFirstFile(dir, &filedata);
    if(findfile == INVALID_HANDLE_VALUE)
    {
        ODS("Didn't get any files; directory %s\n", dir);
        MessageBoxA(app.window, "Check the directory! And don't forget / at the end.", "(Better look at OutputDebugString output)", MB_OK);
        exit(0);
    }
    if(findfile != INVALID_HANDLE_VALUE)
    {
        do
        {
            if((strcmp(filedata.cFileName, ".")  != 0) &&
               (strcmp(filedata.cFileName, "..") != 0))
            {
                for(u32 i = 0; i < IMAGE_EXTENSION_COUNT; i++)
                {
                    for(u32 j = 0; filedata.cFileName[j]; j++)
                        filedata.cFileName[j] = tolower(filedata.cFileName[j]);
                    
                    if(strstr(filedata.cFileName, allowed_image_extensions[i]))
                        file_count++;
                }
            }
        } while(FindNextFile(findfile, &filedata) != 0);
        FindClose(findfile);
    }
    
    return file_count;
}

string **GetFolderFileNames(char *dir, u32 file_count)
{
    string **result = (string **)malloc(sizeof(string *) * file_count);
    
    WIN32_FIND_DATA filedata;
    HANDLE findfile;
    DWORD dwError;
    
    u32 file_counter = 0;
    
    // get the names
    findfile = FindFirstFile(dir, &filedata);
    if(findfile != INVALID_HANDLE_VALUE)
    {
        do
        {
            if((strcmp(filedata.cFileName, ".")  != 0) &&
               (strcmp(filedata.cFileName, "..") != 0))
            {
                for(u32 i = 0; i < IMAGE_EXTENSION_COUNT; i++)
                {
                    for(u32 j = 0; filedata.cFileName[j]; j++)
                        filedata.cFileName[j] = tolower(filedata.cFileName[j]);
                    
                    if(strstr(filedata.cFileName, allowed_image_extensions[i]))
                    {
                        string *name = String(filedata.cFileName);
                        result[file_counter++] = name;
                    }
                }
            }
        } while(FindNextFile(findfile, &filedata) != 0);
        FindClose(findfile);
    }
    return result;
}

// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////                     WIN32 FUNCTIONS ------ ------
// //////////////////////////////////////////////////////////////////////////////



// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                                    FILE IO ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

char *OpenFile_v0(char *filename, int *size, bool removeslashr, bool debugprint)
{
    FILE *f = fopen(filename, "rb");
    if(!f)
    {
        printf("Couldn't open %s for reading\n", filename);
        exit(0);
    }
    
    fseek(f, 0, SEEK_END);
    int length = ftell(f);
    rewind(f);
    
    if(debugprint)
        printf("> OpenFile: ftell says length = %d\n", length);
    
    int alloc = length + 1;
    char *buffer = (char *)malloc(sizeof(char) * alloc);
    fread(buffer, length, 1, f);
    buffer[length] = terminator;
    
    fclose(f);
    
    if(removeslashr)
    {
        int lengthsansr = 0;
        // count length without /r
        char *reader = buffer;
        while(reader[0] != terminator)
        {
            if(reader[0] != carriageret)
                lengthsansr++;
            reader++;
        }
        
        int allocsansr = lengthsansr + 1;
        char *buffersansr = (char *)malloc(sizeof(char) * allocsansr);
        
        reader = buffer;
        char *writer = buffersansr;
        while(reader[0] != terminator)
        {
            if(reader[0] != carriageret)
                *writer++ = *reader;
            reader++;
        }
        buffersansr[lengthsansr] = terminator;
        
        free(buffer);
        
        if(size != NULL)
            *size = lengthsansr;
        return buffersansr;
    }
    
    if(size != NULL)
        *size = length;
    return buffer;
}
char *OpenFile_v0(char *filename, int *size)
{
    bool killslashrburnitdown = true;
    bool debugprint = false;
    
    return OpenFile_v0(filename, size, killslashrburnitdown, debugprint);
}
string *OpenFile(char *filename, int *size, bool removeslashr, bool debugprint)
{
    string *result = (string *)malloc(sizeof(string));
    
    result->text = OpenFile_v0(filename, size, removeslashr, debugprint);
    result->length = *size;
    
    return result;
}
string *OpenFile(char *filename, int *size)
{
    bool removeslashr = true;
    bool debugprint = false;
    
    string *result = (string *)malloc(sizeof(string));
    
    result->text = OpenFile_v0(filename, size, removeslashr, debugprint);
    result->length = *size;
    
    return result;
}
string *OpenFile(char *filename)
{
    bool removeslashr = true;
    bool debugprint = false;
    
    string *result = (string *)malloc(sizeof(string));
    
    int size = 0;
    result->text = OpenFile_v0(filename, &size, removeslashr, debugprint);
    result->length = size;
    
    return result;
}

// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////                             FILE IO ------ ------
// //////////////////////////////////////////////////////////////////////////////



// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                                  TOKENIZER ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

typedef struct
{
    char *At;
} tokenizer;
tokenizer Tokenizer;

enum token_type
{
    token_Unknown,
    
    token_Pound,
    token_Dot,
    token_Comma,
    token_Equals,
    token_Colon,       token_SemiColon,
    token_BraceOpen,   token_BraceClose,
    token_ParensOpen,  token_ParensClose,
    token_BracketOpen, token_BracketClose,
    token_ChevronOpen, token_ChevronClose,
    token_Dash,
    token_Number,
    
    token_Identifier
};

typedef struct
{
    token_type type;
    
    int length;
    char *text;
} Token;

bool IsLetter(char c)
{
    if(('a' <= c && c <= 'z') ||
       ('A' <= c && c <= 'Z'))
        return true;
    
    return false;
}

bool IsNumber(char c)
{
    if('0' <= c && c <= '9')
        return true;
    return false;
}

bool IsNewline(char c)
{
    if(c == '\n' ||
       c == '\r')
        return true;
    return false;
}
bool IsGarbage(char c)
{
    if(c == ' ' ||
       c == '\t' ||
       IsNewline(c) ||
       c == '\0')
        return true;
    return false;
}

Token GetToken()
{
    while(IsGarbage(Tokenizer.At[0]))
        Tokenizer.At++;
    
    Token token;
    
    token.length = 1;
    token.text = Tokenizer.At;
    
    char c = *Tokenizer.At;
    switch(c)
    {
        case '#': { token.type = token_Pound; } break;
        case '.': { token.type = token_Dot;   } break;
        case ',': { token.type = token_Comma; } break;
        case ':': { token.type = token_Colon;     } break;
        case ';': { token.type = token_SemiColon; } break;
        case '=': { token.type = token_Equals; } break;
        
        case '{': { token.type = token_BraceOpen;  } break;
        case '}': { token.type = token_BraceClose; } break;
        case '(': { token.type = token_ParensOpen;  } break;
        case ')': { token.type = token_ParensClose; } break;
        case '[': { token.type = token_BracketOpen;  } break;
        case ']': { token.type = token_BracketClose; } break;
        case '<': { token.type = token_ChevronOpen;  } break;
        case '>': { token.type = token_ChevronClose; } break;
        
        default:
        {
            if(IsLetter(c) || (Tokenizer.At[0] == '*' && Tokenizer.At[1] != ' '))
            {
                token.type = token_Identifier;
                while(IsLetter(Tokenizer.At[0]) ||
                      IsNumber(Tokenizer.At[0]) ||
                      Tokenizer.At[0] == '_' ||
                      Tokenizer.At[0] == '*')
                {
                    Tokenizer.At++;
                }
                token.length = Tokenizer.At - token.text;
                Tokenizer.At--;
            } break;
            
            token.type = token_Unknown;
        } break;
    }
    
    return token;
}

// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////                           TOKENIZER ------ ------
// //////////////////////////////////////////////////////////////////////////////




// --- Program functions ---

char *DecToBin(u64 n)
{
    u32 width = 64;
    
    char *binnum = (char *)malloc(width+1);
    binnum[width] = '\0';
    
    for(int i = 0; i < width; i++)
    {
        if(n >> i & 1)
            binnum[width-i-1] = '1';
        else
            binnum[width-i-1] = '0';
    }
    
    return binnum;
}

char *NumToString(int number, bool debugprint)
{
    int sign = (number < 0) ? -1 : 1;
    if(debugprint)
        printf("Is this %d value positive? %s\n", number, number >= 1 ? "YES" : "NO");
    
    number *= sign;
    int copynum = number;
    int length = 0;
    while(copynum >= 1)
    {
        copynum /= 10;
        length++;
    }
    
    u32 signlength;
    if(sign == 1)
        signlength = 0;
    else
        signlength = 1;
    
    if(length == 0)
        length = 1;
    char *str = (char *)malloc(sizeof(char) * (signlength + length + 1));
    str[length] = terminator;
    for(int i = 0; i < length; i++)
    {
        if(debugprint)
        {
            printf(" --- \n");
            printf("number: %d\n", number);
            printf("number %% 10: %d\n", number % 10);
            printf("symbol: %c\n", (number % 10) + '0');
            printf(" --- \n");
        }
        str[i] = number % 10 + '0';
        number /= 10;
    }
    
    // reverse value
    char *result = (char *)malloc(sizeof(char) * (signlength + length + 1));
    if(sign)
        result[0] = '-';
    
    for(int i = signlength, j = length-1; i < length+signlength; i++, j--)
        result[i] = str[j];
    
    result[length+signlength] = terminator;
    
    return result;
}

// ---



// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                         ENUM INTROSPECTION ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

char *FindLine(char *buffer, int *length, char *searchterm)
{
    char *prelimstart = strstr(buffer, searchterm);
    
    if(prelimstart == NULL)
        return NULL;
    
    char *start;
    char *end;
    
    start = prelimstart;
    while(start != buffer)
    {
        start--;
        if(*start == newline)
        {
            start++;
            break;
        }
    }
    
    end = prelimstart;
    while(*end != terminator)
    {
        end++;
        if(*end == newline)
            break;
    }
    
    *length = (int)(end - start);
    return start;
}

string *RetrieveEnum(char *filename, char *enum_name)
{
    string *buffer = OpenFile(filename);
    
    char *enum_prefix = "typedef enum ";
    char *enum_searchterm = (char *)calloc(strlen(enum_prefix) + strlen(enum_name) + 1, sizeof(char));
    strncpy(enum_searchterm, enum_prefix, strlen(enum_prefix));
    strncat(enum_searchterm, enum_name,   strlen(enum_name));
    
    char *pos = strstr(buffer->text, enum_searchterm);
    if(pos == NULL)
    {
        ODS("Wrong enum name!\n");
        ODS("You were searching for this: %s\n", enum_name);
        exit(0);
    }
    
    
    char *begin = strchr(pos,   braceopen)  + 2;  // scroll forward a brace and a newline
    char *end   = strchr(begin, braceclose) - 1;  // scroll back a newline
    
    int length = (int)(end - begin);
    
    char *enumbuffer = (char *)malloc(sizeof(char) * (length + 1));
    strncpy(enumbuffer, begin, length);
    
    string *result = (string *)malloc(sizeof(string));
    result->text   = enumbuffer;
    result->length = length;
    
    return result;
}
char *RetrieveVkEnumString(string *vkenumbuffer, u32 enumvalue, bool debugprint)
{
    bool deb = false;
    
    char *valuestring = NumToString(enumvalue, debugprint);
    if(debugprint)
        printf("value: %s\n", valuestring);
    
    int length = 0;
    char *enumstring = FindLine(vkenumbuffer->text, &length, valuestring);
    
    Tokenizer.At = enumstring;
    Token token = GetToken();
    
    if(token.length < 0)
    {
        ODS("Strange token length bug\n");
    }
    
    if(deb)
    {
        printf("token text:   %.*s\n", token.length, token.text);
        printf("token length: %d\n", token.length);
    }
    
    char *result = (char *)malloc(sizeof(char) * (token.length + 1));
    strncpy(result, token.text, token.length);
    result[token.length] = terminator;
    
    if(deb)
        printf("string length: %d\n", length);
    
    return result;
}
char *RevEnum(string *enum_buffer, s32 value, bool debugprint)
{
    return RetrieveVkEnumString(enum_buffer, value, debugprint);
}
char *RevEnum(string *enum_buffer, s32 value)
{
    bool debugprint = false;
    return RetrieveVkEnumString(enum_buffer, value, debugprint);
}

// TODO: is there a way to get vulkan sdk path from environment?
void LoadEnums()
{
    char *header_path = (char *)calloc(150, sizeof(char));
    strcpy(header_path, app.vk_sdk_path);
    strcat(header_path, "/Include/vulkan/vulkan_core.h");
    
    data.result_enum      = RetrieveEnum(header_path, "VkResult");
    data.format_enum      = RetrieveEnum(header_path, "VkFormat");
    data.colorspace_enum  = RetrieveEnum(header_path, "VkColorSpaceKHR");
    data.presentmode_enum = RetrieveEnum(header_path, "VkPresentModeKHR");
    data.imagelayout_enum = RetrieveEnum(header_path, "VkImageLayout");
    data.pipeflags_enum   = RetrieveEnum(header_path, "VkPipelineStageFlagBits");
}

// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////                 ENUM INTROSPECTION  ------ ------
// //////////////////////////////////////////////////////////////////////////////



// \\-----------------\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                  RENDERSTATE MANAGEMENT(?) ------ ------ ------
//
// \\\\\------------------\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\------------------\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

typedef struct memory_pool
{
    u8 *start;
    u8 *write;  // reset each frame
    u32 size;
    u32 used;   // same
} memory_pool;


typedef struct renderstate
{
    VkPipeline pipeline;
    VkRenderPass renderpass;
    VkPipelineLayout pipeline_layout;
    VkDescriptorSetLayout ds_layout;
    VkDescriptorSet dset;
    u32 descset_count = 1;
    
    image_data texture_data;
    
    // if it's an overlay rs
    font_data *fd;
    
    // ---
    memory_pool *geometry;
    u32 quad_count;
    VkBuffer vertex_buffer;
    VkDeviceMemory vertex_memory;
    
    memory_pool *indexes;
    u32 index_count;
    VkBuffer index_buffer;
    VkDeviceMemory index_memory;
    // ---
} renderstate;
renderstate viewer_rs;
renderstate overlay_rs;


typedef struct render_init
{
    renderstate *rs;
    char *vert;
    char *frag;
} render_init;
render_init viewer_render_init;
render_init overlay_render_init;

typedef struct font_init
{
    char *fontfile;
    u32 font_size;
    u32 color;
} font_init;
font_init overlay_font_init;


#define KILOBYTE 1024
#define MEGABYTE 1024 * 1024
void MemoryAllocate(memory_pool *mp, u32 size)
{
    mp->start = (u8 *)malloc(size);
    mp->write = mp->start;
    mp->size = size;
    mp->used = 0;
}


void VertexesWrite(renderstate *rs, vertex *vertexes, u32 quad_count)
{
    u32 write_size = sizeof(vertex) * 4 * quad_count;  // 4 vertexes per quad
    memcpy(rs->geometry->write, vertexes, write_size);
    rs->geometry->write += write_size;
    rs->geometry->used += write_size;
    
    rs->quad_count += quad_count;
    
    // I won't run out of memory now, but for the future
    if(rs->geometry->used > rs->geometry->size)
    {
        ODS("Non-overlay geometry pool's been blown out!\n");
        exit(0);
    }
    
    free(vertexes);
}
void VertexesWrite_uv(renderstate *rs, vertex_uv *vertexes, u32 quad_count)
{
    u32 write_size = sizeof(vertex_uv) * 4 * quad_count;
    memcpy(rs->geometry->write, vertexes, write_size);
    rs->geometry->write += write_size;
    rs->geometry->used += write_size;
    
    rs->quad_count += quad_count;
    
    
    if(rs->geometry->used > rs->geometry->size)
    {
        ODS("Non-overlay geometry pool's been blown out!\n");
        exit(0);
    }
    
    free(vertexes);
}


void IndexesWrite(renderstate *rs, u32 *indexes)
{
    u32 write_size = sizeof(u32) * rs->index_count;
    memcpy(rs->indexes->write, indexes, write_size);
    rs->indexes->write += write_size;
    rs->indexes->used += write_size;
    
    // I should really just reallocate my memory pools on size exceed :)
    if(rs->indexes->used > rs->indexes->size)
    {
        ODS("Indexes pool's been blown out!\n");
        exit(0);
    }
    
    free(indexes);
}


u32 *GenerateQuadIndexes(renderstate *rs)
{
    u32 n = rs->quad_count;
    
    u32 indexes_per_polygon = 3;
    u32 polygons_per_quad = 2;
    u32 indexes_per_quad = indexes_per_polygon * polygons_per_quad;
    
    rs->index_count = indexes_per_quad * n;
    u32 *indexes = (u32 *)malloc(sizeof(u32) * rs->index_count);
    
    for(u32 i = 0; i < n; i++)
    {
        for(u32 j = 0; j < indexes_per_quad; j++)
        {
            u32 starting_index = 4*i;
            indexes[indexes_per_quad*i]   = starting_index;
            indexes[indexes_per_quad*i+1] = starting_index+1;
            indexes[indexes_per_quad*i+2] = starting_index+2;
            indexes[indexes_per_quad*i+3] = starting_index+1;
            indexes[indexes_per_quad*i+4] = starting_index+3;
            indexes[indexes_per_quad*i+5] = starting_index+2;
        }
    }
    
    u32 index_datasize = sizeof(u32) * rs->index_count;
    return indexes;
}

void WriteVertexMemory(renderstate *rs)
{
    void *level_geometry_mapptr;
    vkMapMemory(vk.device, rs->vertex_memory, 0, VK_WHOLE_SIZE, 0, &level_geometry_mapptr);
    memcpy(level_geometry_mapptr, rs->geometry->start, rs->geometry->used);
    vkUnmapMemory(vk.device, rs->vertex_memory);
}
void WriteIndexMemory(renderstate *rs)
{
    void *level_index_mapptr;
    vkMapMemory(vk.device, rs->index_memory, 0, VK_WHOLE_SIZE, 0, &level_index_mapptr);
    memcpy(level_index_mapptr, rs->indexes->start, rs->indexes->used);
    vkUnmapMemory(vk.device, rs->index_memory);
}

void WriteRenderstateMemory(renderstate *rs)
{
    WriteVertexMemory(rs);
    IndexesWrite(rs, GenerateQuadIndexes(rs));
    WriteIndexMemory(rs);
}


void QuadsWrite_uv(renderstate *rs, quad_uv *quads, u32 quad_count)
{
    u32 write_size = sizeof(quad_uv) * quad_count;
    memcpy(rs->geometry->write, quads, write_size);
    rs->geometry->write += write_size;
    rs->geometry->used += write_size;
    
    rs->quad_count += quad_count;
    
    if(rs->geometry->used > rs->geometry->size)
    {
        ODS("Overlay geometry pool's been blown out!\n");
        exit(0);
    }
    
    free(quads);
}
void QuadsWrite(renderstate *rs, quad *quads, u32 quad_count)
{
    u32 write_size = sizeof(quad) * quad_count;
    memcpy(rs->geometry->write, quads, write_size);
    rs->geometry->write += write_size;
    rs->geometry->used += write_size;
    
    rs->quad_count += quad_count;
    
    if(rs->geometry->used > rs->geometry->size)
    {
        ODS("Overlay geometry pool's been blown out!\n");
        exit(0);
    }
    
    free(quads);
}


void MemoryReset_geometry(renderstate *rs)
{
    rs->geometry->write = rs->geometry->start;
    rs->geometry->used = 0;
    rs->quad_count = 0;
}
void MemoryReset_indexes(renderstate *rs)
{
    rs->indexes->write = rs->indexes->start;
    rs->indexes->used = 0;
    rs->index_count = 0;
}



// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////              RENDERSTATE MANAGEMENT ------ ------
// //////////////////////////////////////////////////////////////////////////////



// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                           STRING RENDERING ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

typedef enum { left, h_center, right  } h_align;
typedef enum { top,  v_center, bottom } v_align;

u8 *ReadFontFile(char *filename)
{
    FILE *f = fopen(filename, "rb");
    if(!f)
    {
        ODS("File '%s' not found\n", filename);
        exit(0);
    }
    
    fseek(f, 0, SEEK_END);
    
    u32 size = ftell(f);
    rewind(f);
    u8 *buffer = (u8 *)malloc(sizeof(u8) * size);
    
    fread(buffer, size, 1, f);
    fclose(f);
    
    return buffer;
}

quad_uv StringQuad(r32 l,    r32 r,    r32 t,    r32 b,
                   r32 uv_l, r32 uv_r, r32 uv_t, r32 uv_b)
{
    quad_uv result;
    
    result.v0.x = l;
    result.v0.y = b;
    result.v0.z = 0.0f;
    result.v0.w = 1.0f;
    result.v0.u = uv_l;
    result.v0.v = uv_b;
    
    result.v1.x = l;
    result.v1.y = t;
    result.v1.z = 0.0f;
    result.v1.w = 1.0f;
    result.v1.u = uv_l;
    result.v1.v = uv_t;
    
    result.v2.x = r;
    result.v2.y = b;
    result.v2.z = 0.0f;
    result.v2.w = 1.0f;
    result.v2.u = uv_r;
    result.v2.v = uv_b;
    
    result.v3.x = r;
    result.v3.y = t;
    result.v3.z = 0.0f;
    result.v3.w = 1.0f;
    result.v3.u = uv_r;
    result.v3.v = uv_t;
    
    return result;
}


vertex_uv *QuadGenerate_uv(r32 left, r32 top, r32 right, r32 bottom, bool flip)
{
    vertex_uv *result = (vertex_uv *)malloc(sizeof(vertex_uv) * 4);
    
    r32 uv_top;
    r32 uv_bot;
    if(!flip)
    {
        uv_top = 0.0f;
        uv_bot = 1.0f;
    }
    else
    {
        uv_top = 1.0f;
        uv_bot = 0.0f;
    }
    
    
    result[0].x = left;
    result[0].y = bottom;
    result[0].z = 0.0f;
    result[0].w = 1.0f;
    result[0].u = 0.0f;
    result[0].v = uv_bot;
    
    result[1].x = left;
    result[1].y = top;
    result[1].z = 0.0f;
    result[1].w = 1.0f;
    result[1].u = 0.0f;
    result[1].v = uv_top;
    
    result[2].x = right;
    result[2].y = bottom;
    result[2].z = 0.0f;
    result[2].w = 1.0f;
    result[2].u = 1.0f;
    result[2].v = uv_bot;
    
    result[3].x = right;
    result[3].y = top;
    result[3].z = 0.0f;
    result[3].w = 1.0f;
    result[3].u = 1.0f;
    result[3].v = uv_top;
    
    return result;
}
vertex_uv *QuadGenerate_uv_center(u32 w, u32 h, r32 cx, r32 cy)
{
    r32 width  = (r32)w;
    r32 height = (r32)h;
    
    vertex_uv *result = (vertex_uv *)malloc(sizeof(vertex_uv) * 4);
    
    r32 left  = cx - width/2.0f;
    r32 right = cx + width/2.0f;
    r32 top    = cy - height/2.0f;
    r32 bottom = cy + height/2.0f;
    
    result[0].x = left;
    result[0].y = top;
    result[0].z = 0.0f;
    result[0].w = 1.0f;
    result[0].u = 0.0f;
    result[0].v = 1.0f;  // 1
    
    result[1].x = left;
    result[1].y = bottom;
    result[1].z = 0.0f;
    result[1].w = 1.0f;
    result[1].u = 0.0f;
    result[1].v = 0.0f;  // 0
    
    result[2].x = right;
    result[2].y = top;
    result[2].z = 0.0f;
    result[2].w = 1.0f;
    result[2].u = 1.0f;
    result[2].v = 1.0f;  // 1
    
    result[3].x = right;
    result[3].y = bottom;
    result[3].z = 0.0f;
    result[3].w = 1.0f;
    result[3].u = 1.0f;
    result[3].v = 0.0f;  // 0
    
    return result;
}
vertex_uv *QuadGenerate_centered_uv(u32 w, u32 h)
{
    r32 width  = (r32)w;
    r32 height = (r32)h;
    
    r32 cx = app.window_width  / 2.0f;
    r32 cy = app.window_height / 2.0f;
    
    vertex_uv *result = QuadGenerate_uv_center(w, h, cx, cy);
    
    return result;
}

vertex *QuadGenerate(r32 left, r32 top, r32 right, r32 bottom)
{
    vertex *result = (vertex *)malloc(sizeof(vertex) * 4);
    
    result[0].x = left;
    result[0].y = top;
    result[0].z = 0.0f;
    result[0].w = 1.0f;
    
    result[1].x = left;
    result[1].y = bottom;
    result[1].z = 0.0f;
    result[1].w = 1.0f;
    
    result[2].x = right;
    result[2].y = top;
    result[2].z = 0.0f;
    result[2].w = 1.0f;
    
    result[3].x = right;
    result[3].y = bottom;
    result[3].z = 0.0f;
    result[3].w = 1.0f;
    
    return result;
}
vertex *QuadGenerate_center(u32 w, u32 h, r32 cx, r32 cy)
{
    r32 width  = (r32)w;
    r32 height = (r32)h;
    
    vertex *result = (vertex *)malloc(sizeof(vertex) * 4);
    
    r32 left  = cx - width/2.0f;
    r32 right = cx + width/2.0f;
    r32 top    = cy - height/2.0f;
    r32 bottom = cy + height/2.0f;
    
    result[0].x = left;
    result[0].y = top;
    result[0].z = 0.0f;
    result[0].w = 1.0f;
    
    result[1].x = left;
    result[1].y = bottom;
    result[1].z = 0.0f;
    result[1].w = 1.0f;
    
    result[2].x = right;
    result[2].y = top;
    result[2].z = 0.0f;
    result[2].w = 1.0f;
    
    result[3].x = right;
    result[3].y = bottom;
    result[3].z = 0.0f;
    result[3].w = 1.0f;
    
    return result;
}
vertex *QuadGenerate_centered(u32 w, u32 h)
{
    r32 width  = (r32)w;
    r32 height = (r32)h;
    
    r32 cx = app.window_width  / 2.0f;
    r32 cy = app.window_height / 2.0f;
    
    vertex *result = QuadGenerate(w, h, cx, cy);
    
    return result;
}


// --- strings
quad_uv *GenerateStringQuads_topleft(font_data *fdata, u32 font_index,
                                     string *str, r32 x_topleft, r32 y_topleft)
{
    // --- Fill stb quads ---
    // ---
    stbtt_aligned_quad *q = (stbtt_aligned_quad *)malloc(sizeof(stbtt_aligned_quad) * str->length);
    
    u32 i = 0;
    while(str->text[i])
    {
        u32 d3dstyle = 1;
        stbtt_GetBakedQuad(fdata[font_index].baked_chardata, fdata[font_index].atlas_data.width, fdata[font_index].atlas_data.height, str->text[i]-fdata[font_index].first_char, &x_topleft, &y_topleft, &q[i], d3dstyle);
        i++;
    }
    // ---
    
    u32 str_width  = q[str->length-1].x1 - q[0].x0;
    u32 str_height = fdata[font_index].ascent - fdata[font_index].descent;
    
    // --- Write the string quads ---
    // ---
    quad_uv *result = (quad_uv *)malloc(sizeof(quad_uv) * str->length);
    
    i = 0;
    while(str->text[i])
    {
        // --- calculate prospective coordinates ---
        // ---
        r32 l = q[i].x0;
        r32 r = q[i].x1;
        r32 t = app.window_height - q[i].y0 - fdata[font_index].ascent;
        r32 b = app.window_height - q[i].y1 - fdata[font_index].ascent;
        
        u32 w = r - l;
        u32 h = t - b;
        
        r32 uv_l = q[i].s0;
        r32 uv_r = q[i].s1;
        r32 uv_t = q[i].t0;
        r32 uv_b = q[i].t1;
        // ---
        
        // Send em off.
        result[i++] = StringQuad(l,    r,    t,    b,
                                 uv_l, uv_r, uv_t, uv_b);
    }
    // ---
    
    free(q);
    
    return result;
}
quad_uv *GenerateStringQuads_centered(font_data *fdata, u32 font_index, string *str,
                                      r32 x_center, r32 y_center)
{
    // --- Fill stb quads ---
    // ---
    stbtt_aligned_quad *q = (stbtt_aligned_quad *)malloc(sizeof(stbtt_aligned_quad) * str->length);
    
    r32 xcoord = 0.0f;
    r32 ycoord = 0.0f;
    
    u32 i = 0;
    while(str->text[i])
    {
        u32 d3dstyle = 1;
        stbtt_GetBakedQuad(fdata[font_index].baked_chardata, fdata[font_index].atlas_data.width, fdata[font_index].atlas_data.height, str->text[i]-fdata[font_index].first_char, &xcoord, &ycoord, &q[i], d3dstyle);
        i++;
    }
    // ---
    
    u32 str_width  = q[str->length-1].x1 - q[0].x0;
    u32 str_height = fdata[font_index].ascent - fdata[font_index].descent;
    
    r32 hcorr = x_center - str_width/2;
    r32 vcorr = y_center - str_height/2;
    
    // --- Write the string quads ---
    // ---
    quad_uv *result = (quad_uv *)malloc(sizeof(quad_uv) * str->length);
    
    i = 0;
    while(str->text[i])
    {
        // --- calculate prospective coordinates ---
        // ---
        r32 l = q[i].x0;
        r32 r = q[i].x1;
        r32 t = app.window_height - q[i].y0 - fdata[font_index].ascent;
        r32 b = app.window_height - q[i].y1 - fdata[font_index].ascent;
        
        u32 w = r - l;
        u32 h = t - b;
        
        r32 uv_l = q[i].s0;
        r32 uv_r = q[i].s1;
        r32 uv_t = q[i].t0;
        r32 uv_b = q[i].t1;
        // ---
        
        // --- Apply corrections ---
        // ---
        l += hcorr;
        r += hcorr;
        t -= vcorr;
        b -= vcorr;
        // ---
        
        // Send em off.
        result[i++] = StringQuad(l,    r,    t,    b,
                                 uv_l, uv_r, uv_t, uv_b);
    }
    // ---
    
    free(q);
    
    return result;
}


quad_uv *GenerateStringQuads(font_data *fdata, u32 font_index, string *str,
                             h_align h,     v_align v,
                             r32 h_padding, r32 v_padding)
{
    // --- Fill stb quads ---
    // ---
    stbtt_aligned_quad *q = (stbtt_aligned_quad *)malloc(sizeof(stbtt_aligned_quad) * str->length);
    
    r32 xcoord = 0.0f;
    r32 ycoord = 0.0f;
    
    u32 i = 0;
    while(str->text[i])
    {
        u32 d3dstyle = 1;
        stbtt_GetBakedQuad(fdata[font_index].baked_chardata, fdata[font_index].atlas_data.width, fdata[font_index].atlas_data.height, str->text[i]-fdata[font_index].first_char, &xcoord, &ycoord, &q[i], d3dstyle);
        i++;
    }
    // ---
    
    u32 str_width  = q[str->length-1].x1 - q[0].x0;
    u32 str_height = fdata[font_index].ascent - fdata[font_index].descent;
    
    
    // --- calculate corrections ---
    // ---
    r32 hcorr = 0.0f;
    if(h == left)
        hcorr = h_padding;
    else if(h == h_center)
        hcorr = (app.window_width - str_width)/2.0f;
    else if(h == right)
        hcorr = app.window_width - str_width - h_padding;
    else { ODS("Whoops. Wrong enum value.\n"); exit(0); }
    
    r32 vcorr;
    if(v == top)
        vcorr = v_padding;
    else if(v == v_center)
        vcorr = (app.window_height - str_height)/2.0f;
    else if(v == bottom)
        vcorr = app.window_height - fdata[font_index].ascent - v_padding;  // To align by baseline, subtract descent as well
    else { ODS("Whoops. Wrong enum value.\n"); exit(0); }
    // ---
    
    
    // --- Write the string quads ---
    // ---
    quad_uv *result = (quad_uv *)malloc(sizeof(quad_uv) * str->length);
    
    i = 0;
    while(str->text[i])
    {
        // --- calculate coordinates ---
        // ---
        r32 l = q[i].x0;
        r32 r = q[i].x1;
        r32 t = app.window_height - q[i].y0 - fdata[font_index].ascent;
        r32 b = app.window_height - q[i].y1 - fdata[font_index].ascent;
        
        u32 w = r - l;
        u32 h = t - b;
        
        r32 uv_l = q[i].s0;
        r32 uv_r = q[i].s1;
        r32 uv_t = q[i].t0;
        r32 uv_b = q[i].t1;
        // ---
        
        
        // --- Apply corrections ---
        // ---
        l += hcorr;
        r += hcorr;
        t -= vcorr;
        b -= vcorr;
        // ---
        
        
        // Send em off.
        result[i++] = StringQuad(l,    r,    t,    b,
                                 uv_l, uv_r, uv_t, uv_b);
    }
    // ---
    
    free(q);
    
    return result;
}
quad_uv *GenerateStringQuads(font_data *fdata, u32 font_index, string *str,
                             h_align h, v_align v,
                             r32 padding)
{
    return GenerateStringQuads(fdata, font_index, str,
                               h, v,
                               padding, padding);
}
quad_uv *GenerateStringQuads(font_data *fdata, u32 font_index, string *str,
                             h_align h, v_align v)
{
    return GenerateStringQuads(fdata, font_index, str,
                               h, v,
                               0.0f, 0.0f);
}

// ------ ------ ------ divide between stb-facing and render-oriented functions ------ ------ ------

u32 *STB_WritePixels(u8 *bitmap, s32 width, s32 height, u32 color)
{
    u32 *pixels = (u32 *)malloc(sizeof(u32) * width * height);
    
    color = color & 0xFFFFFF;
    
    u32 *writer = pixels;
    u8 *linetracker = bitmap;
    for(u32 y = 0; y < height; y++)
    {
        u8 *reader = linetracker;
        for(u32 x = 0; x < width; x++)
        {
            u8 alpha = *reader++;
            u32 pixel;
            pixel = (alpha << 24) | color;
            
            *writer++ = pixel;
        }
        linetracker += width;
    }
    
    return pixels;
}

#define BUFSIZE 50
void Font_InitAndBake(renderstate *rs, char *fontfile, r32 font_size, u32 color)
{
    u8 *ttf_buffer = ReadFontFile(fontfile);
    stbtt_InitFont(&rs->fd->fontinfo, ttf_buffer, stbtt_GetFontOffsetForIndex(ttf_buffer, 0));
    
    rs->fd->font_size = font_size;
    rs->fd->scale = stbtt_ScaleForPixelHeight(&rs->fd->fontinfo, rs->fd->font_size);
    
    s32 s_ascent;
    s32 s_descent;
    s32 s_linegap;
    stbtt_GetFontVMetrics(&rs->fd->fontinfo, &s_ascent, &s_descent, &s_linegap);
    rs->fd->ascent  = (r32)s_ascent * rs->fd->scale;
    rs->fd->descent = (r32)s_descent * rs->fd->scale;
    rs->fd->linegap = (r32)s_linegap * rs->fd->scale;
    rs->fd->v_advance = rs->fd->ascent - rs->fd->descent + rs->fd->linegap;
    
    s32 char_count = 96;
    rs->fd->atlas_data.width  = 512;
    rs->fd->atlas_data.height = 512;
    
    u8 *bakedfont_bitmap = (u8 *)malloc(rs->fd->atlas_data.width * rs->fd->atlas_data.height);
    rs->fd->baked_chardata = (stbtt_bakedchar *)malloc(sizeof(stbtt_bakedchar) * rs->fd->char_count);
    
    stbtt_BakeFontBitmap(ttf_buffer, 0,
                         font_size,
                         bakedfont_bitmap, rs->fd->atlas_data.width, rs->fd->atlas_data.height,
                         rs->fd->first_char, rs->fd->char_count,
                         rs->fd->baked_chardata);
    
    rs->fd->atlas_data.pixels = STB_WritePixels(bakedfont_bitmap, rs->fd->atlas_data.width, rs->fd->atlas_data.height, color);
    rs->fd->atlas_data.pixels_datasize = rs->fd->atlas_data.width * rs->fd->atlas_data.height * 4;
    
    free(bakedfont_bitmap);
}

void RenderString_va(renderstate *rs, u32 font_index, h_align ha, v_align va, u32 h_pad, u32 v_pad, char *format, va_list args)
{
    // --- format writing ---
    u32 size = BUFSIZE;
    char *buffer = (char *)malloc(size);
    u32 n = vsnprintf(buffer, size, format, args);
    if(size < n)
    {
        while(size < n)
            size *= 2;
        buffer = (char *)realloc(buffer, size);
        vsnprintf(buffer, size, format, args);
    }
    // ---
    
    // --- quad generating ---
    string *str = String(buffer);
    quad_uv *quads = GenerateStringQuads(rs->fd, font_index, str, ha, va, h_pad, v_pad);
    QuadsWrite_uv(rs, quads, str->length);
    // ---
    
    free(buffer);
}
void RenderString(renderstate *rs, u32 font_index, h_align ha, v_align va, u32 h_pad, u32 v_pad, char *format, ...)
{
    va_list args;
    va_start(args, format);
    RenderString_va(rs, font_index, ha, va, h_pad, v_pad, format, args);
    va_end(args);
}
void RenderString(renderstate *rs, u32 font_index, h_align ha, v_align va, u32 pad, char *format, ...)
{
    va_list args;
    va_start(args, format);
    RenderString_va(rs, font_index, ha, va, pad, pad, format, args);
    va_end(args);
}

void RenderString_centered(renderstate *rs, u32 font_index, r32 x, r32 y, char *format, ...)
{
    // --- format writing ---
    u32 size = BUFSIZE;
    char *buffer = (char *)malloc(size);
    va_list args;
    va_start(args, format);
    u32 n = vsnprintf(buffer, size, format, args);
    if(size < n)
    {
        while(size < n)
            size *= 2;
        buffer = (char *)realloc(buffer, size);
        vsnprintf(buffer, size, format, args);
    }
    // ---
    
    // --- quad generating ---
    string *str = String(buffer);
    quad_uv *quads = GenerateStringQuads_centered(rs->fd, font_index, str, x, y);
    QuadsWrite_uv(rs, quads, str->length);
    // ---
    
    free(buffer);
}

void RenderMatrixStrings(renderstate *rs, u32 font_index, h_align ha, v_align va,
                         u32 h_pad, u32 v_pad, char *format, matrix4 m)
{
    r32 v_advance = rs->fd->v_advance;
    RenderString(rs, font_index, ha, va, h_pad, v_pad,
                 format, m[0],  m[1],  m[2],  m[3]);
    RenderString(rs, font_index, ha, va, h_pad, v_pad + v_advance,
                 format, m[4],  m[5],  m[6],  m[7]);
    RenderString(rs, font_index, ha, va, h_pad, v_pad + 2 * v_advance,
                 format, m[8],  m[9],  m[10], m[11]);
    RenderString(rs, font_index, ha, va, h_pad, v_pad + 3 * v_advance,
                 format, m[12], m[13], m[14], m[15]);
}

// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////                    STRING RENDERING ------ ------
// //////////////////////////////////////////////////////////////////////////////



// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                  VULKAN FUNCTION(INTERACTION?) ABSTRACTION ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

// Data-like stuff goes first(of which there's only one function).
// Then "scout"-wrappers.
// Then functions that create constructs.
// Then vk-related functions that actually do something :)
// THEN, at the end, there's the VulkanPrepare().

// But maybe this should be dispersed into a bunch of initialized standalone structs.
// Or pass a vk_struct and make it "InitializeVkData" or something.
void LoadInfos()
{
    vk.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    vk.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    vk.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    vk.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    
    vk.color_sr.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
    vk.color_sr.baseMipLevel   = 0;
    vk.color_sr.levelCount     = 1;
    vk.color_sr.baseArrayLayer = 0;
    vk.color_sr.layerCount     = 1;
    
    vk.cb_bi.sType            = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    vk.cb_bi.pNext            = NULL;
    vk.cb_bi.flags            = 0;
    vk.cb_bi.pInheritanceInfo = NULL;
    
    vk.fence_ci.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    vk.fence_ci.pNext = NULL;
    vk.fence_ci.flags = 0;
    
    vk.semaphore_ci.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    vk.semaphore_ci.pNext = NULL;
    vk.semaphore_ci.flags = 0;
}

// --- --- ---


VKAPI_ATTR VkBool32 VKAPI_CALL
DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT severity,
              VkDebugUtilsMessageTypeFlagsEXT types,
              const VkDebugUtilsMessengerCallbackDataEXT *callback_data,
              void *user_data)
{
    ODS(">>> MessageIdName: %s\n", callback_data->pMessageIdName);
    ODS(">>> MessageIdNum:  %d\n", callback_data->messageIdNumber);
    ODS(">>> Message:       %s\n", callback_data->pMessage);
    ODS("\n");
    
    return VK_FALSE;
}

void Vulkan_SetupDebugging(VkInstance instance, VkDebugUtilsMessengerEXT debug_messenger)
{
    VkResult result;
    
    VkDebugUtilsMessengerCreateInfoEXT debug_messenger_ci = {};
    debug_messenger_ci.sType           = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    debug_messenger_ci.pNext           = NULL;
    debug_messenger_ci.flags           = 0;
    debug_messenger_ci.messageSeverity =
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT|
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT|
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT|
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    debug_messenger_ci.messageType     =
        VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT|
        VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT|
        VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    debug_messenger_ci.pfnUserCallback = DebugCallback;
    debug_messenger_ci.pUserData       = NULL;
    
    result = vkCreateDebugUtilsMessengerEXT(instance, &debug_messenger_ci, NULL, &debug_messenger);
    ODS("Debug utils messenger creation: %s\n", RevEnum(data.result_enum, result));
}

void EnumerateGlobalExtensions()
{
    VkResult result;
    
    u32 global_propscount;
    result = vkEnumerateInstanceExtensionProperties(NULL, &global_propscount, NULL);
    ODS("Instance extension props(count): %s\n", RevEnum(data.result_enum, result));
    VkExtensionProperties *global_props = (VkExtensionProperties *)malloc(sizeof(VkExtensionProperties) * global_propscount);
    result = vkEnumerateInstanceExtensionProperties(NULL, &global_propscount, global_props);
    ODS("Instance extension props(fill):  %s\n", RevEnum(data.result_enum, result));
    
    ODS("\n> Instance-wide extensions: %d\n", global_propscount);
    for(u32 i = 0; i < global_propscount; i++)
    {
        u32 version = global_props[i].specVersion;
        u32 major = VK_VERSION_MAJOR(version);
        u32 minor = VK_VERSION_MINOR(version);
        u32 patch = VK_VERSION_PATCH(version);
        ODS("%2d - %-40s | %d.%d.%d\n", i, global_props[i].extensionName, major, minor, patch);
    }
    ODS("\n");
}

void EnumerateLayerExtensions()
{
    VkResult result;
    
    u32 layer_count = 0;
    result = vkEnumerateInstanceLayerProperties(&layer_count, NULL);
    ODS("Instance layer props(count): %s\n", RevEnum(data.result_enum, result));
    VkLayerProperties *layer_props = (VkLayerProperties *)malloc(sizeof(VkLayerProperties) * layer_count);
    result = vkEnumerateInstanceLayerProperties(&layer_count, layer_props);
    ODS("Instance layer props(fill):  %s\n", RevEnum(data.result_enum, result));
    
    ODS("\n> Instance layers: %d\n", layer_count);
    for(u32 i = 0; i < layer_count; i++)
    {
        u32 spec_version = layer_props[i].specVersion;
        u32 spec_major = VK_VERSION_MAJOR(spec_version);
        u32 spec_minor = VK_VERSION_MINOR(spec_version);
        u32 spec_patch = VK_VERSION_PATCH(spec_version);
        
        u32 impl_version = layer_props[i].implementationVersion;
        u32 impl_major = VK_VERSION_MAJOR(impl_version);
        u32 impl_minor = VK_VERSION_MINOR(impl_version);
        u32 impl_patch = VK_VERSION_PATCH(impl_version);
        
        ODS("%2d - %-40s | %d.%d.%-3d | %d.%d.%d | %.50s\n",
            i,
            layer_props[i].layerName,
            spec_major, spec_minor, spec_patch,
            impl_major, impl_minor, impl_patch,
            layer_props[i].description);
        
        u32 ext_count = 0;
        vkEnumerateInstanceExtensionProperties(layer_props[i].layerName, &ext_count, NULL);
        if(ext_count)
        {
            ODS(">> its extensions: %d\n", ext_count);
            
            VkExtensionProperties *ext_props = (VkExtensionProperties *)malloc(sizeof(VkExtensionProperties) * ext_count);
            vkEnumerateInstanceExtensionProperties(layer_props[i].layerName, &ext_count, ext_props);
            
            for(u32 i = 0; i < ext_count; i++)
            {
                u32 version = ext_props[i].specVersion;
                u32 major = VK_VERSION_MAJOR(version);
                u32 minor = VK_VERSION_MINOR(version);
                u32 patch = VK_VERSION_PATCH(version);
                ODS(" - %2d - %-37s | %d.%d.%d\n", i, ext_props[i].extensionName, major, minor, patch);
            }
        }
    }
    ODS("\n");
}

void GetGPU()
{
    VkResult result;
    
    u32 device_count;
    result = vkEnumeratePhysicalDevices(vk.instance, &device_count, NULL);
    ODS("Physical device(count): %s\n", RevEnum(data.result_enum, result));
    VkPhysicalDevice *gpus = (VkPhysicalDevice *)malloc(sizeof(VkPhysicalDevice) * device_count);
    result = vkEnumeratePhysicalDevices(vk.instance, &device_count, gpus);
    ODS("Physical device(fill):  %s\n", RevEnum(data.result_enum, result));
    
    vk.gpu = gpus[0];
}

void EnumerateDeviceExtensions()
{
    VkResult result;
    
    u32 devext_propcount;
    result = vkEnumerateDeviceExtensionProperties(vk.gpu, NULL, &devext_propcount, NULL);
    ODS("Device extension props(count): %s\n", RevEnum(data.result_enum, result));
    VkExtensionProperties *devext_props = (VkExtensionProperties *)malloc(sizeof(VkExtensionProperties) * devext_propcount);
    result = vkEnumerateDeviceExtensionProperties(vk.gpu, NULL, &devext_propcount, devext_props);
    ODS("Device extension props(fill):  %s\n", RevEnum(data.result_enum, result));
    
    ODS("\n> Device extensions: %d\n", devext_propcount);
    for(u32 i = 0; i < devext_propcount; i++)
    {
        u32 version = devext_props[i].specVersion;
        u32 major = VK_VERSION_MAJOR(version);
        u32 minor = VK_VERSION_MINOR(version);
        u32 patch = VK_VERSION_PATCH(version);
        ODS("%2d - %-40s | %d.%d.%d\n", i, devext_props[i].extensionName, major, minor, patch);
    }
    ODS("\n");
}

void EnumerateDeviceLayers()
{
    VkResult result;
    
    u32 dev_layercount = 0;
    result = vkEnumerateDeviceLayerProperties(vk.gpu, &dev_layercount, NULL);
    ODS("Enumerate device layer props(count): %s\n", RevEnum(data.result_enum, result));
    VkLayerProperties *dev_layerprops = (VkLayerProperties *)malloc(sizeof(VkLayerProperties) * dev_layercount);
    result = vkEnumerateDeviceLayerProperties(vk.gpu, &dev_layercount, dev_layerprops);
    ODS("Enumerate device layer props(fill):  %s\n", RevEnum(data.result_enum, result));
    
    ODS("\n> Device layers: %d\n", dev_layercount);
    for(u32 i = 0; i < dev_layercount; i++)
    {
        u32 spec_version = dev_layerprops[i].specVersion;
        u32 spec_major = VK_VERSION_MAJOR(spec_version);
        u32 spec_minor = VK_VERSION_MINOR(spec_version);
        u32 spec_patch = VK_VERSION_PATCH(spec_version);
        
        u32 impl_version = dev_layerprops[i].implementationVersion;
        u32 impl_major = VK_VERSION_MAJOR(impl_version);
        u32 impl_minor = VK_VERSION_MINOR(impl_version);
        u32 impl_patch = VK_VERSION_PATCH(impl_version);
        
        ODS("%2d - %-40s | %d.%d.%-3d | %d.%d.%d | %.50s\n",
            i,
            dev_layerprops[i].layerName,
            spec_major, spec_minor, spec_patch,
            impl_major, impl_minor, impl_patch,
            dev_layerprops[i].description);
        
        u32 ext_count = 0;
        result = vkEnumerateDeviceExtensionProperties(vk.gpu, dev_layerprops[i].layerName, &ext_count, NULL);
        ODS(" - Enumerate device layer %s props(count): %s\n", dev_layerprops[i].layerName, RevEnum(data.result_enum, result));
        if(ext_count)
        {
            ODS(" > its extensions: %d\n", ext_count);
            
            VkExtensionProperties *ext_props = (VkExtensionProperties *)malloc(sizeof(VkExtensionProperties) * ext_count);
            result = vkEnumerateDeviceExtensionProperties(vk.gpu, dev_layerprops[i].layerName, &ext_count, ext_props);
            ODS(" - Enumerate device layer %s props(fill): %s\n", dev_layerprops[i].layerName, RevEnum(data.result_enum, result));
            
            for(u32 i = 0; i < ext_count; i++)
            {
                u32 version = ext_props[i].specVersion;
                u32 major = VK_VERSION_MAJOR(version);
                u32 minor = VK_VERSION_MINOR(version);
                u32 patch = VK_VERSION_PATCH(version);
                ODS(" - %2d - %-37s | %d.%d.%d\n", i, ext_props[i].extensionName, major, minor, patch);
            }
        }
    }
    ODS("\n");
}

void CheckGPUFeatures()
{
    VkPhysicalDeviceFeatures gpu_features;
    vkGetPhysicalDeviceFeatures(vk.gpu, &gpu_features);
    
    // This was previously generated with a metaprogramming utility.
    // To be showcased in a future portfolio entry :)
    ODS("- %-40s: %s\n", "robustBufferAccess", (gpu_features.robustBufferAccess & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "fullDrawIndexUint32", (gpu_features.fullDrawIndexUint32 & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "imageCubeArray", (gpu_features.imageCubeArray & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "independentBlend", (gpu_features.independentBlend & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "geometryShader", (gpu_features.geometryShader & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "tessellationShader", (gpu_features.tessellationShader & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "sampleRateShading", (gpu_features.sampleRateShading & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "dualSrcBlend", (gpu_features.dualSrcBlend & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "logicOp", (gpu_features.logicOp & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "multiDrawIndirect", (gpu_features.multiDrawIndirect & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "drawIndirectFirstInstance", (gpu_features.drawIndirectFirstInstance & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "depthClamp", (gpu_features.depthClamp & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "depthBiasClamp", (gpu_features.depthBiasClamp & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "fillModeNonSolid", (gpu_features.fillModeNonSolid & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "depthBounds", (gpu_features.depthBounds & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "wideLines", (gpu_features.wideLines & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "largePoints", (gpu_features.largePoints & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "alphaToOne", (gpu_features.alphaToOne & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "multiViewport", (gpu_features.multiViewport & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "samplerAnisotropy", (gpu_features.samplerAnisotropy & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "textureCompressionETC2", (gpu_features.textureCompressionETC2 & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "textureCompressionASTC_LDR", (gpu_features.textureCompressionASTC_LDR & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "textureCompressionBC", (gpu_features.textureCompressionBC & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "occlusionQueryPrecise", (gpu_features.occlusionQueryPrecise & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "pipelineStatisticsQuery", (gpu_features.pipelineStatisticsQuery & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "vertexPipelineStoresAndAtomics", (gpu_features.vertexPipelineStoresAndAtomics & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "fragmentStoresAndAtomics", (gpu_features.fragmentStoresAndAtomics & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderTessellationAndGeometryPointSize", (gpu_features.shaderTessellationAndGeometryPointSize & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderImageGatherExtended", (gpu_features.shaderImageGatherExtended & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderStorageImageExtendedFormats", (gpu_features.shaderStorageImageExtendedFormats & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderStorageImageMultisample", (gpu_features.shaderStorageImageMultisample & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderStorageImageReadWithoutFormat", (gpu_features.shaderStorageImageReadWithoutFormat & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderStorageImageWriteWithoutFormat", (gpu_features.shaderStorageImageWriteWithoutFormat & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderUniformBufferArrayDynamicIndexing", (gpu_features.shaderUniformBufferArrayDynamicIndexing & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderSampledImageArrayDynamicIndexing", (gpu_features.shaderSampledImageArrayDynamicIndexing & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderStorageBufferArrayDynamicIndexing", (gpu_features.shaderStorageBufferArrayDynamicIndexing & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderStorageImageArrayDynamicIndexing", (gpu_features.shaderStorageImageArrayDynamicIndexing & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderClipDistance", (gpu_features.shaderClipDistance & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderCullDistance", (gpu_features.shaderCullDistance & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderFloat64", (gpu_features.shaderFloat64 & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderInt64", (gpu_features.shaderInt64 & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderInt16", (gpu_features.shaderInt16 & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderResourceResidency", (gpu_features.shaderResourceResidency & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "shaderResourceMinLod", (gpu_features.shaderResourceMinLod & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "sparseBinding", (gpu_features.sparseBinding & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "sparseResidencyBuffer", (gpu_features.sparseResidencyBuffer & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "sparseResidencyImage2D", (gpu_features.sparseResidencyImage2D & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "sparseResidencyImage3D", (gpu_features.sparseResidencyImage3D & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "sparseResidency2Samples", (gpu_features.sparseResidency2Samples & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "sparseResidency4Samples", (gpu_features.sparseResidency4Samples & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "sparseResidency8Samples", (gpu_features.sparseResidency8Samples & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "sparseResidency16Samples", (gpu_features.sparseResidency16Samples & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "sparseResidencyAliased", (gpu_features.sparseResidencyAliased & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "variableMultisampleRate", (gpu_features.variableMultisampleRate & 1) ? "YES" : "NO");
    ODS("- %-40s: %s\n", "inheritedQueries", (gpu_features.inheritedQueries & 1) ? "YES" : "NO");
    ODS("\n");
}

void GetFormatAndColorspace()
{
    VkResult result;
    
    u32 surface_formatcount = 0;
    result = vkGetPhysicalDeviceSurfaceFormatsKHR(vk.gpu, vk.surface, &surface_formatcount, NULL);
    ODS("Surface formats(count): %s\n", RevEnum(data.result_enum, result));
    VkSurfaceFormatKHR *surface_formats = (VkSurfaceFormatKHR *)malloc(sizeof(VkSurfaceFormatKHR) * surface_formatcount);
    result = vkGetPhysicalDeviceSurfaceFormatsKHR(vk.gpu, vk.surface, &surface_formatcount, surface_formats);
    ODS("Surface formats(fill):  %s\n", RevEnum(data.result_enum, result));
    
    ODS("> Surface formats:\n");
    for(u32 i = 0; i < surface_formatcount; i++)
    {
        ODS("FormatKHR %d:\n", i);
        ODS("- format:      %s\n", RevEnum(data.format_enum,     surface_formats[i].format));
        ODS("- color space: %s\n", RevEnum(data.colorspace_enum, surface_formats[i].colorSpace));
    }
    ODS("\n");
    
    ODS("> Surface properties:\n");
    for(u32 i = 0; i < surface_formatcount; i++)
    {
        VkFormatProperties surface_props;
        vkGetPhysicalDeviceFormatProperties(vk.gpu, surface_formats[i].format, &surface_props);
        
        ODS("> Format %d:\n", i);
        ODS("Linear  tiling:  %s\n", DecToBin(surface_props.linearTilingFeatures));
        ODS("Optimal tiling:  %s\n", DecToBin(surface_props.optimalTilingFeatures));
        ODS("Buffer features: %s\n", DecToBin(surface_props.bufferFeatures));
        ODS("\n");
    }
    
    vk.format = surface_formats[0].format;
    vk.colorspace = surface_formats[0].colorSpace;
}

void CheckSurfaceCapabilities()
{
    VkResult result;
    
    VkSurfaceCapabilitiesKHR surface_caps;
    result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vk.gpu, vk.surface, &surface_caps);
    ODS("Physical device surface capabilities result: %s\n", RevEnum(data.result_enum, result));
    
    ODS("> Surface capabilities:\n");
    ODS("- min images: %d\n", surface_caps.minImageCount);
    ODS("- max images: %d\n", surface_caps.maxImageCount);
    ODS("- current extent: %-4d x %-4d\n", surface_caps.currentExtent.width,  surface_caps.currentExtent.height);
    ODS("- minimal extent: %-4d x %-4d\n", surface_caps.minImageExtent.width, surface_caps.minImageExtent.height);
    ODS("- maximal extent: %-4d x %-4d\n", surface_caps.maxImageExtent.width, surface_caps.maxImageExtent.height);
    ODS("- max image arrays: %d\n", surface_caps.maxImageArrayLayers);
    ODS("- Supported transforms:      %s\n", DecToBin(surface_caps.supportedTransforms));
    ODS("- Current transform:         %s\n", DecToBin(surface_caps.currentTransform));
    ODS("- Supported composite alpha: %s\n", DecToBin(surface_caps.supportedCompositeAlpha));
    ODS("- Supported usage flags:     %s\n", DecToBin(surface_caps.supportedUsageFlags));
    ODS("\n");
}

void SetPresentMode()
{
    VkResult result;
    
    u32 present_modecount;
    result = vkGetPhysicalDeviceSurfacePresentModesKHR(vk.gpu, vk.surface, &present_modecount, NULL);
    ODS("Surface formats(count): %s\n", RevEnum(data.result_enum, result));
    VkPresentModeKHR *present_modes = (VkPresentModeKHR *)malloc(sizeof(VkPresentModeKHR) * present_modecount);
    result = vkGetPhysicalDeviceSurfacePresentModesKHR(vk.gpu, vk.surface, &present_modecount, present_modes);
    ODS("Surface formats(fill):  %s\n", RevEnum(data.result_enum, result));
    
    ODS("> Present modes:\n");
    for(u32 i = 0; i < present_modecount; i++)
    {
        char *mode = RevEnum(data.presentmode_enum, present_modes[i]);
        ODS("Mode %d: %s\n", i, mode);
        
        if(strstr(mode, "MAILBOX"))
            vk.present_mode = present_modes[i];
    }
    ODS("Chosen present mode: %s\n", RevEnum(data.presentmode_enum, vk.present_mode));
    ODS("\n");
}

void CheckDeviceMemoryProperties()
{
    vkGetPhysicalDeviceMemoryProperties(vk.gpu, &vk.gpu_memprops);
    
    ODS("> Memory properties: \n");
    ODS("- memory heap count: %d\n", vk.gpu_memprops.memoryHeapCount);
    for(u32 i = 0; i < vk.gpu_memprops.memoryHeapCount; i++)
    {
        ODS("-- heap: %d: \n", i);
        ODS("size:  %zd MB\n", vk.gpu_memprops.memoryHeaps[i].size / (1024 * 1024));
        ODS("flags: %s  \n", DecToBin(vk.gpu_memprops.memoryHeaps[i].flags));
        ODS("\n");
    }
    ODS("- memory type count: %d\n", vk.gpu_memprops.memoryTypeCount);
    for(u32 i = 0; i < vk.gpu_memprops.memoryTypeCount; i++)
    {
        ODS("-- memory: %d: \n", i);
        ODS("heap index: %d \n", vk.gpu_memprops.memoryTypes[i].heapIndex);
        ODS("type:       %s \n", DecToBin(vk.gpu_memprops.memoryTypes[i].propertyFlags));
        ODS("\n");
    }
    ODS("\n");
}



// Finding a memory type index
u32 FindMemoryIndex(u32 possibleMemoryIndexes, u32 requiredProperties,
                    VkPhysicalDeviceMemoryProperties memoryProperties)
{
    ODS("Possible indexes:\n%.*s\n", 64,        DecToBin(possibleMemoryIndexes));
    ODS("Looking for these flags:\n%.*s\n", 64, DecToBin(requiredProperties));
    
    u32 memoryTypeCount = memoryProperties.memoryTypeCount;
    // iterate over all of the memory types,
    for(int i = 0; i < memoryTypeCount; i++)
    {
        // if we encountered a bit that's one of the returned from memoryreqs,
        if((possibleMemoryIndexes >> i) & 1)
        {
            // check if it has our required memory properties.
            u32 memoryTypePropertyFlags = memoryProperties.memoryTypes[i].propertyFlags;
            if((memoryTypePropertyFlags & requiredProperties) == requiredProperties)
            {
                ODS("selected index: %d\n", i);
                
                return i;
            }
        }
    }
    
    ODS("Couldn't find anything suitable\n");
    return -1;
}

// --- --- ---

void InstanceCreate(char **instance_layers, u32 layer_count,
                    char **instance_extensions, u32 extension_count)
{
    VkInstanceCreateInfo instance_ci = {};
    instance_ci.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instance_ci.pNext                   = NULL;
    instance_ci.flags                   = 0;
    instance_ci.pApplicationInfo        = NULL;
    instance_ci.enabledLayerCount       = layer_count;
    instance_ci.ppEnabledLayerNames     = instance_layers;
    instance_ci.enabledExtensionCount   = extension_count;
    instance_ci.ppEnabledExtensionNames = instance_extensions;
    
    VkResult result = vkCreateInstance(&instance_ci, NULL, &vk.instance);
    ODS("Vulkan instance creation: %s\n", RevEnum(data.result_enum, result));
}

void CreateSurface()
{
    VkResult result;
    
    VkWin32SurfaceCreateInfoKHR surface_ci = {};
    surface_ci.sType     = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    surface_ci.pNext     = NULL;
    surface_ci.flags     = 0;
    surface_ci.hinstance = app.instance;
    surface_ci.hwnd      = app.window;
    
    result = vkCreateWin32SurfaceKHR(vk.instance, &surface_ci, NULL, &vk.surface);
    ODS("Surface creation: %s\n", RevEnum(data.result_enum, result));
}

void SetupQueue()
{
    VkResult result;
    
    // ---
    u32 queuefam_propcount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(vk.gpu, &queuefam_propcount, NULL);
    VkQueueFamilyProperties *queue_famprops = (VkQueueFamilyProperties *)malloc(sizeof(VkQueueFamilyProperties) * queuefam_propcount);
    vkGetPhysicalDeviceQueueFamilyProperties(vk.gpu, &queuefam_propcount, queue_famprops);
    
    ODS("> Queue family count: %d\n", queuefam_propcount);
    for(u32 i = 0; i < queuefam_propcount; i++)
    {
        ODS("Family %d:\n", i);
        ODS("%3d queues\n", queue_famprops[i].queueCount);
        ODS("Minimum gran: %-4d x %-4d\n", queue_famprops[i].minImageTransferGranularity.width, queue_famprops[i].minImageTransferGranularity.height);
        ODS("- graphics:  %s\n", (queue_famprops[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) ? "YES" : "NO");
        ODS("- compute:   %s\n", (queue_famprops[i].queueFlags & VK_QUEUE_COMPUTE_BIT)  ? "YES" : "NO");
        ODS("- transfer:  %s\n", (queue_famprops[i].queueFlags & VK_QUEUE_TRANSFER_BIT) ? "YES" : "NO");
        ODS("- sparse:    %s\n", (queue_famprops[i].queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) ? "YES" : "NO");
        ODS("- protected: %s\n", (queue_famprops[i].queueFlags & VK_QUEUE_PROTECTED_BIT) ? "YES" : "NO");
        ODS("\n");
    }
    // ---
    
    // ---
    u32 queue_famindex = 0;
    
    for(u32 i = 0; i < queuefam_propcount; i++)
    {
        u32 can_graphics;
        u32 can_present;
        
        can_graphics = queue_famprops[i].queueFlags & VK_QUEUE_GRAPHICS_BIT;
        vkGetPhysicalDeviceSurfaceSupportKHR(vk.gpu, i, vk.surface, &can_present);
        
        if(can_graphics && can_present)
            queue_famindex = i;
    }
    
    vk.queue_family_index = queue_famindex;
    // ---
}
void DeviceCreate(char **device_extensions, u32 device_extension_count, VkPhysicalDeviceFeatures features)
{
    VkResult result;
    
    r32 queue_priorities[] = { 1.0f, 1.0f };
    
    VkDeviceQueueCreateInfo queue_ci = {};
    queue_ci.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_ci.pNext            = NULL;
    queue_ci.flags            = 0;
    queue_ci.queueFamilyIndex = vk.queue_family_index;
    queue_ci.queueCount       = 2;
    queue_ci.pQueuePriorities = queue_priorities;
    
    VkDeviceCreateInfo device_ci = {};
    device_ci.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    device_ci.pNext                   = NULL;
    device_ci.flags                   = 0;
    device_ci.queueCreateInfoCount    = 1;
    device_ci.pQueueCreateInfos       = &queue_ci;
    device_ci.enabledLayerCount       = 0;
    device_ci.ppEnabledLayerNames     = NULL;
    device_ci.enabledExtensionCount   = device_extension_count;
    device_ci.ppEnabledExtensionNames = device_extensions;
    device_ci.pEnabledFeatures        = &features;
    
    result = vkCreateDevice(vk.gpu, &device_ci, NULL, &vk.device);
    ODS("Device creation: %s\n", RevEnum(data.result_enum, result));
}
void DeviceCreate_VariableDescriptorEXT(char **device_extensions, u32 device_extension_count, VkPhysicalDeviceFeatures features)
{
    VkResult result;
    
    r32 queue_priorities[] = { 1.0f, 1.0f };
    
    VkDeviceQueueCreateInfo queue_ci = {};
    queue_ci.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_ci.pNext            = NULL;
    queue_ci.flags            = 0;
    queue_ci.queueFamilyIndex = vk.queue_family_index;
    queue_ci.queueCount       = 2;
    queue_ci.pQueuePriorities = queue_priorities;
    
    VkPhysicalDeviceDescriptorIndexingFeaturesEXT indexing_features_EXT = {};
    indexing_features_EXT.sType                                              = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES_EXT;
    indexing_features_EXT.pNext                                              = NULL;
    indexing_features_EXT.shaderInputAttachmentArrayDynamicIndexing          = false;
    indexing_features_EXT.shaderUniformTexelBufferArrayDynamicIndexing       = false;
    indexing_features_EXT.shaderStorageTexelBufferArrayDynamicIndexing       = false;
    indexing_features_EXT.shaderUniformBufferArrayNonUniformIndexing         = false;
    indexing_features_EXT.shaderSampledImageArrayNonUniformIndexing          = false;
    indexing_features_EXT.shaderStorageBufferArrayNonUniformIndexing         = false;
    indexing_features_EXT.shaderStorageImageArrayNonUniformIndexing          = false;
    indexing_features_EXT.shaderInputAttachmentArrayNonUniformIndexing       = false;
    indexing_features_EXT.shaderUniformTexelBufferArrayNonUniformIndexing    = false;
    indexing_features_EXT.shaderStorageTexelBufferArrayNonUniformIndexing    = false;
    indexing_features_EXT.descriptorBindingUniformBufferUpdateAfterBind      = false;
    indexing_features_EXT.descriptorBindingSampledImageUpdateAfterBind       = false;
    indexing_features_EXT.descriptorBindingStorageImageUpdateAfterBind       = false;
    indexing_features_EXT.descriptorBindingStorageBufferUpdateAfterBind      = false;
    indexing_features_EXT.descriptorBindingUniformTexelBufferUpdateAfterBind = false;
    indexing_features_EXT.descriptorBindingStorageTexelBufferUpdateAfterBind = false;
    indexing_features_EXT.descriptorBindingUpdateUnusedWhilePending          = false;
    indexing_features_EXT.descriptorBindingPartiallyBound                    = false;
    indexing_features_EXT.descriptorBindingVariableDescriptorCount           = true;
    indexing_features_EXT.runtimeDescriptorArray                             = true;
    
    VkDeviceCreateInfo device_ci = {};
    device_ci.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    device_ci.pNext                   = &indexing_features_EXT;
    device_ci.flags                   = 0;
    device_ci.queueCreateInfoCount    = 1;
    device_ci.pQueueCreateInfos       = &queue_ci;
    device_ci.enabledLayerCount       = 0;
    device_ci.ppEnabledLayerNames     = NULL;
    device_ci.enabledExtensionCount   = device_extension_count;
    device_ci.ppEnabledExtensionNames = device_extensions;
    device_ci.pEnabledFeatures        = &features;
    
    result = vkCreateDevice(vk.gpu, &device_ci, NULL, &vk.device);
    ODS("Device creation: %s\n", RevEnum(data.result_enum, result));
}


void SwapchainCreate()
{
    VkResult result;
    
    VkSwapchainCreateInfoKHR swapchain_ci = {};
    swapchain_ci.sType                 = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapchain_ci.pNext                 = NULL;
    swapchain_ci.flags                 = 0;
    swapchain_ci.surface               = vk.surface;
    swapchain_ci.minImageCount         = data.image_count;
    swapchain_ci.imageFormat           = vk.format;
    swapchain_ci.imageColorSpace       = vk.colorspace;
    swapchain_ci.imageExtent           = vk.extent_client_area;
    swapchain_ci.imageArrayLayers      = 1;
    swapchain_ci.imageUsage            = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT|VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
    swapchain_ci.imageSharingMode      = VK_SHARING_MODE_EXCLUSIVE;
    swapchain_ci.queueFamilyIndexCount = 0;
    swapchain_ci.pQueueFamilyIndices   = NULL;
    swapchain_ci.preTransform          = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    swapchain_ci.compositeAlpha        = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapchain_ci.presentMode           = vk.present_mode;
    swapchain_ci.clipped               = VK_TRUE;
    swapchain_ci.oldSwapchain          = NULL;
    
    result = vkCreateSwapchainKHR(vk.device, &swapchain_ci, NULL, &vk.swapchain);
    ODS("Swapchain result): %s\n", RevEnum(data.result_enum, result));
}
void GetSwapchainImages()
{
    VkResult result;
    
    u32 swapchain_imagecount = 0;
    result = vkGetSwapchainImagesKHR(vk.device, vk.swapchain, &swapchain_imagecount, NULL);
    ODS("Swapchain images(count): %s\n", RevEnum(data.result_enum, result));
    vk.swapchain_images = (VkImage *)malloc(sizeof(VkImage) * swapchain_imagecount);
    result = vkGetSwapchainImagesKHR(vk.device, vk.swapchain, &swapchain_imagecount, vk.swapchain_images);
    ODS("Swapchain images(fill):  %s\n", RevEnum(data.result_enum, result));
}

void CreateSwapchainImageViews()
{
    VkResult result;
    
    VkImageViewCreateInfo imageview_ci = {};
    imageview_ci.sType            = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    imageview_ci.pNext            = NULL;
    imageview_ci.flags            = 0;
    imageview_ci.viewType         = VK_IMAGE_VIEW_TYPE_2D;
    imageview_ci.format           = vk.format;
    imageview_ci.components       = vk.components;
    imageview_ci.subresourceRange = vk.color_sr;
    
    vk.swapchain_imageviews = (VkImageView *)malloc(sizeof(VkImageView) * data.image_count);
    for(u32 i = 0; i < data.image_count; i++)
    {
        imageview_ci.image = vk.swapchain_images[i];
        result = vkCreateImageView(vk.device, &imageview_ci, NULL, &vk.swapchain_imageviews[i]);
        ODS("Swapchain imageview result: %s\n", RevEnum(data.result_enum, result));
    }
}

void CreateCommandPool(VkCommandPool *command_pool)
{
    VkResult result;
    
    VkCommandPoolCreateInfo commandpool_ci = {};
    commandpool_ci.sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    commandpool_ci.pNext            = NULL;
    commandpool_ci.flags            = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    commandpool_ci.queueFamilyIndex = vk.queue_family_index;
    
    result = vkCreateCommandPool(vk.device, &commandpool_ci, NULL, &(*command_pool));
    ODS("Command pool result: %s\n", RevEnum(data.result_enum, result));
}

void AllocateCommandBuffer(VkCommandPool command_pool, VkCommandBuffer *command_buffer)
{
    VkResult result;
    
    VkCommandBufferAllocateInfo cb_ai = {};
    cb_ai.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    cb_ai.pNext              = NULL;
    cb_ai.commandPool        = command_pool;
    cb_ai.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cb_ai.commandBufferCount = 1;
    
    result = vkAllocateCommandBuffers(vk.device, &cb_ai, &(*command_buffer));
    ODS("Command buffer allocation: %s\n", RevEnum(data.result_enum, result));
}

VkBuffer CreateBuffer(u32 size, u32 usage, u32 required_memprops,
                      VkDevice device, VkPhysicalDeviceMemoryProperties gpu_memprops, VkDeviceMemory *memory)
{
    // Possible sub-functional breakdown:
    // ---
    VkBufferCreateInfo buffer_ci = {};
    buffer_ci.sType                 = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    buffer_ci.pNext                 = NULL;
    buffer_ci.flags                 = 0;
    buffer_ci.size                  = size;
    buffer_ci.usage                 = usage;
    buffer_ci.sharingMode           = VK_SHARING_MODE_EXCLUSIVE;
    
    VkBuffer buffer;
    vkCreateBuffer(device, &buffer_ci, NULL, &buffer);
    // ---
    
    // ---
    VkMemoryRequirements mem_reqs;
    vkGetBufferMemoryRequirements(device, buffer, &mem_reqs);
    
    VkMemoryAllocateInfo mem_ai = {};
    mem_ai.sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    mem_ai.pNext           = NULL;
    mem_ai.allocationSize  = mem_reqs.size;
    mem_ai.memoryTypeIndex = FindMemoryIndex(mem_reqs.memoryTypeBits,
                                             required_memprops,
                                             gpu_memprops);
    
    vkAllocateMemory(device, &mem_ai, NULL, memory);
    // ---
    
    vkBindBufferMemory(device, buffer, *memory, 0);
    
    return buffer;
}

void CheckCheckpoints()
{
    u32 prop_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties2(vk.gpu, &prop_count, NULL);
    ODS("Queue Fam2 prop count: %d\n", prop_count);
    
    VkQueueFamilyCheckpointPropertiesNV *check_props = (VkQueueFamilyCheckpointPropertiesNV *)calloc(prop_count, sizeof(VkQueueFamilyCheckpointPropertiesNV));
    VkQueueFamilyProperties2 *fam_props2 = (VkQueueFamilyProperties2 *)calloc(prop_count, sizeof(VkQueueFamilyProperties2));
    VkQueueFamilyProperties  *fam_props  = (VkQueueFamilyProperties *)calloc(prop_count, sizeof(VkQueueFamilyProperties));
    
    for(u32 i = 0; i < prop_count; i++)
    {
        fam_props[i] = {};
    }
    
    for(u32 i = 0; i < prop_count; i++)
    {
        fam_props2[i].sType                 = VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2;
        fam_props2[i].pNext                 = &check_props[i];
        fam_props2[i].queueFamilyProperties = fam_props[i];
    }
    vkGetPhysicalDeviceQueueFamilyProperties2(vk.gpu, &prop_count, fam_props2);
    
    ODS("Checkpoint stages: \n");
    for(u32 i = 0; i < prop_count; i++)
    {
        ODS(" - %s\n", RevEnum(data.pipeflags_enum, check_props[i].checkpointExecutionStageMask));
    }
}

// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////         VULKAN FUNCTION ABSTRACTION ------ ------
// //////////////////////////////////////////////////////////////////////////////



// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                        PIPELINE MANAGEMENT ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

VkShaderModule RetrieveShaderModule(char *filepath, VkDevice GPUinterface)
{
    u32 shaderCodeSize;
    int maxShaderSize = 10000;
    char *shaderCode = (char *)malloc(sizeof(char) * maxShaderSize);
    
    HANDLE fileHandle = CreateFile(filepath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
    if(fileHandle == INVALID_HANDLE_VALUE)
    {
        ODS("Couldn't load shader file %s\n", filepath);
        exit(1);
    }
    ReadFile((HANDLE)fileHandle, shaderCode, maxShaderSize, (LPDWORD)&shaderCodeSize, 0);
    CloseHandle(fileHandle);
    
    VkShaderModuleCreateInfo shaderModuleCreateInfo = {};
    shaderModuleCreateInfo.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    shaderModuleCreateInfo.pNext    = NULL;
    shaderModuleCreateInfo.flags    = 0;
    shaderModuleCreateInfo.codeSize = shaderCodeSize;
    shaderModuleCreateInfo.pCode    = (u32 *)shaderCode;
    
    VkShaderModule shaderModule = {};
    VkResult result = vkCreateShaderModule(GPUinterface, &shaderModuleCreateInfo, NULL, &shaderModule);
    ODS("Here's yo shader module!\n");
    
    return shaderModule;
}

void CreateViewport()
{
    vk.viewport.x        = 0;
    vk.viewport.y        = 0;
    vk.viewport.width    = app.window_width;
    vk.viewport.height   = app.window_height;
    vk.viewport.minDepth = 0.0;
    vk.viewport.maxDepth = 1.0;
}

void CreateScissor()
{
    vk.scissor.offset.x = 0;
    vk.scissor.offset.y = 0;
    vk.scissor.extent.width  = app.window_width;
    vk.scissor.extent.height = app.window_height;
}



// --- --- --- These are special. --- --- ---
void CreateRenderpass(renderstate *rs, bool keep_contents, bool last_renderpass)
{
    VkAttachmentDescription att_desc = {};
    att_desc.flags           = 0;
    att_desc.format          = vk.format;
    att_desc.samples         = VK_SAMPLE_COUNT_1_BIT;
    if(keep_contents)
        att_desc.loadOp      = VK_ATTACHMENT_LOAD_OP_LOAD;
    else
        att_desc.loadOp      = VK_ATTACHMENT_LOAD_OP_CLEAR;
    att_desc.storeOp         = VK_ATTACHMENT_STORE_OP_STORE;
    att_desc.stencilLoadOp   = VK_ATTACHMENT_LOAD_OP_CLEAR;
    att_desc.stencilStoreOp  = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    att_desc.initialLayout   = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    if(last_renderpass)
        att_desc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    else
        att_desc.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    
    VkAttachmentReference color_attachment = {};
    color_attachment.attachment = 0;
    color_attachment.layout     = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    
    VkSubpassDescription subpass = {};
    subpass.flags                   = 0;
    subpass.pipelineBindPoint       = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.inputAttachmentCount    = 0;
    subpass.pInputAttachments       = NULL;
    subpass.colorAttachmentCount    = 1;
    subpass.pColorAttachments       = &color_attachment;
    subpass.pResolveAttachments     = NULL;
    subpass.pDepthStencilAttachment = NULL;
    subpass.preserveAttachmentCount = 0;
    subpass.pPreserveAttachments    = NULL;
    
    VkRenderPassCreateInfo renderpass_ci = {};
    renderpass_ci.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderpass_ci.pNext           = NULL;
    renderpass_ci.flags           = 0;
    renderpass_ci.attachmentCount = 1;
    renderpass_ci.pAttachments    = &att_desc;
    renderpass_ci.subpassCount    = 1;
    renderpass_ci.pSubpasses      = &subpass;
    renderpass_ci.dependencyCount = 0;
    renderpass_ci.pDependencies   = NULL;
    
    vkCreateRenderPass(vk.device, &renderpass_ci, NULL, &rs->renderpass);
}


VkPipelineShaderStageCreateInfo *CreateShaderStages(render_init *ri)
{
    VkPipelineShaderStageCreateInfo *shader_stages = (VkPipelineShaderStageCreateInfo *)malloc(sizeof(VkPipelineShaderStageCreateInfo) * 2);
    
    VkShaderModule vertex_module   = RetrieveShaderModule(ri->vert, vk.device);
    VkShaderModule fragment_module = RetrieveShaderModule(ri->frag, vk.device);
    
    VkPipelineShaderStageCreateInfo vertex_shader = {};
    vertex_shader.sType               = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertex_shader.pNext               = NULL;
    vertex_shader.flags               = 0;
    vertex_shader.stage               = VK_SHADER_STAGE_VERTEX_BIT;
    vertex_shader.module              = vertex_module;
    vertex_shader.pName               = "main";
    vertex_shader.pSpecializationInfo = 0;
    
    VkPipelineShaderStageCreateInfo fragment_shader = {};
    fragment_shader.sType               = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragment_shader.pNext               = NULL;
    fragment_shader.flags               = 0;
    fragment_shader.stage               = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragment_shader.module              = fragment_module;
    fragment_shader.pName               = "main";
    fragment_shader.pSpecializationInfo = 0;
    
    shader_stages[0] = vertex_shader;
    shader_stages[1] = fragment_shader;
    
    return shader_stages;
}

VkPipelineVertexInputStateCreateInfo CreateVertexState_uv()
{
    VkVertexInputBindingDescription bind_desc = {};
    bind_desc.binding   = data.vertex_binding;
    bind_desc.stride    = sizeof(r32) * 6;
    bind_desc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    
    VkVertexInputAttributeDescription coord_desc = {};
    coord_desc.location = 0;
    coord_desc.binding  = data.vertex_binding;
    coord_desc.format   = VK_FORMAT_R32G32B32A32_SFLOAT;
    coord_desc.offset   = 0;
    
    VkVertexInputAttributeDescription uv_desc = {};
    uv_desc.location = 1;
    uv_desc.binding  = data.vertex_binding;
    uv_desc.format   = VK_FORMAT_R32G32_SFLOAT;
    uv_desc.offset   = sizeof(r32) * 4;
    
    
    VkVertexInputAttributeDescription attr_descs[] = { coord_desc, uv_desc };
    
    VkPipelineVertexInputStateCreateInfo vertex_state = {};
    vertex_state.sType                           = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertex_state.pNext                           = NULL;
    vertex_state.flags                           = 0;
    vertex_state.vertexBindingDescriptionCount   = 1;
    vertex_state.pVertexBindingDescriptions      = &bind_desc;
    vertex_state.vertexAttributeDescriptionCount = 2;
    vertex_state.pVertexAttributeDescriptions    = attr_descs;
    
    return vertex_state;
}

VkPipelineInputAssemblyStateCreateInfo CreateAssemblyState()
{
    VkPipelineInputAssemblyStateCreateInfo assembly_state = {};
    assembly_state.sType                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    assembly_state.pNext                  = NULL;
    assembly_state.flags                  = 0;
    assembly_state.topology               = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    assembly_state.primitiveRestartEnable = VK_FALSE;
    
    return assembly_state;
}

VkPipelineViewportStateCreateInfo CreateViewportState()
{
    VkPipelineViewportStateCreateInfo viewport_state = {};
    viewport_state.sType         = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewport_state.pNext         = NULL;
    viewport_state.flags         = 0;
    viewport_state.viewportCount = 1;
    viewport_state.pViewports    = &vk.viewport;
    viewport_state.scissorCount  = 1;
    viewport_state.pScissors     = &vk.scissor;
    
    return viewport_state;
}

VkPipelineRasterizationStateCreateInfo CreateRasterizationState()
{
    VkPipelineRasterizationStateCreateInfo raster_state = {};
    raster_state.sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    raster_state.pNext                   = NULL;
    raster_state.flags                   = 0;
    raster_state.polygonMode             = VK_POLYGON_MODE_FILL;
    raster_state.cullMode                = VK_CULL_MODE_BACK_BIT;
    raster_state.frontFace               = VK_FRONT_FACE_CLOCKWISE;
    raster_state.lineWidth               = 1.0f;
    
    return raster_state;
}

VkPipelineMultisampleStateCreateInfo CreateMultisampleState()
{
    VkPipelineMultisampleStateCreateInfo multisample_state = {};
    multisample_state.sType                 = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisample_state.pNext                 = NULL;
    multisample_state.flags                 = 0;
    multisample_state.rasterizationSamples  = VK_SAMPLE_COUNT_1_BIT;
    
    return multisample_state;
}

VkPipelineColorBlendStateCreateInfo CreateColorblendState()
{
    VkPipelineColorBlendAttachmentState colorblend_attachment = {};
    colorblend_attachment.blendEnable         = VK_TRUE;
    colorblend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    colorblend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    colorblend_attachment.colorBlendOp        = VK_BLEND_OP_ADD;
    colorblend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    colorblend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    colorblend_attachment.alphaBlendOp        = VK_BLEND_OP_ADD;
    colorblend_attachment.colorWriteMask      = 0xF;
    
    VkPipelineColorBlendStateCreateInfo colorblend_state = {};
    colorblend_state.sType           = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorblend_state.pNext           = NULL;
    colorblend_state.flags           = 0;
    colorblend_state.attachmentCount = 1;
    colorblend_state.pAttachments    = &colorblend_attachment;
    
    return colorblend_state;
}


#define MAX_IMAGES 4096

void CreatePipeline_viewer(render_init *ri)
{
    //// --- --- --- States --- --- ---
    
    // ---
    VkShaderModule vertex_module   = RetrieveShaderModule(ri->vert, vk.device);
    VkShaderModule fragment_module = RetrieveShaderModule(ri->frag, vk.device);
    
    VkPipelineShaderStageCreateInfo vertex_shader = {};
    vertex_shader.sType               = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertex_shader.pNext               = NULL;
    vertex_shader.flags               = 0;
    vertex_shader.stage               = VK_SHADER_STAGE_VERTEX_BIT;
    vertex_shader.module              = vertex_module;
    vertex_shader.pName               = "main";
    vertex_shader.pSpecializationInfo = 0;
    
    VkPipelineShaderStageCreateInfo fragment_shader = {};
    fragment_shader.sType               = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragment_shader.pNext               = NULL;
    fragment_shader.flags               = 0;
    fragment_shader.stage               = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragment_shader.module              = fragment_module;
    fragment_shader.pName               = "main";
    fragment_shader.pSpecializationInfo = 0;
    
    VkPipelineShaderStageCreateInfo shader_stages[] = { vertex_shader, fragment_shader };
    // ---
    
    
    // ---
    VkVertexInputBindingDescription bind_desc = {};
    bind_desc.binding   = data.vertex_binding;
    bind_desc.stride    = sizeof(r32) * 6;
    bind_desc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    
    VkVertexInputAttributeDescription coord_desc = {};
    coord_desc.location = 0;
    coord_desc.binding  = data.vertex_binding;
    coord_desc.format   = VK_FORMAT_R32G32B32A32_SFLOAT;
    coord_desc.offset   = 0;
    
    VkVertexInputAttributeDescription uv_desc = {};
    uv_desc.location = 1;
    uv_desc.binding  = data.vertex_binding;
    uv_desc.format   = VK_FORMAT_R32G32_SFLOAT;
    uv_desc.offset   = sizeof(r32) * 4;
    
    
    VkVertexInputAttributeDescription attr_descs[] = { coord_desc, uv_desc };
    
    VkPipelineVertexInputStateCreateInfo vertex_state = {};
    vertex_state.sType                           = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertex_state.pNext                           = NULL;
    vertex_state.flags                           = 0;
    vertex_state.vertexBindingDescriptionCount   = 1;
    vertex_state.pVertexBindingDescriptions      = &bind_desc;
    vertex_state.vertexAttributeDescriptionCount = 2;
    vertex_state.pVertexAttributeDescriptions    = attr_descs;
    // ---
    
    
    // ---
    VkPipelineInputAssemblyStateCreateInfo assembly_state = {};
    assembly_state.sType                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    assembly_state.pNext                  = NULL;
    assembly_state.flags                  = 0;
    assembly_state.topology               = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    assembly_state.primitiveRestartEnable = VK_FALSE;
    // ---
    
    
    // ---
    VkPipelineViewportStateCreateInfo viewport_state = {};
    viewport_state.sType         = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewport_state.pNext         = NULL;
    viewport_state.flags         = 0;
    viewport_state.viewportCount = 1;
    viewport_state.pViewports    = &vk.viewport;
    viewport_state.scissorCount  = 1;
    viewport_state.pScissors     = &vk.scissor;
    // ---
    
    
    // ---
    VkPipelineRasterizationStateCreateInfo raster_state = {};
    raster_state.sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    raster_state.pNext                   = NULL;
    raster_state.flags                   = 0;
    raster_state.polygonMode             = VK_POLYGON_MODE_FILL;
    raster_state.cullMode                = VK_CULL_MODE_BACK_BIT;
    raster_state.frontFace               = VK_FRONT_FACE_CLOCKWISE;
    raster_state.lineWidth               = 1.0f;
    // ---
    
    
    // ---
    VkPipelineMultisampleStateCreateInfo multisample_state = {};
    multisample_state.sType                 = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisample_state.pNext                 = NULL;
    multisample_state.flags                 = 0;
    multisample_state.rasterizationSamples  = VK_SAMPLE_COUNT_1_BIT;
    // ---
    
    
    // ---
    VkPipelineColorBlendAttachmentState colorblend_attachment = {};
    colorblend_attachment.blendEnable         = VK_TRUE;
    colorblend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    colorblend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    colorblend_attachment.colorBlendOp        = VK_BLEND_OP_ADD;
    colorblend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    colorblend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    colorblend_attachment.alphaBlendOp        = VK_BLEND_OP_ADD;
    colorblend_attachment.colorWriteMask      = 0xF;
    
    VkPipelineColorBlendStateCreateInfo colorblend_state = {};
    colorblend_state.sType           = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorblend_state.pNext           = NULL;
    colorblend_state.flags           = 0;
    colorblend_state.attachmentCount = 1;
    colorblend_state.pAttachments    = &colorblend_attachment;
    // ---
    //// --- --- ---
    
    
    //// --- --- --- Descriptor stuff --- --- ---
    // --- pools
    VkDescriptorPoolSize ortho_poolsize = {};
    ortho_poolsize.type            = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    ortho_poolsize.descriptorCount = 1;
    
    VkDescriptorPoolSize view_poolsize = {};
    view_poolsize.type            = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    view_poolsize.descriptorCount = 1;
    
    VkDescriptorPoolSize samplerpool_size = {};
    samplerpool_size.type            = VK_DESCRIPTOR_TYPE_SAMPLER;
    samplerpool_size.descriptorCount = 1;
    
    VkDescriptorPoolSize imagepool_size = {};
    imagepool_size.type            = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
    imagepool_size.descriptorCount = MAX_IMAGES;
    
    VkDescriptorPoolSize dpool_sizes[] = { ortho_poolsize, view_poolsize, samplerpool_size, imagepool_size };
    
    VkDescriptorPoolCreateInfo dpool_ci = {};
    dpool_ci.sType         = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    dpool_ci.pNext         = NULL;
    dpool_ci.flags         = 0;
    dpool_ci.maxSets       = ri->rs->descset_count;
    dpool_ci.poolSizeCount = sizeof(dpool_sizes) / sizeof(dpool_sizes[0]);
    dpool_ci.pPoolSizes    = dpool_sizes;
    
    VkDescriptorPool dpool;
    vkCreateDescriptorPool(vk.device, &dpool_ci, NULL, &dpool);
    
    
    // --- layout
    
    VkDescriptorSetLayoutBinding ortho_binding = {};
    ortho_binding.binding            = data.matrix_binding;
    ortho_binding.descriptorType     = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    ortho_binding.descriptorCount    = 1;
    ortho_binding.stageFlags         = VK_SHADER_STAGE_VERTEX_BIT;
    ortho_binding.pImmutableSamplers = NULL;
    
    VkDescriptorSetLayoutBinding view_binding = {};
    view_binding.binding            = 1;
    view_binding.descriptorType     = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    view_binding.descriptorCount    = 1;
    view_binding.stageFlags         = VK_SHADER_STAGE_VERTEX_BIT;
    view_binding.pImmutableSamplers = NULL;
    
    VkDescriptorSetLayoutBinding sampler_binding = {};
    sampler_binding.binding            = 2;
    sampler_binding.descriptorType     = VK_DESCRIPTOR_TYPE_SAMPLER;
    sampler_binding.descriptorCount    = 1;
    sampler_binding.stageFlags         = VK_SHADER_STAGE_FRAGMENT_BIT;
    sampler_binding.pImmutableSamplers = NULL;
    
    VkDescriptorSetLayoutBinding image_binding = {};
    image_binding.binding            = 3;
    image_binding.descriptorType     = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
    image_binding.descriptorCount    = MAX_IMAGES;
    image_binding.stageFlags         = VK_SHADER_STAGE_FRAGMENT_BIT;
    image_binding.pImmutableSamplers = NULL;
    
    VkDescriptorSetLayoutBinding dsl_bindings[] = { ortho_binding, view_binding, sampler_binding, image_binding };
    
    
    VkDescriptorBindingFlagsEXT binding_flags[] = { 0, 0, 0, VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT_EXT };
    
    VkDescriptorSetLayoutBindingFlagsCreateInfoEXT binding_flags_ci_EXT = {};
    binding_flags_ci_EXT.sType         = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO_EXT;
    binding_flags_ci_EXT.pNext         = NULL;
    binding_flags_ci_EXT.bindingCount  = sizeof(binding_flags) / sizeof(binding_flags[0]);
    binding_flags_ci_EXT.pBindingFlags = binding_flags;
    
    ODS("Descriptor ext binding count: %d\n", binding_flags_ci_EXT.bindingCount);
    
    VkDescriptorSetLayoutCreateInfo dsl_ci = {};
    dsl_ci.sType        = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    dsl_ci.pNext        = &binding_flags_ci_EXT;
    dsl_ci.flags        = 0;
    dsl_ci.bindingCount = sizeof(dsl_bindings) / sizeof(dsl_bindings[0]);
    dsl_ci.pBindings    = dsl_bindings;
    vkCreateDescriptorSetLayout(vk.device, &dsl_ci, NULL, &ri->rs->ds_layout);
    
    
    u32 variable_count = MAX_IMAGES;
    
    VkDescriptorSetVariableDescriptorCountAllocateInfoEXT variable_desc_alloc = {};
    variable_desc_alloc.sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_ALLOCATE_INFO_EXT;
    variable_desc_alloc.pNext              = NULL;
    variable_desc_alloc.descriptorSetCount = 1;
    variable_desc_alloc.pDescriptorCounts  = &variable_count;
    
    VkDescriptorSetAllocateInfo dset_ai = {};
    dset_ai.sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    dset_ai.pNext              = &variable_desc_alloc;
    dset_ai.descriptorPool     = dpool;
    dset_ai.descriptorSetCount = ri->rs->descset_count;
    dset_ai.pSetLayouts        = &ri->rs->ds_layout;
    vkAllocateDescriptorSets(vk.device, &dset_ai, &ri->rs->dset);
    // ---
    
    
    // --- Pipeline layout
    VkPipelineLayoutCreateInfo pipeline_lci = {};
    pipeline_lci.sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipeline_lci.pNext                  = NULL;
    pipeline_lci.flags                  = 0;
    pipeline_lci.setLayoutCount         = 1;
    pipeline_lci.pSetLayouts            = &ri->rs->ds_layout;
    
    vkCreatePipelineLayout(vk.device, &pipeline_lci, NULL, &ri->rs->pipeline_layout);
    // ---
    
    
    // --- Pipeline
    u32 stage_count = 2;
    
    VkGraphicsPipelineCreateInfo pipeline_ci = {};
    pipeline_ci.sType               = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipeline_ci.pNext               = NULL;
    pipeline_ci.flags               = 0;
    pipeline_ci.stageCount          = stage_count;
    pipeline_ci.pStages             = shader_stages;
    pipeline_ci.pVertexInputState   = &vertex_state;
    pipeline_ci.pInputAssemblyState = &assembly_state;
    pipeline_ci.pTessellationState  = NULL;
    pipeline_ci.pViewportState      = &viewport_state;
    pipeline_ci.pRasterizationState = &raster_state;
    pipeline_ci.pMultisampleState   = &multisample_state;
    pipeline_ci.pDepthStencilState  = NULL;
    pipeline_ci.pColorBlendState    = &colorblend_state;
    pipeline_ci.pDynamicState       = NULL;
    pipeline_ci.layout              = ri->rs->pipeline_layout;
    pipeline_ci.renderPass          = ri->rs->renderpass;
    pipeline_ci.subpass             = 0;
    pipeline_ci.basePipelineHandle  = NULL;
    pipeline_ci.basePipelineIndex   = NULL;
    
    vkCreateGraphicsPipelines(vk.device, NULL, 1, &pipeline_ci, NULL, &ri->rs->pipeline);
    // ---
}
void CreatePipeline_overlay(render_init *ri)
{
    // ---
    VkShaderModule vertex_module   = RetrieveShaderModule(ri->vert, vk.device);
    VkShaderModule fragment_module = RetrieveShaderModule(ri->frag, vk.device);
    
    VkPipelineShaderStageCreateInfo vertex_shader = {};
    vertex_shader.sType               = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertex_shader.pNext               = NULL;
    vertex_shader.flags               = 0;
    vertex_shader.stage               = VK_SHADER_STAGE_VERTEX_BIT;
    vertex_shader.module              = vertex_module;
    vertex_shader.pName               = "main";
    vertex_shader.pSpecializationInfo = 0;
    
    VkPipelineShaderStageCreateInfo fragment_shader = {};
    fragment_shader.sType               = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragment_shader.pNext               = NULL;
    fragment_shader.flags               = 0;
    fragment_shader.stage               = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragment_shader.module              = fragment_module;
    fragment_shader.pName               = "main";
    fragment_shader.pSpecializationInfo = 0;
    
    VkPipelineShaderStageCreateInfo shader_stages[] = { vertex_shader, fragment_shader };
    // ---
    
    
    // ---
    VkVertexInputBindingDescription bind_desc = {};
    bind_desc.binding   = data.vertex_binding;
    bind_desc.stride    = sizeof(r32) * 6;
    bind_desc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    
    VkVertexInputAttributeDescription coord_desc = {};
    coord_desc.location = 0;
    coord_desc.binding  = data.vertex_binding;
    coord_desc.format   = VK_FORMAT_R32G32B32A32_SFLOAT;
    coord_desc.offset   = 0;
    
    VkVertexInputAttributeDescription uv_desc = {};
    uv_desc.location = 1;
    uv_desc.binding  = data.vertex_binding;
    uv_desc.format   = VK_FORMAT_R32G32_SFLOAT;
    uv_desc.offset   = sizeof(r32) * 4;
    
    
    VkVertexInputAttributeDescription attr_descs[] = { coord_desc, uv_desc };
    
    VkPipelineVertexInputStateCreateInfo vertex_state = {};
    vertex_state.sType                           = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertex_state.pNext                           = NULL;
    vertex_state.flags                           = 0;
    vertex_state.vertexBindingDescriptionCount   = 1;
    vertex_state.pVertexBindingDescriptions      = &bind_desc;
    vertex_state.vertexAttributeDescriptionCount = 2;
    vertex_state.pVertexAttributeDescriptions    = attr_descs;
    // ---
    
    
    // ---
    VkPipelineInputAssemblyStateCreateInfo assembly_state = {};
    assembly_state.sType                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    assembly_state.pNext                  = NULL;
    assembly_state.flags                  = 0;
    assembly_state.topology               = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    // ---
    
    
    // ---
    VkPipelineViewportStateCreateInfo viewport_state = {};
    viewport_state.sType         = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewport_state.pNext         = NULL;
    viewport_state.flags         = 0;
    viewport_state.viewportCount = 1;
    viewport_state.pViewports    = &vk.viewport;
    viewport_state.scissorCount  = 1;
    viewport_state.pScissors     = &vk.scissor;
    // ---
    
    
    // ---
    VkPipelineRasterizationStateCreateInfo raster_state = {};
    raster_state.sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    raster_state.pNext                   = NULL;
    raster_state.flags                   = 0;
    raster_state.polygonMode             = VK_POLYGON_MODE_FILL;
    raster_state.cullMode                = VK_CULL_MODE_BACK_BIT;
    raster_state.frontFace               = VK_FRONT_FACE_CLOCKWISE;
    raster_state.lineWidth               = 1.0f;
    // ---
    
    
    // ---
    VkPipelineMultisampleStateCreateInfo multisample_state = {};
    multisample_state.sType                 = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisample_state.pNext                 = NULL;
    multisample_state.flags                 = 0;
    multisample_state.rasterizationSamples  = VK_SAMPLE_COUNT_1_BIT;
    // ---
    
    
    // ---
    VkPipelineColorBlendAttachmentState colorblend_attachment = {};
    colorblend_attachment.blendEnable         = VK_TRUE;
    colorblend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    colorblend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    colorblend_attachment.colorBlendOp        = VK_BLEND_OP_ADD;
    colorblend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    colorblend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    colorblend_attachment.alphaBlendOp        = VK_BLEND_OP_ADD;
    colorblend_attachment.colorWriteMask      = 0xF;
    
    VkPipelineColorBlendStateCreateInfo colorblend_state = {};
    colorblend_state.sType           = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorblend_state.pNext           = NULL;
    colorblend_state.flags           = 0;
    colorblend_state.attachmentCount = 1;
    colorblend_state.pAttachments    = &colorblend_attachment;
    // ---
    
    
    
    VkDescriptorSetLayoutBinding matrix_layout_binding = {};
    matrix_layout_binding.binding            = 0;
    matrix_layout_binding.descriptorType     = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    matrix_layout_binding.descriptorCount    = 1;
    matrix_layout_binding.stageFlags         = VK_SHADER_STAGE_VERTEX_BIT;
    matrix_layout_binding.pImmutableSamplers = NULL;
    
    VkDescriptorSetLayoutBinding sampler_layout_binding = {};
    sampler_layout_binding.binding            = 1;
    sampler_layout_binding.descriptorType     = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    sampler_layout_binding.descriptorCount    = 1;
    sampler_layout_binding.stageFlags         = VK_SHADER_STAGE_FRAGMENT_BIT;
    sampler_layout_binding.pImmutableSamplers = NULL;
    
    VkDescriptorSetLayoutBinding dsl_bindings[] = { matrix_layout_binding, sampler_layout_binding };
    
    
    VkDescriptorSetLayoutCreateInfo dsl_ci = {};
    dsl_ci.sType        = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    dsl_ci.pNext        = NULL;
    dsl_ci.flags        = 0;
    dsl_ci.bindingCount = 2;
    dsl_ci.pBindings    = dsl_bindings;
    vkCreateDescriptorSetLayout(vk.device, &dsl_ci, NULL, &ri->rs->ds_layout);
    
    
    VkDescriptorPoolSize matrixpool_size = {};
    matrixpool_size.type            = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    matrixpool_size.descriptorCount = ri->rs->descset_count;
    
    VkDescriptorPoolSize samplerpool_size = {};
    samplerpool_size.type            = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    samplerpool_size.descriptorCount = ri->rs->descset_count;
    
    VkDescriptorPoolSize dpool_sizes[] = { matrixpool_size, samplerpool_size };
    
    VkDescriptorPoolCreateInfo dpool_ci = {};
    dpool_ci.sType         = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    dpool_ci.pNext         = NULL;
    dpool_ci.flags         = 0;
    dpool_ci.maxSets       = ri->rs->descset_count;
    dpool_ci.poolSizeCount = 2;
    dpool_ci.pPoolSizes    = dpool_sizes;
    
    VkDescriptorPool dpool;
    vkCreateDescriptorPool(vk.device, &dpool_ci, NULL, &dpool);
    
    
    VkDescriptorSetAllocateInfo dset_ai = {};
    dset_ai.sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    dset_ai.pNext              = NULL;
    dset_ai.descriptorPool     = dpool;
    dset_ai.descriptorSetCount = ri->rs->descset_count;
    dset_ai.pSetLayouts        = &ri->rs->ds_layout;
    vkAllocateDescriptorSets(vk.device, &dset_ai, &ri->rs->dset);
    // ---
    
    
    // ---
    VkPipelineLayoutCreateInfo pipeline_lci = {};
    pipeline_lci.sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipeline_lci.pNext                  = NULL;
    pipeline_lci.flags                  = 0;
    pipeline_lci.setLayoutCount         = 1;
    pipeline_lci.pSetLayouts            = &ri->rs->ds_layout;
    
    vkCreatePipelineLayout(vk.device, &pipeline_lci, NULL, &ri->rs->pipeline_layout);
    // ---
    
    
    // ---
    u32 stage_count = 2;
    
    VkGraphicsPipelineCreateInfo pipeline_ci = {};
    pipeline_ci.sType               = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipeline_ci.pNext               = NULL;
    pipeline_ci.flags               = 0;
    pipeline_ci.stageCount          = stage_count;
    pipeline_ci.pStages             = shader_stages;
    pipeline_ci.pVertexInputState   = &vertex_state;
    pipeline_ci.pInputAssemblyState = &assembly_state;
    pipeline_ci.pTessellationState  = NULL;
    pipeline_ci.pViewportState      = &viewport_state;
    pipeline_ci.pRasterizationState = &raster_state;
    pipeline_ci.pMultisampleState   = &multisample_state;
    pipeline_ci.pDepthStencilState  = NULL;
    pipeline_ci.pColorBlendState    = &colorblend_state;
    pipeline_ci.pDynamicState       = NULL;
    pipeline_ci.layout              = ri->rs->pipeline_layout;
    pipeline_ci.renderPass          = ri->rs->renderpass;
    pipeline_ci.subpass             = 0;
    pipeline_ci.basePipelineHandle  = NULL;
    pipeline_ci.basePipelineIndex   = NULL;
    
    vkCreateGraphicsPipelines(vk.device, NULL, 1, &pipeline_ci, NULL, &ri->rs->pipeline);
    // ---
}

// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////                 PIPELINE MANAGEMENT ------ ------
// //////////////////////////////////////////////////////////////////////////////





void InitRenderstateMemory(renderstate *rs, u32 geometry_size, u32 indexes_size)
{
    rs->geometry = (memory_pool *)malloc(sizeof(memory_pool));
    MemoryAllocate(rs->geometry, geometry_size);
    
    rs->indexes = (memory_pool *)malloc(sizeof(memory_pool));
    MemoryAllocate(rs->indexes, indexes_size);
    
    rs->vertex_buffer = CreateBuffer(rs->geometry->size, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
                                     vk.device, vk.gpu_memprops, &rs->vertex_memory);
    
    rs->index_buffer = CreateBuffer(rs->indexes->size, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
                                    vk.device, vk.gpu_memprops, &rs->index_memory);
}


void CreateRenderstate_viewer(render_init *ri, bool keep_contents, bool last_renderpass)
{
    InitRenderstateMemory(ri->rs, 300 * KILOBYTE, 100 * KILOBYTE);  // this will supply a little bit over 4096 quads
    
    // --- Pipeline
    CreateRenderpass(ri->rs, keep_contents, last_renderpass);
    CreatePipeline_viewer(ri);
}
void CreateRenderstate_overlay(render_init *ri, font_init *ti, bool keep_contents, bool last_renderpass)
{
    // --- --- --- Text init --- --- ---
    ri->rs->fd = (font_data *)malloc(sizeof(font_data));
    ri->rs->fd->first_char = 32;
    ri->rs->fd->char_count = 96;
    
    Font_InitAndBake(ri->rs, ti->fontfile, ti->font_size, ti->color);
    // ---
    
    
    // --- --- --- Render init --- --- ---
    // --- Renderstate memory
    InitRenderstateMemory(ri->rs, MEGABYTE, 240 * KILOBYTE);
    
    // --- Pipeline
    CreateRenderpass(ri->rs, keep_contents, last_renderpass);
    CreatePipeline_overlay(ri);
}
// ------------------------------------------



VkFramebuffer *CreateFramebuffers(renderstate *rs, VkImageView *imageviews, u32 image_count)
{
    VkFramebufferCreateInfo framebuffer_ci = {};
    framebuffer_ci.sType           = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebuffer_ci.pNext           = NULL;
    framebuffer_ci.flags           = 0;
    framebuffer_ci.renderPass      = rs->renderpass;
    framebuffer_ci.attachmentCount = 1;
    framebuffer_ci.width           = app.window_width;
    framebuffer_ci.height          = app.window_height;
    framebuffer_ci.layers          = 1;
    
    VkFramebuffer *framebuffers = (VkFramebuffer *)malloc(sizeof(VkFramebuffer) * image_count);
    for(u32 i = 0; i < data.image_count; i++)
    {
        framebuffer_ci.pAttachments = &imageviews[i];
        vkCreateFramebuffer(vk.device, &framebuffer_ci, NULL, &framebuffers[i]);
    }
    return framebuffers;
}


void CreateSamplerImage(u32 width, u32 height, VkImage *image, VkDeviceMemory *memory)
{
    // ---
    VkExtent3D extent = {};
    extent.width  = width;
    extent.height = height;
    extent.depth  = 1;
    
    VkImageCreateInfo image_ci = {};
    image_ci.sType                 = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    image_ci.pNext                 = NULL;
    image_ci.flags                 = 0;
    image_ci.imageType             = VK_IMAGE_TYPE_2D;
    image_ci.format                = vk.format;
    image_ci.extent                = extent;
    image_ci.mipLevels             = 1;
    image_ci.arrayLayers           = 1;
    image_ci.samples               = VK_SAMPLE_COUNT_1_BIT;
    image_ci.tiling                = VK_IMAGE_TILING_OPTIMAL;
    image_ci.usage                 = VK_IMAGE_USAGE_SAMPLED_BIT|VK_IMAGE_USAGE_TRANSFER_DST_BIT;
    image_ci.sharingMode           = VK_SHARING_MODE_EXCLUSIVE;
    image_ci.queueFamilyIndexCount = 0;
    image_ci.pQueueFamilyIndices   = NULL;
    image_ci.initialLayout         = VK_IMAGE_LAYOUT_UNDEFINED;
    
    vkCreateImage(vk.device, &image_ci, NULL, image);
    // ---
    
    // ---
    VkMemoryRequirements memreqs;
    vkGetImageMemoryRequirements(vk.device, *image, &memreqs);
    
    VkMemoryAllocateInfo mem_ai = {};
    mem_ai.sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    mem_ai.pNext           = NULL;
    mem_ai.allocationSize  = memreqs.size;
    mem_ai.memoryTypeIndex = FindMemoryIndex(memreqs.memoryTypeBits,
                                             VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                                             vk.gpu_memprops);
    
    vkAllocateMemory(vk.device, &mem_ai, NULL, memory);
    
    vkBindImageMemory(vk.device, *image, *memory, 0);
    // ---
}

void CreateImage(VkImage *image, VkDeviceMemory *memory,
                 s32 width, s32 height,
                 VkImageTiling tiling, u32 usage,
                 VkImageLayout layout, VkMemoryPropertyFlags memory_properties)
{
    VkExtent3D extent = {};
    extent.width  = width;
    extent.height = height;
    extent.depth  = 1;
    
    // ---
    VkImageCreateInfo image_ci = {};
    image_ci.sType                 = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    image_ci.pNext                 = NULL;
    image_ci.flags                 = 0;
    image_ci.imageType             = VK_IMAGE_TYPE_2D;
    image_ci.format                = vk.format;
    image_ci.extent                = extent;
    image_ci.mipLevels             = 1;
    image_ci.arrayLayers           = 1;
    image_ci.samples               = VK_SAMPLE_COUNT_1_BIT;
    image_ci.tiling                = tiling;
    image_ci.usage                 = usage;
    image_ci.sharingMode           = VK_SHARING_MODE_EXCLUSIVE;
    image_ci.queueFamilyIndexCount = 0;
    image_ci.pQueueFamilyIndices   = NULL;
    image_ci.initialLayout         = layout;
    
    vkCreateImage(vk.device, &image_ci, NULL, image);
    // ---
    
    // ---
    VkMemoryRequirements memreqs;
    vkGetImageMemoryRequirements(vk.device, *image, &memreqs);
    
    VkMemoryAllocateInfo mem_ai = {};
    mem_ai.sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    mem_ai.pNext           = NULL;
    mem_ai.allocationSize  = memreqs.size;
    mem_ai.memoryTypeIndex = FindMemoryIndex(memreqs.memoryTypeBits,
                                             memory_properties,
                                             vk.gpu_memprops);
    
    VkResult result;
    result = vkAllocateMemory(vk.device, &mem_ai, NULL, memory);
    ODS("Memory allocation: %s\n", RevEnum(data.result_enum, result));
    
    vkBindImageMemory(vk.device, *image, *memory, 0);
    // ---
}

void CreateImageView(VkImage *image, VkImageView *imageview)
{
    VkComponentMapping components = {};
    components.r = VK_COMPONENT_SWIZZLE_B;
    components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    components.b = VK_COMPONENT_SWIZZLE_R;
    components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    
    VkImageViewCreateInfo imageview_ci = {};
    imageview_ci.sType            = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    imageview_ci.pNext            = NULL;
    imageview_ci.flags            = 0;
    imageview_ci.image            = *image;
    imageview_ci.viewType         = VK_IMAGE_VIEW_TYPE_2D;
    imageview_ci.format           = vk.format;
    imageview_ci.components       = components;
    imageview_ci.subresourceRange = vk.color_sr;
    
    vkCreateImageView(vk.device, &imageview_ci, NULL, imageview);
}

void CreateSampler(VkSampler *sampler)
{
    VkSamplerCreateInfo sampler_ci = {};
    sampler_ci.sType                   = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    sampler_ci.pNext                   = NULL;
    sampler_ci.flags                   = 0;
    sampler_ci.magFilter               = VK_FILTER_LINEAR;
    sampler_ci.minFilter               = VK_FILTER_LINEAR;
    sampler_ci.mipmapMode              = VK_SAMPLER_MIPMAP_MODE_NEAREST;
    sampler_ci.addressModeU            = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    sampler_ci.addressModeV            = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    sampler_ci.addressModeW            = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    sampler_ci.mipLodBias              = 0.0f;
    sampler_ci.anisotropyEnable        = VK_FALSE;
    sampler_ci.compareEnable           = VK_FALSE;
    sampler_ci.minLod                  = 1.0f;
    sampler_ci.maxLod                  = 1.0f;
    sampler_ci.borderColor             = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    sampler_ci.unnormalizedCoordinates = VK_FALSE;
    
    vkCreateSampler(vk.device, &sampler_ci, NULL, sampler);
}
void CreateSampler_tile(VkSampler *sampler)
{
    VkSamplerCreateInfo sampler_ci = {};
    sampler_ci.sType                   = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    sampler_ci.pNext                   = NULL;
    sampler_ci.flags                   = 0;
    sampler_ci.magFilter               = VK_FILTER_LINEAR;
    sampler_ci.minFilter               = VK_FILTER_LINEAR;
    sampler_ci.mipmapMode              = VK_SAMPLER_MIPMAP_MODE_NEAREST;
    sampler_ci.addressModeU            = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    sampler_ci.addressModeV            = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    sampler_ci.addressModeW            = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    sampler_ci.mipLodBias              = 0.0f;
    sampler_ci.anisotropyEnable        = VK_FALSE;
    sampler_ci.compareEnable           = VK_FALSE;
    sampler_ci.minLod                  = 1.0f;
    sampler_ci.maxLod                  = 1.0f;
    sampler_ci.borderColor             = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    sampler_ci.unnormalizedCoordinates = VK_FALSE;
    
    vkCreateSampler(vk.device, &sampler_ci, NULL, sampler);
}

// --- --- ---


VkSubmitInfo GenerateSubmitInfo(u32 wait_count,      VkSemaphore *wait_semaphores,
                                VkPipelineStageFlags *wait_mask,
                                u32 command_buffer_count, VkCommandBuffer *command_buffers,
                                u32 signal_count,    VkSemaphore *signal_semaphores)
{
    VkSubmitInfo result = {};
    result.sType                = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    result.pNext                = NULL;
    result.waitSemaphoreCount   = wait_count;
    result.pWaitSemaphores      = wait_semaphores;
    result.pWaitDstStageMask    = wait_mask;
    result.commandBufferCount   = command_buffer_count;
    result.pCommandBuffers      = command_buffers;
    result.signalSemaphoreCount = signal_count;
    result.pSignalSemaphores    = signal_semaphores;
    
    return result;
}

CRITICAL_SECTION crit_sec;

void TransitImageLayout(VkImageLayout old_layout, VkImageLayout new_layout, VkImage image,
                        VkQueue queue, VkCommandBuffer command_buffer, VkFence fence,
                        u32 wait_semaphore_count,   VkSemaphore *wait_semaphores,
                        u32 signal_semaphore_count, VkSemaphore *signal_semaphores)
{
    VkImageMemoryBarrier barrier = {};
    barrier.sType               = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.pNext               = NULL;
    barrier.srcAccessMask       = VK_ACCESS_HOST_READ_BIT;
    barrier.dstAccessMask       = VK_ACCESS_HOST_WRITE_BIT;
    barrier.oldLayout           = old_layout;
    barrier.newLayout           = new_layout;
    barrier.image               = image;
    barrier.subresourceRange    = vk.color_sr;
    
    VkPipelineStageFlags wait_stage_mask = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    VkSubmitInfo queue_si = GenerateSubmitInfo(wait_semaphore_count, wait_semaphores,
                                               &wait_stage_mask,
                                               1, &command_buffer,
                                               signal_semaphore_count, signal_semaphores);
    
    void *checkpoint_marker = calloc(1, sizeof(void *));
    
    EnterCriticalSection(&crit_sec);
    
    vkBeginCommandBuffer(command_buffer, &vk.cb_bi);
    vkCmdPipelineBarrier(command_buffer,
                         VK_PIPELINE_STAGE_HOST_BIT, VK_PIPELINE_STAGE_HOST_BIT,
                         0,
                         0, NULL,
                         0, NULL,
                         1, &barrier);
    vkEndCommandBuffer(command_buffer);
    vkQueueSubmit(queue, 1, &queue_si, fence);
    
    LeaveCriticalSection(&crit_sec);
    
    ODS("Waiting on transit fence\n");
    vkWaitForFences(vk.device, 1, &fence, VK_TRUE, UINT64_MAX);
    VkResult result = vkGetFenceStatus(vk.device, fence);
    ODS("Transition fence result: %s\n", RevEnum(data.result_enum, result));
    
    ODS("> %s -> %s\n", RevEnum(data.imagelayout_enum, old_layout), RevEnum(data.imagelayout_enum, new_layout));
    
    ODS("Resetting transit fence\n");
    vkResetFences(vk.device, 1, &fence);
}
void TransitImageLayout(VkImageLayout old_layout, VkImageLayout new_layout, VkImage image,
                        VkFence fence,
                        u32 wait_semaphore_count,   VkSemaphore *wait_semaphores,
                        u32 signal_semaphore_count, VkSemaphore *signal_semaphores)
{
    TransitImageLayout(old_layout, new_layout, image,
                       vk.queue, vk.command_buffer, fence,
                       wait_semaphore_count, wait_semaphores,
                       signal_semaphore_count, signal_semaphores);
}
void TransitImageLayout(VkImageLayout old_layout, VkImageLayout new_layout, VkImage image, VkFence fence)
{
    TransitImageLayout(old_layout, new_layout, image,
                       vk.queue, vk.command_buffer, fence,
                       0, NULL,
                       0, NULL);
}

void TransitSwapchainImageLayouts()
{
    for(u32 i = 0; i < data.image_count; i++)
    {
        TransitImageLayout(VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                           vk.swapchain_images[i], vk.fence_transit);
    }
}

void StageImage(VkImage image, u32 width, u32 height, VkImageLayout new_layout,
                VkQueue queue, VkCommandBuffer command_buffer,
                u32 wait_semaphore_count,   VkSemaphore *wait_semaphores,
                u32 signal_semaphore_count, VkSemaphore *signal_semaphores)
{
    VkImageSubresourceLayers subresource_layers = {};
    subresource_layers.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
    subresource_layers.mipLevel       = 0;
    subresource_layers.baseArrayLayer = 0;
    subresource_layers.layerCount     = 1;
    
    VkExtent3D extent = {};
    extent.width  = width;
    extent.height = height;
    extent.depth  = 1;
    
    VkBufferImageCopy regions = {};
    regions.bufferOffset      = 0;
    regions.bufferRowLength   = 0;
    regions.bufferImageHeight = 0;
    regions.imageSubresource  = subresource_layers;
    regions.imageExtent       = extent;
    regions.imageOffset.x = 0;
    regions.imageOffset.y = 0;
    regions.imageOffset.z = 0;
    // ---
    
    VkImageMemoryBarrier barrier = {};
    barrier.sType               = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.pNext               = NULL;
    barrier.srcAccessMask       = VK_ACCESS_HOST_READ_BIT;
    barrier.dstAccessMask       = VK_ACCESS_HOST_WRITE_BIT;
    barrier.oldLayout           = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    barrier.newLayout           = new_layout;
    barrier.image               = image;
    barrier.subresourceRange    = vk.color_sr;
    
    VkPipelineStageFlags staging_mask = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    VkSubmitInfo queue_si = GenerateSubmitInfo(wait_semaphore_count, wait_semaphores,
                                               &staging_mask,
                                               1, &command_buffer,
                                               signal_semaphore_count, signal_semaphores);
    
    void *checkpoint_marker = calloc(1, sizeof(void *));
    EnterCriticalSection(&crit_sec);
    
    vkBeginCommandBuffer(command_buffer, &vk.cb_bi);
    vkCmdCopyBufferToImage(command_buffer, data.staging_buffer, image,
                           VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &regions);
    vkCmdPipelineBarrier(command_buffer,
                         VK_PIPELINE_STAGE_HOST_BIT, VK_PIPELINE_STAGE_HOST_BIT,
                         0,
                         0, NULL,
                         0, NULL,
                         1, &barrier);
    vkEndCommandBuffer(command_buffer);
    vkQueueSubmit(queue, 1, &queue_si, vk.fence_stage);
    
    LeaveCriticalSection(&crit_sec);
    
    ODS("Waiting on staging fence\n");
    vkWaitForFences(vk.device, 1, &vk.fence_stage, VK_TRUE, UINT64_MAX);
    
    ODS("Resetting staging fence\n");
    vkResetFences(vk.device, 1, &vk.fence_stage);
}
void StageImage(VkImage image, u32 width, u32 height, VkImageLayout new_layout,
                u32 wait_semaphore_count,   VkSemaphore *wait_semaphores,
                u32 signal_semaphore_count, VkSemaphore *signal_semaphores)
{
    StageImage(image, width, height, new_layout,
               vk.queue, vk.command_buffer,
               wait_semaphore_count, wait_semaphores,
               signal_semaphore_count, signal_semaphores);
}


void CopySwapchainImageToScreenshotImage(u32 width, u32 height,
                                         VkImage src_image, VkImageLayout layout_of_src,
                                         VkImage dst_image, VkImageLayout layout_of_dst,
                                         u32 wait_semaphore_count,   VkSemaphore *wait_semaphores,
                                         u32 signal_semaphore_count, VkSemaphore *signal_semaphores)
{
    VkImageSubresourceLayers subresource_layers = {};
    subresource_layers.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
    subresource_layers.mipLevel       = 0;
    subresource_layers.baseArrayLayer = 0;
    subresource_layers.layerCount     = 1;
    
    VkOffset3D offset = {};
    offset.x = 0;
    offset.y = 0;
    offset.z = 0;
    
    VkExtent3D extent = {};
    extent.width  = width;
    extent.height = height;
    extent.depth  = 1;
    
    VkImageCopy region = {};
    region.srcSubresource = subresource_layers;
    region.srcOffset      = offset;
    region.dstSubresource = subresource_layers;
    region.dstOffset      = offset;
    region.extent         = extent;
    
    VkResult result;
    
    VkFence fence;
    result = vkCreateFence(vk.device, &vk.fence_ci, NULL, &fence);
    ODS("Swapchain image copy fence create: %s\n", RevEnum(data.result_enum, result));
    
    VkPipelineStageFlags wait_stage_mask = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    VkSubmitInfo queue_si = GenerateSubmitInfo(1, wait_semaphores,
                                               &wait_stage_mask,
                                               1, &vk.command_buffer,
                                               1, signal_semaphores);
    
    EnterCriticalSection(&crit_sec);
    
    vkBeginCommandBuffer(vk.command_buffer, &vk.cb_bi);
    vkCmdCopyImage(vk.command_buffer,
                   src_image, layout_of_src,
                   dst_image, layout_of_dst,
                   1,
                   &region);
    vkEndCommandBuffer(vk.command_buffer);
    
    LeaveCriticalSection(&crit_sec);
    
    result = vkQueueSubmit(vk.queue, 1, &queue_si, fence);
    ODS("Swapchain image copy fence create: %s\n", RevEnum(data.result_enum, result));
    
    vkWaitForFences(vk.device, 1, &fence, VK_TRUE, UINT64_MAX);
    ODS("Swapchain image copy fence wait:   %s\n", RevEnum(data.result_enum, result));
    
    vkDestroyFence(vk.device, fence, NULL);
}

// --- --- ---

// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////         VULKAN FUNCTION ABSTRACTION ------ ------
// //////////////////////////////////////////////////////////////////////////////



// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                      SCREENSHOT FACILITIES ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

// ---
u8 *ReadImage(char *filename, u32 *width, u32 *height)
{
    s32 image_channels;
    s32 force_channels = 4;
    u8 *pixels = stbi_load(filename, (s32 *)width, (s32 *)height, &image_channels, force_channels);
    
    return pixels;
}

// ---

void Pixels32BitTo24Bit(u32 *screenshot_pixels, u8 *screenshot_final_pixels)
{
    u32 *reader = screenshot_pixels;
    u8  *writer = screenshot_final_pixels;
    
    for(u32 i = 0; i < app.window_height; i++)
    {
        for(u32 j = 0; j < app.window_width; j++)
        {
            u32 pixel = *reader++;
            
            u8 A = pixel >> 24;
            u8 R = pixel >> 16;
            u8 G = pixel >> 8;
            u8 B = pixel;
            
            *writer++ = R;
            *writer++ = G;
            *writer++ = B;
        }
    }
}

void WriteScreenshot(u32 counter, u8 *pixels, u32 channels)
{
    char *dir = "../screenshots/";
    if(!PathFileExistsA(dir))
    {
        CreateDirectoryA(dir, NULL);
    }
    
    char *format = "../screenshots/screenshot_%05d.png";
    
    char buf[50];
    snprintf(buf, 50, format, counter);
    
    s32 result = stbi_write_png(buf,
                                app.window_width, app.window_height,
                                channels, pixels,
                                app.window_width * channels);
    ODS("Writing screenshot: %d", result);
}

// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////               SCREENSHOT FACILITIES ------ ------
// //////////////////////////////////////////////////////////////////////////////



// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                               IMAGE VIEWER ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


string **GetFullNames(string *folder, string **names, u32 count)
{
    string **result = (string **)malloc(sizeof(string *) * count);
    
    for(u32 i = 0; i < count; i++)
    {
        u32 len = folder->length + names[i]->length + 1;
        char *finalname = (char *)malloc(len);
        strcpy(finalname, folder->text);
        strcat(finalname, names[i]->text);
        finalname[len] = terminator;
        
        result[i] = String(finalname);
    }
    
    return result;
}

string **ScanFolderForImages(string *image_folder, u32 *image_count)
{
    char *folder_win32_search_name = (char *)calloc(image_folder->length+2, sizeof(char));
    memcpy(folder_win32_search_name, image_folder->text, image_folder->length);
    folder_win32_search_name[image_folder->length] = '*';
    folder_win32_search_name[image_folder->length+1] = terminator;
    
    *image_count        = CountFolderFiles(folder_win32_search_name);
    ODS("%d images found\n", *image_count);
    string **names      = GetFolderFileNames(folder_win32_search_name, *image_count);
    string **full_names = GetFullNames(image_folder, names, *image_count);
    
    return full_names;
}

void BlitImage(VkImage from, u32 from_w, u32 from_h,
               VkImage to,   u32 to_w,   u32 to_h,
               VkQueue queue, VkCommandBuffer command_buffer,
               u32 wait_semaphore_count,   VkSemaphore *wait_semaphores,
               u32 signal_semaphore_count, VkSemaphore *signal_semaphores)
{
    VkImageSubresourceLayers src_subresource = {};
    src_subresource.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
    src_subresource.mipLevel       = 0;
    src_subresource.baseArrayLayer = 0;
    src_subresource.layerCount     = 1;
    
    VkImageSubresourceLayers dst_subresource = {};
    dst_subresource.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
    dst_subresource.mipLevel       = 0;
    dst_subresource.baseArrayLayer = 0;
    dst_subresource.layerCount     = 1;
    
    
    VkImageBlit region = {};
    region.srcSubresource = src_subresource;
    region.srcOffsets[0].x = 0;
    region.srcOffsets[0].y = 0;
    region.srcOffsets[0].z = 0;
    region.srcOffsets[1].x = from_w;
    region.srcOffsets[1].y = from_h;
    region.srcOffsets[1].z = 1;
    region.dstSubresource = dst_subresource;
    region.dstOffsets[0].x = 0;
    region.dstOffsets[0].y = 0;
    region.dstOffsets[0].z = 0;
    region.dstOffsets[1].x = to_w;
    region.dstOffsets[1].y = to_h;
    region.dstOffsets[1].z = 1;
    
    VkPipelineStageFlags wait_stage_mask = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    VkSubmitInfo queue_si = GenerateSubmitInfo(wait_semaphore_count, wait_semaphores,
                                               &wait_stage_mask,
                                               1, &command_buffer,
                                               signal_semaphore_count, signal_semaphores);
    
    void *checkpoint_marker = calloc(1, sizeof(void *));
    EnterCriticalSection(&crit_sec);
    
    vkBeginCommandBuffer(command_buffer, &vk.cb_bi);
    vkCmdBlitImage(command_buffer,
                   from, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                   to,   VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                   1, &region,
                   VK_FILTER_LINEAR);
    vkEndCommandBuffer(command_buffer);
    vkQueueSubmit(queue, 1, &queue_si, vk.fence_blit);
    
    LeaveCriticalSection(&crit_sec);
    
    ODS("Waiting on blit fence\n");
    vkWaitForFences(vk.device, 1, &vk.fence_blit, VK_TRUE, UINT64_MAX);
    
    ODS("Resetting blit fence\n");
    vkResetFences(vk.device, 1, &vk.fence_blit);
}
void BlitImage(VkImage from, u32 from_w, u32 from_h,
               VkImage to,   u32 to_w,   u32 to_h,
               u32 wait_semaphore_count,   VkSemaphore *wait_semaphores,
               u32 signal_semaphore_count, VkSemaphore *signal_semaphores)
{
    BlitImage(from, from_w, from_h,
              to,   to_w,   to_h,
              vk.queue, vk.command_buffer,
              wait_semaphore_count, wait_semaphores,
              signal_semaphore_count, signal_semaphores);
}



// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////                        IMAGE VIEWER ------ ------
// //////////////////////////////////////////////////////////////////////////////



// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                     TRIPLE-THREAD SOLUTION ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

// VERY careful with exposing the head.
void AddEntry(image_entry *im_entry)
{
    EnterCriticalSection(&crit_sec);
    
    r32 ratio = 0.0f;
    if(im_entry->width > im_entry->height)
    {
        ratio = (r32)im_entry->height / (r32)im_entry->width;
        
        viewer.thumbs[viewer.processed_image_count].width  = (u32)viewer.thumbnail_size;
        viewer.thumbs[viewer.processed_image_count].height = (u32)(viewer.thumbs[viewer.processed_image_count].width * ratio);
    }
    else
    {
        ratio = (r32)im_entry->width / (r32)im_entry->height;
        
        viewer.thumbs[viewer.processed_image_count].height = (u32)viewer.thumbnail_size;
        viewer.thumbs[viewer.processed_image_count].width  = (u32)(viewer.thumbs[viewer.processed_image_count].height * ratio);
    }
    
    // if no head, become head
    if(!viewer.image_head)
    {
        viewer.image_head = (image_ll *)calloc(1, sizeof(image_ll));
        viewer.image_head->ptr = im_entry;
        viewer.image_head->next = NULL;
    }
    // if head, go down next until next is NULL, become next
    else
    {
        image_ll *image_curr = viewer.image_head;
        while(image_curr->next != NULL)
            image_curr = image_curr->next;
        
        // now make an LL entry out of image entry
        image_ll *ll_entry = (image_ll *)calloc(1, sizeof(image_ll));
        
        ll_entry->ptr  = im_entry;
        ll_entry->next = NULL;
        
        // and become the next;
        image_curr->next = ll_entry;
    }
    
    viewer.processed_image_count++;
    
    LeaveCriticalSection(&crit_sec);
}


// reads images from folder, leaves pixels in an LL
DWORD WINAPI Threaded_DiskProc(LPVOID param)
{
    string **file_names = (string **)param;
    
    for(u32 i = 0; i < viewer.image_count; i++)
    {
        u32 width  = 0;
        u32 height = 0;
        u32 *pixels = (u32 *)ReadImage(file_names[i]->text, &width, &height);
        u32 pixel_bytes = width * height * 4;
        
        if(strstr(file_names[i]->text, "?")!=NULL)
        {
            ODS("Image %d: UNSUPPORTED FILENAME: %.*s\n", i, file_names[i]->length, file_names[i]->text);
            free(pixels);
        }
        else if((width == 0) || (height == 0))
        {
            ODS("Image %d: POSSIBLE CORRUPTION: %.*s\n", i, file_names[i]->length, file_names[i]->text);
            free(pixels);
        }
        else if(pixel_bytes > 100 * MEGABYTE)
        {
            ODS("Image %d: FOOTPRINT OVER 100MB: %.*s\n", i, file_names[i]->length, file_names[i]->text);
            free(pixels);
        }
        else
        {
            ODS(" --- Processing image %d begins --- \n", i);
            
            image_entry *entry = (image_entry *)calloc(1, sizeof(image_entry));
            entry->pixels = pixels;
            entry->width  = width;
            entry->height = height;
            entry->pixel_bytes = pixel_bytes;
            
            AddEntry(entry);
            
            ODS(" --- Processing image %d ends --- \n", i);
        }
    }
    
    return 0;
}

// Takes images off of LL, creates VkImages of pixels, VkImages of thumbs, blits and frees pixels;
//  writes thumbs to an array
void ProcessImage(image_entry *entry)
{
    VkSemaphore semaphore_0, semaphore_1, semaphore_2, semaphore_3;
    vkCreateSemaphore(vk.device, &vk.semaphore_ci, NULL, &semaphore_0);
    vkCreateSemaphore(vk.device, &vk.semaphore_ci, NULL, &semaphore_1);
    vkCreateSemaphore(vk.device, &vk.semaphore_ci, NULL, &semaphore_2);
    vkCreateSemaphore(vk.device, &vk.semaphore_ci, NULL, &semaphore_3);
    
    // create image
    VkImage original;
    VkImageView original_view;
    VkDeviceMemory original_memory;
    CreateImage(&original, &original_memory, entry->width, entry->height,
                VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_SAMPLED_BIT|VK_IMAGE_USAGE_TRANSFER_SRC_BIT|VK_IMAGE_USAGE_TRANSFER_DST_BIT,
                VK_IMAGE_LAYOUT_UNDEFINED, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    CreateImageView(&original, &original_view);
    
    void *staging_mapptr;
    vkMapMemory(vk.device, data.staging_memory, 0, entry->pixel_bytes, 0, &staging_mapptr);
    memcpy(staging_mapptr, entry->pixels, entry->pixel_bytes);
    vkUnmapMemory(vk.device, data.staging_memory);
    
    CreateImage(&viewer.thumbs[viewer.ready_image_count].image, &viewer.thumbs[viewer.ready_image_count].memory, viewer.thumbs[viewer.ready_image_count].width, viewer.thumbs[viewer.ready_image_count].height,
                VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_SAMPLED_BIT|VK_IMAGE_USAGE_TRANSFER_SRC_BIT|VK_IMAGE_USAGE_TRANSFER_DST_BIT,
                VK_IMAGE_LAYOUT_UNDEFINED, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    CreateImageView(&viewer.thumbs[viewer.ready_image_count].image, &viewer.thumbs[viewer.ready_image_count].view);
    
    // transit
    TransitImageLayout(VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, original, 
                       vk.queue_thumb, vk.command_buffer_thumb, vk.fence_transit_processing,
                       0, NULL,
                       1, &semaphore_0);
    // stage
    StageImage(original, entry->width, entry->height, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
               vk.queue_thumb, vk.command_buffer_thumb,
               1, &semaphore_0,
               1, &semaphore_1);
    // transit
    TransitImageLayout(VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, viewer.thumbs[viewer.ready_image_count].image,
                       vk.queue_thumb, vk.command_buffer_thumb, vk.fence_transit_processing,
                       1, &semaphore_1,
                       1, &semaphore_2);
    // blit
    BlitImage(original, entry->width, entry->height,
              viewer.thumbs[viewer.ready_image_count].image, viewer.thumbs[viewer.ready_image_count].width, viewer.thumbs[viewer.ready_image_count].height,
              vk.queue_thumb, vk.command_buffer_thumb,
              1, &semaphore_2,
              1, &semaphore_3);
    // transit
    TransitImageLayout(VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, viewer.thumbs[viewer.ready_image_count].image,
                       vk.queue_thumb, vk.command_buffer_thumb, vk.fence_transit_processing,
                       1, &semaphore_3,
                       0, NULL);
    
    vkDestroyImageView(vk.device, original_view, NULL);
    vkDestroyImage(vk.device, original, NULL);
    vkFreeMemory(vk.device, original_memory, NULL);
    
    vkDestroySemaphore(vk.device, semaphore_0, NULL);
    vkDestroySemaphore(vk.device, semaphore_1, NULL);
    vkDestroySemaphore(vk.device, semaphore_2, NULL);
    vkDestroySemaphore(vk.device, semaphore_3, NULL);
}

void MoveHead()
{
    viewer.image_head = viewer.image_head->next;
}

void FreeEntry(image_entry *entry)
{
    free(entry->pixels);
    free(entry);
}

DWORD WINAPI Threaded_ThumbProc(LPVOID param)
{
    viewer.thread_thumb = GetCurrentThread();
    
    CreateCommandPool(&vk.command_pool_thumb);
    AllocateCommandBuffer(vk.command_pool_thumb, &vk.command_buffer_thumb);
    vkGetDeviceQueue(vk.device, vk.queue_family_index, 1, &vk.queue_thumb);
    
    while(app.running)
    {
        if(!viewer.image_head)
            WaitForSingleObject(viewer.thread_thumb, 1);
        else
        {
            EnterCriticalSection(&crit_sec);
            
            image_entry *entry = viewer.image_head->ptr;
            
            ProcessImage(entry);
            
            MoveHead();
            
            FreeEntry(entry);
            
            // There's now more images ready to be rendered.
            ODS("Image %d ready\n", viewer.ready_image_count);
            viewer.ready_image_count++;
            LeaveCriticalSection(&crit_sec);
        }
    }
    
    return 0;
}

// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////              TRIPLE-THREAD SOLUTION ------ ------
// //////////////////////////////////////////////////////////////////////////////



// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                    THREADED LL SCREENSHOTS ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

void AddScreenshotEntry(screenshot_entry *sc_entry)
{
    EnterCriticalSection(&crit_sec);
    
    // if no head, become head
    if(!viewer.screenshot_head)
    {
        viewer.screenshot_head = (screenshot_ll *)calloc(1, sizeof(screenshot_ll));
        viewer.screenshot_head->ptr = sc_entry;
        viewer.screenshot_head->next = NULL;
    }
    // if head, go down next until next is NULL, become next
    else
    {
        screenshot_ll *screenshot_curr = viewer.screenshot_head;
        while(screenshot_curr->next != NULL)
            screenshot_curr = screenshot_curr->next;
        
        // now make an LL entry out of screenshot entry
        screenshot_ll *ll_entry = (screenshot_ll *)calloc(1, sizeof(screenshot_ll));
        ll_entry->ptr  = sc_entry;
        ll_entry->next = NULL;
        
        // and become the next;
        screenshot_curr->next = ll_entry;
    }
    
    LeaveCriticalSection(&crit_sec);
}


// - already have swapchain->screenshot image copy
// - memory is mapped
// - forming an entry already done, and ezpz anyway
// - adding to LL already implemented and also ezpz
void AddScreenshotToLL(u32 index, u32 counter)
{
    VkSemaphore semaphore_0, semaphore_1, semaphore_2;
    vkCreateSemaphore(vk.device, &vk.semaphore_ci, NULL, &semaphore_0);
    vkCreateSemaphore(vk.device, &vk.semaphore_ci, NULL, &semaphore_1);
    vkCreateSemaphore(vk.device, &vk.semaphore_ci, NULL, &semaphore_2);
    
    //EnterCriticalSection(&crit_sec);
    
    // copy swapchain image to an already prepared screenshot image
    TransitImageLayout(VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, vk.swapchain_images[index],
                       vk.queue, vk.command_buffer, vk.fence_transit,
                       0, NULL,
                       1, &semaphore_0);
    
    TransitImageLayout(VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, data.screenshot_image,
                       vk.queue, vk.command_buffer, vk.fence_transit,
                       1, &semaphore_0,
                       1, &semaphore_1);
    
    CopySwapchainImageToScreenshotImage(app.window_width, app.window_height,
                                        vk.swapchain_images[index], VK_IMAGE_LAYOUT_UNDEFINED,
                                        data.screenshot_image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                                        1, &semaphore_1,
                                        1, &semaphore_2);
    
    TransitImageLayout(VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL, data.screenshot_image,
                       vk.queue, vk.command_buffer, vk.fence_transit,
                       1, &semaphore_2,
                       0, NULL);
    
    //LeaveCriticalSection(&crit_sec);
    
    vkDestroySemaphore(vk.device, semaphore_0, NULL);
    vkDestroySemaphore(vk.device, semaphore_1, NULL);
    vkDestroySemaphore(vk.device, semaphore_2, NULL);
    
    // its memory is mapped, copy pixels from it
    u32 copy_pixels_bytes = app.window_width * app.window_height * 4;
    u32 *copy_pixels = (u32 *)calloc(copy_pixels_bytes, sizeof(u32));
    
    memcpy(copy_pixels, viewer.screenshot_mapptr, copy_pixels_bytes);
    
    u32 entry_pixels_bytes = app.window_width * app.window_height * 3;
    u8 *entry_pixels = (u8 *)calloc(entry_pixels_bytes, sizeof(u8));
    
    Pixels32BitTo24Bit(copy_pixels, entry_pixels);
    
    // write the pixels into an entry, and add it to LL
    screenshot_entry *entry = (screenshot_entry *)calloc(1, sizeof(screenshot_entry));
    entry->pixels = entry_pixels;
    entry->width  = app.window_width;
    entry->height = app.window_height;
    entry->pixel_bytes = entry_pixels_bytes;
    entry->index = counter;
    
    AddScreenshotEntry(entry);  // this could be a dangerous addition.
}


void MoveScreenshotHead()
{
    viewer.screenshot_head = viewer.screenshot_head->next;
}

void FreeScreenshotEntry(screenshot_entry *entry)
{
    free(entry->pixels);
    free(entry);
}


// - looks just like image->thumb proc, with LL management
DWORD WINAPI Threaded_ScreenshotProc(LPVOID param)
{
    viewer.thread_screenshot = GetCurrentThread();
    
    // This good enough for termination condition?
    while(app.running)
    {
        if(!viewer.screenshot_head)
        {
            WaitForSingleObject(viewer.thread_screenshot, 1);
        }
        else
        {
            screenshot_entry *entry = viewer.screenshot_head->ptr;
            
            // write file
            WriteScreenshot(entry->index, entry->pixels, 3);
            
            MoveScreenshotHead();
            
            FreeScreenshotEntry(entry);
            
            ODS("Screenshot %d written \n", viewer.screenshots_recorded);
            viewer.screenshots_recorded++;
        }
    }
    
    return 0;
}


// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////             THREADED LL SCREENSHOTS ------ ------
// //////////////////////////////////////////////////////////////////////////////



// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\
//
//                                              MAIN CONTROLS ------ ------ ------
//
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

void VulkanPrepare()
{
    Vulkan_LoadInstanceFunctions();
    EnumerateGlobalExtensions();
    EnumerateLayerExtensions();
    
    char *instance_layers[] = {
        "VK_LAYER_LUNARG_assistant_layer",
        "VK_LAYER_KHRONOS_validation" };
    u32 layer_count = sizeof(instance_layers) / sizeof(instance_layers[0]);
    
    char *instance_extensions[] = {
        "VK_KHR_surface",
        "VK_KHR_win32_surface",
        "VK_EXT_debug_utils",
        "VK_KHR_get_physical_device_properties2"};
    u32 extension_count = sizeof(instance_extensions) / sizeof(instance_extensions[0]);
    
    InstanceCreate(instance_layers, layer_count,
                   instance_extensions, extension_count);
    
    Vulkan_LoadExtensionFunctions(vk.instance);
    
    Vulkan_SetupDebugging(vk.instance, vk.debug_messenger);
    GetGPU();
    EnumerateDeviceExtensions();
    EnumerateDeviceLayers();
    CheckGPUFeatures();
    CreateSurface();
    
    SetupQueue();
    char *device_extensions[] = { "VK_KHR_swapchain", "VK_KHR_maintenance3", "VK_EXT_descriptor_indexing" };
    u32 device_extension_count = sizeof(device_extensions) / sizeof(device_extensions[0]);
    VkPhysicalDeviceFeatures enable_features = {};
    DeviceCreate_VariableDescriptorEXT(device_extensions, device_extension_count, enable_features);
    vkGetDeviceQueue(vk.device, vk.queue_family_index, 0, &vk.queue);
    
    GetFormatAndColorspace();
    CheckSurfaceCapabilities();
    SetPresentMode();
    SwapchainCreate();
    GetSwapchainImages();
    CreateSwapchainImageViews();
    
    CreateCommandPool(&vk.command_pool);
    AllocateCommandBuffer(vk.command_pool, &vk.command_buffer);
    
    CheckDeviceMemoryProperties();
    
    CreateScissor();
    CreateViewport();
    
    CheckCheckpoints();
    
    // --- fences
    ODS("Creating acquisition fence\n");
    vkCreateFence(vk.device, &vk.fence_ci, NULL, &vk.fence_acquisition_complete);
    ODS("Creating render fence\n");
    vkCreateFence(vk.device, &vk.fence_ci, NULL, &vk.fence_render_complete);
    
    ODS("Creating transit fence\n");
    vkCreateFence(vk.device, &vk.fence_ci, NULL, &vk.fence_transit);
    ODS("Creating transit processing fence\n");
    vkCreateFence(vk.device, &vk.fence_ci, NULL, &vk.fence_transit_processing);
    ODS("Creating blit fence\n");
    vkCreateFence(vk.device, &vk.fence_ci, NULL, &vk.fence_blit);
    ODS("Creating staging fence\n");
    vkCreateFence(vk.device, &vk.fence_ci, NULL, &vk.fence_stage);
    
    ODS("> Transiting swapchain images\n");
    TransitSwapchainImageLayouts();
}





void DataPrepare()
{
    // --- Application preparations ---
    viewer_render_init.rs = &viewer_rs;
    viewer_render_init.vert = "../build/viewer_vert.spv";
    viewer_render_init.frag = "../build/viewer_frag.spv";
    CreateRenderstate_viewer(&viewer_render_init, false, false);
    
    overlay_render_init.rs   = &overlay_rs;
    overlay_render_init.vert = "../build/overlay_vert.spv";
    overlay_render_init.frag = "../build/overlay_frag.spv";
    overlay_font_init.fontfile  = "C:/Windows/Fonts/consola.ttf";
    overlay_font_init.font_size = 20.0f;
    overlay_font_init.color     = 0xFFFFFF;  // BGR
    CreateRenderstate_overlay(&overlay_render_init, &overlay_font_init, true, true);
    
    vk.framebuffers = CreateFramebuffers(&viewer_rs, vk.swapchain_imageviews, data.image_count);
    // ---
    
    if(data.RECORD)
    {
        CreateImage(&data.screenshot_image, &data.screenshot_memory,
                    app.window_width, app.window_height,
                    VK_IMAGE_TILING_LINEAR,
                    VK_IMAGE_USAGE_TRANSFER_DST_BIT,
                    VK_IMAGE_LAYOUT_UNDEFINED,
                    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT|VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
    }
    
    vkCreateSemaphore(vk.device, &vk.semaphore_ci, NULL, &data.semaphore_execution_complete);
    
    data.staging_buffer = CreateBuffer(100 * MEGABYTE, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                                       VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT|VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                                       vk.device, vk.gpu_memprops, &data.staging_memory);
    
    
    //// --- --- --- ATLAS PREPARATIONS --- --- ---
    void *staging_mapptr;
    vkMapMemory(vk.device, data.staging_memory, 0, overlay_rs.fd->atlas_data.pixels_datasize, 0, &staging_mapptr);
    memcpy(staging_mapptr, overlay_rs.fd->atlas_data.pixels, overlay_rs.fd->atlas_data.pixels_datasize);
    vkUnmapMemory(vk.device, data.staging_memory);
    
    CreateSamplerImage(overlay_rs.fd->atlas_data.width, overlay_rs.fd->atlas_data.height,
                       &overlay_rs.fd->atlas_data.image,
                       &overlay_rs.fd->atlas_data.memory);
    CreateImageView(&overlay_rs.fd->atlas_data.image, &overlay_rs.fd->atlas_data.imageview);
    
    VkSemaphore semaphore_0;
    vkCreateSemaphore(vk.device, &vk.semaphore_ci, NULL, &semaphore_0);
    
    ODS("> Transiting atlas layout\n");
    TransitImageLayout(VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, overlay_rs.fd->atlas_data.image, vk.fence_transit,
                       0, NULL,
                       1, &semaphore_0);
    StageImage(overlay_rs.fd->atlas_data.image, overlay_rs.fd->atlas_data.width, overlay_rs.fd->atlas_data.height, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
               1, &semaphore_0,
               0, NULL);
    
    vkDestroySemaphore(vk.device, semaphore_0, NULL);
    
    CreateSampler(&overlay_rs.fd->atlas_data.sampler);
    // ---
    
    
    //// --- --- --- IMAGE PREPARATIONS --- --- ---
    CreateSampler(&viewer.sampler);
    
    string **file_names = ScanFolderForImages(viewer.image_folder, &viewer.image_count);
    viewer.image_count = (viewer.image_count < MAX_IMAGES) ? viewer.image_count : MAX_IMAGES;
    ODS("> Checking folder image names:\n");
    for(u32 i = 0; i < viewer.image_count; i++)
    {
        ODS("%.*s\n", file_names[i]->length, file_names[i]->text);
    }
    
    viewer.images = (viewer_image *)calloc(viewer.image_count, sizeof(viewer_image));
    viewer.thumbs = (viewer_thumb *)calloc(viewer.image_count, sizeof(viewer_thumb));
    
    viewer.thread_disk       = CreateThread(NULL, 0, Threaded_DiskProc,       file_names, 0, NULL);
    viewer.thread_thumb      = CreateThread(NULL, 0, Threaded_ThumbProc,      NULL, 0, NULL);
    viewer.thread_screenshot = CreateThread(NULL, 0, Threaded_ScreenshotProc, NULL, 0, NULL);
    
    //// --- --- --- GEOMETRY PREPARATIONS --- --- ---
    
    
    // Orthographics matrix for overlay renderstate's pipeline
    data.orthographic_matrix = GenerateOrthographicMatrix(app.window_width, app.window_height);
    
    
    // --- Writing matrix info
    u32 matrix_datasize = sizeof(r32) * 16;
    data.matrix_buffer = CreateBuffer(matrix_datasize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
                                      vk.device, vk.gpu_memprops, &data.matrix_memory);
    void *matrix_mapptr;
    vkMapMemory(vk.device, data.matrix_memory, 0, VK_WHOLE_SIZE, 0, &matrix_mapptr);
    memcpy(matrix_mapptr, data.orthographic_matrix, matrix_datasize);
    vkUnmapMemory(vk.device, data.matrix_memory);
    
    
    viewer.view = Matrix4();
    viewer.view_buffer = CreateBuffer(matrix_datasize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
                                      vk.device, vk.gpu_memprops, &viewer.view_memory);
    // ---
    
    
    // Initialize view matrix
    data.view_matrix = Matrix4();
    
    vkMapMemory(vk.device, viewer.view_memory, 0, VK_WHOLE_SIZE, 0, &viewer.view_mapptr);
    vkMapMemory(vk.device, data.screenshot_memory, 0, VK_WHOLE_SIZE, 0, &viewer.screenshot_mapptr);                                                                                               
}


void ScrollUp(r32 speed)
{
    viewer.scroll_y -= speed * data.dt;
}
void ScrollDown(r32 speed)
{
    viewer.scroll_y += speed * data.dt;
}


void GenerateQuadCenters(u32 count, u32 columns,
                         r32 **x_array, r32 **y_array)
{
    r32 x_start = 0.0f;
    r32 y_start = (r32)app.window_height;
    
    r32 size = (r32)app.window_width / (r32)columns;
    
    u32 x_count = (columns < count) ? columns : count;
    u32 y_count = count / columns + !((count % columns) == 0);
    
    r32 *x_coords = (r32 *)calloc(x_count, sizeof(r32));
    r32 *y_coords = (r32 *)calloc(y_count, sizeof(r32));
    
    r32 x_first = x_start + size / 2.0f;
    for(u32 i = 0; i < x_count; i++)
        x_coords[i] = x_first + i*size;
    
    r32 y_first = y_start - size / 2.0f;
    for(u32 i = 0; i < y_count; i++)
        y_coords[i] = y_first - i*size;
    
    *x_array = x_coords;
    *y_array = y_coords;
}


void Process()
{
    // --- index cleanup
    MemoryReset_indexes(&viewer_rs);
    MemoryReset_indexes(&overlay_rs);
    
    viewer.current_ready_image_count = viewer.ready_image_count;
    u32 current_screenshots = viewer.screenshots_recorded;
    
    //// --- --- --- IMAGE RENDERING --- --- ---
    
    u32 row_count = viewer.current_ready_image_count / viewer.column_count;
    
    viewer.scroll_min = 0.0f;
    viewer.scroll_max = row_count * viewer.thumbnail_size - app.window_height + viewer.thumbnail_size;
    
    // disable if recording
    if(!data.RECORD)
    {
        if(viewer.scroll_y > viewer.scroll_max) viewer.scroll_y = viewer.scroll_max;
        if(viewer.scroll_y < viewer.scroll_min) viewer.scroll_y = viewer.scroll_min;
    }
    viewer.view = GenerateTranslationMatrix(Vector3(0.0f, viewer.scroll_y, 0.0f));
    
    u32 matrix_datasize = sizeof(r32) * 16;
    memcpy(viewer.view_mapptr, viewer.view, matrix_datasize);
    
    
    
    // Generate the centers based on thumbnail size and thumbnail count per row
    u32 quad_count = viewer.ready_image_count;
    r32 *xs, *ys;
    GenerateQuadCenters(quad_count, viewer.column_count, &xs, &ys);
    
    // Generate quads from centers
    for(u32 i = 0; i < viewer.ready_image_count; i++)
    {
        u32 x_index = i % viewer.column_count;
        u32 y_index = i / viewer.column_count;
        vertex_uv *thumb_quad = QuadGenerate_uv_center(viewer.thumbs[i].width, viewer.thumbs[i].height,
                                                       xs[x_index], ys[y_index]);
        VertexesWrite_uv(&viewer_rs, thumb_quad, 1);
    }
    WriteRenderstateMemory(&viewer_rs);
    
    // ---
    
    //// --- --- --- OVERLAY --- --- ---
    u32 font_index = 0;
    r32 v_advance = overlay_rs.fd->v_advance;
    
    r32 pad = 5.0f;
    r32 v_pad = 5.0f;
    r32 h_pad = 5.0f;
    
    RenderString(&overlay_rs, font_index, left, top, h_pad, v_pad,                 "Warmup time: %6.3f ms", data.time_warmup);
    RenderString(&overlay_rs, font_index, left, top, h_pad, v_pad + 1 * v_advance, "Delta t: %f", data.dt);
    RenderString(&overlay_rs, font_index, left, top, h_pad, v_pad + 2 * v_advance, "Current FPS: %6.3f", 1.0f / data.dt);
    RenderString(&overlay_rs, font_index, left, top, h_pad, v_pad + 3 * v_advance, "Current frame: %4d", data.frame_counter);
    
    RenderString(&overlay_rs, font_index, left, top, h_pad, v_pad + 5 * v_advance, "Total images opened:  %d", viewer.current_ready_image_count);
    if(data.RECORD)
    {
        RenderString(&overlay_rs, font_index, left, top, h_pad, v_pad + 6 * v_advance, "Screenshots recorded: %d", current_screenshots);
    }
    
    WriteRenderstateMemory(&overlay_rs);
    // ---
    
    
    // --- geometry cleanup
    MemoryReset_geometry(&viewer_rs);
    MemoryReset_geometry(&overlay_rs);
}


void Render()
{
    VkResult result;
    
    // --- Acquire image ---
    // ---
    vkAcquireNextImageKHR(vk.device, vk.swapchain, UINT64_MAX, VK_NULL_HANDLE, vk.fence_acquisition_complete, &data.acquired_index);
    
    ODS("Waiting on acquisition fence\n");
    result = vkWaitForFences(vk.device, 1, &vk.fence_acquisition_complete, VK_TRUE, UINT64_MAX);
    ODS("Acquisition fence wait: %s\n", RevEnum(data.result_enum, result));
    if(result != VK_SUCCESS)
        ODS("Uh-oh, device lost\n");
    
    ODS("Resetting acquisition fence\n");
    result = vkResetFences(vk.device, 1, &vk.fence_acquisition_complete);
    ODS("Acquisition fence reset: %s\n", RevEnum(data.result_enum, result));
    if(result != VK_SUCCESS)
        ODS("Uh-oh, device lost\n");
    // ---
    
    
    // Transit into color attachment for rendering
    TransitImageLayout(VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                       vk.swapchain_images[data.acquired_index], vk.fence_transit);
    
    
    // --- Prepare renderpass ---
    // ---
    VkClearValue clear_color;
    clear_color = { 0.15f, 0.15f, 0.15f, 1.0f };
    
    // viewer_rs
    VkRenderPassBeginInfo viewer_renderpass_bi = {};
    viewer_renderpass_bi.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    viewer_renderpass_bi.pNext           = NULL;
    viewer_renderpass_bi.renderPass      = viewer_rs.renderpass;
    viewer_renderpass_bi.framebuffer     = vk.framebuffers[data.acquired_index];
    viewer_renderpass_bi.renderArea      = vk.scissor;
    viewer_renderpass_bi.clearValueCount = 1;
    viewer_renderpass_bi.pClearValues    = &clear_color;
    
    VkRenderPassBeginInfo overlay_renderpass_bi = {};
    overlay_renderpass_bi.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    overlay_renderpass_bi.pNext           = NULL;
    overlay_renderpass_bi.renderPass      = overlay_rs.renderpass;
    overlay_renderpass_bi.framebuffer     = vk.framebuffers[data.acquired_index];
    overlay_renderpass_bi.renderArea      = vk.scissor;
    overlay_renderpass_bi.clearValueCount = 0;
    overlay_renderpass_bi.pClearValues    = NULL;
    // ---
    
    
    //// --- --- --- Render resource management --- --- ---
    // --- write matrixes
    VkDescriptorBufferInfo ortho_buffer_info = {};
    ortho_buffer_info.buffer = data.matrix_buffer;
    ortho_buffer_info.offset = 0;
    ortho_buffer_info.range  = VK_WHOLE_SIZE;
    
    VkDescriptorBufferInfo view_buffer_info = {};
    view_buffer_info.buffer = viewer.view_buffer;
    view_buffer_info.offset = 0;
    view_buffer_info.range  = VK_WHOLE_SIZE;
    
    // viewer
    VkWriteDescriptorSet viewer_ortho_write = {};
    viewer_ortho_write.sType            = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    viewer_ortho_write.pNext            = NULL;
    viewer_ortho_write.dstSet           = viewer_rs.dset;
    viewer_ortho_write.dstBinding       = data.matrix_binding;
    viewer_ortho_write.dstArrayElement  = 0;
    viewer_ortho_write.descriptorCount  = viewer_rs.descset_count;
    viewer_ortho_write.descriptorType   = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    viewer_ortho_write.pImageInfo       = NULL;
    viewer_ortho_write.pBufferInfo      = &ortho_buffer_info;
    viewer_ortho_write.pTexelBufferView = NULL;
    
    VkWriteDescriptorSet viewer_view_write = {};
    viewer_view_write.sType            = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    viewer_view_write.pNext            = NULL;
    viewer_view_write.dstSet           = viewer_rs.dset;
    viewer_view_write.dstBinding       = 1;
    viewer_view_write.dstArrayElement  = 0;
    viewer_view_write.descriptorCount  = viewer_rs.descset_count;
    viewer_view_write.descriptorType   = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    viewer_view_write.pImageInfo       = NULL;
    viewer_view_write.pBufferInfo      = &view_buffer_info;
    viewer_view_write.pTexelBufferView = NULL;
    
    
    // overlay
    VkWriteDescriptorSet overlay_matrix_write = {};
    overlay_matrix_write.sType            = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    overlay_matrix_write.pNext            = NULL;
    overlay_matrix_write.dstSet           = overlay_rs.dset;
    overlay_matrix_write.dstBinding       = data.matrix_binding;
    overlay_matrix_write.dstArrayElement  = 0;
    overlay_matrix_write.descriptorCount  = overlay_rs.descset_count;
    overlay_matrix_write.descriptorType   = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    overlay_matrix_write.pImageInfo       = NULL;
    overlay_matrix_write.pBufferInfo      = &ortho_buffer_info;
    overlay_matrix_write.pTexelBufferView = NULL;
    // ---
    
    // --- write samplers
    VkDescriptorImageInfo overlay_sampler_image_info = {};
    overlay_sampler_image_info.sampler     = overlay_rs.fd->atlas_data.sampler;
    overlay_sampler_image_info.imageView   = overlay_rs.fd->atlas_data.imageview;
    overlay_sampler_image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    
    VkWriteDescriptorSet overlay_sampler_write = {};
    overlay_sampler_write.sType            = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    overlay_sampler_write.pNext            = NULL;
    overlay_sampler_write.dstSet           = overlay_rs.dset;
    overlay_sampler_write.dstBinding       = 1;
    overlay_sampler_write.dstArrayElement  = 0;
    overlay_sampler_write.descriptorCount  = overlay_rs.descset_count;
    overlay_sampler_write.descriptorType   = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    overlay_sampler_write.pImageInfo       = &overlay_sampler_image_info;
    overlay_sampler_write.pBufferInfo      = NULL;
    overlay_sampler_write.pTexelBufferView = NULL;
    
    
    VkDescriptorImageInfo viewer_sampler_image_info = {};
    viewer_sampler_image_info.sampler     = viewer.sampler;
    
    VkWriteDescriptorSet viewer_sampler_write = {};
    viewer_sampler_write.sType            = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    viewer_sampler_write.pNext            = NULL;
    viewer_sampler_write.dstSet           = viewer_rs.dset;
    viewer_sampler_write.dstBinding       = 2;
    viewer_sampler_write.dstArrayElement  = 0;
    viewer_sampler_write.descriptorCount  = 1;
    viewer_sampler_write.descriptorType   = VK_DESCRIPTOR_TYPE_SAMPLER;
    viewer_sampler_write.pImageInfo       = &viewer_sampler_image_info;
    viewer_sampler_write.pBufferInfo      = NULL;
    viewer_sampler_write.pTexelBufferView = NULL;
    // ---
    
    ODS("Currently ready: %d\n", viewer.current_ready_image_count);
    
    VkWriteDescriptorSet overlay_writes[] = { overlay_matrix_write, overlay_sampler_write };
    u32 overlay_write_count = sizeof(overlay_writes) / sizeof(overlay_writes[0]);
    vkUpdateDescriptorSets(vk.device, overlay_write_count, overlay_writes, 0, NULL);
    
    VkWriteDescriptorSet viewer_writes[] = { 
        viewer_ortho_write, viewer_view_write, viewer_sampler_write };
    u32 viewer_write_count  = sizeof(viewer_writes) / sizeof(viewer_writes[0]);
    vkUpdateDescriptorSets(vk.device, viewer_write_count, viewer_writes, 0, NULL);
    
    if(viewer.current_ready_image_count)
    {
        ODS("Writing %d descriptors!\n", viewer.current_ready_image_count);
        
        VkDescriptorImageInfo *image_infos = (VkDescriptorImageInfo *)calloc(viewer.current_ready_image_count, sizeof(VkDescriptorImageInfo));
        for(u32 i = 0; i < viewer.current_ready_image_count; i++)
        {
            ODS("- descriptor %d\n", i);
            image_infos[i].imageView   = viewer.thumbs[i].view;
            image_infos[i].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        }
        
        VkWriteDescriptorSet write = {};
        write.sType            = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        write.pNext            = NULL;
        write.dstSet           = viewer_rs.dset;
        write.dstBinding       = 3;
        write.dstArrayElement  = 0;  // <--- !!! IT WAS THIS ALL ALONG
        write.descriptorCount  = viewer.current_ready_image_count;
        write.descriptorType   = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
        write.pImageInfo       = image_infos;
        write.pBufferInfo      = NULL;
        write.pTexelBufferView = NULL;
        vkUpdateDescriptorSets(vk.device, 1, &write, 0, NULL);
    }
    
    // --- Record render commands ---
    // ---
    VkPipelineStageFlags wait_stage_mask = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    VkSubmitInfo render_queue_si = GenerateSubmitInfo(0, NULL,
                                                      &wait_stage_mask,
                                                      1, &vk.command_buffer,
                                                      1, &data.semaphore_execution_complete);
    EnterCriticalSection(&crit_sec);
    
    VkDeviceSize offset = 0;
    void *checkpoint_marker = calloc(1, sizeof(void *));
    
    vkBeginCommandBuffer(vk.command_buffer, &vk.cb_bi);
    
    // viewer
    vkCmdBindVertexBuffers(vk.command_buffer, data.vertex_binding, 1, &viewer_rs.vertex_buffer, &offset);
    vkCmdBindIndexBuffer(vk.command_buffer, viewer_rs.index_buffer, 0, VK_INDEX_TYPE_UINT32);
    vkCmdBindPipeline(vk.command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, viewer_rs.pipeline);
    if(viewer.current_ready_image_count)
        vkCmdBindDescriptorSets(vk.command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, viewer_rs.pipeline_layout, 0, viewer_rs.descset_count, &viewer_rs.dset, 0, NULL);
    vkCmdBeginRenderPass(vk.command_buffer, &viewer_renderpass_bi, VK_SUBPASS_CONTENTS_INLINE);
    if(viewer.current_ready_image_count)
        vkCmdDrawIndexed(vk.command_buffer, viewer_rs.index_count, 1, 0, 0, 0);
    vkCmdEndRenderPass(vk.command_buffer);
    
    // overlay
    vkCmdBindVertexBuffers(vk.command_buffer, data.vertex_binding, 1, &overlay_rs.vertex_buffer, &offset);
    vkCmdBindIndexBuffer(vk.command_buffer, overlay_rs.index_buffer, 0, VK_INDEX_TYPE_UINT32);
    vkCmdBindPipeline(vk.command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, overlay_rs.pipeline);
    vkCmdBindDescriptorSets(vk.command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, overlay_rs.pipeline_layout, 0, overlay_rs.descset_count, &overlay_rs.dset, 0, NULL);
    vkCmdBeginRenderPass(vk.command_buffer, &overlay_renderpass_bi, VK_SUBPASS_CONTENTS_INLINE);
    if(data.display_overlay)
        vkCmdDrawIndexed(vk.command_buffer, overlay_rs.index_count, 1, 0, 0, 0);
    vkCmdEndRenderPass(vk.command_buffer);
    
    vkEndCommandBuffer(vk.command_buffer);
    // ---
    
    
    // --- Render ---
    // ---
    
    vkQueueSubmit(vk.queue, 1, &render_queue_si, vk.fence_render_complete);
    
    ODS("Waiting on render fence\n");
    result = vkWaitForFences(vk.device, 1, &vk.fence_render_complete, VK_TRUE, UINT64_MAX);
    ODS("Render fence wait: %s\n", RevEnum(data.result_enum, result));
    if(result != VK_SUCCESS)
        ODS("Uh-oh, device lost\n");
    
    ODS("Resetting render fence\n");
    result = vkResetFences(vk.device, 1, &vk.fence_render_complete);
    ODS("Render fence reset: %s\n", RevEnum(data.result_enum, result));
    if(result != VK_SUCCESS)
        ODS("Uh-oh, device lost\n");
    
    LeaveCriticalSection(&crit_sec);
    // ---
}

void Present()
{
    EnterCriticalSection(&crit_sec);
    
    VkResult present_result;
    VkPresentInfoKHR queue_pi = {};
    queue_pi.sType              = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    queue_pi.pNext              = NULL;
    queue_pi.waitSemaphoreCount = 1;
    queue_pi.pWaitSemaphores    = &data.semaphore_execution_complete;
    queue_pi.swapchainCount     = 1;
    queue_pi.pSwapchains        = &vk.swapchain;
    queue_pi.pImageIndices      = &data.acquired_index;
    queue_pi.pResults           = &present_result;
    vkQueuePresentKHR(vk.queue, &queue_pi);
    
    ODS("Queue presentation: %s\n", RevEnum(data.result_enum, present_result));
    if(present_result != VK_SUCCESS)
        ODS("Uh-oh, device lost\n");
    
    LeaveCriticalSection(&crit_sec);
}

// ////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////                       MAIN CONTROLS ------ ------
// //////////////////////////////////////////////////////////////////////////////