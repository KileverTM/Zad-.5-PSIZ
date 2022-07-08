// Jakub Strzalka 146789



#include <iostream>
#include<stdio.h>
#include <limits>

using namespace std;

struct File_header
{
    char name[2];
    unsigned int size;
    unsigned short int reserved_1;
    unsigned short int reserved_2;
    unsigned int offset;
}file_header;


int main(int argc, char* argv[])
{
    const char* File_Name;

    if (nullptr == argv[1])
        File_Name = "test.bmp";
    else
        File_Name = argv[1];

    FILE* f = fopen(File_Name, "rb");

    if (f == nullptr) {
        cout << "Blad! Problem z otwarciem pliku" << endl;
    }
    else {
        cout << "Informacje o pliku:" << endl << endl;

        fread(&file_header.name, 2, 1, f);
        fread(&file_header.size, sizeof(file_header.size), 1, f);
        fread(&file_header.reserved_1, sizeof(file_header.reserved_1), 1, f);
        fread(&file_header.reserved_2, sizeof(file_header.reserved_2), 1, f);
        fread(&file_header.offset, sizeof(file_header.offset), 1, f);

        cout << "Pierwsze dwa znaki :" << (char)file_header.name[0] << file_header.name[1] << endl;
        cout << "Rozmiar pkiku: " << file_header.size << " bajtow"<<endl;
        cout << "Zarezerwowane 1: " << file_header.reserved_1 <<endl;
        cout << "Zarezerwowane 2: " << file_header.reserved_1 <<endl;
        cout << "Offset: " << file_header.offset <<endl;




    }

    return 0;
}
