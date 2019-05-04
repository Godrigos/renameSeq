#include "renameSeq.hpp"

/* delimiter function -- defines the names
delimiter */

char delimiter(const std::string filename)
{
    std::ifstream fNew(filename);
    std::string line;
    char delim{'\0'};
    getline(fNew, line);

    if (line.find(';') != std::string::npos)
        delim = ';';
    else if (line.find(',') != std::string::npos)
        delim = ',';
    else if (line.find('\t') != std::string::npos)
        delim = '\t';
    else
    {
        std::cout << "Wrong delimiter, correct your names list file.\n";
        std::cout << "Use ',' or 'tab' or ';' as delimiter.\n";
        exit (EXIT_FAILURE);
    }

    fNew.close();

    return delim;
}

