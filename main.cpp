#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

enum BusinessType { MAIN, ADDITIONAL, FRANCHISE };

struct Location {
    char city[40];
};

struct Marketplace {
    char name[40];
    int pvz_count;
    Location loc;
    double market_value;
    char type[40];
    BusinessType b_type;
};

// Функции для 9 практики

void displayOne(Marketplace m) {
    const char* bTypes[] = { "Основной", "Вспомогательный", "Франшиза" };
    cout << "-----------------------------------" << endl;
    cout << "Маркетплейс: " << m.name << " | Тип: " << m.type << endl;
    cout << "Город: " << m.loc.city << " | ПВЗ: " << m.pvz_count << endl;
    cout << "Стоимость: $" << m.market_value << " млн | Бизнес: " << bTypes[m.b_type] << endl;
}

void wrapperDisplay(Marketplace arr[], int size, const char* title) {
    cout << "\n========== " << title << " ==========" << endl;
    for (int i = 0; i < size; i++) {
        displayOne(arr[i]);
    }
}

void findByName(Marketplace arr[], int size, const char* target) {
    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i].name, target) == 0) {
            wrapperDisplay(&arr[i], 1, "РЕЗУЛЬТАТ ПОИСКА");
            return;
        }
    }
    cout << "\nМаркетплейс '" << target << "' не найден." << endl;
}

void updateData(Marketplace arr[], int size, const char* target) {
    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i].name, target) == 0) {
            cout << "\n[Обновление] Введите новое кол-во ПВЗ для " << target << ": ";
            cin >> arr[i].pvz_count;
            return;
        }
    }
}

int filterFood(Marketplace src[], int srcSize, Marketplace dest[]) {
    int count = 0;
    for (int i = 0; i < srcSize; i++) {
        if (strcmp(src[i].type, "продуктовый") == 0) {
            dest[count++] = src[i];
        }
    }
    return count;
}

int filterNotKazan(Marketplace src[], int srcSize, Marketplace dest[]) {
    int count = 0;
    for (int i = 0; i < srcSize; i++) {
        if (strcmp(src[i].loc.city, "Казань") != 0) {
            dest[count++] = src[i];
        }
    }
    return count;
}

