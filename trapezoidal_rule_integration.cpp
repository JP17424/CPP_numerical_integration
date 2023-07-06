#include <iostream>
#include <cmath>
#include <iomanip>


// structure for trapezoidal ruke
struct trapezoidal_rule {

        // constructor
        trapezoidal_rule(double a_in, double b_in, int n_in){
                a = a_in;
                b = b_in;
                n = n_in;
        }

        // --- *** - define function here - *** ---
        double fx(double x){
                return sin(x);
        }

        // estimate integral
        double estimate_integral(){

                h = (b-a)/n;

                // calculate trapezoids
                for(int i = 0; i < n; i++) {

                        x = a + i * h;
                        sum += fx(x);
                }

                // calculate integral
                answer = (h/2) * (fx(a) + 2 * sum + fx(b));

                return answer;
        }

        // getter - print answer
        void print_answer(){

                std::cout << " Trapezoidal_rule called... " << '\n';
                std::cout << " lower limit = " << a << '\n';
                std::cout << " upper limit = " << b << '\n';
                std::cout << " intervals = " << n << '\n';
                std::cout << std::setprecision(16) << " integral = " << answer << '\n';
        }

        ~trapezoidal_rule() = default;

protected:
        double a{}, b{}, h{}, sum{}, x{}, answer{};
        int n{};
}; //


// main
int main(){


        // -----
        // READ ME
        //
        //
        // This script uses the trapezoidal rule to numerically integrate a given function.
        // the function can be specified in the above structure, see 'define function here',
        // the lower limit (a), upper limit (b) and number of intervals (n) can be specified as below.
        // The code should be compiled, run, and results will be printed to terminal.

        // specify parameters here
        double a = 0, b = 2;
        int n = 100;

        // create structure
        trapezoidal_rule integral_1 = trapezoidal_rule(a,b,n);

        // estimate integral
        integral_1.estimate_integral();

        // print answer
        integral_1.print_answer();


        std::cout << "done." << '\n';
        return 0;
}
