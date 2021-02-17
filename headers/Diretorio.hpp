#pragma once
#include <memory>
#include "Balde.hpp"

typedef unsigned int uint;

class Diretorio
{
private:
    uint m_profundidade_global = 1;
    uint m_nBaldes = 1;
    uint m_nChaves = 0;
    uint m_tamanho_balde;
    uint m_bits_pseudochave;
    std::vector<std::shared_ptr<Balde>> m_baldes;
    bool duplicaBalde(uint index);
    bool duplicaDiretorio();
public:
    Diretorio(uint tamanho_balde, uint bits_pseudochave);
    virtual ~Diretorio();
    bool insere(std::string k);
    bool busca(std::string k);
    float getFatorDeCarga();
};
