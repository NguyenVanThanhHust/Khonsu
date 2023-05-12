#include "linear.h"

LinearLayer::LinearLayer(int input_dim_, int output_dim_, std::string layer_name_="linear")
{
    input_dim = input_dim_;
    output_dim = output_dim_;
    layer_name = layer_name_;
    weight = new float[input_dim*output_dim];
    bias = new float[1*output_dim];
};

~LinearLayer::LinearLayer()
{
    delete[] weight;
    delete[] bias;
};

LinearLayer::forward();
LinearLayer::backward();
LinearLayer::update_params();