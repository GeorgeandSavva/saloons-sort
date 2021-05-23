#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <clocale>


using namespace std;

const string zero_to_return = "Для возврата нажмите 0: ";

struct salon {
    int workers;
    int wait_time;
    int price;
    int rating; 
    string name;
    string haircut;
};

vector<salon> fromprevsteps[4];

vector<string> read_file(string filename) {
    ifstream file (filename);

    vector<string> row;
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            row.push_back(line);
        }
    }

    return row;
}

salon init_salon_from_record(vector<string> record) {
    salon s;
    
    try {
        s.name = record.at(0);
        s.workers = atoi(record.at(1).c_str());
        s.haircut = record.at(2);
        s.wait_time = atoi(record.at(3).c_str());
        s.price = atoi(record.at(4).c_str());
        s.rating = atoi(record.at(5).c_str());
    } catch (const std::out_of_range & ex) {
        cout << "not valid record" << endl;
    }

    return s;
}

vector<salon> init_saloons_from_file(vector<string> filelines) {
    vector<salon> saloons;
    string temp;

    for (string l : filelines) {
        stringstream s(l);
        vector<string> linesinrow;
        salon sl;

        while(getline(s, temp, ',')) {
            linesinrow.push_back(temp);
        }

        if (linesinrow.size() != 6) {
            cout << l << ": " << "is set incorrectly" << endl;
        }

        sl = init_salon_from_record(linesinrow);

        saloons.push_back(sl);
    }

    return saloons;
}

vector<salon> sort_by_price() {
    const int val = 350;
    
    int input;
    vector<salon> sorted;

    cout << "За какую цену вы хотите подстричься? Если меньше " << val << " нажмите 1, если больше " << val << " нажмите 2. " << zero_to_return;
    cin >> input;

    if (input == 0) {
        return sort_by_price();
    }

    for (salon s : fromprevsteps[0]) {
        if (input == 1 && s.price < val) {
            sorted.push_back(s);
        }
        if (input == 2 && s.price > val) {
            sorted.push_back(s);
        }
    }

    return sorted;
}

vector<salon> sort_by_wait_time() {
    const int time = 6;
    
    int input;
    vector<salon> sorted;

    cout << "Какое время ожидания вас устраивает? Если меньше " << time << " нажмите 1, если больше " << time << " нажмите 2 " << zero_to_return;
    cin >> input;

    if (input == 0) {
        fromprevsteps[1] = sort_by_price();

        return sort_by_wait_time();
    }

    for (salon s : fromprevsteps[1]) {
        if (input == 1 && s.wait_time < time) {
            sorted.push_back(s);
        }
        if (input == 2 && s.wait_time > time) {
            sorted.push_back(s);
        }
    }

    return sorted;
}

vector<salon> sort_by_haircut() {
    std::string a = "мужская", b = "женская";
    
    int input;
    vector<salon> sorted;

    cout << "Какая стрижка вам нужна? Если " << a << " нажмите 1, если " << b << " нажмите 2. " << zero_to_return;
    cin >> input;

    if (input == 0) {
        fromprevsteps[2] = sort_by_wait_time();

        return sort_by_haircut();
    }

    for (salon s : fromprevsteps[2]) {
        if (input == 1 && s.haircut == a) {
            sorted.push_back(s);
        }
        if (input == 2 && s.haircut == b) {
            sorted.push_back(s);
        }
    }

    return sorted;
}

vector<salon> sort_by_workers() {
    const int worker = 4;
    
    int input;
    vector<salon> sorted;

    cout << "Какое количесво работников в парикмахерской вас устраивает? Если меньше " << worker << " нажмите 1, если больше " << worker << " нажмите 2 " << zero_to_return;
    cin >> input;

    if (input == 0) {
        fromprevsteps[3] = sort_by_haircut();

        return sort_by_workers();
    }

    for (salon s : fromprevsteps[3]) {
        if (input == 1 && s.workers < worker) {
            sorted.push_back(s);
        }
        if (input == 2 && s.workers > worker) {
            sorted.push_back(s);
        }
    }

    return sorted;
}

int main(int arglen, char* argv[]) 
{
    setlocale(LC_CTYPE, "rus");
    if (arglen != 2) {
        cout << "Укажите пожалуйста имя файла";
        return 2;
    }

    string filename = argv[1];
    vector<string> filelines = read_file(filename);

    fromprevsteps[0] = init_saloons_from_file(filelines);
    fromprevsteps[1] = sort_by_price();
    fromprevsteps[2] = sort_by_wait_time();
    fromprevsteps[3] = sort_by_haircut();
    vector<salon> saloons = sort_by_workers();

    if (saloons.size() == 0) {
        cout << "Ничего не найдено." << endl;

        return 0;
    } 

    for (salon s : saloons) {
        cout << "Вам подходит парикмахерская \"" << s.name << "\":" << endl 
             << "\tЦена: " << s.price << "₽" << endl
             << "\tВремя ожидания: " << s.wait_time << " минуты" << endl
             << "\tТип стрижки: " << s.haircut << endl
             << "\tКоличество работников: " << s.workers << endl
             << "\tРейтинг парикмахерской: " << s.rating << "%" << endl;
    }

    return 0;
}
 