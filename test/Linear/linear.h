#ifndef LINEAR_LAYER_H
#define LINEAR_LAYER_H
#include <iostream>
#include <random>
#include <string>

class Tensor 
{
public:
    
};

class LinearLayer
{
    int input_dim=1, output_dim=1;
    std::string layer_name;
    float *weight, *bias;

public:
    LinearLayer(int input_dim_, int output_dim_, std::string layer_name_="linear");
    ~LinearLayer();
    forward();
    backward();
    update_params();
};

#endif