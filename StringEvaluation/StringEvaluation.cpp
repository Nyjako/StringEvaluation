#include <iostream>
#include "StringEvaluation.h"

int main()
{
    std::cout << KT::StringEvaluation::resolveMath("5+6-N7") << std::endl; // 5+6--7 = 18
    std::cout << KT::StringEvaluation::resolveMath("(2+4/2)P2") << std::endl; // (2+4/2)^2 = 4^2 = 12
    std::cout << KT::StringEvaluation::resolveMath("((8/(1+1))*2)*N1") << std::endl; // (8/(1+1))*2 = 4*2 = 8
    std::cout << KT::StringEvaluation::resolveMath("2S4") << std::endl; // 4^(1/2) = 2
}