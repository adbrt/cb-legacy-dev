#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>

#include "ini.h"

std::string iniPath = "C:\\WINDOWS\\SYSTEM.ini";
bool quiet = true;

int main(int argc, char **argv)
{

    if (argc <= 1)
    {
        std::cerr << "Usage: dbox/ps2 [filename=C:\\WINDOWS\\SYSTEM.ini]  " << std::endl;
        return 1;
    }
    if (argc >= 2)
    {

        if (argc == 3) iniPath = argv[2];
        std::string arg = argv[1];

        // Read from INI file
        mINI::INIFile file(iniPath);
        mINI::INIStructure ini;
        file.read(ini);

        // Check values
        std::string value = ini.get("boot").get("mouse.drv");
        if (!quiet) std::cout << std::string("Current [boot]mouse.drv = ") + value << std::endl;

        value = ini.get("boot.description").get("mouse");
        if (!quiet) std::cout << std::string("Current [boot.description]mouse.drv = ") + value << std::endl;

        value = ini.get("386Enh").get("mouse");
        if (!quiet) std::cout << std::string("Current [386Enh]mouse = ") + value << std::endl;


        if ( std::string(arg).find(std::string("dbox")) != std::string::npos )
        {
            // Update values
            ini["boot"]["mouse.drv"] = "dboxmpi.drv";
            ini["boot.description"]["mouse.drv"] = "DOSBox-X Mouse Pointer Integration";
            ini["386Enh"]["mouse"] = "";

            if (!quiet)
            {
                std::cout << std::endl;
                std::cout << "New [boot]mouse.drv = dboxmpi.drv" << std::endl;
                std::cout << "New [boot.description]mouse.drv = DOSBox-X Mouse Pointer Integration" << std::endl;
                std::cout << "New [386Enh]mouse = " << std::endl;
            }

            file.write(ini);
        }

        if ( std::string(arg).find(std::string("ps2")) != std::string::npos )
        {
            // Update values
            ini["boot"]["mouse.drv"] = "mouse.drv";
            ini["boot.description"]["mouse.drv"] = "Standard mouse";
            ini["386Enh"]["mouse"] = "*vmouse, msmouse.vxd";

            if (!quiet)
            {
                std::cout << std::endl;
                std::cout << "New [boot]mouse.drv = mouse.drv" << std::endl;
                std::cout << "New [boot.description]mouse.drv = Standard mouse" << std::endl;
                std::cout << "New [386Enh]mouse = *vmouse, msmouse.vxd" << std::endl;
            }

            file.write(ini);
        }

    }


}
