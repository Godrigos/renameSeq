#include "renameSeq.hpp"

/* seqCheck function -- check file content
manipulated by renameSeq */

int seqCheck(const std::string filename)
{
    std::cout << "\nChecking if old and new files have the same content!\n";
    /* Open the text file containing the file names list
    to be substituted in the new directory */
    std::ifstream fNew(filename);

    std::ostringstream oldSeqName (std::ostringstream::app);
    std::ostringstream newSeqName (std::ostringstream::app);
    std::ostringstream oldAb1Name (std::ostringstream::app);
    std::ostringstream newAb1Name (std::ostringstream::app);

    std::fstream log2;
    time_t now2 = time(0);

    for (std::string nOld, nNew; getline(fNew, nOld, delimiter(filename)) && getline(fNew, nNew); )
    {
        std::cout << "Old Name: " << nOld << " -> New Name: " << nNew << std::endl;

        // Create old seq files names string
        oldSeqName.str(nOld);
        oldSeqName << ".seq";
        std::string osn = "./Seq/" + oldSeqName.str();

        // Create new seq files names string
        newSeqName.str(nNew);
        newSeqName << ".seq";
        std::string nsn = "./renamed/" + newSeqName.str();

        std::ifstream ifseq(osn, std::ios::binary);
        std::ifstream ofseq(nsn, std::ios::binary);

        if(ifseq.good() && ofseq.good())
        {
            std::string sifseq((std::istreambuf_iterator<char>(ifseq)),
                                std::istreambuf_iterator<char>());

            std::string sofseq((std::istreambuf_iterator<char>(ofseq)),
                                std::istreambuf_iterator<char>());

            if (sifseq.compare(sofseq) == 0)
            {

                log2.open("FileCheck.log", std::fstream::out | std::fstream::app);
                log2 << ctime(&now2) << " - " << "File " << osn << " matches " << nsn << std::endl;
                log2.close();
                std::cout << "File " << osn << " " << "\x1B[44mmatches\x1B[0m" << " " << nsn << "!" << std::endl;
            }
            else
            {
                log2.open("FileCheck.log", std::fstream::out | std::fstream::app);
                log2 << ctime(&now2) << " - " << "File " << osn << " DOES NOT MATCH " << nsn << std::endl;
                log2.close();
                std::cout << "File " << osn << " " << "\x1B[41mDOES NOT MATCH\x1B[0m" << " " << nsn << "!" << std::endl;
            }
        }
        else
        {
            log2.open("FileCheck.log", std::fstream::out | std::fstream::app);
            log2 << ctime(&now2) << " - " << "File " << osn << " does not exists or is unavailable!" << std::endl;
            log2.close();
            std::cout << "File " << osn << " does not exists or is unavailable!" << std::endl;
        }

        ifseq.close();
        ofseq.close();

        // Create old ab1 files names string
        oldAb1Name.str(nOld);
        oldAb1Name << ".ab1";
        std::string oan = "./Seq/" + oldAb1Name.str();

        // Create new ab1 files names string
        newAb1Name.str(nNew);
        newAb1Name << ".ab1";
        std::string nan = "./renamed/" + newAb1Name.str();

        std::ifstream ifab1(oan, std::ios::binary);
        std::ifstream ofab1(nan, std::ios::binary);

        if(ifab1.good() && ofab1.good())
        {

            std::string sifab1((std::istreambuf_iterator<char>(ifab1)),
                                std::istreambuf_iterator<char>());

            std::string sofab1((std::istreambuf_iterator<char>(ofab1)),
                                std::istreambuf_iterator<char>());

            if (sifab1.compare(sofab1) == 0)
            {
                log2.open("FileCheck.log", std::fstream::out | std::fstream::app);
                log2 << ctime(&now2) << " - " << "File " << oan << " matches " << nan << std::endl;
                log2.close();
                std::cout << "File " << oan << " " << "\x1B[44mmatches\x1B[0m" << " " << nan << "!" << std::endl;
            }
            else
            {
                log2.open("FileCheck.log", std::fstream::out | std::fstream::app);
                log2 << ctime(&now2) << " - " << "File " << oan << " DOES NOT MATCH " << nan << std::endl;
                log2.close();
                std::cout << "File " << oan << " " << "\x1B[41mDOES NOT MATCH\x1B[0m" << " " << nan << "!" << std::endl;
            }
        }
        else
        {
            log2.open("FileCheck.log", std::fstream::out | std::fstream::app);
            log2 << ctime(&now2) << " - " << "File " << oan << " does not exists or is unavailable!" << std::endl;
            log2.close();
            std::cout << "File " << oan << " does not exists or is unavailable!" << std::endl;
        }

        ifab1.close();
        ofab1.close();

    }

    fNew.close();
    return EXIT_SUCCESS;
}

