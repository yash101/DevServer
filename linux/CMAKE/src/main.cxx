#include "preprocessor.hxx"

inline bool start_server()
{
    try
    {
        glob::srv.start_async();
        return true;
    }
    catch(std::exception& e)
    {
        std::cout << "Failed to launch the server!" << std::endl;
        return false;
    }
}

#ifdef ALLOW_SHUTDOWN_MESSAGE
inline void shutdown_server()
{
    try
    {
        dlib::iosockstream sock("localhost:" + dlib::cast_to_string(glob::server_port));
        sock << "GET /force_shdn HTTP/1.0\r\n\r\n";
        while(sock.get() != EOF)
        {
            //Just ignore everything. We probably won't be getting anything anyways!
        }
    }
    catch(std::exception& e)
    {
        //This means that there is no server to shut down!
        std::cout << e.what() << std::endl;
    }
}
#endif

void server()
{
#ifdef ALLOW_SHUTDOWN_MESSAGE
    //Try to create a connection on localhost:same port and send a polite shutdown signal. This
    //signal will be read by the server and std::terminate() will be caused. This will cause a program
    //crash, but we don't care. That means the program is running properly!
    shutdown_server();
#endif

    //Try to start the server. If this fails, that means there is a problem. We call terminate() and crash
    //the program. This is an actual crash!
    if(!start_server())
    {
        std::cout << "Failed at launching server!" << std::endl;
        std::terminate();
    }
}

//This function is a bit cheaty. It allows me to spawn the thread to run the userprgm without too much pain!
#ifdef RUN_USERPRGM
void userprgtm_launcher()
{
    prgm::launch();
}
#endif

#ifdef ENABLE_CONSOLE
void console()
{
    std::cout << "Welcome to the DevServer Console! Type \"help\" for assistabce!" << std::endl;
    while(true)
    {
        std::cout << "$ " << std::endl;
        std::string cmd = dev::str::toLower(dev::str::cinGetLineWithSpaces());
        if(!strcmp(cmd.c_str(), "help"))
        {
            std::cout << "Help: No commands enabled yet!" << std::endl;
            continue;
        }

        if(!strcmp(cmd.c_str(), "add"))
        {
            std::cout << "Add: Enter Key:" << std::endl;
            std::string key = dev::str::cinGetLineWithSpaces();
            if(key.size() == 0)
            {
                std::cout << "Sorry! You entered an invalid key! [" << key << "]!" << std::endl;
                continue;
            }
            std::cout << "Add: Enter Value:" << std::endl;
            std::string value = dev::str::cinGetLineWithSpaces();
            if(value.size() != 0)
            {
                glob::srv.put(key, value);
                std::cout << "Success!" << std::endl;
            }
            else
            {
                std::cout << "Sorry! You entered an invalid value! [" << value << "]!" << std::endl;
            }
            continue;
        }

        std::cout << "Syntax Error: Unknown command: [" << cmd << "]! Type \"help\" to get help!" << std::endl;
    }
}
#endif

void program()
{
    //Load the program! This loads all assets, etc.
    prog::load();
    //Set the listening port. To change this, you must change the config option and then recompile! The config option is located in globals.hxx
    glob::srv.set_listening_port(glob::server_port);
    //If we want to run the userprgm, do this. Otherwise, don't even compile it!
#ifdef RUN_USERPRGM
    //Spawn the thread
    std::thread userprgm(userprgtm_launcher);
    //Detach it so it can run without interruption
    userprgm.detach();
#endif
    //Finally, we launch the server!
    server();
#ifdef ENABLE_CONSOLE
    console();
#else
#ifdef DETAILED_DEBUG
    std::cout << "Console Disabled!" << std::endl;
#endif
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(300));
    }
#endif
}

//Main function. Called upon program launch
int main(int argc, char* argv[])
{
    program();
    //The code below keeps the main thread just waiting. Quite pointless and crappy!
//    std::thread prgm(program);

//    while(true)
//    {
//        std::this_thread::sleep_for(std::chrono::seconds(300));
//    }

    return 0;
}
