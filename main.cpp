#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct Zadanie
{
    int numer;
    int czas_calkowity;
    int czas_pozostaly;
    int czas_przyjscia;
    int priorytet;
    int kwant_czasu_wykonywania;
};

struct Procesor
{
    int zadanie_na_procesorze=-1;
};

bool porownanie_po_dlugosci_zadania(Zadanie &p1, Zadanie &p2)
{
    if(p1.czas_pozostaly!=p2.czas_pozostaly)
    {
        return p1.czas_pozostaly < p2.czas_pozostaly;
    }
    else //jak taki sam czas to numer decyduje
    {
        return p1.numer<p2.numer;
    }
}

bool porownywanie_po_priorytecie_SRTF(Zadanie &p1, Zadanie &p2)
{
    if(p1.priorytet!=p2.priorytet)
    {
        return p1.priorytet < p2.priorytet;
    }
    else
    {
        return porownanie_po_dlugosci_zadania(p1,p2); //jak ten sam priorytet to porownanie po pozostalym czasie wynonywania
    }
}

bool porownywanie_po_priorytecie_FCFS(Zadanie &p1, Zadanie &p2)
{
    if(p1.priorytet!=p2.priorytet)
    {
        return p1.priorytet < p2.priorytet;
    }
    else
    {
        //return porownanie_po_dlugosci_zadania(p1, p2);
        return p1.numer < p2.numer; //jak ten sam priorytet to porownanie po numerze nizszy numer -> szybciej przyszedl -> FCFS
    }
}

bool sort_procesorow(Procesor &p1, Procesor &p2) //odpowiednie zadania wpuszczone na procesor. Teraz trzeba dac zadania o najnizszych numrach
{                                                //na pierwsze procesory
    if(p1.zadanie_na_procesorze == -1)
    {
        return false;
    }
    if(p2.zadanie_na_procesorze == -1)
    {
        return true;
    }
    return p1.zadanie_na_procesorze < p2.zadanie_na_procesorze;
}


void czy_pracuje(vector<Procesor>&procesory)//-2 - procesor nie zajety, ale niewylaczony
{
    for(int i=0;i<procesory.size();i++)
    {
        if(procesory[i].zadanie_na_procesorze==-2)
        {
            procesory[i].zadanie_na_procesorze=-1;
        }
    }
}

void FCFS(vector<Zadanie>&procesy,vector<Procesor>&procesory)
{
    czy_pracuje(procesory);
    int j =0;
    for(int i =0; i< procesory.size(); i++)
    {
        if (j >= procesy.size())
        {
            procesory[i].zadanie_na_procesorze = -1;
        }
        else
        {
            procesory[i].zadanie_na_procesorze = procesy[j].numer;
        }
        j++;
    }
}

void SJF(vector<Zadanie>&procesy,vector<Procesor>&procesory)
{
    czy_pracuje(procesory);
    int j =0;
    int zajete=0;
    for(int i=0;i<procesory.size();i++)
    {
        if(procesory[i].zadanie_na_procesorze!=-1)
        {
            zajete++;
        }
    }
    partial_sort(procesy.begin()+zajete,procesy.end(),procesy.end(),porownanie_po_dlugosci_zadania); //odkad,dokad,koniec,funkcja wg ktorej sortowac
    for(int i =0; i< procesory.size(); i++)
    {
        if (j >= procesy.size())
        {
            procesory[i].zadanie_na_procesorze = -1;
        }
        else
        {
            procesory[i].zadanie_na_procesorze = procesy[j].numer;
        }
        j++;
    }
    sort(procesory.begin(),procesory.end(),sort_procesorow);
}

void SRTF(vector<Zadanie>&procesy,vector<Procesor>&procesory)
{
    czy_pracuje(procesory);
    int j =0;
    sort(procesy.begin(),procesy.end(), porownanie_po_dlugosci_zadania);
    for(int i =0; i< procesory.size(); i++)
    {
        if (j >= procesy.size())
        {
            procesory[i].zadanie_na_procesorze = -1;
        }
        else
        {
            procesory[i].zadanie_na_procesorze = procesy[j].numer;
        }
        j++;
    }
    sort(procesory.begin(),procesory.end(),sort_procesorow);
}

void SPZW_FCFS(vector<Zadanie>&procesy,vector<Procesor>&procesory)
{
    czy_pracuje(procesory);
    int j =0;
    sort(procesy.begin(),procesy.end(), porownywanie_po_priorytecie_FCFS);
    for(int i =0; i< procesory.size(); i++)
    {
        if (j >= procesy.size())
        {
            procesory[i].zadanie_na_procesorze = -1;
        }
        else
        {
            procesory[i].zadanie_na_procesorze = procesy[j].numer;
        }
        j++;
    }
    sort(procesory.begin(),procesory.end(),sort_procesorow);
}

void SPZW_SRTF(vector<Zadanie>&procesy,vector<Procesor>&procesory)
{
    czy_pracuje(procesory);
    int j =0;
    sort(procesy.begin(),procesy.end(), porownywanie_po_priorytecie_SRTF);
    for(int i =0; i< procesory.size(); i++)
    {
        if (j >= procesy.size())
        {
            procesory[i].zadanie_na_procesorze = -1;
        }
        else
        {
            procesory[i].zadanie_na_procesorze = procesy[j].numer;
        }
        j++;
    }
    sort(procesory.begin(),procesory.end(),sort_procesorow);
}

