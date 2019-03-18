#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string.h>

int main()
{
    std::cout << "Writing \n";
    std::cout << "------------------------------------\n\n";
    std::string fileName("binary");
    std::string configJson("something value here something value heresomething value heresomething value heresomething value heresomething value here");
    std::ofstream outFile(fileName,std::ofstream::binary);

    outFile << 'P';
    outFile << strlen(configJson.c_str());
    outFile << ';';
    std::cout << "size of " << std::to_string(strlen(configJson.c_str())) << std::endl;
    outFile << configJson.c_str();
    std::cout << "dump : " << configJson.c_str() << std::endl;

    outFile.close();

    std::cout << "\n\nReading \n";
    std::cout << "------------------------------------\n\n";

    std::ifstream mouldingFile(fileName, std::ios::in | std::ios::binary);
    const std::size_t len_arr = 8;
    char jsonSize[len_arr] = {0};

    std::streampos filePos = mouldingFile.tellg();
    char frameType;
    mouldingFile >> frameType;

    if (frameType == 'P') {
        for(int i = 0; ; i++) {
            mouldingFile >> frameType;
            if(frameType == ';')
                break;
            else
            {
                jsonSize[i] = frameType;
            }
        }
        std::cout << "size of: " << jsonSize << std::endl;
        std::size_t jlen = 0;
        sscanf(jsonSize, "%d", &jlen);
        std::cout << "len of: " << std::to_string(jlen) << std::endl;


        char* buffer = new char[jlen];
        memset(buffer, 0x00, jlen);
        mouldingFile.read(buffer, jlen);
        std::cout << "dump: " << buffer << std::endl;
        filePos = mouldingFile.tellg();
        delete [] buffer;
    }
    return 0;
}
