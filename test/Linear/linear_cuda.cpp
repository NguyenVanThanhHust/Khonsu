#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector> 
#include <sstream>
#include <algorithm>
#include <cassert> 
#include <random>
#include <cmath>

#include "yaml-cpp/yaml.h"

using std::cout;
using std::cin;
using std::endl;

struct Tensor {
    std::shared_ptr<float> weight;
}

struct sample {
    float x1;
    float x2;
    int y;
};


class LinearLayer {
public:
    std::shared_ptr<float> host_weight=nullptr;
    LinearLayer(std::vector<int> _shape);
    ~LinearLayer();
    Tensor& forward(Tensor& input);
    Tensor& backward(Tensor& output);
}


LinearLayer::LinearLayer(std::vector<int> _shape)
{
    std::random_device device_random_;
    std::default_random_engine generator_(device_random_());

    std::assert(_shape.size() == 2, "currently, accept only MxN matrix to test")
    shape = _shape;
    std::normal_distribution<> distribution_x(0.0, 0.5);
    std::normal_distribution<> distribution_y(0.0, 0.5);

    
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

    // Define layer in here
    std::vector<int> shape{2, 6};
    LinearLayer linearLayer = LinearLayer(shape);
    return 0;
}