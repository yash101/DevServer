#pragma once
//Wither to attempt to use OpenMP. This can offer several performance improevments, especially when processing large amounts of data!
#define USE_OPENMP
//We are not using DLib GUI support, so we will disable it. This also removes the requirement for use to have libx11_dev
#define DLIB_NO_GUI_SUPPORT
//Whether to prepopulate the RAMFs
#define PREPOPULATE_RAMFS
//This will cause a spam of information streamed to STDOUT. Qhis info is EXTREMELY detailed!
#define DETAILED_DEBUG
//This server allows you to build in a small program. It will run in a separate thread.
//This programmable area is located in userprgm.hxx.
#define RUN_USERPRGM
//Run as a daemon?
#define DAEMONIZE
//Allow us to shut down the server via http://localhost:port/shdn
#define ENABLE_WEB_SHUTDOWN
//Allow this server to attempt to shut down other DevServers using the same port?
#define ALLOW_SHUTDOWN_MESSAGE
//Put a random number in the web interface. This is just for debugging purposes, so please disable this. There is a RNG function in this server anyways
#define DEBUG_RNG

//=====================[BEHIND THE SCENE (not really :D)=========================
