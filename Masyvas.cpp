#include <iostream>
#include <string>
#include <iomanip>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::setw;
using std::left;

struct duomenys {
    string Vard, Pav;
    int paz[10] = { 0 };
    int egz;
    float Gal = 0;
};



void count_median(int pazymiai[]) //funkcija, kuri suskaiciuoja mediana
{
    int counter = 0;
    for (int i = 0; i < 10; i++)
    {
        if (pazymiai[i] > 0)
        {
            counter++;
        }
        if (pazymiai[i] == -1)
        {
            pazymiai[i] = 0;
            break;
        }
    }
    if (counter % 2 == 0)
    {
        cout << float(((pazymiai[counter / 2 - 1]) + (pazymiai[(counter / 2)])) / 2.0);
    }
    else
    {
        cout << pazymiai[(counter / 2)];
    }
    cout << endl;
}

int generate_random_mark() //Sugeneruojami atsistiktiniai skaiciai nuo 1 iki 10.
{
    srand(time(NULL));
    return rand() % 10 + 1;
}

void automated_marks_input(duomenys Eil[], int i, int how_many_marks) //funckija, kuri suveda pazymius
{
    Eil[i].egz = generate_random_mark();
    for (int x = 0; x < how_many_marks; x++)
    {
        Eil[i].paz[x] = generate_random_mark();
    }
    Eil[i].Gal = Eil[i].Gal / how_many_marks;
    Eil[i].Gal = Eil[i].Gal * 0.4 + 0.6 * Eil[i].egz;

}

void input_by_hand(duomenys Eil[], int i) //funkcija, kuri duos zmogui suvesti paciam pazymius
{
    do {
        cout << "Iveskite studento egzamino pazymi:";
        cin >> Eil[i].egz;
    } while (Eil[i].egz < 0 || Eil[i].egz > 10);
    cout << "Iveskite studento pazymius (kai baigsite, iveskite -1):";
    int counter = 0;
    do {
        cin >> Eil[i].paz[counter];
        if (Eil[i].paz[counter] != -1) { Eil[i].Gal = Eil[i].Gal + (float)Eil[i].paz[counter]; }
        counter++;
    } while (Eil[i].paz[counter - 1] != -1);
    counter--;
    Eil[i].Gal = Eil[i].Gal / counter;
    Eil[i].Gal = Eil[i].Gal * 0.4 + 0.6 * Eil[i].egz;
}
bool has_digit(string s)
{
    return (s.find_first_of("0123456789") != string::npos);
}

void name_input(duomenys Eil[], int i) //funkcija kurios pagalba suvedame studentu vardus ir pavardes
{
    cout << "Iveskite studento nr. " << i + 1 << " duomenis:\n";
    do {
        cout << "Iveskite studento nr. " << i + 1 << " VARDA:\n";
        cin >> Eil[i].Vard;
    } while (Eil[i].Vard.length() < 0 || Eil[i].Vard.length() > 25 || has_digit(Eil[i].Vard));
    do {
        cout << "Iveskite studento nr. " << i + 1 << " PAVARDE:\n";
        cin >> Eil[i].Pav;
    } while (Eil[i].Pav.length() < 0 && Eil[i].Pav.length() > 25 || has_digit(Eil[i].Pav));
    cout << endl;
}

void print_student(duomenys Eil[], int studentu_sk) //funkcija kuri atspausdina gautus rezultatus
{
    cout << "\n\n";
    cout << setw(25) << left << "Vardas"
        << setw(25) << left << "Pavarde"
        << setw(20) << left << "Galutinis(vid.)/"
        << left << "Galutinis(med.)\n"
        << "--------------------------------------------------------------------------------------\n";
    for (int i = 0; i < studentu_sk; i++)
    {
        cout << setw(25) << left << Eil[i].Vard
            << setw(25) << left << Eil[i].Pav
            << setw(20) << left << Eil[i].Gal;
        count_median(Eil[i].paz);
    }
}

int main()
{
    int studentu_sk;
    char temp;
    do
    {
        cout << "Iveskite studentu kieki:";
        cin >> studentu_sk;
    } while (int(studentu_sk) < 0 || int(studentu_sk) > 300);
    duomenys Eil[25];
    do
    {
        cout << "Jeigu norite, kad studentu pazymiai butu suvesti automatiskai - SPAUSKITE \"A arba a\"\n O jeigu norite suvesti duomenis patys - RASYKITE \"P arba p\"\n";
        cin >> temp;
        if (temp != 'a' && temp != 'A' && temp != 'p' && temp != 'P') { cout << "Netinkamas simbolis. Iveskite per naujo\n"; }
    } while (temp != 'a' && temp != 'A' && temp != 'p' && temp != 'P');
    for (int i = 0; i < studentu_sk; i++)
    {
        name_input(Eil, i);
        if (temp == 'p' || temp == 'P') { input_by_hand(Eil, i); }
        else { automated_marks_input(Eil, i, 5); }
    }
    print_student(Eil, studentu_sk);
    system("pause");
    return 0;
}
