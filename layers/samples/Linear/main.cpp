#pragma once
#include <iostream>
#include <fstream>
#include <string> 
#include "yaml-cpp/yaml.h"

using std::cout;
using std::cin;
using std::endl;

int main(int argc, char** argv)
{
    YAML::Node config = YAML::LoadFile("../config.yaml");
    std::string data_file = config["path"].as<std::string>();

    std::ifstream MyReadFile(data_file);
    std::string line;
    if (MyReadFile.is_open())
    {
        while ( getline (MyReadFile,line) )
        {
        cout << line << '\n';
        }
        MyReadFile.close();
    }
    return 0;
}