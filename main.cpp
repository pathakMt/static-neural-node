#include <iostream>
#include "matrix.hpp"
using namespace std;

constexpr bool test_multiply() noexcept {
    nn::matrix<float, 2, 3> a{};
    a(0U, 0U) = 1.0F; a(0U, 1U) = 2.0F; a(0U, 2U) = 3.0F;
    a(1U, 0U) = 4.0F; a(1U, 1U) = 5.0F; a(1U, 2U) = 6.0F;

    nn::matrix<float, 3, 2> b{};
    b(0U, 0U) = 7.0F;  b(0U, 1U) = 8.0F;
    b(1U, 0U) = 9.0F;  b(1U, 1U) = 10.0F;
    b(2U, 0U) = 11.0F; b(2U, 1U) = 12.0F;

    const auto c = a * b;

    return (c(0U, 0U) == 58.0F) && (c(0U, 1U) == 64.0F) && (c(1U, 0U) == 139.0F) && (c(1U, 1U) == 154.0F);   //computed by hand
}

constexpr bool test_add() noexcept {
    nn::matrix<float, 2, 2> a{};
    a(0U, 0U) = 1.0F; a(0U, 1U) = 2.0F;
    a(1U, 0U) = 3.0F; a(1U, 1U) = 4.0F;

    nn::matrix<float, 2, 2> b{};
    b(0U, 0U) = 10.0F; b(0U, 1U) = 20.0F;
    b(1U, 0U) = 30.0F; b(1U, 1U) = 40.0F;

    const auto c = a + b;

    return (c(0U, 0U) == 11.0F) && (c(0U, 1U) == 22.0F)
       && (c(1U, 0U) == 33.0F) && (c(1U, 1U) == 44.0F);
}

constexpr bool test_layer() noexcept {
    //2 neurons, 3 inputs each
    nn::matrix<float, 2, 3> w{};
    w(0U, 0U) = 1.0F;  w(0U, 1U) = 0.0F; w(0U, 2U) = 2.0F;
    w(1U, 0U) = -1.0F; w(1U, 1U) = 1.0F; w(1U, 2U) = 0.0F;

    //input
    nn::matrix<float, 3, 1>x{};
    x(0U, 0U) = 3.0F;
    x(1U, 0U) = 1.0F;
    x(2U, 0U) = 2.0F;

    //One bias ber neuron
    nn::matrix<float, 2, 1>b{};
    b(0U, 0U) = -1.0F;
    b(1U, 0U) = 0.0F;

    const auto output = nn::relu((w * x) + b);

    return (output(0U, 0U) == 6 ) && (output(1U, 0U) == 0 );
}


int main() {
  
    static_assert(test_multiply(), "matrix multiply is wrong");
    static_assert(test_add(), "matrix add is wrong");
    static_assert(test_layer(), "layer comp is wrong");
}



