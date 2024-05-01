#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Zadanie{
public:
    int nr;  //nr zadania
    int pj;  // czas wykonywania
    Zadanie(){
        pj=0;
    }
    Zadanie(int Nr, int Pj) : nr(Nr), pj(Pj){}
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
};

    int combinationCount = 0;
    int final_time=0;
    int bestTime = INT_MAX; // Najlepszy czas znaleziony dotychczas
    vector<Zadanie> bestFirst, bestSecond; // Najlepsze kombinacje

    void generateCombinations(const vector<Zadanie>& Zadania, vector<Zadanie>& first, vector<Zadanie>& second, int index) {
    if (index == Zadania.size()) {
        combinationCount++;
        int czas1=0;
        int czas2=0;

        //cout << "Combination " << combinationCount << ":\n";
        //cout << "First: ";
        for (const auto& num : first) {
            //cout << num.nr << " ";
            czas1+=num.pj;
        }
        //cout << "\nCzas 1: " << czas1;
        //cout << "\nSecond: ";
        for (const auto& num : second) {
            //cout << num.nr << " ";
            czas2+=num.pj;
        }
        //cout << "\nCzas 2: " << czas2;
        //cout << endl << endl;

        if (czas1 > czas2) {
            final_time = czas1;
        } 
        else {
            final_time = czas2;
        }

        if (final_time < bestTime) {
            bestTime = final_time;
            bestFirst = first;
            bestSecond = second;
        }

        return;
    }

    // Spróbuj dodać element na pierwszą listę
    first.push_back(Zadania[index]);
    //cout<<"Push 1: "<<Zadania[index].nr<<endl;
    generateCombinations(Zadania, first, second, index + 1);
    first.pop_back();
    //cout<<"Pop 1: "<<Zadania[index].nr<<endl;

    // Spróbuj dodać element na drugą listę
    second.push_back(Zadania[index]);
    //cout<<"Push 2: "<<Zadania[index].nr<<endl;
    generateCombinations(Zadania, first, second, index + 1);
    second.pop_back();
    //cout<<"Pop 2: "<<Zadania[index].nr<<endl;
}

int main(int argc, char *argv[]) {
    Problem problem;
    Zadanie zadanie;
    vector<Zadanie> first, second;
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

    generateCombinations(problem.Zadania, first, second, 0);

    // Wyświetlenie najlepszej kombinacji i czasu wykonania
    cout << "Best combination:\n";
    cout << "First: ";
    for (const auto& num : bestFirst) {
        cout << num.nr << " ";
    }
    cout << "\nSecond: ";
    for (const auto& num : bestSecond) {
        cout << num.nr << " ";
    }
    cout << "\nBest time: " << bestTime << endl;

    return 0;
}