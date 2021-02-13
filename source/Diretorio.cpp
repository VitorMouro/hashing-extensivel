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

bool Diretorio::insere(std::string pseudochave)
{
    std::string d_bits_esquerda = pseudochave.substr(0, m_profundidade_global);
    uint index_balde = std::stoi(d_bits_esquerda, 0, 2);
    std::shared_ptr<Balde> b = m_baldes[index_balde];
    if (b->insere(pseudochave))
    {
        m_nChaves++;
        return true;
    }
    else if (m_profundidade_global == b->getProfundidadeLocal())
    {
        duplicaDiretorio();
        if(!duplicaBalde(2*index_balde)){return false;};
        return insere(pseudochave);
    }
    if(!duplicaBalde(index_balde)){return false;};
    return insere(pseudochave);
}
 
bool Diretorio::duplicaBalde(uint index)
{
    if(m_baldes[index]->getProfundidadeLocal() >= m_bits_pseudochave)
    {
        return false;
    }
    std::vector<std::string> pseudochaves = m_baldes[index]->getPseudochaves();
    m_baldes[index]->clear();
    m_baldes[index]->incrementaProfundidadeLocal();
    m_baldes[index] = std::shared_ptr<Balde>(new Balde(m_tamanho_balde, m_baldes[index]->getProfundidadeLocal()));
    for (auto pseudochave : pseudochaves)
    {
        insere(pseudochave);
        m_nChaves--;
    }
    m_nBaldes++;
    return true;
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
        baldes[2*i] = m_baldes[i];
        baldes[(2*i)+1] = m_baldes[i];
    }
    m_baldes = baldes;
}

bool Diretorio::busca(std::string pseudochave)
{
    std::string d_bits_esquerda = pseudochave.substr(0, m_profundidade_global);
    uint index_balde = std::stoi(d_bits_esquerda, 0, 2);
    std::shared_ptr<Balde> b = m_baldes[index_balde];
    return b->busca(pseudochave);
}

float Diretorio::getFatorDeCarga()
{
    return m_nChaves/float(m_nBaldes*m_tamanho_balde);
}