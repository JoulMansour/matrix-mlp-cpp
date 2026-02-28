## What’s inside
- `Matrix` – dynamic 2D float matrix with common operations (mul/add, transpose, vectorize, argmax, stream I/O).
- `Activation` – `relu` and `softmax`.
- `Dense` – a fully-connected layer: `activation(W * x + b)`.
- `MlpNetwork` – chains 4 Dense layers and returns:
  - predicted digit (`0–9`)
  - probability (max softmax value)
