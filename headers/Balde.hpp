#pragma once
#include <vector>
#include <string>

class Balde
{
private:
    unsigned int _tamanho;
    std::vector<std::string> _pseudochaves;
public:
    Balde(unsigned int tamanho);
    ~Balde();
};