void SPBW_FCFS(vector<Zadanie>&procesy,vector<Procesor>&procesory)
{
    czy_pracuje(procesory);
    int j =0;
    int zajete=0;
    for(int i=0;i<procesory.size();i++)
    {
        if(procesory[i].zadanie_na_procesorze!=-1)
        {
            zajete++;
        }
    }
    partial_sort(procesy.begin()+zajete,procesy.end(),procesy.end(), porownywanie_po_priorytecie_FCFS); //odkad,dokad,koniec,funkcja wg ktorej sortowac
    for(int i =0; i< procesory.size(); i++)
    {
        if (j >= procesy.size())
        {
            procesory[i].zadanie_na_procesorze = -1;
        }
        else
        {
            procesory[i].zadanie_na_procesorze = procesy[j].numer;
        }
        j++;
    }
    sort(procesory.begin(),procesory.end(),sort_procesorow);
}

void RR(vector<Zadanie>&procesy,vector<Procesor>&procesory,int kwant_czasu)
{
    czy_pracuje(procesory);
    for(int i=0;i<procesy.size();i++)
    {
        if(procesy[i].kwant_czasu_wykonywania == kwant_czasu)
        {
            procesy[i].kwant_czasu_wykonywania=0;
            Zadanie x = procesy[i];
            procesy.erase(procesy.begin()+i);
            procesy.push_back(x);
            i--; //przesuwajac element na koniec jezeli nie odejme od i 1 to pomine element wektora
        }
    }
    int j=0;
    for(int i =0; i< procesory.size(); i++)
    {
        if (j >= procesy.size())
        {
            procesory[i].zadanie_na_procesorze = -1;
        }
        else
        {
            procesory[i].zadanie_na_procesorze = procesy[j].numer;
            procesy[j].kwant_czasu_wykonywania++;
        }
        j++;
    }
    sort(procesory.begin(),procesory.end(),sort_procesorow);
}

bool czy_wolne(vector<Procesor> &procesory)
{
    int wolne_procesory=0;
    for(int i=0;i<procesory.size();i++)
    {
        if(procesory[i].zadanie_na_procesorze==-1)
        {
            wolne_procesory++;
        }
    }
    if(wolne_procesory == procesory.size())
    {
        return false; //jak wszystkie wolne to false bo chcemy wtedy skonczyc petle
    }
    else
    {
        return true; //jak pracuja to true zeby petla z zadaniami chodzila
    }
}

int main(int argc, char* argv[])
{
    int alg_planowania = strtol(argv[1],nullptr,10); //atoi(argv[1]); podobno strtol lepsze niz atoi
    int liczba_procesorow = 1; //jak nie podane to rowne 1
    int kwant_czasu =1;
    if(argc>2) //jesli podane to ustawiam wartosc
    {
        liczba_procesorow = strtol(argv[2],nullptr,10);
    }
    if(argc>3)
    {
        kwant_czasu = strtol(argv[3], nullptr, 10);
    }
    vector<Zadanie> procesy;
    vector<Procesor> procesory(liczba_procesorow);
    int czas= 0;
    int zm1,zm2,zm3; //zm pomocniczne
    string linia;
    int czas_wykonywania=0;
    bool czy_input=true;
    while(czy_input || czy_wolne(procesory))
    {
        int znak = getchar();// getc(stdin); //biore znak (ASCII -> int) i na podstawie jego wartosci determinuje czy to koniec inputu
        if (znak <=10) //0-10 to taki obszar z tabulatorami, znakami nowej linii, znakami konca
        {
            czy_input=false;
        }
        else
        {
            czy_input=true;
            ungetc(znak, stdin); //zwracam "zapozyczony" znak na pozatek strumienia
            getline(cin, linia); //biore cala linie
            stringstream strumien(linia); //i wczytuje ja do strumienia
            strumien >> czas;
            while(strumien.tellp() == 0) //dopoki strumien nie pusty
            {
                while(strumien >> zm1 >> zm2 >> zm3)
                {
                    Zadanie proc; //wczytuje dane
                    proc.czas_przyjscia = czas;
                    proc.numer = zm1;
                    proc.priorytet = zm2;
                    proc.czas_calkowity = zm3;
                    proc.czas_pozostaly = zm3;
                    proc.kwant_czasu_wykonywania=0;
                    procesy.push_back(proc);
                    //printf("%d %d %d %d\n",procesy[procesy.size()-1].czas_przyjscia,procesy[procesy.size()-1].numer,procesy[procesy.size()-1].priorytet,procesy[procesy.size()-1].czas_calkowity);
                }
            }
        }
        cout << czas_wykonywania << " ";
        switch(alg_planowania) //wybor uzywanej taktyki szeregowania
        {
            case(0):
                FCFS(procesy,procesory);
                break;
            case(1):
                SJF(procesy,procesory);
                break;
            case(2):
                SRTF(procesy,procesory);
                break;
            case(3):
                RR(procesy,procesory,kwant_czasu);
                break;
            case(4):
                SPZW_FCFS(procesy,procesory);
                break;
            case(5):
                SPZW_SRTF(procesy,procesory);
                break;
            case(6):
                SPBW_FCFS(procesy,procesory);
                break;
            default:
                cout << "Error, nie wybrano strategii szeregowania\n";
                return 0;
                break;
        }
        for(int i=0;i<procesory.size();i++) //wypisywanie zadan na procesorze
        {
            cout << procesory[i].zadanie_na_procesorze << " ";
            for(int j=0;j<procesy.size();j++)
            {
                if(procesy[j].numer == procesory[i].zadanie_na_procesorze)
                {
                    procesy[j].czas_pozostaly--; //skracamy czas wykonywania (wykonywalo sie na procesorze teraz)
                    if(procesy[j].czas_pozostaly==0)
                    {
                        procesy.erase(procesy.begin()+j); //jak sie skonczylo to kasacja
                        procesory[i].zadanie_na_procesorze = -2; //ustawienia procesora na nieuzywany
                    }
                    break;
                }
            }
        }
        cout << endl;
        czas_wykonywania++;
    }
    return 0;
}