#include <cmath>
#include <bitset>
#include "Diretorio.hpp"

Diretorio::Diretorio(uint tamanho_balde, uint bits_pseudochave) : m_tamanho_balde(tamanho_balde), m_bits_pseudochave(bits_pseudochave)
{
    std::shared_ptr<Balde> b(new Balde(tamanho_balde, 0));

    for (int i = 0; i < pow(2, m_profundidade_global); i++)
    {
        m_baldes.push_back(b);
    }
}

Diretorio::~Diretorio()
{
}

std::string Diretorio::Hash(uint k)
{
    float a = (sqrt(5) - 1) / 2;                      // Sugestão Knuth[1971]
    float parte_fracionaria = (k * a) - floor(k * a); // kA mod 1
    std::string pseudochave = std::bitset<128>(floor(200 * parte_fracionaria)).to_string();
    return pseudochave.substr(pseudochave.length()-m_bits_pseudochave, m_bits_pseudochave);
}

bool Diretorio::Insere(uint k)
{
    std::string pseudochave = Hash(k);
    return InserePseudochave(pseudochave);
}

bool Diretorio::InserePseudochave(std::string pseudochave)
{
    std::string d_bits_esquerda = pseudochave.substr(0, m_profundidade_global);
    uint index_balde = std::stoi(d_bits_esquerda, 0, 2);
    std::shared_ptr<Balde> b = m_baldes[index_balde];
    if (b->Insere(pseudochave))
    {
        return true;
    }
    else if (m_profundidade_global == b->getProfundidadeLocal())
    {
        // Duplica diretório
    }
    DuplicaBalde(index_balde);
    InserePseudochave(pseudochave);
    return true;
}

void Diretorio::DuplicaBalde(uint index)
{
    std::vector<std::string> pseudochaves = m_baldes[index]->getPseudochaves();
    m_baldes[index]->clear();
    m_baldes[index]->IncrementaProfundidadeLocal();
    m_baldes[index] = std::shared_ptr<Balde>(new Balde(m_tamanho_balde, m_baldes[index]->getProfundidadeLocal()));
    for (auto pseudochave : pseudochaves)
    {
        InserePseudochave(pseudochave);
    }
    // for(auto balde : m_baldes)
    // {

    // }
}

void Diretorio::DuplicaDiretorio()
{
    
}
