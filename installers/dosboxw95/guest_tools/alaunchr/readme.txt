This application can be placed in Startup directory inside virtual/emulated machine.
It will check if a file launchit.cfg (or other pre-configured name) is located in D: (or other drive) and if yes, then it will launch an application specified in launchit.cfg file. It can also turn the computer off after execution is completed.

Create config file for auto-launcher.
Place it next to launcher executable or in %WINDIR%\alaunchr.cfg

Example contents:

D:
launchit.cfg
SHUTDOWN\

D: is working directory
launchit.cfg is the name of file containing name of executable to launch (both located in working directory)
SHUTDOWN (optional) means the computer will turn off automatically after launched app is closed (only for Win 9x).