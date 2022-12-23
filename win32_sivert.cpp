#include <windows.h>

#define internal static
#define local_persist static
#define global_variable static

internal void 
ResizeDIBSection(){
}

// Temporary global variable
global_variable bool GlobalRunning = true;

LRESULT CALLBACK
MainWindowCallback(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
    LRESULT Result = 0;

    switch (Message)
    {
    case WM_SIZE:
    {   RECT ClientRect;
        BOOL GetClientRect(Window, &ClientRect)
        int Width = ClientRect.right - Paint.rcPaint.left;
        int Height = ClientRect.bottom - Paint.rcPaint.top;
        ResizeDIBSection(Width, Height);
        OutputDebugStringA("WM_SIZE\n");
    }
    break;

    case WM_DESTROY:
    {
         // TODO: Message handler to user 
        // OutputDebugStringA("WM_DESTROY\n");
        GlobalRunning = false;
    }
    break;

    case WM_CLOSE:
    {
         // TODO: Message handler to user 
        // OutputDebugStringA("WM_CLOSE\n");
        GlobalRunning = false;
    }
    break;

    case WM_ACTIVATEAPP:
    {
        OutputDebugStringA("WM_ACTIVATEAPP\n");
    }
    break;

    case WM_PAINT:
    {
        PAINTSTRUCT Paint;
        HDC DeviceContext = BeginPaint(Window, &Paint);
        int X = Paint.rcPaint.left;
        int Y = Paint.rcPaint.top;
        LONG Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
        LONG Width = Paint.rcPaint.right - Paint.rcPaint.left;
        local_persist DWORD Operation = WHITENESS;
        PatBlt(DeviceContext, X, Y, Width, Height, WHITENESS);
        EndPaint(Window, &Paint);
    }
    break;

    default:
    {
        // OutputDebugStringA("default\n");
        Result = DefWindowProc(Window, Message, WParam, LParam);
    }
    break;
    }
    return (Result);
}

int CALLBACK
WinMain(HINSTANCE Instance,
        HINSTANCE PrevInstance,
        LPSTR CmdLine,
        int ShowCode)
{

    WNDCLASS WindowClass = {};
    WindowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    WindowClass.lpfnWndProc = MainWindowCallback;
    WindowClass.hInstance = Instance;
    WindowClass.lpszClassName = "SievertWindowClass";
    // WindowClass.hIcon;
    // WindowClass.hCursor;

    if (RegisterClass(&WindowClass))
    {
        // Create a window.
        HWND WindowHandle = CreateWindowExA(
            0,
            WindowClass.lpszClassName,
            "Sievert",
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            0,
            0,
            Instance,
            0);

        if (WindowHandle)
        {
            GlobalRunning = true;
            while(GlobalRunning)
            {
                MSG Message;
                BOOL MessageResult = GetMessage(&Message, 0, 0, 0);
                if (MessageResult > 0)
                {
                    // Translate keyboard messages
                    TranslateMessage(&Message);
                    DispatchMessage(&Message);
                }
                else
                {
                    // break out of infinite for loop.
                    break;
                }
            }
        }
        else
        {
            // logging
        }
    }
    else
    {
        // logging
    }

    return (0);
}
