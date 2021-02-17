#include <iostream>
#include <chrono>
#include "Diretorio.hpp"

std::string geraPseudochaveAleatoria(unsigned int n_bits)
{
    std::string chave;
    for (unsigned int i = 0; i < n_bits; i++)
    {
        rand() > (RAND_MAX / 2) ? chave.push_back('1') : chave.push_back('0');
    }
    return chave;
}

std::string geraPseudochaveAleatoriaComPrefixo(std::string prefixo, unsigned int n_bits)
{
    std::string chave = prefixo;
    for (unsigned int i = 0; i < n_bits - prefixo.size(); i++)
    {
        rand() > (RAND_MAX / 2) ? chave.push_back('1') : chave.push_back('0');
    }
    return chave;
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    unsigned int m, b;
    std::cout << "Digite o tamanho de cada balde (M): ";
    std::cin >> m;
    std::cout << "Digite o número de bits a ser usado para as pseudo-chaves (B): ";
    std::cin >> b;

    int n = 100000;

    // Teste pseudochaves aleatórias com mesmo padrão de bits
    unsigned long long time = 0;
    long double fatorCarga = 0;
    for (int j = 0; j < 10; j++)
    {
        Diretorio d1(m, b);
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now(), end;
        for (int i = 0; i < n; i++)
        {
            d1.insere(geraPseudochaveAleatoria(b));
        }
        end = std::chrono::steady_clock::now();
        time += std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        fatorCarga += d1.getFatorDeCarga();
    }
    std::cout << "Insersão Pseudochaves aleatórias:" << std::endl;
    std::cout << "\tDuração Média (10 iterações): " << time/10 << "ms" << std::endl;
    std::cout << "\tFator de Carga Média (10 iterações): " << fatorCarga/10 << std::endl;
    
    // Teste pseudochaves iniciadas com mesmo padrão de bits
    time = 0;
    fatorCarga = 0;
    for (int j = 0; j < 10; j++)
    {
        Diretorio d2(m, b);
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now(), end;
        begin = std::chrono::steady_clock::now();
        for (int i = 0; i < n; i++)
        {
            d2.insere(geraPseudochaveAleatoriaComPrefixo("00000000", b));
        }
        end = std::chrono::steady_clock::now();
        time += std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        fatorCarga += d2.getFatorDeCarga();
    }
    std::cout << "Insersão Pseudochaves aleatórias com mesmo padrão de bits:" << std::endl;
    std::cout << "\tDuração Média (10 iterações): " << time/10 << "ms" << std::endl;
    std::cout << "\tFator de Carga Média (10 iterações): " << fatorCarga/10 << std::endl;
    return 0;
}
