#include <iostream>
#include <cmath>
#include <vector>

double y_line(const double x) {
    return -0.5 * x + 4;
}

double y_parabola_upper(const double x) {
    if (x < 0) {
        throw std::invalid_argument("Undefined at this point");
    }
    return sqrt(x);
}

double y_parabola_lower(const double x) {
    if (x < 0) {
        throw std::invalid_argument("Undefined at this point");
    }
    return -sqrt(x);
}

void cross(double first_function(const double),
           double second_function(const double),
           std::vector<double>& cross_array) {
    const int n = 1000, left_limit = -100 * n, right_limit = 100 * n;

    for (int i = left_limit; i < right_limit; i++) {
        double x = (double)i / n;
        try {
            double y_first = first_function(x), y_second = second_function(x);
            if (y_first == y_second) cross_array.push_back(x);
        }
        catch (std::invalid_argument& e) {
            continue;
        }
    }
}

void cross(double function(const double),
           std::vector<double>& cross_array) {
    const int n = 1000, left_limit = -100 * n, right_limit = 100 * n;

    for (int i = left_limit; i < right_limit; i++) {
        const double x = (double)i / n;
        try {
            double y = function(x);
            if (y == 0) cross_array.push_back(x);
        }
        catch (std::invalid_argument& e) {
            continue;
        }
    }
}

double integral(const double a,
                const double b,
                double func(const double)) {
    const int n = 10000; // Number of intervals
    const double width = (b - a) / n;

    double simpson_integral = 0;

    for (int step = 0; step < n; step++) {
        const double x1 = a + step * width;
        const double x2 = a + (step + 1) * width;

        simpson_integral += (x2 - x1) / 6 * (func(x1) + 4 * func((x1 + x2) / 2) + func(x2));
    }

    return simpson_integral;
}

int main() {
    std::vector<double> functions_cross, axis_parabola_cross;

    cross(y_parabola_upper, y_line, functions_cross);
    cross(y_parabola_lower, y_line, functions_cross);

    cross(y_parabola_upper, axis_parabola_cross);
    cross(y_parabola_lower, axis_parabola_cross);

    const double res = integral(axis_parabola_cross[0], functions_cross[0], y_parabola_upper) -
                       integral(axis_parabola_cross[0], functions_cross[1], y_parabola_lower) +
                       integral(functions_cross[0], functions_cross[1], y_line);

    std::cout << "Area between two functions equals to " << res << std::endl;
    return 0;
}
