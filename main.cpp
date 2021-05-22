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

vector<salon> sort_by_price(vector<salon> saloons) {
    const int val = 350;
    
    int input;
    vector<salon> sorted;

    cout << "За какую цену вы хотите подстричься? Если меньше " << val << " нажмите 1, если больше " << val << " нажмите 2. " << zero_to_return;
    cin >> input;

    if (input == 0) {
        return sort_by_price(saloons);
    }

    for (salon s : saloons) {
        if (input == 1 && s.price < val) {
            sorted.push_back(s);
        }
        if (input == 2 && s.price > val) {
            sorted.push_back(s);
        }
    }

    return sorted;
}

vector<salon> sort_by_wait_time(vector<salon> saloons) {
    const int time = 6;
    
    int input;
    vector<salon> sorted;

    cout << "Какое время ожидания вас устраивает? Если меньше " << time << " нажмите 1, если больше " << time << " нажмите 2. Для возврата нажмите 0: ";
    cin >> input;

    if (input == 0) {
        saloons = sort_by_price(saloons);

        return sort_by_wait_time(saloons);
    }

    for (salon s : saloons) {
        if (input == 1 && s.wait_time < time) {
            sorted.push_back(s);
        }
        if (input == 2 && s.wait_time > time) {
            sorted.push_back(s);
        }
    }

    return sorted;
}

vector<salon> sort_by_haircut(vector<salon> saloons) {
    std::string a = "мужская", b = "женская";
    
    int input;
    vector<salon> sorted;

    cout << "Какая стрижка вам нужна? Если " << a << " нажмите 1, если " << b << " нажмите 2. " << zero_to_return;
    cin >> input;

    if (input == 0) {
        saloons = sort_by_wait_time(saloons);

        return sort_by_haircut(saloons);
    }

    for (salon s : saloons) {
        if (input == 1 && s.haircut == a) {
            sorted.push_back(s);
        }
        if (input == 2 && s.haircut == b) {
            sorted.push_back(s);
        }
    }

    return sorted;
}

vector<salon> sort_by_workers(vector<salon> saloons) {
    const int worker = 4;
    
    int input;
    vector<salon> sorted;

    cout << "Какое количесво работников в парикмахерской устраивает? Если меньше " << worker << " нажмите 1, если больше " << worker << " нажмите 2. Для возврата нажмите 0: ";
    cin >> input;

    if (input == 0) {
        saloons = sort_by_haircut(saloons);

        return sort_by_workers(saloons);
    }

    for (salon s : saloons) {
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
        return 2;
    }

    string filename = argv[1];
    vector<string> filelines = read_file(filename);

    vector<salon> saloons = init_saloons_from_file(filelines);
    vector<salon> saloons_by_price = sort_by_price(saloons);
    vector<salon> saloons_by_wait_time = sort_by_wait_time(saloons_by_price);
    vector<salon> saloons_by_reviews = sort_by_haircut(saloons_by_wait_time);
    vector<salon> saloons_by_workers = sort_by_workers(saloons_by_reviews);

    if (saloons_by_workers.size() == 0) {
        cout << "Ничего не найдено." << endl;

        return 0;
    } 

    for (salon s : saloons_by_workers) {
        cout << s.name 
             << ": \n\tЦена: " << s.price 
             << "₽\n\tВремя ожидания: " << s.wait_time 
             << " минут\n\tТип стрижки: " << s.haircut 
             << "\n\tКоличество работников: " << s.workers 
             << "\n\tРейтинг организации: " << s.rating << "%" << endl;
    }

    return 0;
}
 