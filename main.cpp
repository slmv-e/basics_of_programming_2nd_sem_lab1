#include <iostream>
#include <cmath>
#include <vector>

double y_line(double x) {
    return -0.5 * x + 4;
}

double y_parabola_upper(double x) {
    if (x < 0) {
        throw std::invalid_argument("Undefined at this point");
    }
    return sqrt(x);
}

double y_parabola_lower(double x) {
    if (x < 0) {
        throw std::invalid_argument("Undefined at this point");
    }
    return -sqrt(x);
}

void cross(double first_function(double),
           double second_function(double),
           std::vector<double>& cross_array) {
    int n = 1000, left_limit = -100 * n, right_limit = 100 * n;

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

void cross(double function(double),
           std::vector<double>& cross_array) {
    int n = 1000, left_limit = -100 * n, right_limit = 100 * n;
    for (int i = left_limit; i < right_limit; i++) {
        double x = (double)i / n;
        try {
            double y = function(x);
            if (y == 0) cross_array.push_back(x);
        }
        catch (std::invalid_argument& e) {
            continue;
        }
    }
}

double integration(double a, double b, double func(double)) {
    int n = 10000; // Number of intervals
    double h = (b - a) / n;

    double sum_odds = 0.0;

    for (int i = 1; i < n; i += 2)
    {
        sum_odds += func(a + i * h);
    }
    double sum_evens = 0.0;

    for (int i = 2; i < n; i += 2)
    {
        sum_evens += func(a + i * h);
    }

    return (func(a) + func(b) + 2 * sum_evens + 4 * sum_odds) * h / 3;
}

int main() {
    std::vector<double> functions_cross, axis_parabola_cross;
    double res;

    cross(y_parabola_upper, y_line, functions_cross);
    cross(y_parabola_lower, y_line, functions_cross);

    cross(y_parabola_upper, axis_parabola_cross);
    cross(y_parabola_lower, axis_parabola_cross);

    res = integration(axis_parabola_cross[0], functions_cross[0], y_parabola_upper) -
            integration(axis_parabola_cross[0], functions_cross[1], y_parabola_lower) +
            integration(functions_cross[0], functions_cross[1], y_line);
    std::cout << "Area between two functions equal to " << res << std::endl;
    return 0;
}
