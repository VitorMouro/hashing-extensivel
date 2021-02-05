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
    std::string pseudochave = std::bitset<32>(floor(200 * parte_fracionaria)).to_string();
    return pseudochave.substr(pseudochave.length()-m_bits_pseudochave, m_bits_pseudochave);
}

bool Diretorio::insere(uint k)
{
    std::string pseudochave = Hash(k);
    return inserePseudochave(pseudochave);
}

bool Diretorio::inserePseudochave(std::string pseudochave)
{
    std::string d_bits_esquerda = pseudochave.substr(0, m_profundidade_global);
    uint index_balde = std::stoi(d_bits_esquerda, 0, 2);
    std::shared_ptr<Balde> b = m_baldes[index_balde];
    if (b->insere(pseudochave))
    {
        return true;
    }
    else if (m_profundidade_global == b->getProfundidadeLocal())
    {
        duplicaDiretorio();
        duplicaBalde(index_balde*index_balde);
        inserePseudochave(pseudochave);
        return true;
    }
    duplicaBalde(index_balde);
    inserePseudochave(pseudochave);
    return true;
}

void Diretorio::duplicaBalde(uint index)
{
    std::vector<std::string> pseudochaves = m_baldes[index]->getPseudochaves();
    m_baldes[index]->clear();
    m_baldes[index]->incrementaProfundidadeLocal();
    m_baldes[index] = std::shared_ptr<Balde>(new Balde(m_tamanho_balde, m_baldes[index]->getProfundidadeLocal()));
    for (auto pseudochave : pseudochaves)
    {
        inserePseudochave(pseudochave);
    }
}

void Diretorio::duplicaDiretorio()
{
    m_profundidade_global++;
    std::vector<std::shared_ptr<Balde>> baldes;
    for (int i = 0; i < pow(2, m_profundidade_global); i++)
    {
        baldes.push_back(nullptr);
    }
    for (unsigned int i = 0; i < m_baldes.size(); i++)
    {
        if(i!=1)
        {
            baldes[i*i] = m_baldes[i];
            baldes[(i*i)+1] = m_baldes[i];
        }
        else
        {
            baldes[2] = m_baldes[1];
            baldes[3] = m_baldes[1];
        }
    }
    m_baldes = baldes;
}
