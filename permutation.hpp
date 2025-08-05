#ifndef PERMUTATION_HPP
#define PERMUTATION_HPP

#include <key.hpp>

bool checkNb(uint64_t data, int key, int data_length){
    if (data >> (data_length - 1 - key) & 1){return 1;}
    return 0;
}

uint64_t permutationC1(uint64_t data, int collum, int row, int real_collum, int real_row){
    // int cout = 0;
    uint64_t outdata = 0;
    
    for (int c = 0; c < ceil(real_collum/2); c++){
        for (int r = row - 1; r >= 0; r--){
            if (c + 1 == ceil(real_collum/2) && r < row/2){break;}
            int nb = r * real_collum + c;
            // std::cout<< checkNb(data, nb) << "   ";
            // if (cout == 6){std::cout<< std::endl; cout = 0;}
            // else{cout ++;}
            outdata <<= 1;
            outdata += checkNb(data, nb, 64);
            // std::cout<< outdata<<std::endl;
        }
    }
    bool lastrow = false;
    for (int c = collum - 1; c >= floor(real_collum/2) - 1; c--){
        for (int r = row - 1; r >= 0; r--){
            if (c == floor(real_collum/2) - 1 && !lastrow){r -= int(row/2); lastrow = true;}
            int nb = r * real_collum + c;
            // std::cout<< checkNb(data, nb) << "   ";
            // if (cout == 6){std::cout<< std::endl; cout = 0;}
            // else{cout ++;}
            outdata <<= 1;
            outdata += checkNb(data, nb, 64);
        }
    }
    return outdata;
}

uint64_t permutationC2(uint64_t data, int* lock, int length_lock, int length_data){
    uint64_t outdata = 0;
    for (int i = 0; i < length_lock; i++){
        outdata <<= 1;
        outdata += checkNb(data, lock[i] - 1, length_data);
        // std::cout<< checkNb(data, lock[i] - 1, 56) << "  ";
    }
    return outdata;
}

uint32_t permutationC2_32bit(uint32_t data, int* lock, int length_lock, int length_data){
    uint32_t outdata = 0;
    for (int i = 0; i < length_lock; i++){
        outdata <<= 1;
        outdata += checkNb(data, lock[i] - 1, length_data);
        // std::cout<< checkNb(data, lock[i] - 1, 56) << "  ";
    }
    return outdata;
}
#endif