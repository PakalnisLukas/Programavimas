#include "biblioteka.h"

int main()
{
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine eng(seed);
    std::uniform_int_distribution <int> dist(1, 10);

    vector <Studentas> S;
    Studentas StudentObject;
    string Entry;
    int EntryChoice;
    string::size_type IlgiausiasVardas = 0,
        IlgiausiaPavarde = 0;

    EntryChoice = pasirinkimas();

    if (EntryChoice == 1)
    {
        int AverageChoice;

        NewLine();
        cout << "Kaip norite apskaiciuoti studento galutini pazymi?\nSpauskite 1, jei norite, jog butu naudojamas studento rezultatu vidurkis,\n2, jei norite, jog butu naudojama mediana." << endl;

        while (cin >> Entry)
        {
            if (Entry == "1")
            {
                AverageChoice = 1;
                break;
            }
            else if (Entry == "2")
            {
                AverageChoice = 2;
                break;
            }
            else
                cout << Error << endl;
        }
        cin.ignore();

        while (true)
        {
            NewLine();
            cout << "Iveskite " << S.size() + 1 << "-o studento varda bei pavarde, baige paspauskite Enter" << endl;
            getline(cin, Entry);

            if (!Entry.empty())
            {
                int Position = Entry.find(" ");

                if (Entry.length() - 1 > Position && Raides(Entry) == true)
                {
                    StudentObject.Vardas = Entry.substr(0, Position);
                    IlgiausiasVardas = max(IlgiausiasVardas, StudentObject.Vardas.length());
                    DidRaid(StudentObject.Vardas);
                    StudentObject.Pavarde = Entry.substr(Position + 1);;
                    IlgiausiaPavarde = max(IlgiausiaPavarde, StudentObject.Pavarde.length());
                    DidRaid(StudentObject.Pavarde);
                    NewLine();

                    cout << "Kokiu formatu bus pateikiami studento namu darbu rezultatai?\nSpauskite 1, jei rezultatus ivesite Jus,\n2, jei norite, jog duomenys butu sugeneruoti atsitiktinai." << endl;

                    while (cin >> Entry)
                    {
                        if (Entry == "1")
                        {
                            StudentObject.Rezultatai.clear();
                            cout << "Veskite skaicius nuo 1-o iki 10-ies, noredami baigti vedima iveskite bet koki kita skaiciu." << endl;
                            while (cin >> Entry)
                            {
                                if (Skaiciai(Entry) == true)
                                {
                                    int Mark = stoi(Entry);

                                    if (Mark > 0 && Mark < 11)
                                        StudentObject.Rezultatai.push_back(Mark);

                                    else
                                    {
                                        if (StudentObject.Rezultatai.size() != 0)
                                            break;
                                        else
                                            cout << "Iveskite skaiciu." << endl;
                                    }
                                }
                                else
                                    cout << Error << endl;
                            }
                            break;
                        }
                        else if (Entry == "2")
                        {
                            StudentObject.Rezultatai.clear();
                            cout << "Kiek skaiciu generuoti?" << endl;

                            while (cin >> Entry)
                            {
                                if (Skaiciai(Entry) == true)
                                {
                                    int Mark = stoi(Entry);

                                    if (Mark > 0)
                                    {
                                        for (int i = 0; i < Mark; i++)
                                            StudentObject.Rezultatai.push_back(dist(eng));
                                        break;
                                    }
                                    else
                                    {
                                        if (StudentObject.Rezultatai.size() != 0)
                                            break;
                                        else
                                            cout << "Truksta duomenu." << endl;
                                    }
                                }
                                else
                                    cout << Error << endl;
                            }
                            break;
                        }
                        else
                        {
                            cin.ignore();
                            cin.clear();
                            cout << Error << endl;
                        }
                    }
                    cout << "Iveskite studento egzamino rezultata:" << endl;

                    string EntryString;

                    while (cin >> EntryString)
                    {
                        int Entry;

                        if (Skaiciai(EntryString) == false)
                            Entry = -1;
                        else
                            Entry = stoi(EntryString);

                        if (Entry < 0 || Entry > 10)
                            cout << Error << endl;
                        else
                        {
                            StudentObject.Egzaminas = Entry;
                            break;
                        }
                    }

                    S.push_back(StudentObject);
                    sort(S.begin(), S.end(), Lyginimas);

                    cin.ignore();
                    cin.clear();
                }
                else
                    cout << Error << endl;
            }

            else
            {
                if (S.size() == 0)
                    cout << "Iveskite bent vieno studento duomenis." << endl;


                else
                {
                    auto Start = std::chrono::high_resolution_clock::now();
                    auto StartSorting = std::chrono::high_resolution_clock::now();
                    vector<Studentas> Neigiami;
                    vector<Studentas>::iterator IT = S.begin();
                    while (IT != S.end())
                    {
                        if (GP((*IT), Vidurkis) < 5.0 && GP((*IT), Mediana) < 5.0)
                        {
                            Neigiami.push_back(*IT);
                        }
                        else
                            IT++;
                    }
                    vector<Studentas> Teigiami;
                    vector<Studentas>::iterator II = S.begin();
                    while (IT != S.end())
                    {
                        if (GP((*II), Vidurkis) >= 5.0 && GP((*II), Mediana) >= 5.0)
                        {
                            Teigiami.push_back(*II);
                        }
                        else
                            II++;
                    }


                    std::ofstream IrasymasNeigiami;
                    IrasymasNeigiami.open("Neigiami.txt");

                    for (vector<Studentas>::iterator IT = Neigiami.begin(); IT != Neigiami.end(); IT++)
                    {
                        IrasymasNeigiami << (*IT).Vardas << string(IlgiausiasVardas + 1 - (*IT).Vardas.size(), ' ');
                        IrasymasNeigiami << (*IT).Pavarde << string(IlgiausiaPavarde + 1 - (*IT).Pavarde.size(), ' ');

                        streamsize prec = cout.precision();
                        if (AverageChoice == 1)
                            IrasymasNeigiami << std::fixed << setprecision(2) << GP((*IT), Vidurkis) << setprecision(prec) << endl;
                        else
                            IrasymasNeigiami << std::fixed << setprecision(2) << GP((*IT), Mediana) << setprecision(prec) << endl;

                    }
                    for (auto i = 0; i != IlgiausiasVardas + IlgiausiaPavarde + 10; i++)
                        IrasymasNeigiami << endl;
                    IrasymasNeigiami.close();


                    std::ofstream IrasymasTeigiami;
                    IrasymasTeigiami.open("Teigiami.txt");

                    for (vector<Studentas>::iterator IT = Teigiami.begin(); IT != Teigiami.end(); IT++)
                    {
                        IrasymasTeigiami << (*IT).Vardas << string(IlgiausiasVardas + 1 - (*IT).Vardas.size(), ' ');
                        IrasymasTeigiami << (*IT).Pavarde << string(IlgiausiaPavarde + 1 - (*IT).Pavarde.size(), ' ');

                        streamsize prec = cout.precision();
                        if (AverageChoice == 1)
                            IrasymasTeigiami << std::fixed << setprecision(2) << GP((*IT), Vidurkis) << setprecision(prec) << endl;
                        else
                            IrasymasTeigiami << std::fixed << setprecision(2) << GP((*IT), Mediana) << setprecision(prec) << endl;
                    }
                    for (auto i = 0; i != IlgiausiasVardas + IlgiausiaPavarde + 10; i++)
                        IrasymasTeigiami << endl;
                    IrasymasTeigiami.close();

                    auto EndSorting = std::chrono::high_resolution_clock::now();
                    cout << "Studentu skirstymas ir isvedimas uztruko " << std::chrono::duration_cast<std::chrono::milliseconds>(EndSorting - StartSorting).count() << " ms." << endl;


                    break;
                }
            }
        }
    }

    else if (EntryChoice == 2)
    {
        string Vardas,
            Pavarde,
            Egzaminas,
            EntryLine;

        ifstream ReadFile("kursiokai.txt");

        try
        {
            if (!ReadFile.good())
                throw "Toks failas neegzistuoja.";
        }
        catch (const char* Message)
        {
            cout << Message << endl;
        }
        auto Start = std::chrono::high_resolution_clock::now();

        while (getline(ReadFile, EntryLine))
        {
            auto Start = std::chrono::high_resolution_clock::now();

            istringstream ReadLine(EntryLine);
            ReadLine >> Vardas >> Pavarde >> Egzaminas;

            if (Raides(Vardas) && Raides(Pavarde) && Skaiciai(Egzaminas))
            {
                StudentObject.Vardas = Vardas;
                IlgiausiasVardas = max(IlgiausiasVardas, StudentObject.Vardas.length());
                DidRaid(StudentObject.Vardas);
                StudentObject.Pavarde = Pavarde;
                IlgiausiaPavarde = max(IlgiausiaPavarde, StudentObject.Pavarde.length());
                DidRaid(StudentObject.Pavarde);
                StudentObject.Egzaminas = stoi(Egzaminas);

                if (ReadLine)
                {
                    StudentObject.Rezultatai.clear();

                    while (ReadLine >> Entry)
                    {
                        if (Skaiciai(Entry))
                        {
                            int Mark = stoi(Entry);

                            if (Mark > 0 && Mark < 11)
                                StudentObject.Rezultatai.push_back(Mark);
                        }
                    }

                    S.push_back(StudentObject);
                    ReadLine.clear();
                }
                ReadLine.end;

            }
            else
                cout << Error << endl;
        }
        auto End = std::chrono::high_resolution_clock::now();
        cout << "Duomenu skaitymas uztruko: " << std::chrono::duration_cast<std::chrono::milliseconds>(End - Start).count() << "ms" << endl;


        sort(S.begin(), S.end(), Lyginimas);
        {
            auto Start = std::chrono::high_resolution_clock::now();
            auto StartSorting = std::chrono::high_resolution_clock::now();
            vector<Studentas> Neigiami;
            vector<Studentas>::iterator IT = S.begin();
            while (IT != S.end())
            {
                if (GP((*IT), Vidurkis) < 5.0 && GP((*IT), Mediana) < 5.0)
                {
                    Neigiami.push_back(*IT);
                }
                else
                    IT++;
            }
            vector<Studentas> Teigiami;
            vector<Studentas>::iterator II = S.begin();
            while (IT != S.end())
            {
                if (GP((*II), Vidurkis) >= 5.0 && GP((*II), Mediana) >= 5.0)
                {
                    Teigiami.push_back(*II);
                }
                else
                    II++;
            }


            std::ofstream IrasymasNeigiami;
            IrasymasNeigiami.open("Neigiami.txt");

            for (vector<Studentas>::iterator IT = Neigiami.begin(); IT != Neigiami.end(); IT++)
            {
                IrasymasNeigiami << (*IT).Vardas << string(IlgiausiasVardas + 1 - (*IT).Vardas.size(), ' ');
                IrasymasNeigiami << (*IT).Pavarde << string(IlgiausiaPavarde + 1 - (*IT).Pavarde.size(), ' ');

                streamsize prec = cout.precision();
                IrasymasNeigiami << std::fixed << setprecision(2) << GP((*IT), Vidurkis) << " " << GP((*IT), Mediana) << setprecision(prec) << endl;

            }
            for (auto i = 0; i != IlgiausiasVardas + IlgiausiaPavarde + 10; i++)
                IrasymasNeigiami << endl;
            IrasymasNeigiami.close();


            std::ofstream IrasymasTeigiami;
            IrasymasTeigiami.open("Teigiami.txt");

            for (vector<Studentas>::iterator IT = Teigiami.begin(); IT != Teigiami.end(); IT++)
            {
                IrasymasTeigiami << (*IT).Vardas << string(IlgiausiasVardas + 1 - (*IT).Vardas.size(), ' ');
                IrasymasTeigiami << (*IT).Pavarde << string(IlgiausiaPavarde + 1 - (*IT).Pavarde.size(), ' ');

                streamsize prec = cout.precision();
                IrasymasTeigiami << std::fixed << setprecision(2) << GP((*IT), Vidurkis) << " " << GP((*IT), Mediana) << setprecision(prec) << endl;
            }
            for (auto i = 0; i != IlgiausiasVardas + IlgiausiaPavarde + 10; i++)
                IrasymasTeigiami << endl;
            IrasymasTeigiami.close();

            auto EndSorting = std::chrono::high_resolution_clock::now();
            cout << "Studentu skirstymas ir isvedimas uztruko " << std::chrono::duration_cast<std::chrono::milliseconds>(EndSorting - StartSorting).count() << " ms." << endl;



        }
        ReadFile.end;
    }

    if (EntryChoice == 3)
    {
        {
            int a;
            cout << "Norite generuoti failus (1) ar naudoti jau sugeneruotus (0) ?";
        label:
            cin >> a;
            if (a == 1)

                for (size_t i = 1000; i <= 10000000; i *= 10)
                {
                    S.clear();

                    auto Start = std::chrono::high_resolution_clock::now();
                    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
                    std::default_random_engine eng(seed);
                    std::uniform_int_distribution <int> Interval(1, 10), Amount(10, 20);

                    int NumberOfStudents = i,
                        AmountOfResults = Amount(eng);

                    std::ofstream Write;
                    Write.open("Studentai_" + std::to_string(i) + ".txt");

                    for (size_t j = 1; j <= NumberOfStudents; j++)
                    {
                        Write << "Vardas" + std::to_string(j) << " Pavarde" + std::to_string(j) << " " << Interval(eng);

                        vector <int> Rezultatai;
                        vector <int>::iterator IT;

                        for (size_t k = 0; k < AmountOfResults; k++)
                            Rezultatai.push_back(Interval(eng));

                        for (IT = Rezultatai.begin(); IT < Rezultatai.end(); IT++)
                            Write << " " << *IT;

                        Write << endl;
                    }
                    Write.close();
                    auto End = std::chrono::high_resolution_clock::now();
                    cout << "Studentai_" + std::to_string(i) + ".txt generavimas uztruko " << std::chrono::duration_cast<std::chrono::milliseconds>(End - Start).count() << " ms." << endl;
                }    S.clear();

                if (a != 1 and a != 0)
                {
                    cout << "toks variantas negalimas, iveskite kita skaiciu ";
                    goto label;
                }

                for (size_t i = 1000; i <= 10000000; i *= 10)
                {
                    S.clear();
                    string Vardas,
                        Pavarde,
                        Egzaminas,
                        EntryLine;


                    ifstream ReadFile("Studentai_" + std::to_string(i) + ".txt");

                    try
                    {
                        if (!ReadFile.good())
                            throw "Toks failas neegzistuoja.";
                    }
                    catch (const char* Message)
                    {
                        cout << Message << endl;
                    }

                    while (getline(ReadFile, EntryLine))
                    {
                        istringstream ReadLine(EntryLine);
                        ReadLine >> Vardas >> Pavarde >> Egzaminas;

                        StudentObject.Vardas = Vardas;
                        IlgiausiasVardas = max(IlgiausiasVardas, StudentObject.Vardas.length());
                        StudentObject.Pavarde = Pavarde;
                        IlgiausiaPavarde = max(IlgiausiaPavarde, StudentObject.Pavarde.length());
                        StudentObject.Egzaminas = stoi(Egzaminas);

                        if (ReadLine)
                        {
                            StudentObject.Rezultatai.clear();

                            while (ReadLine >> Entry)
                            {
                                if (Skaiciai(Entry))
                                {
                                    int Mark = stoi(Entry);

                                    if (Mark > 0 && Mark < 11)
                                        StudentObject.Rezultatai.push_back(Mark);
                                }
                            }
                            S.push_back(StudentObject);
                            ReadLine.clear();
                        }
                        ReadLine.end;
                    }

                    {
                        auto Start = std::chrono::high_resolution_clock::now();
                        auto StartSorting = std::chrono::high_resolution_clock::now();
                        vector<Studentas> Neigiami;
                        vector<Studentas>::iterator IT = S.begin();
                        while (IT != S.end())
                        {
                            if (GP((*IT), Vidurkis) < 5.0 && GP((*IT), Mediana) < 5.0)
                            {
                                Neigiami.push_back(*IT);
                            }
                            else
                                IT++;
                        }
                        vector<Studentas> Teigiami;
                        vector<Studentas>::iterator II = S.begin();
                        while (IT != S.end())
                        {
                            if (GP((*II), Vidurkis) >= 5.0 && GP((*II), Mediana) >= 5.0)
                            {
                                Teigiami.push_back(*II);
                            }
                            else
                                II++;
                        }

                        std::ofstream IrasymasNeigiami;
                        IrasymasNeigiami.open("Neigiami" + std::to_string(i) + ".txt");

                        for (vector<Studentas>::iterator IT = Neigiami.begin(); IT != Neigiami.end(); IT++)
                        {
                            IrasymasNeigiami << (*IT).Vardas << string(IlgiausiasVardas + 1 - (*IT).Vardas.size(), ' ');
                            IrasymasNeigiami << (*IT).Pavarde << string(IlgiausiaPavarde + 1 - (*IT).Pavarde.size(), ' ');

                            streamsize prec = cout.precision();
                            IrasymasNeigiami << std::fixed << setprecision(2) << GP((*IT), Vidurkis) << " " << GP((*IT), Mediana) << setprecision(prec) << endl;

                        }
                        for (auto i = 0; i != IlgiausiasVardas + IlgiausiaPavarde + 10; i++)
                            IrasymasNeigiami << endl;
                        IrasymasNeigiami.close();


                        std::ofstream IrasymasTeigiami;
                        IrasymasTeigiami.open("Teigiami" + std::to_string(i) + ".txt");

                        for (vector<Studentas>::iterator IT = Teigiami.begin(); IT != Teigiami.end(); IT++)
                        {
                            IrasymasTeigiami << (*IT).Vardas << string(IlgiausiasVardas + 1 - (*IT).Vardas.size(), ' ');
                            IrasymasTeigiami << (*IT).Pavarde << string(IlgiausiaPavarde + 1 - (*IT).Pavarde.size(), ' ');

                            streamsize prec = cout.precision();
                            IrasymasTeigiami << std::fixed << setprecision(2) << GP((*IT), Vidurkis) << " " << GP((*IT), Mediana) << setprecision(prec) << endl;
                        }
                        for (auto i = 0; i != IlgiausiasVardas + IlgiausiaPavarde + 10; i++)
                            IrasymasTeigiami << endl;
                        IrasymasTeigiami.close();

                        auto EndSorting = std::chrono::high_resolution_clock::now();
                        cout << "Studentu skirstymas ir isvedimas uztruko " << std::chrono::duration_cast<std::chrono::milliseconds>(EndSorting - StartSorting).count() << " ms." << endl;

                    }
                }
        }
        return 0;
    }
}
