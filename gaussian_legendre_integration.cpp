#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <limits>


// structure for gaussian-legendre method
struct gauss_legendre {

        // constructor
        gauss_legendre(double a_in, double b_in, int n_in){
                a = a_in;
                b = b_in;
                n = n_in;
                samplePoints.resize(n_in);
                weights.resize(n_in);
        }

        // --- *** - define function here - *** ---
        // this is the function which you want to integrate
        double fx(double x){
                return sin(x);
        }

        // Function which calls the Gauss-Legendre method to estimate the integral
        double estimate_integral(){

                // get sample points and weights
                points_n_weights();

                scale_factor = (b-a) / 2;

                for(int i = 0; i < n; i++) {

                        current_xi = ((b - a) * samplePoints[i] + (b + a)) / 2.0;
                        current_wi = weights[i];

                        answer += current_wi * fx(current_xi);

                }

                answer *= scale_factor;
                return answer;
        }

        // getter - print sample points and weight
        void print_samples_weights(){

                std::cout << " sample points & weights " << '\n';
                for(int i =0; i < samplePoints.size(); i++) {
                        std::cout << i << " - " << "point: " << samplePoints[i]
                                  << " _ weight: " << weights[i]  << '\n';
                }
        }

        // getter - print answer
        void print_answer(){

                std::cout << " Gaussian-Legendre called... " << '\n';
                std::cout << " lower limit = " << a << '\n';
                std::cout << " upper limit = " << b << '\n';
                std::cout << " intervals = " << n << '\n';
                std::cout << std::setprecision(16) << " integral = " << answer << '\n';
        }

        ~gauss_legendre() = default;

// protected
protected:

        // Function to calculate the Legendre polynomial of degree n at x
        double legendre_polynomial(int n, double x) {

                if (n == 0) {return 1;}
                if (n == 1) {return x;}

                return ((2 * n - 1) * x * legendre_polynomial(n - 1, x) - (n - 1) * legendre_polynomial(n - 2, x)) / n;
        }

        // Function to calculate the derivative of the Legendre polynomial
        double legendre_polynomial_diff(int n, double x) {
                return n / (x * x - 1) * (x * legendre_polynomial(n, x) - legendre_polynomial(n - 1, x));
        }

        // Gauss-Legendre algorithm to calculate sample points and weights
        void points_n_weights() {

                // Solve roots of Legendre polynomial using initial approximations
                for (int i = 0; i < n; ++i) {

                        x = std::cos(M_PI * (i + 0.75) / (n + 0.5)); // Initial approximation

                        // Use Newton's method to refine the approximation
                        while (std::abs(x - prevX) > std::numeric_limits<double>::epsilon()) {
                                prevX = x;
                                x = x - legendre_polynomial(n, x) / legendre_polynomial_diff(n, x);
                        }

                        samplePoints[i] = x;
                }

                // Calculate the weights based on the sample points
                for (int i = 0; i < n; ++i) {
                        xi = samplePoints[i];
                        weights[i] = 2 / ((1 - xi * xi) * legendre_polynomial_diff(n, xi) * legendre_polynomial_diff(n, xi));
                }

                // Normalize the weights
                for (int i = 0; i < n; ++i) {
                        sumWeights += weights[i];
                }
                for (int i = 0; i < n; ++i) {
                        weights[i] *= 2 / sumWeights;
                }
        }

        int n{};
        double a{}, b{}, x{}, prevX{}, xi{}, sumWeights{}, scale_factor{}, answer{}, current_xi{}, current_wi{};
        std::vector<double> samplePoints;
        std::vector<double> weights;
};  // gauss_legendre


// main
int main(){


        // -----
        // READ ME
        //
        //
        // This script uses a gaussian-legendre method to numerically integrate a given function.
        // the function can be specified in the above structure, see 'define function here',
        // the lower limit (a), upper limit (b) and number of samples (n) can be specified as below.
        // The code should be compiled, run, and results will be printed to terminal.
        //
        // Note:
        // far less samples are used compared to the trapezoidal and simpsons rule,
        // 10 points (even less) produce a very precise result

        // specify parameters here
        double a = 0, b = 2;
        double n = 10;

        // create structure for integral
        gauss_legendre integral_1(a, b, n);

        // estimate integral
        integral_1.estimate_integral();

        // print answer
        integral_1.print_answer();


        std::cout << "done." << '\n';
        return 0;
}
