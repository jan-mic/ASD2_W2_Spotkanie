#include <iostream>
#include <vector>

using namespace std;

class Street {
public:
    // age - ulica ze wzgledu na wiek M/D, type - typ ulicy J/D
    // a - miejsce poczatkowe, b - miejsce koncowe, effort - wysilek na przejscie ulicy
    int age, type, a, b, effort;

    void set(int age, int type, int a, int b, int effort) {
        this->age = age;
        this->type = type;
        this->a = a;
        this->b = b;
        this->effort = effort;
    }
};

void set_neighbours(vector <Street> streets, vector <vector<int>>& neighbours, int i) {
    neighbours[streets[i].a - 65].push_back(streets[i].b);
    //sprawdza czy ulica jest dwukierunkowa
    if (streets[i].type == 68)   
        neighbours[streets[i].b - 65].push_back(streets[i].a);
}


int main()
{
    // n - liczba ulic, max-letter - najwieksza uzyta litera
    int n, max_letter=65;
    cin >> n;

    //tablica przechowujaca informacje o ulicach
    vector <Street> streets(n);
    //wczytuje dane ulic do tablicy
    for (int i = 0; i < n; i++) {
        char age, type, a, b;
        int effort;
        cin >> age >> type >> a >> b >> effort;
        int age_int, type_int, a_int, b_int;
        age_int = static_cast<int>(age);
        type_int = static_cast<int>(type);
        a_int = static_cast<int>(a);
        b_int = static_cast<int>(b);
        streets[i].set(age_int, type_int, a_int, b_int, effort);
        if (a_int > max_letter)
            max_letter = a_int;
        if (b_int > max_letter)
            max_letter = b_int;
    }

    //tablica zawierajaca sasiadow danego punktu z podzialem na rodzaj ulicy: m - dla studenstow, d - dla profesorow
    vector < vector<int>> neighbours_m(max_letter - 64);
    vector < vector<int>> neighbours_d(max_letter - 64);

    for (int i = 0; i < n; i++) {
        //sprawdza do ktorej grupy wiekowej nalezy ulica
        if (streets[i].age == 77)
            set_neighbours(streets, neighbours_m, i);
        else
            set_neighbours(streets, neighbours_d, i);

    }
    
    /*WYPISAWANIE SASIADOW
    for (int i = 0; i < max_letter - 64; i++) {
        cout << "sasiedzi " << (char)(i + 65) << ": ";
        for (int j = 0; j < neighbours_m[i].size(); j++) {
            cout << (char)neighbours_m[i][j] << ' ';
        }
        cout << '\n';
    }*/



}