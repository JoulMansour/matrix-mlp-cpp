#include "Dense.h"

Dense::Dense(const Matrix &weights, const Matrix &bias,
    const ActivationFunction &activation_function) :
weights{weights}, bias{bias},
activation_function{activation_function} {}

Matrix Dense::get_weights() const {
    return weights;
}

Matrix Dense::get_bias() const {
    return bias;
}

ActivationFunction Dense::get_activation() const {
    return activation_function;
}


Matrix Dense::operator()(const Matrix &input) const {
    return activation_function(weights*input+bias);
}



