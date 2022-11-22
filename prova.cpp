#include "cpr/cpr.h"
#include <iostream>
#include <fstream>

int main(){
    cpr::Response r = cpr::Get(cpr::Url{"https://www.songfacts.com/songs/queen"});
    std::cout << r.text << std::endl;
    return 0;
}