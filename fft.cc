#include <iostream>
#include <vector>
#include <complex> 

using samples = std::complex<float>;
class fastFourier {
private:

public:

    std::vector<samples> fft(const std::vector<samples>& input){
      return std::vector<samples>{};    
    };


    std::vector<samples> ifft(const std::vector<samples>& input){
        return std::vector<samples>{};
    };
    
};



using std::cout;
using std::endl;
int main(){
    return 0;
}
