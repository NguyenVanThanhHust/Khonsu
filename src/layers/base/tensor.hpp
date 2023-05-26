#pragma once
#ifndef TENSOR_H
#define TENSOR_H

#include <memory>

namespace khonsu{
    class Tensor {
    public:
        std::shared_ptr<float> host_data;
        Tensor();
        ~Tensor();
    };
};
#endif