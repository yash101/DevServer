#pragma once

//Whether to attempt to use OpenMP. This can offer several performance improevments, especially when processing large amounts of data!
//#define USE_OPENMP

//We are not using DLib GUI support, so we will disable it. This also removes the requirement for use to have libx11_dev
//If you are using the CMakeLists.txt that I provide, DO NOT DISABLE THIS. WILL CAUSE SERIOUS ERRORS!
#define DLIB_NO_GUI_SUPPORT

//Just print out a warning that you are disabling this! Don't worry!
#ifndef DLIB_NO_GUI_SUPPORT
#pragma warning("You may recieve tons of errors because you disaled DLIB_NO_GUI_SUPPORT!")
#endif

//Whether to prepopulate the RAMFs
#define PREPOPULATE_RAMFS

//This will cause a spam of information streamed to STDOUT. Qhis info is EXTREMELY detailed!
#define DETAILED_DEBUG

//This server allows you to build in a small program. It will run in a separate thread.
//This programmable area is located in userprgm.hxx.
#define RUN_USERPRGM

//Allow us to shut down the server via http://localhost:port/shdn
#define ENABLE_WEB_SHUTDOWN

//Allow this server to attempt to shut down other DevServers using the same port?
#define ALLOW_SHUTDOWN_MESSAGE

//Put a random number in the web interface. This is just for debugging purposes, so please disable this. There is a RNG function in this server anyways
#define DEBUG_RNG

//Whether to show the request information in the terminal window. Requires DETAILED_DEBUG
#define DEBUG_WEBINF

//Whether to enable the console or not
#define ENABLE_CONSOLE

//Whether to disable the file cache. This will only affect the autocache function.
//This is extremely useful when you are working on the web interface, which is not
//compiled in! Just disable the cache and code edits will update instantly.
//Make sure to disable this once done to decrease latency by a lot!
#define DISABLE_CACHE

//==============================[DO NOT COMMENT OUT]==============================
//File Variables! PLEASE ADD TO FILECACHE.DAT FOR MAX PERFORMANCE!
#define homepage "input.html"
#define monitor_form "monitor.htx"
#define inject_form "inject.htx"
#define css_file "style.css"
#define js_file "javascript.js"
#define inet_png "inet.png"
#define net_png "net.png"

//Other variables
const static long SERVER_MUTEX_TIMEOUT = 1000;

//=====================[BEHIND THE SCENE (not really :D)]=========================
