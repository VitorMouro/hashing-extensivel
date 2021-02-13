#include "Balde.hpp"
#include <iostream>

Balde::Balde(uint tamanho, uint profundidade_local) : m_tamanho(tamanho), m_profundidade_local(profundidade_local)
{
}

Balde::~Balde()
{
}

uint Balde::getTamanho() const
{
    return m_tamanho;
}

std::vector<std::string> Balde::getPseudochaves() const
{
    return m_pseudochaves;
}

uint Balde::getProfundidadeLocal() const
{
    return m_profundidade_local;
}

bool Balde::insere(std::string pseudochave)
{
    if (m_pseudochaves.size() < m_tamanho)
    {
        m_pseudochaves.push_back(pseudochave);
        return true;
    }
    return false;
}

void Balde::clear()
{
    m_pseudochaves.clear();
}

void Balde::incrementaProfundidadeLocal()
{
    m_profundidade_local++;
}

bool Balde::busca(std::string pseudochave)
{
    for (auto pc : m_pseudochaves)
        if (pc == pseudochave)
            return true;
    return false;
}
