#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <chrono>
#include <numeric>
#include <list>

struct duomenys {
	std::string Vard, Pav;
	std::vector<int> paz = { 0 };
	int egz;
	float GP = 0;
};

duomenys get(std::list<duomenys> _list, int _i) {
	std::list<duomenys>::iterator it = _list.begin();
	for (int i = 0; i < _i; i++) {
		++it;
	}
	return *it;
}

int generate_random()
{
	return rand() % 10 + 1;
}

std::vector<int> auto_marks(int how_many_marks)
{
	std::vector<int> skaiciai;
	for (int i = 0; i < how_many_marks; i++)
	{
		skaiciai.push_back(generate_random());
	}
	return skaiciai;

}
float count_GP(std::vector<int> skaiciai) {
	duomenys Eil;
	Eil.GP = 0.4 * std::accumulate(skaiciai.begin(), skaiciai.end(), 0) / skaiciai.size() + 0.6 * generate_random();
	return Eil.GP;
}

int generavimas(std::vector<int> pazymiai)
{
	int kiek;
	std::cout << "Iveskite studentu skaiciu: ";
	std::cin >> kiek;
	std::string pavadinimas = "Studentai_" + std::to_string(kiek) + ".txt";
	std::ofstream out_data(pavadinimas);
	std::vector<int> skaiciai;
	duomenys Eil;
	out_data << std::setw(20) << std::left << "Vardas"
		<< std::setw(20) << std::left << "Pavarde"
		<< std::setw(20) << std::left << "Galutinis(vid.)" << std::endl;
	
	
	
	for (int s = 1; s <= kiek; s = s + 1)
	{
		skaiciai = auto_marks(5);
		out_data << std::setw(20) << "Vardas" + std::to_string(s) <<
			std::setw(20) << "Pavarde" + std::to_string(s) <<
			std::setw(18) << count_GP(skaiciai) << std::endl;;
		skaiciai.clear();
	}
	return kiek;
}
void readFromFile(std::list<duomenys>& Eil, int kiek)
{
	int student_counter = 0;
	std::ifstream fileRead;
	std::string pavadinimas = "Studentai_" + std::to_string(kiek) + ".txt";
	std::string buff;
	fileRead.open(pavadinimas);
	if (fileRead.is_open()) {

		auto start = std::chrono::high_resolution_clock::now();
		auto st = start;
		getline(fileRead >> std::ws, buff);
		while (student_counter < kiek)
		{
			duomenys duom;
			fileRead >> duom.Vard;
			fileRead >> duom.Pav;
			fileRead >> duom.GP;
			Eil.push_back(duom);
			student_counter++;
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = end - start;
		std::cout << "Failo su " + std::to_string(kiek) + " studentu nuskaitymas uztruko: " << diff.count() << "s\n";
	}
}

int main()

{
	std::vector<int> skaiciai;

	int kiek = generavimas(skaiciai);
	std::list<duomenys> studentai;
	readFromFile(studentai, kiek);
	std::list<duomenys> teigiami;
	std::list<duomenys> neigiami;
	int neig = 0;
	int teig = 0;

	auto start = std::chrono::high_resolution_clock::now();
	auto st = start;
	for (int i = 0; i < kiek; i++) {
		float paz = 5.00;
		if (get(studentai, i).GP < paz) {
			neigiami.push_back(get(studentai, i));
			neig++;
		}
	}
	for (int j = 0; j < kiek; j++) {
		float paz = 5.00;
		int _gp = get(studentai, j).GP;
		if (get(studentai, j).GP >= paz) {
			teigiami.push_back(get(studentai, j));
			teig++;
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	std::cout << "Failo rusiavimas su " + std::to_string(kiek) + " studentais i dvi grupes uztruko : " << diff.count() << "s\n";
	std::string pav;
	pav = "neigiami_" + std::to_string(kiek) + ".txt";
	std::ofstream neig_failas(pav);
	auto start1 = std::chrono::high_resolution_clock::now();
	auto st1 = start1;
	for (int i = 0; i < neig; i++) {
		
		float paz = 5.00;
		if (get(neigiami, i).GP < 5.00) {
			neig_failas << get(neigiami, i).Vard << std::setw(20) << get(neigiami, i).Pav << std::setw(18) << get(neigiami, i).GP << std::endl;
		}
	}
	auto end1 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff1 = end1 - start1;
	std::cout << "Failo isvedimas su " + std::to_string(kiek) + " studentais  i neigiamus uztruko : " << diff1.count() << "s\n";

	pav = "teigiami_" + std::to_string(kiek) + ".txt";
	std::ofstream teig_failas(pav);
	auto start2 = std::chrono::high_resolution_clock::now();
	auto st2 = start2;
	for (int j = 0; j < kiek; j++) {
		float paz = 5.00;
		if (get(studentai, j).GP >= paz) {
			teig_failas << get(studentai, j).Vard << std::setw(20) << get(studentai, j).Pav << std::setw(18) << get(studentai, j).GP << std::endl;
		}
	}
	auto end2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff2 = end2 - start2;
	std::cout << "Failo isvedimas su " + std::to_string(kiek) + " studentais  i teigiamus uztruko : " << diff2.count() << "s\n";
}
