#include <iostream>
#include <math.h>
#include <iomanip>

double solve()
{
    // avoiding division until the last moment.
    size_t squareSize = 40000; // N samples each axis for a size=1 square.
    size_t nSampleInsideCircle = 0;
    for (size_t x = 0; x < squareSize; x++)
        for (size_t y = 0; y < squareSize; y++)
            if (x * x + y * y < squareSize * squareSize)
                nSampleInsideCircle += 1;
    // quadrant area = nSampleInsideCircle / totalSampleSize
    // rant area = 4 * quadrant area = pi * r^2 = pi  // set r=1
    // (4 * nSampleInsideCircle) / squareSize^2 = pi * squareSize^2
    // pi = (4 * nSampleInsideCircle) / squareSize^4
    return 4 * nSampleInsideCircle / std::pow(squareSize, 2);
}

int main(int argc, char *argv[])
{
    double result = solve();
    std::cout << "Result: " << result << "\n";
    std::cout << std::setprecision(4) << "Result: " << result << "\n";
    return 0;
}
