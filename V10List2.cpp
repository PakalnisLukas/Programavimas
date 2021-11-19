#include "biblioteka.h"


double Vidurkis(vector<int> Grade) //apskaiciuojamas vidurkis 
{
    if (Grade.size() == 0)
        throw std::domain_error("Iveskite teigiama skaiciu");

    return std::accumulate(Grade.begin(), Grade.end(), 0.0) / Grade.size();
}

double Mediana(vector<int> Grade) //apskaiciuojama mediana
{
    typedef vector <int>::size_type VecSize;
    VecSize size = Grade.size();

    if (size == 0)
        throw std::domain_error("Iveskite teigiama skaiciu");

    sort(Grade.begin(), Grade.end());

    VecSize Middle = size / 2;

    if (size % 2 == 0)
        return (Grade[Middle - 1] + Grade[Middle]) / 2;
    else
        return Grade[Middle];
}

double GP(double Exam, double Score)
{
    return 0.4 * Score + 0.6 * Exam;
}


double GP(const Studentas& S, double (*Criteria)(vector<int>))
{
    return GP(S.Egzaminas, Criteria(S.Rezultatai));
}

bool Raides(string Input) //tikrinama ar ivestos raides

{
    for (int i = 0; i < Input.length(); i++)
    {
        int UppercaseCharacter = toupper(Input[i]);

        if (UppercaseCharacter < 'A' || UppercaseCharacter > 'Z')
        {
            if (UppercaseCharacter != 32)
                return false;
        }
    }
    return true;
}

bool Skaiciai(const string& str) //tikrinama ar ivesti skaiciai
{
    return all_of(str.begin(), str.end(), ::isdigit);
}

void DidRaid(string& Text)
{
    if (islower(Text.at(0)))
        Text.at(0) = toupper(Text.at(0));

    for (int i = 1; i < Text.length(); i++)
        if (isupper(Text.at(i)))
            Text.at(i) = tolower(Text.at(i));
}

bool Lyginimas(const Studentas& x, const Studentas& y)
{
    return x.Pavarde < y.Pavarde;
}

void NewLine()
{
    cout << endl;
}


void Generavimas(size_t Value)
{

    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine eng(seed);
    std::uniform_int_distribution <int> Interval(1, 10), Amount(10, 20);

    int NumberOfStudents = Value,
        AmountOfResults = Amount(eng);

    std::ofstream Write;
    Write.open("Studentai_" + std::to_string(Value) + ".txt");

    for (size_t j = 1; j <= NumberOfStudents; j++)
    {
        Write << "Vardas" + std::to_string(j) << " Pavardë" + std::to_string(j) << " " << Interval(eng);
        vector <int> Results;
        vector <int>::iterator IT;

        for (size_t k = 0; k < AmountOfResults; k++)
            Results.push_back(Interval(eng));

        for (IT = Results.begin(); IT < Results.end(); IT++)
            Write << " " << *IT;

        Write << endl;
    }
    Write.close();
}
int pasirinkimas()
{
    int var;
    cout << "Ar norite duomenis suvesti pats( iveskite 1)\n Ar norite, kad jie butu nuskaityti is failo (iveskite 2)\n Ar norite generuoti 5 tekstinius failus (iveskite 3)" << endl;
label:
    cin >> var;

    while (cin.fail())
    {
        cout << "Klaida, turite ivesti 1 arba 2 arba 3" << std::endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> var;
    }
    if (var < 1 or var>3)
    {
        cout << "Toks pasirinkimas negalimas, iveskite 1 arba 2 arba 3" << endl;
        goto label;
    }
    return var;
}
