#pragma once

////includes

//STL includes. Basics to use
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <cmath>
#include <thread>
#include <mutex>
#include <vector>
#include <map>
#include <unordered_map>
#include <stdlib.h>

//Configuration Data
#include "config.hxx"

//Let's try to get OpenMP!
#ifdef USE_OPENMP
#include <omp.h>
#endif

//DLib Includes
#include "dlib/server.h"
#include "dlib/threads.h"
#include "dlib/iosockstream.h"
#include "dlib/logger.h"
#include "dlib/sockets.h"

#include "devlib.hxx"

//Program Includes
//This header just contains constants, etc.
#include "globals.hxx"
//This contains the DevFileSystem
#include "filesystem.hxx"
//This is the actual web server!
#include "server.hxx"
//This is the program launcher
#include "load.hxx"
//Contains the constants used by the program
#include "config.hxx"
//user program
#ifdef RUN_USERPRGM
#include "userprgm.hxx"
#endif
#include "termserv.hxx"

#ifdef _WIN32
#define WINDOWS
#endif
#ifdef _WIN64
#define WINDOWS
#endif
#define WINDOWS
//To find memory leaks
#ifdef WINDOWS
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#endif