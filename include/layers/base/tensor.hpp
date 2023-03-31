#pragma once
#ifndef TENSOR
#define TENSOR

#include <memory>
#include "shape.hpp"

class Tensor {
public:
    Shape shape;
    std::shared_ptr<float> host_data;
    Tensor();
    ~Tensor();
}
#endif