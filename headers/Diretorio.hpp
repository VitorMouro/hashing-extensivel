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
    bool InserePseudochave(std::string pseudochave);
public:
    Diretorio(uint tamanho_balde, uint bits_pseudochave);
    virtual ~Diretorio();
    std::string Hash(uint k);
    bool Insere(uint k);
    bool Busca(uint k);
    void DuplicaBalde(uint index);
    void DuplicaDiretorio();
};
