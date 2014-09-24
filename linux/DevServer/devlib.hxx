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
#include <iterator>
#include <algorithm>
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

        std::string encryptAndDecryptString(const std::string input, const char key)
        {
            std::string tmp = input;
            if(input.length() != 0)
            {
                for(unsigned int i = 0; i < input.size(); i++)
                {
                    tmp[i] ^= key;
                }
            }
            return tmp;
        }

        std::vector<std::string> encryptAndDecryptString(const std::vector<std::string> input, const char key)
        {
            std::vector<std::string> out;
            for(unsigned int i = 0; i < input.size(); i++)
            {
                out.push_back(encryptAndDecryptString(input[i], key));
            }
            return out;
        }

        std::string swapCertainCharacters(std::string string, char search_char, char replace_char)
        {
            std::stringstream stringstream;
            for(unsigned int i = 0; i < string.size(); i++)
            {
                if(string[i] == search_char)
                {
                    stringstream << replace_char;
                }
                else
                {
                    stringstream << string[i];
                }
            }

            return stringstream.str();
        }

        std::string swapCertainCharactersEndl(std::string string)
        {
            std::stringstream stringstream;
            for(unsigned int i = 0; i < string.size(); i++)
            {
                if(string[i] == ' ')
                {
                    stringstream << std::endl;
                }
                else
                {
                    stringstream << string[i];
                }
            }

            return stringstream.str();
        }

        std::string swapCharacterWithString(std::string string, char search_char, std::string replace_string)
        {
            std::stringstream stringstream;
            for(unsigned int i = 0; i < string.size(); i++)
            {
                if(string[i] == search_char)
                {
                    stringstream << replace_string;
                }
                else
                {
                    stringstream << string[i];
                }
            }
            return stringstream.str();
        }

        std::vector<std::string> swapCharacterWithString(std::vector<std::string> input, char search_char, std::string replace_string)
        {
            std::vector<std::string> out;
            for(unsigned int i = 0; i < input.size(); i++)
            {
                out.push_back(swapCharacterWithString(input[i], search_char, replace_string));
            }
            return out;
        }

        std::string swapCertainCharactersMulti(std::string string, std::string search_string, std::string replace_string)
        {
            if(search_string.size() != replace_string.size())
            {
                std::cerr << "IN swapCertainCharactersMulti(), SEARCH_STRING AND REPLACE_STRING HAVE DIFFERENT VALUES" << std::endl;
            }

            std::string out = string;

            for(unsigned int i = 0; i < search_string.size(); i++)
            {
                out = swapCertainCharacters(out, search_string[i], replace_string[i]);
            }
            return out;
        }

        std::vector<std::string> swapCertainCharacters(std::vector<std::string> strings, char search_char, char replace_char)
        {
            std::vector<std::string> strings_out;
            for(unsigned int i = 0; i < strings.size(); i++)
            {
                strings_out.push_back(swapCertainCharacters(strings[i], search_char, replace_char));
            }

            return strings_out;
        }

        std::vector<std::string> swapCertainCharactersMulti(std::vector<std::string> strings, std::string search_string, std::string replace_string)
        {
            std::vector<std::string> strings_out;
            for(unsigned int i = 0; i < strings.size(); i++)
            {
                strings_out.push_back(swapCertainCharactersMulti(strings[i], search_string, replace_string));
            }

            return strings_out;
        }

        std::vector<char> stringToCharVector(std::string string)
        {
            std::vector<char> outputCharArray;
            for(unsigned int i = 0; i < string.size(); i++)
            {
                outputCharArray.push_back(string[i]);
            }
            return outputCharArray;
        }

        std::string charVectorToString(std::vector<char> charVector)
        {
            std::stringstream stringstream;
            for(unsigned int i = 0; i < charVector.size(); i++)
            {
                stringstream << charVector[i];
            }
            return stringstream.str();
        }

        std::string reverseString(std::string input)
        {
            std::stringstream stringstream;
            copy(input.rbegin(), input.rend(), std::ostream_iterator<char>(stringstream));
            return stringstream.str();
        }

        std::string trimString(std::string input)
        {
            std::stringstream stringstream;
            bool check = true;
            for(unsigned int i = 0; i < input.length(); i++)
            {
                if(check)
                {
                    if(!isspace(input[i]))
                    {
                        check = false;
                    }
                    else
                    {
                        check = true;
                    }
                }
                if(!check)
                {
                    stringstream << input[i];
                }
            }
            std::string newString = reverseString(stringstream.str());
            check = true;
            std::stringstream stringstream2;
            for(unsigned int i = 0; i < newString.length(); i++)
            {
                if(check)
                {
                    if(!isspace(newString[i]))
                    {
                        check = false;
                    }
                    else
                    {
                        check = true;
                    }
                }
                if(!check)
                {
                    stringstream2 << newString[i];
                }
            }
            return reverseString(stringstream2.str());
        }

#ifndef READ_LENGTH
#define READ_LENGTH 65535
#endif

        std::string cinGetLineWithSpaces()
        {
            std::stringstream out;
            char characterArrayBuffer[READ_LENGTH];
            for(unsigned int i = 0; i < READ_LENGTH; i++)
            {
                characterArrayBuffer[i] = ' ';
            }

            std::cin.getline(characterArrayBuffer, READ_LENGTH);

            for(unsigned int i = 0; i < READ_LENGTH; i++)
            {
                out << characterArrayBuffer[i];
            }

            return dev::str::trimString(out.str());
        }

        std::string formatMemorySize2(unsigned long long input)
        {
            std::string units[] = {"B", "KiB", "MiB", "GiB", "EiB"};
            double number = input;
            unsigned int i = 0;
            while(number > 1024)
            {
                i++;
                number /= 1024;
            }
            std::stringstream str;
            str << number << " " << units[i];
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
