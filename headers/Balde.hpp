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
    Balde(uint, uint);
    virtual ~Balde();
    uint getTamanho() const;
    std::vector<std::string> getPseudochaves() const;
    uint getProfundidadeLocal() const;
    void clear();
    bool insere(std::string);
    bool busca(std::string);
    void incrementaProfundidadeLocal();
};

