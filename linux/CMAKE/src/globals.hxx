#pragma once
#include "preprocessor.hxx"
#include "filesystem.hxx"

namespace glob
{
    //Which port should the server run on?
    static unsigned int server_port = 2014;
    //How many threads should OpenMP try to use. This really only matters wherever I use OpenMP
	static unsigned int openmp_thread_count = 4;
    //Should I automatically populate "openmp_thread_count" at launch with the detected number of cores on your system
    //RECOMMENDED
	static bool use_hardware_concurrency_count_openmp = true;
    //Where should I pull the preload file database from?
    static std::string file_list = "filecache.dat";
    //This contains the info from the file, with the name in "file_list". It is what I use to populate the Database!
    static std::vector<std::string> preload_db;
    //This holds all the arguments sent to the server before launch
    static std::vector<std::string> arguments;
}
