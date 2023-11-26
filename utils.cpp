#include "utils.h"
#include <chrono>
#include <thread>
#include <iostream>
void sleep(unsigned int ms) {
  std::this_thread::sleep_for(std::chrono::milliseconds(ms) );
}
void ligne_vague(){
    std::cout << "   .-.     .-.     .-.     .-.     .-.     .-.     .-.  "<<std::endl;
    std::cout << " .'   `._.'   `._.'   `._.'   `._.'   `._.'   `._.'   `."<<std::endl<<std::endl;
};
