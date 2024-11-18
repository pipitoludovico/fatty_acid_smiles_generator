#include <iostream>
#include <sstream>
#include <algorithm>
#include <set>
#include <fstream>
#include "headers/Permutate.h"
#include "headers/Replace.h" 

int main(int argc, char* argv[])
{
    std::vector<std::string> ResultArray;
    std::vector<int> lengths;
    std::set<std::string> final_SMILES;
    int compoundCount = 0;
    
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-lengths" || (argv[i][1] == 'l' && argv[i][0] == '-'))
        {
            for (int j = i + 1; j < argc; ++j) {
                int length = std::stoi(argv[j]);
                lengths.push_back(length);
            }
            break;
        }
    }
    if (lengths.empty()) 
    {
        std::cerr << "Please specify '-lengths or -l with a space-separated sequence of numbers: [-l 2 4 5 6]'!" << std::endl;
        return 1;
    }

    std::ofstream out("oriented_smiles.smi", std::ios::trunc);

    if (out.tellp() == 0) {
        out << "ID\tSMILES\n";
    }

    for (int length: lengths)
    {
        char BondType[] = {'0', '1'};

        char Orientations[] = {'\\', '/'};
        std::vector<std::string> OrientationCombos;

        int sizeOfArray = sizeof(BondType) / sizeof(BondType[0]);

        std::string separator = "";

        Permutate(BondType, separator, sizeOfArray, length, ResultArray, 4);

        Permutate(Orientations, separator, 2, 2, OrientationCombos, 2);

        for (auto combo : OrientationCombos){
            for (auto sequence: ResultArray){
                std::cout << sequence << "\n";

                std::string initial = "CC";
                std::string replaced = ReplaceAll(sequence, "0", "C");
                replaced = initial + replaced;
                replaced = ReplaceAll(replaced, "1", std::string(1, combo[0]) + "C=C" + std::string(1, combo[1]));
                
                std::string finalString = initial + replaced;

                replaced += "CC(=O)O";
                int carbons = std::count(replaced.begin(), replaced.end(), 'C');
                
                if (final_SMILES.find(replaced) == final_SMILES.end()) {
                    compoundCount ++;
                    final_SMILES.insert(replaced);
                    std::cout << replaced << " Carbon count: " << carbons << "\n";
                    out << compoundCount << "\t" << replaced << "\n";
                }
            }
        }
    }
    out.close();
    std::cout << "TOTAL COMPOUNDS: " << compoundCount << std::endl;
    return 0;
}
