#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct VideoStore {
    string name;
    string genre;
    string director;
    double popularity;
    double price;
};

const int MAX_MOVIES = 10;

void Show(VideoStore movies[], int& count) {
    if (count == 0) {
        cout << "\nнемає доступних фільмів.\n";
        return;
    }
    cout << "\n\tНазва\t\tРежисер\t\tЖанр\t\tРейтинг\tЦіна\n";
    for (int i = 0; i < count; i++) {
        cout << i + 1 << ")\t" << movies[i].name << "\t" << movies[i].director << "\t" << movies[i].genre
            << "\t" << movies[i].popularity << "\t" << movies[i].price << endl;
    }
}

void AddMovie(VideoStore movies[], int& count) {
    if (count >= MAX_MOVIES) {
        cout << "\nНеможливо додати більше записів.\n";
        return;
    }

    VideoStore newMovie;
    cout << "\nВведіть назву фільму: ";
    cin.ignore();
    getline(cin, newMovie.name);
    cout << "Введіть режисера: ";
    getline(cin, newMovie.director);
    cout << "Введіть жанр: ";
    getline(cin, newMovie.genre);
    cout << "Введіть рейтинг популярності: ";
    cin >> newMovie.popularity;
    cout << "Введіть ціну: ";
    cin >> newMovie.price;

    movies[count] = newMovie;
    count++;
    cout << "\n успіх\n";
}

void SaveToFile(const string& filename, VideoStore movies[], int count) {
    ofstream file(filename);
    if (!file) {
        cout << "\nПомилка збереження у файл.\n";
        return;
    }

    for (int i = 0; i < count; i++) {
        file << movies[i].name << "\n"
            << movies[i].genre << "\n"
            << movies[i].director << "\n"
            << movies[i].popularity << "\n"
            << movies[i].price << "\n";
    }

    file.close();
    cout << "\nДані успішно збережено у файл.\n";
}

void LoadFromFile(const string& filename, VideoStore movies[], int& count) {
    ifstream file(filename);
    if (!file) {
        cout << "\nФайл не знайдено. Починаємо з порожнього списку.\n";
        return;
    }

    count = 0;
    while (count < MAX_MOVIES) {
        VideoStore temp;
        if (!getline(file, temp.name)) break;
        if (!getline(file, temp.genre)) break;
        if (!getline(file, temp.director)) break;
        if (!(file >> temp.popularity)) break;
        if (!(file >> temp.price)) break;
        file.ignore(32767, '\n'); 
        movies[count] = temp;
        count++;
    }

    file.close();
    if (count > 0) {
        cout << "\n успіх.\n";
    }
    else {
        cout << "\nФайл порожній.\n";
    }
}

void SearchByName(VideoStore movies[], int count) {
    if (count == 0) {
        cout << "\nнемає фільмів для пошуку.\n";
        return;
    }

    string searchName;
    cout << "\nВведіть назву фільму для пошуку: ";
    cin.ignore();
    getline(cin, searchName);

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (movies[i].name == searchName) {
            cout << "\nФільм знайдено: " << endl;
            cout << "Назва: " << movies[i].name << "\nРежисер: " << movies[i].director
                << "\nЖанр: " << movies[i].genre << "\nРейтинг: " << movies[i].popularity
                << "\nЦіна: " << movies[i].price << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nфільм не знайдено.\n";
    }
}

int main() {
    system("chcp 1251>null");

    VideoStore movies[MAX_MOVIES];
    int count = 0;
    string filename = "film.txt";

    LoadFromFile(filename, movies, count);

    int choice;
    do {
        cout << "\nПослуги відеокрамниці:\n";
        cout << "1) Показати всі фільми\n";
        cout << "2) Пошук за назвою\n";
        cout << "3) Додати новий фільм\n";
        cout << "4) Зберегти дані у файл\n";
        cout << "0) Вихід\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
        case 1:
            Show(movies, count);
            break;
        case 2:
            SearchByName(movies, count);
            break;
        case 3:
            AddMovie(movies, count);
            break;
        case 4:
            SaveToFile(filename, movies, count);
            break;
        case 0:
            cout << "\nдос!\n";
            break;
        default:
            cout << "\nнеправильний вибір.\n";
        }
    } while (choice != 0);

    return 0;
}