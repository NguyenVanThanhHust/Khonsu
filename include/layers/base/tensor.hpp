#pragma once
#ifndef TENSOR
#define TENSOR

#include <memory>
#include "shape.hpp"

namespace khonsu{
    class Tensor {
    public:
        Shape shape;
        std::shared_ptr<float> host_data;
        Tensor();
        ~Tensor();
    }
}
#endif