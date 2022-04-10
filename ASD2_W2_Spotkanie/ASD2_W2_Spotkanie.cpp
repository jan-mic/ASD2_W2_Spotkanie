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

void set_neighbours(vector <Street> streets, vector <vector<int>>& neighbours, vector <vector<int>>& efforts, int i) {
    neighbours[streets[i].a - 65].push_back(streets[i].b);
    efforts[streets[i].a - 65].push_back(streets[i].effort);
    //sprawdza czy ulica jest dwukierunkowa
    if (streets[i].type == 68) {
        neighbours[streets[i].b - 65].push_back(streets[i].a);
        efforts[streets[i].b - 65].push_back(streets[i].effort);
    }
}

void connection(vector <vector<int>> neighbours, vector <bool>& visited, vector <vector<int>> efforts, int a, int b, int effort_sum, vector <vector<int>>& possible_points) {
    int new_a = neighbours[a][b]-65;
    visited[a] = true;
  
    effort_sum += efforts[a][b];
    vector <int> temporary(2);
    temporary[0] = effort_sum;
    temporary[1] = new_a + 65;
    possible_points.push_back(temporary);
    temporary.clear();
    //cout << effort_sum << (char)(new_a + 65) <<'\n';

    for (int i = 0; i < neighbours[new_a].size(); i++) {
        if (!(visited[neighbours[new_a][i] - 65]))
            connection(neighbours, visited, efforts, new_a, i, effort_sum, possible_points);
    }
}

void find_connection(vector <vector<int>> neighbours, vector <vector<int>> efforts, int start, int max_letter, vector <vector<int>>& possible_points) {
    start -= 65;
    for (int i = 0; i < neighbours[start].size(); i++) {
        //tworzy tablice ktora sprawdza czy dany punkt zostal juz odwiedzony
        vector <bool> visited(max_letter - 64, false);
        
        int effort_sum = 0;
        connection(neighbours, visited, efforts, start, i, effort_sum, possible_points);
        visited.clear();
    }
}


int main()
{
    // n - liczba ulic, max-letter - najwieksza uzyta litera
    int n, max_letter=64;
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
    //wczytuje s_start - punkt startowy studenta, p_start - punkt strartowy profesora
    char s, p;
    int s_start, p_start;
    cin >> s >> p;
    s_start = static_cast<int>(s);
    p_start = static_cast<int>(p);

    //tablica zawierajaca sasiadow danego punktu z podzialem na rodzaj ulicy: m - dla studenstow, d - dla profesorow
    vector < vector<int>> neighbours_m(max_letter - 64);
    vector < vector<int>> neighbours_d(max_letter - 64);
    vector <vector<int>> efforts_m(max_letter - 64);
    vector <vector<int>> efforts_d(max_letter - 64);

    //wczytuje do tabeli sasiadow poszcegolnych punktow
    for (int i = 0; i < n; i++) {
        //sprawdza do ktorej grupy wiekowej nalezy ulica
        if (streets[i].age == 77)
            set_neighbours(streets, neighbours_m, efforts_m, i);
        else
            set_neighbours(streets, neighbours_d, efforts_d, i);

    }
    
    /*/WYPISAWANIE SASIADOW
    for (int i = 0; i < max_letter - 64; i++) {
        cout << "sasiedzi " << (char)(i + 65) << ": ";
        for (int j = 0; j < neighbours_m[i].size(); j++) {
            cout <<efforts_m[i][j]<< (char)neighbours_m[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
    for (int i = 0; i < max_letter - 64; i++) {
        cout << "sasiedzi " << (char)(i + 65) << ": ";
        for (int j = 0; j < neighbours_d[i].size(); j++) {
            cout << efforts_d[i][j] << (char)neighbours_d[i][j] << ' ';
        }
        cout << '\n';
    }*/

    //tworzy tablice w ktorych beda mozliwe punkty spotkania
    vector <vector<int>> possible_points_m;
    vector <vector<int>> possible_points_d;


    find_connection(neighbours_m, efforts_m, s_start, max_letter, possible_points_m);
    find_connection(neighbours_d, efforts_d, p_start, max_letter, possible_points_d);
   
    
    /*
    for (int i = 0; i < possible_points_m.size(); i++) {
        cout << possible_points_m[i][0] <<(char) possible_points_m[i][1] << '\n';
    }
    cout << "\n\n\n";
    for (int i = 0; i < possible_points_d.size(); i++) {
        cout << possible_points_d[i][0] << (char)possible_points_d[i][1] << '\n';
    }*/

    for (int i = 0; i < possible_points_m.size(); i++) {
        for (int j = 0; j < possible_points_d.size(); j++) {

        }
    }



    //czyszczenie pamieci
    streets.clear();
    for (int i = 0; i < neighbours_m.size(); i++) 
        neighbours_m[i].clear();
    for (int i = 0; i < neighbours_d.size(); i++)
        neighbours_d[i].clear();
    neighbours_m.clear();
    neighbours_d.clear();
    efforts_m.clear();
    efforts_d.clear();
    possible_points_m.clear();
    possible_points_d.clear();
}