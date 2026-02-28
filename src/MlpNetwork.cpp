#include "MlpNetwork.h"

MlpNetwork::MlpNetwork(const Matrix *weights, const Matrix *bias) :
r1{Dense(weights[0], bias[0], activation::relu)},
r2{Dense(weights[1], bias[1], activation::relu)},
r3{Dense(weights[2], bias[2], activation::relu)},
r4{Dense(weights[3], bias[3], activation::softmax)} {}


digit MlpNetwork::operator()(const Matrix& input) const{
    Matrix temp(input);
    temp.vectorize();
    Matrix output = r4(r3(r2(r1(temp))));
    int max_index = output.argmax();
    float max_value = output[max_index];
    digit result;
    result.value = max_index;
    result.probability = max_value;
    return result;
}



