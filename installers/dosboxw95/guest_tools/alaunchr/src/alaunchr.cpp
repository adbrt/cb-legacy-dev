#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <string>
#include <fstream.h>
#include <algorithm>
#include <tlhelp32.h>

#define IDT_TIMER1 1001

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("AutoAppLauncher");

PROCESS_INFORMATION pi;

bool shutdownOnEnd = false;
bool shutdownOnlyLegacyOS = true; // Shutdown only for Win9x and < XP

bool pauseEnd = false;

bool timerOn = false;

DWORD dwVersion = 0;
DWORD dwMajorVersion = 0;
DWORD dwMinorVersion = 0;
DWORD dwBuild = 0;


std::string globalConfigFile = std::string(getenv("WINDIR")) + "\\alaunchr.cfg";
std::string cfgFile = "";
std::string startupPath = "";

std::string ReadNthLine(const std::string& filename, int N)
{
   std::ifstream in(filename.c_str());

   std::string s;
   //for performance
   s.reserve(1024);

   //skip N lines
   for(int i = 0; i < N; ++i)
       std::getline(in, s);

   std::getline(in,s);
   return s;
}

BOOL FileExists(LPCTSTR szPath)
{
  DWORD dwAttrib = GetFileAttributes(szPath);

  return (dwAttrib != -1 &&
         !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}


bool CheckOneInstance()
{

    HANDLE  m_hStartEvent = CreateEventA( NULL, FALSE, FALSE, "Global\\BALAUNCR" );

    if(m_hStartEvent == NULL)
    {
    CloseHandle( m_hStartEvent );
        return false;
    }


    if ( GetLastError() == ERROR_ALREADY_EXISTS ) {

        CloseHandle( m_hStartEvent );
        m_hStartEvent = NULL;
        // already exist
        // send message from here to existing copy of the application
        return false;
    }
    // the only instance, start in a usual way
    return true;
}

bool startup(LPSTR lpApplicationName, PROCESS_INFORMATION &pi)
{
   STARTUPINFO si;
    //PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

    // Start the child process.
    if( !CreateProcessA( NULL,   // No module name (use command line)
        lpApplicationName,        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        startupPath.c_str(), // Start in...
        &si,            // Pointer to STARTUPINFO structure
        &pi )           // Pointer to PROCESS_INFORMATION structure
    )
    {
        // Failed
        return false;
    }

    // Wait until child process exits.
    //WaitForSingleObject( pi.hProcess, INFINITE );

    // Close process and thread handles.
    //CloseHandle( pi.hProcess );
    //CloseHandle( pi.hThread );
    return true;
}


int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{



    /*
    // Kill older process if needed (when abort option is passed as an argument)
    if ( strstr(lpszArgument, "abort") || strstr(lpszArgument, "ABORT"))
    {
        PostQuitMessage (0);
    }
    */


    // Don't proceed if there is more than one instance of app
    if (!CheckOneInstance())
    {

        pauseEnd = true;

        int msgboxID = MessageBox(
        NULL,
        (LPCSTR) "Launcher is already running",
        (LPCSTR)"Launcher already running",
        MB_ICONWARNING | MB_OK
        );

        switch (msgboxID)
        {
        case IDOK:

            pauseEnd = false;
            PostQuitMessage (0); // Quit if no success launching
            break;
        }


        PostQuitMessage (0);
    }

    // Get the Windows version.
    dwVersion = GetVersion();
    dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
    dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));

    // Get the build number.

    if (dwVersion < 0x80000000)
        dwBuild = (DWORD)(HIWORD(dwVersion));


    // Load global application config file
    // First line = working drive/directory path (example: D: )
    startupPath = ReadNthLine(globalConfigFile,0);

    if (startupPath == "")
    {
        globalConfigFile = "alaunchr.cfg";
        startupPath = ReadNthLine(globalConfigFile,0);
    }

    if (startupPath == "")
    {
        pauseEnd = true;

        int msgboxID = MessageBox(
        NULL,
        (LPCSTR) "This application can be used as auto-launcher for other applications (useful for auto-starting applications from VM shared drives).\n"
                                  "Place it in startup directory to use it when Windows starts."
                                  "\n\nCreate config file for auto-launcher.\nPlace it next to launcher executable or in %WINDIR%\\alaunchr.cfg.\n"
                                  "Example contents:\n\nD:\n\launchit.cfg\nSHUTDOWN\n\nD: is working directory\n"
                                  "launchit.cfg is the name of file containing name of executable to launch (both located in working directory)\n"
                                  "SHUTDOWN (optional) means the computer will turn off automatically after launched app is closed (only for Win 9x).",
        (LPCSTR)"Auto-launcher",
        MB_ICONWARNING | MB_OK
        );

        switch (msgboxID)
        {
        case IDOK:

            pauseEnd = false;
            PostQuitMessage (0); // Quit if no success launching
            break;
        }

    }


    // Read app startup path from global config file
    startupPath = ReadNthLine(globalConfigFile,0);
    if (startupPath == "") PostQuitMessage (0); // Quit if it was not there

    // Read app config file name from global config file
    cfgFile = ReadNthLine(globalConfigFile,1);

    if (cfgFile == "") PostQuitMessage (0); // Quit if it was not there

    cfgFile = startupPath + "\\" + cfgFile;

    // Exit if file is not found on drive
    if (!FileExists(cfgFile.c_str()))
    {
        PostQuitMessage (0);
        return 0;
    }

    // Read shutdown setting in global configuration file
    std::string shouldShutdown = ReadNthLine(globalConfigFile,2);
    shouldShutdown.erase(std::remove_if(shouldShutdown.begin(), shouldShutdown.end(), ::isspace), shouldShutdown.end());
    if (shouldShutdown == "SHUTDOWN" || shouldShutdown == "shutdown") shutdownOnEnd = true;
    else shutdownOnEnd = false;



    // Read app config file
    std::string cmdLine = ReadNthLine(cfgFile,0);
    if (cmdLine == "") PostQuitMessage (0); // Quit if command was not there


    // Override shutdown setting in app configuration file
    std::string arg = ReadNthLine(cfgFile,1);
    arg.erase(std::remove_if(arg.begin(), arg.end(), ::isspace), arg.end());
    if (arg == "SHUTDOWN" || arg == "shutdown") shutdownOnEnd = true;
    if (arg == "NOSHUTDOWN" || arg == "noshutdown") shutdownOnEnd = true;




    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("AutoAppLauncher"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           200,                 /* The programs width */
           200,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    //ShowWindow (hwnd, nCmdShow);

    std::string cmdToLaunch = startupPath + "\\" + cmdLine;


    bool forceShutdown = false;

    std::string cmd = cmdLine;
    cmd.erase(std::remove_if(cmd.begin(), cmd.end(), ::isspace), cmd.end());
    if (cmd == "SHUTDOWN" || cmd == "shutdown")
    {
        shutdownOnEnd = false;
        pauseEnd = true;

        if (shutdownOnlyLegacyOS)
        {
            if (dwMajorVersion >= 3 && dwMajorVersion <= 5) WinExec("C:\\WINDOWS\\RUNDLL32.EXE user.exe,ExitWindows",0);
        }
        else WinExec("C:\\WINDOWS\\RUNDLL32.EXE user.exe,ExitWindows",0);
        PostQuitMessage(0);

        forceShutdown = true;

    }
    else timerOn = true;


    if (arg == "NOWORKINGDIR" || arg == "noworkingdir")
    {
        cmdToLaunch = cmdLine;
        startupPath = "C:\\";
    }


    if (!forceShutdown && cmdToLaunch != "" && !startup((char*) cmdToLaunch.c_str(), pi))
    {

        pauseEnd = true;

        int msgboxID = MessageBox(
        NULL,
        (LPCSTR) (std::string("Unable to execute file:\n") + cmdToLaunch).c_str(),
        (LPCSTR)"Launcher error",
        MB_ICONWARNING | MB_OK
        );

        switch (msgboxID)
        {
        case IDOK:

            pauseEnd = false;
            PostQuitMessage (0); // Quit if no success launching
            break;
        }


    }









SetTimer(hwnd,             // handle to main window
    IDT_TIMER1,            // timer identifier
    200,                 // interval in milliseconds
    (TIMERPROC) NULL);     // no timer callback


    //PostQuitMessage (0);


    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;

        case WM_TIMER:
            switch (wParam)
            {
                case IDT_TIMER1:

                    if (timerOn)
                    {
                        // process the timer
                        // Check if launched application is still working
                        DWORD exitCode;
                        GetExitCodeProcess(pi.hProcess, &exitCode);
                        if (exitCode != STILL_ACTIVE && !pauseEnd)
                        {
                            if (shutdownOnEnd)
                            {
                                if (shutdownOnlyLegacyOS)
                                {
                                    if (dwMajorVersion >= 3 && dwMajorVersion <= 5) WinExec("C:\\WINDOWS\\RUNDLL32.EXE user.exe,ExitWindows",0);
                                }
                                else WinExec("C:\\WINDOWS\\RUNDLL32.EXE user.exe,ExitWindows",0);
                            }

                            PostQuitMessage(0);
                        }
                    }


                    return 0;
            }


        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
