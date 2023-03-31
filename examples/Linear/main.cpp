#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector> 
#include <sstream>
#include <algorithm>
#include "yaml-cpp/yaml.h"

using std::cout;
using std::cin;
using std::endl;

struct sample {
    float x1;
    float x2;
    int y;
};


class LinearLayer {
public:
    std::shared_ptr<float> weight=nullptr;
    void forward(float );
    void backward();
}
int main(int argc, char** argv)
{
    cout<<"Loading config"<<endl;
    YAML::Node config = YAML::LoadFile("../config.yaml");
    std::string data_file = config["path"].as<std::string>();
    float num_positive = config["num_positive"].as<float>();
    float num_negative = config["num_negative"].as<float>();

    std::ifstream MyReadFile(data_file);
    std::string line;

    cout<<"Loading data"<<endl;
    std::vector<sample> positive_samples;
    std::vector<sample> negative_samples;

    int line_index = 0;
    std::string space_delimeter = " ";

    if (MyReadFile.is_open())
    {
        std::string temp_string;
        float temp_value;
        while ( getline (MyReadFile, line) )
        {
            std::istringstream temp_ss(line);
            sample current_sample;
            int temp_index=0;
            while (temp_ss>>temp_string)
            {
                temp_value = std::stof(temp_string);
                if(temp_index == 0){
                    current_sample.x1 = temp_value;
                    temp_index++;
                }
                else{
                    current_sample.x2 = temp_value;
                }
            }
            
            if (line_index < num_positive){
                current_sample.y = 1;
                positive_samples.push_back(current_sample);
            }
            else {
                current_sample.y = -1;
                negative_samples.push_back(current_sample);
            }
            line_index++;
        }
        MyReadFile.close();
    }

    for (auto sample: positive_samples)
    {
        cout<<"x1: "<<sample.x1<<" x2: "<<sample.x2<<" y: "<<sample.y<<endl;
    }
    for (auto sample: negative_samples)
    {
        cout<<"x1: "<<sample.x1<<" x2: "<<sample.x2<<" y: "<<sample.y<<endl;
    }

    
    return 0;
}