void sortByPVZ(Marketplace arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].pvz_count < arr[j + 1].pvz_count) {
                Marketplace temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Функции для 10 практики

void writePvzToTextFile(Marketplace arr[], int size, const char* filename) {
    ofstream fout;
    fout.open(filename);
    if (!fout.is_open()) {
        cout << "Ошибка: не удалось открыть файл для записи: " << filename << endl;
        return;
    }
    for (int i = 0; i < size; i++) {
        fout << arr[i].name << " " << arr[i].pvz_count << "\n";
    }
    fout.close();
    cout << "\n[Текст. файл] Данные записаны в: " << filename << endl;
}

void readPvzFromTextFile(Marketplace arr[], int size, const char* filename) {
    ifstream fin;
    fin.open(filename);
    if (!fin.is_open()) {
        cout << "Ошибка: не удалось открыть файл для чтения: " << filename << endl;
        return;
    }

    char nameFromFile[40];
    int pvzFromFile;

    while (!fin.eof()) {
        fin >> nameFromFile >> pvzFromFile;
        if (fin.fail()) break;
        for (int i = 0; i < size; i++) {
            if (strcmp(arr[i].name, nameFromFile) == 0) {
                arr[i].pvz_count = pvzFromFile;
            }
        }
    }

    fin.close();
    cout << "[Текст. файл] Данные прочитаны из: " << filename << endl;
}

void writeBinaryFile(Marketplace arr[], int size, const char* filename) {
    ofstream out(filename, ios::binary | ios::out);
    if (!out.is_open()) {
        cout << "Ошибка: не удалось открыть бинарный файл для записи: " << filename << endl;
        return;
    }
    out.write((char*)&size, sizeof(int));
    for (int i = 0; i < size; i++) {
        out.write((char*)&arr[i], sizeof(Marketplace));
    }
    out.close();
    cout << "\n[Бин. файл] Массив структур записан в: " << filename << endl;
}

int readBinaryFile(Marketplace dest[], const char* filename) {
    fstream in(filename, ios::binary | ios::in);
    if (!in.is_open()) {
        cout << "Ошибка: не удалось открыть бинарный файл для чтения: " << filename << endl;
        return 0;
    }
    int size = 0;
    in.read((char*)&size, sizeof(int));
    for (int i = 0; i < size; i++) {
        in.read((char*)&dest[i], sizeof(Marketplace));
    }
    in.close();
    cout << "[Бин. файл] Прочитано " << size << " записей из: " << filename << endl;
    return size;
}

int main() {
    setlocale(LC_ALL, "Russian");

    Marketplace list[20] = {
        {"Самокат",         1200,  {"Москва"},          500.0,  "продуктовый",    MAIN},
        {"OZON",            15000, {"Москва"},          2000.0, "все-подряд",     FRANCHISE},
        {"Wildberries",     20000, {"Подольск"},        3000.0, "все-подряд",     MAIN},
        {"ВкусВилл",        800,   {"Казань"},          300.0,  "продуктовый",    MAIN},
        {"Яндекс Лавка",    500,   {"Санкт-Петербург"}, 400.0, "продуктовый",    MAIN},
        {"Leroy Merlin",    120,   {"Химки"},           1500.0, "товары для дома",MAIN},
        {"KazanExpress",    600,   {"Казань"},          250.0,  "все-подряд",     MAIN},
        {"СберМаркет",      2000,  {"Москва"},          800.0,  "продуктовый",    ADDITIONAL},
        {"AliExpress",      5000,  {"Ханчжоу"},         5000.0, "все-подряд",     MAIN},
        {"IKEA",            50,    {"Эльмхульт"},       4000.0, "товары для дома",MAIN},
        {"Магнит Доставка", 3000,  {"Краснодар"},       700.0,  "продуктовый",    MAIN},
        {"Пятерочка",       4500,  {"Москва"},          900.0,  "продуктовый",    MAIN},
        {"Lamoda",          400,   {"Москва"},          600.0,  "все-подряд",     MAIN},
        {"Hoff",            60,    {"Москва"},          200.0,  "товары для дома",FRANCHISE},
        {"Fix Price",       5000,  {"Москва"},          1100.0, "все-подряд",     MAIN},
        {"Delivery Club",   100,   {"Казань"},          150.0,  "продуктовый",    ADDITIONAL},
        {"Ситилинк",        300,   {"Москва"},          450.0,  "все-подряд",     MAIN},
        {"DNS",             2000,  {"Владивосток"},     800.0,  "все-подряд",     MAIN},
        {"M-Видео",         600,   {"Москва"},          700.0,  "все-подряд",     MAIN},
        {"Лента",           300,   {"Санкт-Петербург"}, 550.0,  "продуктовый",    MAIN}
    };

// Задания из 9 практики
    
    // 1. Фильтрация только продуктовых в новый массив
    Marketplace foodMarkets[20];
    int foodCount = filterFood(list, 20, foodMarkets);
    
    // 2. Сортировка продуктовых пузырьком
    sortByPVZ(foodMarkets, foodCount);
    
    // 3. Вывод данных по конкретному маркетплейсу
    findByName(list, 20, "OZON");
    
    // 4. Вывод 3 самых популярных (после сортировки)
    wrapperDisplay(foodMarkets, 3, "3 САМЫХ ПОПУЛЯРНЫХ ПРОДУКТОВЫХ");
    
    // 5. Изменение данных
    updateData(list, 20, "Самокат");

    // 6. Маркетплейсы не из Казани (в отдельный массив)
    Marketplace notKazan[20];
    int notKCount = filterNotKazan(list, 20, notKazan);
    
    // 7. Вывод отфильтрованных (не из Казани) через обертку
    wrapperDisplay(notKazan, notKCount, "МАРКЕТПЛЕЙСЫ НЕ ИЗ КАЗАНИ");

// Задания из 10 практики

    cout << "\n\nПрактика 10 задание 1(текстовый файл)" << endl;

    writePvzToTextFile(list, 20, "pvz_data.txt");

    list[0].pvz_count = 0;
    list[11].pvz_count = 0;
    cout << "До чтения из файла — Самокат ПВЗ: " << list[0].pvz_count << endl;

    readPvzFromTextFile(list, 20, "pvz_data.txt");
    cout << "После чтения из файла — Самокат ПВЗ: " << list[0].pvz_count << endl;

    cout << "\n\nПрактика 10 задание 2(бинарный файл)" << endl;

    writeBinaryFile(list, 20, "marketplaces.bin");

    Marketplace loadedList[20];
    
    int loadedCount = readBinaryFile(loadedList, "marketplaces.bin");
    wrapperDisplay(loadedList, loadedCount, "ВСЕ ЗАПИСИ ИЗ БИНАРНОГО ФАЙЛА");

    return 0;
}

