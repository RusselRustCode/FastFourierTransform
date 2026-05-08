#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <complex> 
#include <cmath>
#include <random>


using samples = std::complex<float>;
using std::cout;
using std::endl;
class fastFourier {
private:
    size_t num_of_samples;
    std::vector<samples> input;
    std::vector<samples> out;
    

public:
    explicit fastFourier(size_t num, std::vector<samples> input) : num_of_samples(num), input(std::move(input)), out(std::vector<samples>(num, samples(0.0f, 0.0f))){}


    std::vector<samples> dft(){
        if(input.empty()){
            cout << "Вектор пустой" << endl;
            return {};
        }

        for(size_t k = 0; k < num_of_samples; ++k){
            for(size_t i = 0; i < num_of_samples; ++i){
                float twiddle = 2 * M_PI * k * i / num_of_samples;
                out[k] += input[i] * samples(std::cos(twiddle), -std::sin(twiddle));
            }
        }
        return out;
        
    }

    std::vector<samples> fft(){
        if(input.empty()){
            return {};
        }
        
        return std::vector<samples>{};    
    };


    std::vector<samples> ifft(){
        return std::vector<samples>{};
    };
    
};




int main(){
    std::random_device rd;
    std::mt19937 generator(rd());

    size_t size = 10000;
    std::uniform_real_distribution<float> distr (-100.0f, 100.0f);
    std::vector<samples> input(size);
    for(size_t i = 0; i < input.size(); ++i){
        float real = distr(generator);
        float imag = distr(generator);
        input[i] = samples(real, imag);
    }

    for(size_t i = 0; i < 10; i++){
        cout << input[i].real() << " " << input[i].imag() << endl;
    }
    
    
    return 0;
}
