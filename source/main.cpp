#include <iostream>
#include <fstream>
#include <memory>
#include "Diretorio.hpp"

int main(int argc, char const *argv[])
{
    unsigned int m, b;
    std::cout << "Digite o tamanho de cada balde (M): ";
    std::cin >> m;
    std::cout << "Digite o número de bits a ser usado para as pseudo-chaves (B): ";
    std::cin >> b;
    Diretorio d(m, b);
    d.Insere(100);
    d.Insere(200);
    d.Insere(500);
    d.Insere(1000);
    return 0;
}
