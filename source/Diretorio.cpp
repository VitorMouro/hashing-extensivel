#include <cmath>
#include <bitset>
#include <iostream>
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
        if(!duplicaDiretorio())
        {
            std::cout << "Não foi possível inserir pseudochave " << pseudochave << ": Diretório cheio" << std::endl;
            return false;
        }
        if (!duplicaBalde(2 * index_balde))
        {
            std::cout << "Não foi possível inserir pseudochave " << pseudochave << ": índice lotado" << std::endl;
            return false;
        }
        return insere(pseudochave);
    }
    if (!duplicaBalde(index_balde))
    {
        std::cout << "Não foi possível inserir pseudochave " << pseudochave << ": índice lotado" << std::endl;
        return false;
    }
    return insere(pseudochave);
}

bool Diretorio::duplicaBalde(uint index)
{
    if (m_baldes[index]->getProfundidadeLocal() >= m_bits_pseudochave)
    {
        std::cout << "Balde " << index << " com profundidade local máxima" << std::endl;
        return false;
    }
    std::vector<std::string> pseudochaves = m_baldes[index]->getPseudochaves();
    m_baldes[index]->clear();
    m_baldes[index]->incrementaProfundidadeLocal();
    std::shared_ptr<Balde> b = std::shared_ptr<Balde>(new Balde(m_tamanho_balde, m_baldes[index]->getProfundidadeLocal()));
    
    std::string bits_esquerda_index = std::bitset<64>(index).to_string().substr(64-m_profundidade_global, b->getProfundidadeLocal());
    for (uint i = 0; i < m_baldes.size(); i++)
    {
        std::string bits_esqueda_i = std::bitset<64>(i).to_string().substr(64-m_profundidade_global, b->getProfundidadeLocal());
        if(bits_esqueda_i == bits_esquerda_index)
        {
            m_baldes[i] = b;
        }
    }
    
    for (auto pseudochave : pseudochaves)
    {
        m_nChaves--;
        insere(pseudochave);
    }
    m_nBaldes++;
    return true;
}

bool Diretorio::duplicaDiretorio()
{
    if (m_profundidade_global >= m_bits_pseudochave)
    {
        std::cout << "Diretório com profundidade máxima" << std::endl;
        return false;
    }
    m_profundidade_global++;
    std::vector<std::shared_ptr<Balde>> baldes;
    for (int i = 0; i < pow(2, m_profundidade_global); i++)
    {
        baldes.push_back(nullptr);
    }
    for (unsigned int i = 0; i < m_baldes.size(); i++)
    {
        baldes[2 * i] = m_baldes[i];
        baldes[(2 * i) + 1] = m_baldes[i];
    }
    m_baldes = baldes;
    return true;
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
    return m_nChaves / float(m_nBaldes * m_tamanho_balde);
}