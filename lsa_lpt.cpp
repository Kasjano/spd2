#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Zadanie{
public:
    int nr;  //nr zadania
    int pj;  // czas wykonywania
    int rozpoczecie;  //rozpoczecia zadania
    int nr_maszyny;
    Zadanie(){
        pj=0;
    }
    Zadanie(int Nr, int Pj) : nr(Nr), pj(Pj){}
    bool operator<(const Zadanie& other) const {
        return nr < other.nr;
    }
};

class Problem{
public:
    int n; //liczba zadań
    vector<Zadanie> Zadania;

    //funkcja dodania zadania do listy
    void dodajZadanie(int Nr,int Pj) {
        Zadanie zadanie(Nr,Pj);
        Zadania.push_back(zadanie);
    }

    void sortowanie(){
        sort(Zadania.begin(), Zadania.end(),[](const Zadanie& a, const Zadanie& b) {return a.pj > b.pj;});
    }

    void WypiszUszeregowanie(){
        for (const auto& obiekt : Zadania) {
            cout<< obiekt.nr << " ";
        }
        cout << endl;
    }

    void WypiszUszeregowanie2(){
        for (const auto& obiekt : Zadania) {
            cout<< obiekt.nr << " ";
        }
        cout << endl;
    }

    class Maszyna{
    public:
        int nr_zadania;
    };

    void Algorytm(){
        Maszyna Maszyny[2];
        int czas=0;
        int liczba_zadań=n;
        for (int i = 0; i < liczba_zadań; i++){
            Zadania[i].rozpoczecie=1;
        }
        for(int y=0;y<2;y++){                
            Maszyny[y].nr_zadania=y;
            Zadania[Maszyny[y].nr_zadania].nr_maszyny=y;
            Zadania[Maszyny[y].nr_zadania].rozpoczecie=0;
        }
        for (int i = 0; i < liczba_zadań; i++){
            while(Zadania[i].pj>0){
                cout<<"Moment: "<<czas<<endl;              
                for(int y=0;y<2;y++){
                    if(Zadania[Maszyny[y].nr_zadania].pj>0){
                        cout<<"Nr zadania: "<<(Zadania[Maszyny[y].nr_zadania].nr)<<" Pozostalo czasu: "<<Zadania[Maszyny[y].nr_zadania].pj<<endl;
                        Zadania[Maszyny[y].nr_zadania].pj--;
                    }
                    else{
                        while(Zadania[Maszyny[y].nr_zadania].rozpoczecie==0){                  
                            Maszyny[y].nr_zadania=Maszyny[y].nr_zadania+1;                   
                        } 
                        if(Maszyny[y].nr_zadania<=liczba_zadań){
                            cout<<"Nr zadania: "<<(Zadania[Maszyny[y].nr_zadania].nr)<<" Pozostalo czasu: "<<Zadania[Maszyny[y].nr_zadania].pj<<endl;
                            Zadania[Maszyny[y].nr_zadania].pj--;
                            Zadania[Maszyny[y].nr_zadania].rozpoczecie=0;
                        }
                        else
                            cout<<"Brak dostepnych zadan"<<endl;
                    }                   
                }           
                czas++;   
            }
        }
        cout<<"Czas wykonania: "<<czas<<endl;
    }

    // Wyświetlanie elementów wektora
    void wypiszWektor() {
        //cout << "Elementy wektora:" << endl;
        for (const auto& obiekt : Zadania) {
            cout << "nr" << obiekt.nr << " pj:" << obiekt.pj <<endl;
        }
    }
};

int main(int argc, char *argv[]) {
    Problem problem;
    Zadanie zadanie;
    int Rozpoczecie=0;
    char linia[200];
    char *nazwa=argv[1];
    int nr=1;

    FILE *dane = fopen(nazwa, "r");
    if (!dane) {
        printf("Nie udalo sie otworzyc pliku");
        return 1;
    }

    while (fgets(linia,200,dane)!=NULL){
        sscanf(linia,"%d", &problem.n);
        while(fgets(linia, 200, dane) != NULL && sscanf(linia,"%d",&zadanie.pj)==1){
            //cout << zadanie.rj <<zadanie.pj << zadanie.qj << endl;
            problem.dodajZadanie(nr,zadanie.pj);
            nr++;
        }   
    }

    Problem problem2=problem;

    cout << "Oto wczytany wektor zadan" << endl;
    problem.wypiszWektor();
    cout << endl << "Uszeregowanie dla LSA: ";
    problem.WypiszUszeregowanie();
    problem.Algorytm();
    problem2.sortowanie();
    cout << endl << "Uszeregowanie dla LPT: ";
    problem2.WypiszUszeregowanie2();
    problem2.Algorytm();
    return 0;
}
