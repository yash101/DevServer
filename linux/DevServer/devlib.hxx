#pragma once
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
#include <time.h>
#include "stdio.h"

namespace dev
{
    namespace str
    {
        std::string toLower(std::string line)
        {
            std::string tmp = line;
            std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
            return tmp;
        }

        std::string toUpper(std::string line)
        {
            std::string tmp = line;
            std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);
            return tmp;
        }

        //Input: [X. Y. Z], [y] Output: [Y. Z]
        std::string stristr(std::string line, std::string search)
        {
            std::string tmpx = toLower(line);
            std::string tmpy = toLower(search);

            unsigned int index = tmpx.find(search.c_str());

            return line.substr(index, line.size());
        }

        char charAt(std::string input, unsigned int index)
        {
            return input[index];
        }

        bool compareTo(std::string aString, std::string anotherString)
        {
            return !strcmp(aString.c_str(), anotherString.c_str());
        }

        bool compareToIgnoreCase(std::string aString, std::string anotherString)
        {
            return !strcmp(toLower(aString).c_str(), toLower(anotherString).c_str());
        }

        unsigned int contains(std::string content, std::string search)
        {
            if (search.size() > content.size())
            {
                return -1;
            }
            else
            {
                for (unsigned int i = 0; i < content.size() - search.size(); i++)
                {
                    if (compareTo(search, content.substr(i, i + search.size())))
                    {
                        return i;
                    }
                }
            }
            return -1;
        }

        unsigned int indexOf(std::string input, char ch)
        {
            for (unsigned int i = 0; i < input.size(); i++)
            {
                if (input[i] == ch)
                {
                    return i;
                }
            }
            return -1;
        }

        unsigned int indexOf(std::string input, char ch, unsigned int fromIndex)
        {
            if (fromIndex > input.size())
            {
                return -1;
            }

            for (unsigned int i = fromIndex; i < input.size(); i++)
            {
                if (input[i] == ch)
                {
                    return i;
                }
            }
            return -1;
        }

        bool empty(std::string input)
        {
            if (input.size() == 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        template<typename T>
        std::string cast_to_string(T input)
        {
            std::stringstream str;
            str << input;
            return str.str();
        }
        std::string getTime()
        {
            std::stringstream str;
            time_t rawtime;
            tm* timeinfo;

            time(&rawtime);
            timeinfo = localtime(&rawtime);
            str << asctime(timeinfo);
            return str.str();
        }
    }

    namespace math
    {
        namespace random
        {
            template<typename T>
                T random(T min, T max)
                {
                    T maxx = min - max;
                    T x = (T)rand() % maxx + min;

                    return x;
                }

            char random_hex_char()
            {
                unsigned int gen = dev::math::random::random(0, 15);
                char array[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
                return array[gen];
            }

            std::string random_hex_string(unsigned int length)
            {
                std::stringstream str;
                for(unsigned int i = 0; i < length; i++)
                {
                    str << dev::math::random::random_hex_char();
                }
                return str.str();
            }
        }
    }
}
