// #include <iostream>
#include <permutation.hpp>
#include <bitset> // Required for std::bitset



void Create_Key(uint64_t Key, uint64_t* K_list){
    uint64_t CD_list[16];
    uint64_t K_plus = permutationC1(Key, 7, 8, 8, 8);
    uint32_t C_before = K_plus >> 28;
    uint32_t D_before = (K_plus << (28 + 8)) >> (28 + 8);
    
    // D0 >>= (28 + 9);
    // std::cout<< K_plus << "   "<< C_before << "   "<< D_before << std::endl;
    for (int i = 0; i < 16; i ++){

        uint32_t Ci = C_before, Di = D_before;
    
        for (int loop = 0; loop < KEY_CREATE_LOOP[i]; loop++){
            Ci <<= 5; Di <<= 5;
            Ci >>= 4; Di >>= 4;
            Ci += checkNb(C_before, loop, 28);
            Di += checkNb(D_before, loop, 28);
        }
        C_before = Ci; D_before = Di;
        uint64_t CDi = (uint64_t(Ci)<<28) + Di;
        CD_list[i] = CDi;
        // std::cout<< CDi <<std::endl;
    }
    //create K_i lock
    

    for (int i = 0; i < 16; i ++){
        K_list[i] = permutationC2(CD_list[i], FIXED_PC2_48BIT, 48, 56);
        // std::cout<< K_list[i]<<std::endl;
    }
}

uint8_t S_box(uint8_t Bi, uint8_t* SBox){
    uint8_t row = 0;
    if (Bi & 0b100000) row += 0b10;
    if (Bi & 0b1) row += 0b1;

    Bi <<= 3; Bi >>= 4;
    return SBox[row * 16 + Bi];
}

uint32_t F_function(uint32_t indata, uint64_t Key){
    uint64_t E = permutationC2(indata, FIXED_EXTEND_PC2_48BIT, 48, 32);
    uint64_t handled_data = E ^ Key;
    // std::cout<< indata << "  ";
    // std::cout<< E << " ";

    handled_data <<= 16;

    uint32_t SboxOutPut = 0;
    for (int i = 0; i < 8; i ++){
        uint8_t Bi = handled_data >> (42 + 16);
        // std::cout<< int(Bi) << "  ";
        SboxOutPut <<= 4;
        SboxOutPut += S_box(Bi, SBox_list[i]);
        handled_data <<= 6;
        
    }
    // std::cout<< SboxOutPut<<" ";
    
    uint32_t OutPut_data = permutationC2_32bit(SboxOutPut, P_box, 32, 32);
    return OutPut_data;
}

uint64_t Des_encryption(uint64_t M){
    // std::cout<< permutationC1(0b0001001100110100010101110111100110011011101111001101111111110001, 7, 8, 8, 8) <<std::endl;
    // std::cout<< permutationC2(K_LOCK, FIXED_PC2_48BIT, 48) << std::endl;
    uint64_t K_list[16];
    Create_Key(K_LOCK, K_list);
    
    // uint64_t M = 0b0000000100100011010001010110011110001001101010111100110111101111;
    uint64_t IP = permutationC2(M, FIXED_PC2_IP_64BIT, 64, 64);
    // std::cout<< IP <<std::endl;
    uint32_t L_before = IP >> 32;
    uint32_t R_before = (IP << 32) >> 32;

    // std::cout<< R_before<<std::endl;

    // std::cout<< K_list[0] <<std::endl;
    // std::cout<< (F_function(171426665, K_list[11]) ^ 1008904651) <<std::endl;
    for (int i = 0; i < 16; i ++){
        // std::cout<< K_list[i] <<std::endl;
        uint32_t R_new = F_function(R_before, K_list[i]) ^ L_before;
        L_before = R_before;
        R_before = R_new;
        // std::cout<< L_before << "   " << R_before <<std::endl;
    }
    uint64_t LR16 = (uint64_t(R_before)<<32) + L_before;
    // std::cout<<std::hex << permutationC2(LR16, FIXED_CP2_IP1_64BIT, 64, 64) <<std::endl;
    return permutationC2(LR16, FIXED_CP2_IP1_64BIT, 64, 64);
}

int main(){
    std::string plant_text = "";
    std::cout<< "Write your plantext: ";
    std::cin>> plant_text;

    uint64_t translate_text = 0;
    int cout_char = 0;
    int number_char = plant_text.length();
    // for (int i = 0; i < number_char; i++){
    //     std::cout<< int(plant_text[i]) << std::endl;
    // }
    std::cout<< std::hex<< Des_encryption(0b0000000100100011010001010110011110001001101010111100110111101111)<<std::endl ;
    
    // std::cout<< "Encrypted text: ";
    // for (int i = 0; i < number_char; i++){
    //     int num = int(plant_text[i]);
    //     translate_text <<= 8;
    //     translate_text += num;
    //     cout_char ++;
    //     if (cout_char == 8 || i + 1 == number_char){
    //         std::cout<< std::hex << Des_encryption(translate_text) ;
    //         cout_char = 0;
    //         translate_text = 0;
    //     }
    // }
    std::cout<< std::endl;
    
}