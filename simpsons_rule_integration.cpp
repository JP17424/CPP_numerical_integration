#include <iostream>
#include <cmath>
#include <iomanip>


// structure for simpsons rule
struct simpsons_rule {

        // constructor
        simpsons_rule(double a_in, double b_in, int n_in){
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
                sum = fx(a) + fx(b);
                x = a;

                // calculate quads
                for(int i = 1; i < n; i++) {

                        x += h;

                        if(i%2 ==0) {
                                sum += 2 * fx(x);
                        }
                        else{
                                sum += 4 * fx(x);
                        }
                }

                answer = (h/3) * sum;

                return answer;
        }

        // getter - print answer
        void print_answer(){

                std::cout << " Simpsons_rule called... " << '\n';
                std::cout << " lower limit = " << a << '\n';
                std::cout << " upper limit = " << b << '\n';
                std::cout << " intervals = " << n << '\n';
                std::cout << std::setprecision(16) << " integral = " << answer << '\n';
        }

        ~simpsons_rule() = default;

protected:
        double a{}, b{}, h{}, sum{}, x{}, answer{};
        int n{};
};


// main
int main(){


        // -----
        // READ ME
        //
        //
        // This script uses simpsons rule to numerically integrate a given function.
        // the function can be specified in the above structure, see 'define function here',
        // the lower limit (a), upper limit (b) and number of intervals (n) can be specified as below.
        // The code should be compiled, run, and results will be printed to terminal.

        // specify parameters here
        double a = 0, b = 2;
        int n = 100;

        // create structure
        simpsons_rule integral_1 = simpsons_rule(a, b, n);

        // estimate integral
        integral_1.estimate_integral();

        // print answer
        integral_1.print_answer();


        std::cout << "done." << '\n';
        return 0;
}
