/* renameSeq-Win64.cpp -- rename files provenient from
an ABI 3500 sequencer */

#include "renameSeq.hpp"
#include <boost/filesystem.hpp>

int main ()
{

    /* Open the text file containing the labels list
    to be substituted in the new directory */
    std::string filename;
    std::cout << "Enter the name of the file containing the sequences names: ";
    std::cin >> filename;
    std::ifstream fNew(filename);

    // Test if plain text file exists or quit
    while (fNew.fail())
    {
        fNew.clear();
        std::cout << "File does not exist! Try again (or enter 'q' to quit): ";
        std::cin >> filename;
        if ((filename == "q") || (filename == "Q"))
            exit(EXIT_SUCCESS);
        else
            fNew.open(filename);
    }

    /* Show file content for user verification */
    std::cout << "File content for " << filename << ":\n";
    std::string line;
    while (getline(fNew, line))
    {
        std::cout << line << "\n";
    }
    fNew.close();

    /* Ask the user for the veracity of the file content */
    char ch = 'n';
    std::cout << "Is the file content correct? (y/n): ";
    std::cin >> ch;

    /* Check answer and run routines */
    if (ch == 'y' || ch == 'Y')
    {
        /* Create a directory for renamed files,
        preserving the originals */
        boost::filesystem::path dir("./renamed");
            if(boost::filesystem::create_directory(dir))
            {
                std::cout << "renamed directory successfully created!" << std::endl;
            }
            else
            {
                std::cout << "renamed directory already exists!" << std::endl;
                std::cout << "Removing its former content!" << std::endl;
                boost::filesystem::remove_all(dir);
                boost::filesystem::create_directory(dir);
            }

        /* Copying to "renamed" directory with new names */
        int nLines = 0;

        fNew.open(filename);
        while (getline(fNew, line))
        {
            ++nLines;
        }
        fNew.close();

        fNew.open(filename);
        std::ostringstream oldSeqName (std::ostringstream::ate);
        std::ostringstream newSeqName (std::ostringstream::ate);
        std::ostringstream oldAb1Name (std::ostringstream::ate);
        std::ostringstream newAb1Name (std::ostringstream::ate);

        std::fstream log;
        time_t now = time(0);

        for (std::string nOld, nNew; getline(fNew, nOld, delimiter(filename)) && getline(fNew, nNew); )
        {
            std::cout << "Old Name: " << nOld << " -> New Name: " << nNew << std::endl;

            // Keep a log of the name changes
            log.open("NameChanges.log", std::fstream::out | std::fstream::app);
            log << ctime(&now) << " - " <<  "Old Name: " << nOld << " -> New Name: " << nNew << std::endl;
            log.close();

            // Create old seq files names string
            oldSeqName.str(nOld);
            oldSeqName << ".seq";
            std::string osn = "./Seq/" + oldSeqName.str();

            // Create new seq files names string
            newSeqName.str(nNew);
            newSeqName << ".seq";
            std::string nsn = "./renamed/" + newSeqName.str();

            std::ifstream ifseq(osn, std::ios::binary);

            if (ifseq.good())
            {
                std::ifstream ofseq(nsn, std::ios::binary);
                if (ofseq.good())
                {
                    log.open("NameChanges.log", std::fstream::out | std::fstream::app);
                    log << nsn << " file already exists!\n";
                    log << "renameSeq will not overwrite it!\n";
                    log.close();
                    std::cout << nsn << " file already exists!\n";
                    std::cout << "renameSeq will not overwrite it!\n";
                    ifseq.close();
                    ofseq.close();
                }
                else
                {
                    std::ofstream ofseq(nsn, std::ios::binary);
                    ofseq << ifseq.rdbuf();
                    ifseq.close();
                    ofseq.close();
                }
            }
            else
            {
                std::cout << "File " << osn << " does not exists or is unavailable!" << std::endl;
                ifseq.close();
            }

            // Create old ab1 files names string
            oldAb1Name.str(nOld);
            oldAb1Name << ".ab1";
            std::string oan = "./Seq/" + oldAb1Name.str();

            // Create new ab1 files names string
            newAb1Name.str(nNew);
            newAb1Name << ".ab1";
            std::string nan = "./renamed/" + newAb1Name.str();

            std::ifstream ifab1(oan, std::ios::binary);

            if(ifab1.good())
            {
                std::ifstream ofab1(nan, std::ios::binary);
                if (ofab1.good())
                {
                    log.open("NameChanges.log", std::fstream::out | std::fstream::app);
                    log << nan << " file already exists!\n";
                    log << "renameSeq will not overwrite it!\n";
                    log.close();
                    std::cout << nan << " file already exists!\n";
                    std::cout << "renameSeq will not overwrite it!\n";
                    ifab1.close();
                    ofab1.close();
                }
                else
                {
                    std::ofstream ofab1(nan, std::ios::binary);
                    ofab1 << ifab1.rdbuf();
                    ifab1.close();
                    ofab1.close();
                }
            }
            else
            {
                std::cout << "File " << oan << " does not exists or is unavailable!" << std::endl;
                ifab1.close();
            }
        }

        std::cout << "Tried to copy " << nLines*2 << " files to \"renamed\" directory with their new names!" << std::endl;

        fNew.close();
        seqCheck(filename);

    }

    else
    {
        std::cout << "Correct the file name or content and try again!" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Press ENTER to exit...";
    std::cin.get();
    std::cin.get();

    return EXIT_SUCCESS;
}
