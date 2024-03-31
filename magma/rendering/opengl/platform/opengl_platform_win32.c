#include "opengl_platform.h"

#if MG_PLATFORM_WINDOWS

#include <windows.h>
#include <glad/glad.h>

typedef struct mg_win32_handle_info
{
    HINSTANCE h_instance;
    HWND hwnd;
}
mg_win32_handle_info_t;

typedef struct mg_opengl_win32_platform_context
{
    HWND hwnd;
    HDC hdc;
    HGLRC hrc;
}
mg_opengl_win32_platform_context_t;

static mg_opengl_win32_platform_context_t context;

void mg_opengl_platform_initialize(mg_platform_t *platform)
{
    mg_win32_handle_info_t *handle = (mg_win32_handle_info_t*)platform->handle;
    context.hwnd = handle->hwnd;
    context.hdc = GetDC(context.hwnd);

    PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    INT format = ChoosePixelFormat(context.hdc, &pfd);
    SetPixelFormat(context.hdc, format, &pfd);

    context.hrc = wglCreateContext(context.hdc);
    wglMakeCurrent(context.hdc, context.hrc);

    gladLoadGL();
}

void mg_opengl_platform_shutdown(void)
{
    wglMakeCurrent(0, 0);
    wglDeleteContext(context.hrc);
    ReleaseDC(context.hwnd, context.hdc);
}

void mg_opengl_platform_swapbuffers(void)
{
    SwapBuffers(context.hdc);
}

#endif