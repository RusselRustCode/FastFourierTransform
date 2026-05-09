#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#define _USE_MATH_DEFINES


using samples = std::complex<float>;
using std::cout;
using std::endl;
using samplesBuff = std::vector<samples>;
using std::pow;
bool is_power_of_5(size_t size){
    while(size % 5 == 0) size /= 5;
    return size == 1;
}

samplesBuff fft(const samplesBuff& input){
    if(!is_power_of_5(input.size())){
        return {};
    }

    if(input.empty()){
        return {};
    }

    if(input.size() <= 1){
        return input;
    }

    size_t new_size = input.size() / 5;

    samplesBuff vector_a(new_size, samples(0.0f, 0.0f));
    samplesBuff vector_b(new_size, samples(0.0f, 0.0f));
    samplesBuff vector_c(new_size, samples(0.0f, 0.0f));
    samplesBuff vector_d(new_size, samples(0.0f, 0.0f));
    samplesBuff vector_e(new_size, samples(0.0f, 0.0f));


    for(size_t n = 0; n < new_size; ++n){
        vector_a[n] = input[5*n];
        vector_b[n] = input[5*n + 1];
        vector_c[n] = input[5*n + 2];
        vector_d[n] = input[5*n + 3];
        vector_e[n] = input[5*n + 4];
    }

    vector_a = fft(vector_a);
    vector_b = fft(vector_b);
    vector_c = fft(vector_c);
    vector_d = fft(vector_d);
    vector_e = fft(vector_e);

    samples phi = samples(
        std::cos(2 * M_PI / 5),
        -std::sin(2 * M_PI / 5)
    );
    
    samplesBuff out(input.size(), samples(0.0f, 0.0f));
    for(size_t k = 0; k < new_size; k++){
        samples twiddleFactor = samples(
            std::cos(2 * M_PI * k / input.size()),
            -std::sin(2 * M_PI * k / input.size())
        );

        samples twiddleFactor2 = samples(
            std::cos(4 * M_PI * k / input.size()),
            -std::sin(4 * M_PI * k / input.size())
        );

        samples twiddleFactor3 = samples(
            std::cos(6 * M_PI * k / input.size()),
            -std::sin(6 * M_PI * k / input.size())
        );

        samples twiddleFactor4 = samples(
            std::cos(8 * M_PI * k / input.size()),
            -std::sin(8 * M_PI * k / input.size())
        );

        out[k] = vector_a[k] + twiddleFactor * vector_b[k] + twiddleFactor2 * vector_c[k] + twiddleFactor3 * vector_d[k]
        + twiddleFactor4 * vector_e[k];

        out[k + input.size() / 5] = vector_a[k] + phi * twiddleFactor * vector_b[k] + pow(phi, 2) * twiddleFactor2 * vector_c[k] + 
        pow(phi, 3) * twiddleFactor3 * vector_d[k] + pow(phi, 4) * twiddleFactor4 * vector_e[k];
        
        out[k + 2 * input.size() / 5] = vector_a[k] + pow(phi, 2) * twiddleFactor * vector_b[k] + pow(phi, 4) * twiddleFactor2
        * vector_c[k] + phi * twiddleFactor3 * vector_d[k] + pow(phi, 3) * twiddleFactor4 * vector_e[k];        
        
        out[k + 3 * input.size() / 5] = vector_a[k] + pow(phi, 3) * twiddleFactor * vector_b[k] + phi * twiddleFactor2
                * vector_c[k] + pow(phi, 4) * twiddleFactor3 * vector_d[k] + pow(phi, 2) * twiddleFactor4 * vector_e[k];
                
        out[k + 4 * input.size() / 5] =  vector_a[k] + pow(phi, 4) * twiddleFactor * vector_b[k] + pow(phi, 3) * twiddleFactor2
                * vector_c[k] + pow(phi, 2) * twiddleFactor3 * vector_d[k] + phi * twiddleFactor4 * vector_e[k];
          
    }
    return out;

    
}


int main(){
    return 0;
}
