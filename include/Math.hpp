//
// Created by doktorov-av on 11/5/25.
//

#ifndef REST_SENDER_MATH_HPP
#define REST_SENDER_MATH_HPP

template<class T, class V>
constexpr  bool InRange(T&& value, V&& lowerBound, V&& upperBound, bool inclusive = true) {
    if (inclusive) {
        return value >= lowerBound && value <= upperBound;
    }
    return value > lowerBound && value < upperBound;
}

static_assert(InRange(0.5, 0, 1));
static_assert(InRange(0, 0, 1));
static_assert(InRange(0, 0, 1));
static_assert(!InRange(1.1, 0, 1));
static_assert(!InRange(-0.1, 0, 1));
static_assert(!InRange(-0.00001, 0, 1));

#endif //REST_SENDER_MATH_HPP