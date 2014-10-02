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
        bool spammy = false;
        glob::srv.put("Hehe", "Hoho");
        //Let's have some fun here!!! :D
        while(true)
        {
            if(!strcmp(glob::srv.get("Hehe").c_str(), "Hoho"))
            {
                glob::srv.put("Hehe", "Haha");
            }
            else
            {
                glob::srv.put("Hehe", "Hoho");
            }
            glob::srv.put("Hoho! Haunty!", "x");
            if(!strcmp(glob::srv.get("hi").c_str(), "Magic!!!"))
            {
                glob::srv.put("x", "I'm Haunting You already!");
            }
            glob::srv.put("Time", dev::str::getTime());
            if(glob::srv.get("Spammy").size() != 0 && !spammy)
            {
                spammy = true;
                for(unsigned int i = 0; i < 16; i++)
                {
                    glob::srv.put(dev::math::random::random_hex_string(16), dev::math::random::random_hex_string(16));
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
    }
}
