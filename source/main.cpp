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
    d.insere(0);
    d.insere(1);
    d.insere(2);
    d.insere(3);
    d.insere(4);
    d.insere(5);
    d.insere(6);
    d.insere(7);
    d.insere(8);
    d.insere(9);
    d.insere(10);
    return 0;
}
