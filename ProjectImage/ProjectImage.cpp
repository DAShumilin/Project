#include <iostream>
#include "Filter.h"

int main(){

    std::cout << "Starting..." << std::endl;

    Filter Foto;
    
    Foto.PrepareImage();

    std::cout << "Complete" << std::endl;

    return 0;
}