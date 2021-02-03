#pragma once
#include <vector>
#include <string>

typedef unsigned int uint;

class Balde
{
private:
    uint m_tamanho;
    uint m_profundidade_local;
    std::vector<std::string> m_pseudochaves;
public:
    Balde(uint tamanho, uint profundidade_local);
    virtual ~Balde();
    uint getTamanho() const;
    std::vector<std::string> getPseudochaves() const;
    uint getProfundidadeLocal() const;
    void clear();
    bool Insere(std::string);
    void IncrementaProfundidadeLocal();
};

