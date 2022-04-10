#include <iostream>
#include <vector>
#include <algorithm>

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

void connection(vector <vector<int>> neighbours, vector <bool>& visited, vector <vector<int>> efforts, int a, int b, int effort_sum, vector <int>& possible_points_effort, vector <int>& possible_points_letter) {
    int new_a = neighbours[a][b]-65;
    visited[a] = true;
  
    //wpisuje potencjalny punkt do tablicy
    effort_sum += efforts[a][b];   
    possible_points_effort.push_back(effort_sum);
    possible_points_letter.push_back(new_a + 65);

    for (int i = 0; i < neighbours[new_a].size(); i++) {
        if (!(visited[neighbours[new_a][i] - 65]))
            connection(neighbours, visited, efforts, new_a, i, effort_sum, possible_points_effort, possible_points_letter);
    }
}

void find_connection(vector <vector<int>> neighbours, vector <vector<int>> efforts, int start, int max_letter, vector <int>& possible_points_effort, vector <int>& possible_points_letter) {
    start -= 65;
    for (int i = 0; i < neighbours[start].size(); i++) {
        //tworzy tablice ktora sprawdza czy dany punkt zostal juz odwiedzony
        vector <bool> visited(max_letter - 64, false);
        
        int effort_sum = 0;
        connection(neighbours, visited, efforts, start, i, effort_sum, possible_points_effort, possible_points_letter);
        visited.clear();
    }
}

void find_smallest(vector <int>& possible_points_effort, vector <int>& possible_points_letter) {
    for (int i = 0; i < possible_points_effort.size()-1; i++) {
        for (int j = i+1; j < possible_points_effort.size(); j++) {
            if (possible_points_letter[i] == possible_points_letter[j]) {
                if (possible_points_effort[i] > possible_points_effort[j]) 
                    swap(possible_points_effort[i], possible_points_effort[j]);
        
                possible_points_effort.erase(possible_points_effort.begin() + j);
                possible_points_letter.erase(possible_points_letter.begin() + j);
                j--;
            }
        }
    }
}

int temporary_min(vector <int> possible_points_effort) {
    sort(possible_points_effort.begin(), possible_points_effort.end());
    return possible_points_effort[possible_points_effort.size()-1];
}


int main()
{
    // n - liczba ulic, max-letter - najwieksza uzyta litera
    int n;
    cin >> n;

    while (n) {
        int max_letter = 64;

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

        //===========================================

        

        //===========================================

        //tablica zawierajaca sasiadow danego punktu z podzialem na rodzaj ulicy: m - dla studenstow, d - dla profesorow
        vector <vector<int>> neighbours_m(max_letter - 64);
        vector <vector<int>> neighbours_d(max_letter - 64);
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

        //tworzy tablice w ktorych beda mozliwe punkty spotkania
        vector <int> possible_points_m_effort;
        vector <int> possible_points_m_letter;
        vector <int> possible_points_d_effort;
        vector <int> possible_points_d_letter;


        find_connection(neighbours_m, efforts_m, s_start, max_letter, possible_points_m_effort, possible_points_m_letter);
        find_connection(neighbours_d, efforts_d, p_start, max_letter, possible_points_d_effort, possible_points_d_letter);

        find_smallest(possible_points_m_effort, possible_points_m_letter);
        find_smallest(possible_points_d_effort, possible_points_d_letter);

        int min_effort = temporary_min(possible_points_m_effort) + temporary_min(possible_points_d_effort);

        for (int i = 0; i < possible_points_m_effort.size(); i++) {
            for (int j = 0; j < possible_points_d_effort.size(); j++) {
                if (possible_points_m_letter[i] == possible_points_d_letter[j]) {
                    if (possible_points_m_effort[i] + possible_points_d_effort[j] < min_effort)
                        min_effort = possible_points_m_effort[i] + possible_points_d_effort[j];

                }
            }
        }

        vector <int> out_letters;
        cout << min_effort;
        for (int i = 0; i < possible_points_m_effort.size(); i++) {
            for (int j = 0; j < possible_points_d_effort.size(); j++) {
                if (possible_points_m_letter[i] == possible_points_d_letter[j]) {
                    if (possible_points_m_effort[i] + possible_points_d_effort[j] == min_effort)
                        out_letters.push_back(possible_points_m_letter[i]);

                }
            }
        }

        //wypisywanie w porzadku leksykograficznym
        sort(out_letters.begin(), out_letters.end());
        for (int i = 0; i < out_letters.size(); i++)
            cout << ' ' << (char)out_letters[i];

        cin >> n;
        if (n)
            cout << '\n';

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
        possible_points_m_effort.clear();
        possible_points_m_letter.clear();
        possible_points_d_effort.clear();
        possible_points_d_letter.clear();
    }
}