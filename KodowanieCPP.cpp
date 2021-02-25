#include <iostream>
#include <bitset>
#include <fstream>
#include <string>
using namespace std;

int ile = 3;
int ile_bitow = ile * 8;
string G[1000];
char Tablica[63];

string int_tobin(int A) {
    string s = bitset<8>(A).to_string();
    return s;   //zwraca ascii znak jako binary np 1000010
}

int bin_toint(string s) {
    int w = bitset<8>(s).to_ulong();
    return w;   //zwraca ascii znak z binary na int np 16
}

void zapisz_mnie_to(string Gy[], int j) {
    char tablica[1000];
    int licznik;
    for (int i = 0; i < j; i++) {
        if (Gy[i]=="=") {
            tablica[i] = '=';
        }
        else {
            licznik = bin_toint(Gy[i]);
            tablica[i] = Tablica[licznik];
        }
    }
    for (int i = 0; i < j; i++) {
        cout << tablica[i] << endl;
    }
    cout << "koniec" << endl;
}

void takesix(string S, string Gy[], int ile_bitow) {
    string g;
    int jest_szesc=0;
    int do_cztery = 0;
    int j = 0;
    
        for (int i = 0; i <= ile_bitow; i++) {
            if (i%6 != 0 || i==0 ) {
                g = g + S[i];
                jest_szesc++;
            }
            else {
                Gy[j] = g;
                g = "";
                jest_szesc = 0;
                do_cztery++;
                g = g + S[i];
                jest_szesc++;
                j++;
            }
        }
        if (jest_szesc != 6 && jest_szesc != 1) {
            int roznica = 6 - jest_szesc;
            g.pop_back();
            for (int a = 0; a < roznica+1; a++) {
                g.push_back('0');
            }
            Gy[j] = g;
            j++;
            do_cztery++;
        }
        if (do_cztery%4!=0) {
            int zmienna = j;
            int jznak = do_cztery % 4;
            jznak = -1*(jznak - 4);
            for (int i = zmienna; i < zmienna+jznak; i++) {
                Gy[i] = '=';
                j++;
            }
        }
        zapisz_mnie_to(Gy, j);
}

void wczytaj_tablice(char Tablica[]) {
    fstream tablica;
    string linia;
    tablica.open("Tablica.txt");
    int licznik = 0;
    while (getline(tablica, linia)) {
        Tablica[licznik] = linia[0];
        licznik++;
    }
    tablica.close();
}

void szyfr(char Dane[], int licznik) {
    int A;
    string b;
    string bitword;
    ile_bitow = licznik * 8;
    for (int i = 0; i < licznik; i++) {
        A = Dane[i];
        b = int_tobin(A);
        bitword = bitword + b;
    }
    takesix(bitword, G, ile_bitow);
}

void wczytaj_plik(char Dane[], int ile) {
    fstream plik;
    string linia;
    int lenght = 0;
    plik.open("plik.txt");

    while (getline(plik, linia)) {
        lenght = linia.length();
        int licznik = 0;
        for (int i = 1; i < lenght+1; i++) {
            Dane[licznik] = linia[i - 1];
            licznik++;
        }
        szyfr(Dane, licznik);
    }
    plik.close();
}

int main(){
    wczytaj_tablice(Tablica); //wczytaj tablice z pliku Tablica.txt
    char Dane[100]; //Dane
    int dlugosc = 0;
    wczytaj_plik(Dane, ile);       
}