#pragma once
#include "preprocessor.hxx"
namespace prgm
{
    //This function is launched in a separate thread! Put your code in here!
    //You can access the DevServer from here too! Not just that, but it is much
    //more efficient because the server API does not use networking!

    //Make sure to properly link/etc all libraries and include them. Otherwise, nothing will compile!
    void launch()
    {
        //Let's have some fun here!!! :D
        while(true)
        {
            glob::srv.put("Hoho! Haunty!", "x");
            if(!strcmp(glob::srv.get("hi").c_str(), "Magic!!!"))
            {
                glob::srv.put("x", "I'm Haunting You already!");
            }
            glob::srv.put("Time", dev::str::getTime());
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        }
    }
}
