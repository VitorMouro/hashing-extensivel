#pragma once
#include <memory>
#include "Balde.hpp"

typedef unsigned int uint;

class Diretorio
{
private:
    uint m_profundidade_global = 1;
    uint m_tamanho_balde;
    uint m_bits_pseudochave;
    std::vector<std::shared_ptr<Balde>> m_baldes;
    bool inserePseudochave(std::string pseudochave);
    void duplicaBalde(uint index);
    void duplicaDiretorio();
    std::string Hash(uint k);
public:
    Diretorio(uint tamanho_balde, uint bits_pseudochave);
    virtual ~Diretorio();
    bool insere(uint k);
    bool busca(uint k);
};
