// Jakub Strzalka 146789



#include <iostream>
#include<stdio.h>
#include <limits>

using namespace std;

struct File_header
{
    char name[2];
     int size;
     short int reserved_1;
     short int reserved_2;
     int offset;
}file_header;


struct Picture_header {
     int headerSize;
     int width;
     int height;
     short int planes;
     short int bitPerPixel;
     int compresion;
     int imageSize;
     int xPelsPerMeter;
     int yPelsPerMeter;
     int colorUsed;
     int colorImportant;


}picture_header;


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

        fread(&picture_header, sizeof(struct Picture_header), 1, f);

        cout << "Wielkosc naglowka informacyjnego: " << picture_header.headerSize <<endl;
        cout << "Szerokosc obrazu: " << picture_header.width << "px"<<endl;;
        cout << "Wysokosc obrazu: " << picture_header.height << " px"<<endl;;
        cout << "Liczba warstw kolorow: " << picture_header.planes <<endl;
        cout << "Liczba bitow na piksel: " << picture_header.bitPerPixel <<endl;
        cout << "Algorytm kompresji: " << picture_header.compresion <<endl;
        cout << "Rozmiar samego rysunku: " << picture_header.imageSize <<endl;
        cout << "Rozdzielczosc pozioma: " << picture_header.xPelsPerMeter <<endl;
        cout << "Rozdzielczosc pionowa: " << picture_header.yPelsPerMeter <<endl;
        cout << "Liczba kolorow w palecie: " << picture_header.colorUsed <<endl;
        cout << "Liczba waznych kolorow w palecie: " << picture_header.colorImportant <<endl;

        FILE* n = fopen("Negativ.bmp", "wb");
        if (nullptr == n) {
            cout << endl << endl << "Problem z otwarciem pliku" << endl;
        }
        else {
            cout << endl << endl << "Tworze negatyw obrazku" << endl;

            fwrite(&file_header.name[0], 1, 1, n);
            fwrite(&file_header.name[1], 1, 1, n);
            fwrite(&file_header.size, sizeof(file_header.size), 1, n);
            fwrite(&file_header.reserved_1, sizeof(file_header.reserved_1), 1, n);
            fwrite(&file_header.reserved_2, sizeof(file_header.reserved_2), 1, n);
            fwrite(&file_header.offset, sizeof(file_header.offset), 1, n);

            fwrite(&picture_header, sizeof(struct Picture_header), 1, n);

            int bmpImg;
            for (int i = file_header.offset; i < file_header.size; i++)
            {
                fseek(f, i, SEEK_SET);
                fseek(n, i, SEEK_SET);
                fread(&bmpImg, 3, 1, f);
                bmpImg = INT_MAX - bmpImg;
                fwrite(&bmpImg, 3, 1, n);
            }

            cout << "Negatyw zostal utworzony";

            fclose(f);
            fclose(n);
        }





    }

    return 0;
}
