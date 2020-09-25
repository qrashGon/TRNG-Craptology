#include <iostream>
#include <fstream> //import biblioteki fstream
#include <stdio.h> //import biblioteki stdio.h
#include <stdlib.h>     /* atof */
#include <string>
#include <math.h>

using namespace std;

double ParkingLotTest(unsigned short int tablica[100000]){
double p=0;
int parking[100][100]={0};
int liczbaProb = 0;
int liczbaKolizji = 0;
int x,y;
int licznik=0;
int sprawdzenie=0;
int ksrednie=3523;
double odchylenie=21.9;

for(int i=0; i<12000; i++){
      x = (tablica[licznik])/2.55;
      y = (tablica[licznik+1])/2.55;
      licznik = licznik+2;
      if(parking[x][y] == 0){
            parking[x][y]=1;
            liczbaProb++;
      }
      else{
         liczbaProb++;
         liczbaKolizji++;
      }
}
//cout<<" "<<liczbaKolizji<<" "<<liczbaProb;

p=(liczbaKolizji-ksrednie)/odchylenie;
p = p/12000;
//cout<<" "<<p;

return p;
}


unsigned short int b8ToInt(unsigned short int bity[8]=0){
unsigned short int liczba=0;
for(int i=7; i>=0; i--){
      if(bity[i]==1){
            liczba = liczba + pow(2,i);
      }
}
return liczba;
}

unsigned short int b16Tob1(int liczba){
unsigned short int bity=0;
int dzielnik=32768;
int current=0;
for(int i=0; i<16 ; i++){
      current = (liczba-dzielnik);
      if( 0 <= current ){
            bity++;
            liczba = liczba - dzielnik;
            dzielnik = dzielnik / 2;
      }
      else{
            dzielnik = dzielnik / 2;
      }
}
return (bity % 2);
}


unsigned short int tworzenieLiczby(unsigned short int bufor[100], unsigned short int poprzednia = 0){
unsigned short int liczba=0;
unsigned short int liczba_=0;

for(int i=0; i<100; i++){
      liczba = b16Tob1(bufor[i]);
      if(liczba==liczba_) liczba_ = 0;
      else liczba_ = 1;
}
return liczba_;
}



int main()
{
      unsigned short int liczbyLosowe[800000];
      unsigned short int liczbyLosoweInt[100000];
      unsigned short int bufor[100];
      unsigned short int bufor2[8];
	ifstream dane;
	dane.open("matlab/dane.bin", ios::in | ios::binary);
    	if (!dane.is_open()) {
		cerr << "Nie udalo sie otworzyc pliku 'matlab/dane.bin'" << endl;
		return 1;
	}
	else{
            cerr << "Udalo sie otworzyc plik 'matlab/dane.bin'."<< endl << "Generowanie liczb potrwa okolo 20 sekund...";
	}
    	unsigned short int num=0;
	for(int i=0; i < 1; i++){
            for(int j=0; j<100; j++){
                  dane.read((char*)&num, sizeof(num));
                  bufor[j] = num;
            }
            liczbyLosowe[i] = tworzenieLiczby(bufor);

	}

	for(int i=1; i < 800000; i++){
            for(int j=0; j<100; j++){
                  dane.read((char*)&num, sizeof(num));
                  bufor[j] = num;
            }
            liczbyLosowe[i] = tworzenieLiczby(bufor,liczbyLosowe[i-1]);
	}

      int licznik = 0;
      for(int i=0; i<800000;){
            for(int j=0; j<8; j++){
                  bufor2[j] = liczbyLosowe[i];
                  i++;
                  if(j==7){liczbyLosoweInt[licznik] = b8ToInt(bufor2); licznik++;}
            }
      }

	double p1=0;
//////////////////////////////////////////////////////////// tutaj wynik to to magiczne p zrob cos z tym

	p1 = ParkingLotTest(liczbyLosoweInt);

//////////////////////////////////////////////////////////// Wynik tego testu to w sumie chyba histogram, ktory znajdziesz w folderze 'histogramy'
      float * liczbaF;
      liczbaF = new float[100000];
      for(int i = 0; i < 100000; i++){
            unsigned short int bufor1 = liczbyLosoweInt[i];
            float bufor2 = (float)bufor1;
            liczbaF[i] = bufor2;
            liczbaF[i] = liczbaF[i] / 256;
      }
      float bufor3=0;
      int licznik1=0;
      ofstream SumTest("SumTest.txt");
      for(int i = 0; i < 1000; i++){
            for(int j = 0; j < 100; j++){
                   bufor3 = bufor3 + liczbaF[licznik1];
                   licznik1++;
            }
            SumTest<<bufor3<<";";
            bufor3 = 0;
      }
      delete [] liczbaF;

//////////////////////////////////////////////////////////// Ten test z literkami
// wynik to histogram znowu, masz wszystkie dane w plikach tekstowych
      short int * literki;
      literki = new short int[100000];
      for(int i = 0; i<100000; i++ ){
            if((liczbyLosoweInt[i]>=0) && (liczbyLosoweInt[i]<37)) literki[i] = 1;
            if((liczbyLosoweInt[i]>=37) && (liczbyLosoweInt[i]<93)) literki[i] = 2;
            if((liczbyLosoweInt[i]>=93) && (liczbyLosoweInt[i]<163)) literki[i] = 3;
            if((liczbyLosoweInt[i]>=163) && (liczbyLosoweInt[i]<219)) literki[i] = 4;
            if((liczbyLosoweInt[i]>=219) && (liczbyLosoweInt[i]<256)) literki[i] = 5;
      }
      int licznik2 = 0;
      int bufor4 = 0;
      ofstream Literkix5("literki.txt");
      for(int i = 0; i<20000; i++ ){
                  bufor4 = bufor4 + ((literki[licznik2])*10000);
                  licznik2++;
                  bufor4 = bufor4 + ((literki[licznik2])*1000);
                  licznik2++;
                  bufor4 = bufor4 + ((literki[licznik2])*100);
                  licznik2++;
                  bufor4 = bufor4 + ((literki[licznik2])*10);
                  licznik2++;
                  bufor4 = bufor4 + ((literki[licznik2])*1);
                  licznik2++;
                  Literkix5<<bufor4<<";";
                  bufor4 = 0;
      }

      delete [] literki;

////////////////////////////////////////////////////////////

	ofstream LOSOWE("LOSOWE.txt");
	for(int i=0;i<100000;i++)
	{
		LOSOWE<<liczbyLosoweInt[i]<<";";
	}

      dane.close();
	return 0;
}


