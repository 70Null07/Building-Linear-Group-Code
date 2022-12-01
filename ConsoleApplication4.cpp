#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

#define informationPartLength 5
using namespace std;

// Функция перевода в двоичную систему
string FuncTo2(int number)
{
    if (number == 1)
        return "1";
    else if (number == 0)
        return "0";
    else
        return FuncTo2(number / 2) + to_string(number % 2);
}

int main()
{

    // Создание порождающей матрицы
    vector<vector<int>> G = { {1,0,0,0,0,1,1,1,1}, {0,1,0,0,0,1,1,1,0}, {0,0,1,0,0,1,1,0,1}, {0,0,0,1,0,1,0,1,1}, {0,0,0,0,1,0,1,1,1} }, GOverall;

    // Вывод порождающей матрицы
    cout << "Порождающая матрица : " << endl;
    for (auto it : G)
    {
        cout << "||";
        for (auto it : it)
            cout << it << " ";
        cout << "||" << endl;
    }

    map <char, vector<int>> BinaryCode, LinearGroupCode;

    char a[] = { 'а', 'б', 'в', 'г', 'д', 'е', ' ', 'ж', 'з', 'и', 'й', 'к', 'л', 'м', 'н', 'о', 'п', 'р', 'с', 'т', 'у', 'ф', 'х', 'ц', 'ч', 'ш', 'щ', 'ъ', 'ы', 'э', 'ю', 'я' };

    for (int j = 0; j < 32; j++)
    {
        string s = FuncTo2(j);
        while (s.size() < informationPartLength)
            s = "0" + s;

        BinaryCode[a[j]] = {s[0] - '0', s[1] - '0', s[2] - '0', s[3] - '0', s[4] - '0'};
    }

    for (auto it : BinaryCode)
    {
        cout << it.first << " ";
        for (auto it : it.second)
            cout << it;
        cout << endl;
    }

    for (auto it : BinaryCode)
    {
        bool successfulSearch = false;
        vector<int> searchResultP;
        searchResultP.resize(4, 0);
        for (auto it2 : G)
        {
            int matchingRatio = 0;
            for (int i = 0; i < informationPartLength; i++)
            {
                if (it.second.at(i) == it2.at(i))
                {
                    matchingRatio++;

                    if (it2.at(i) == 1)
                    {
                        searchResultP.at(0) += it2.at(5);
                        searchResultP.at(1) += it2.at(6);
                        searchResultP.at(2) += it2.at(7);
                        searchResultP.at(3) += it2.at(8);
                    }
                }
            }
            if (matchingRatio == informationPartLength)
                successfulSearch = true;
        }

        if (!successfulSearch)
            GOverall.push_back({ it.second.at(0),it.second.at(1),it.second.at(2),it.second.at(3),it.second.at(4),
                searchResultP.at(0) % 2, searchResultP.at(1) % 2, searchResultP.at(2) % 2, searchResultP.at(3) % 2, });
        searchResultP.clear();
    }


    for (auto it : G)
        GOverall.push_back(it);

    for (auto it : GOverall)
    {
        cout << "||";
        for (auto it : it)
        {
            cout << it << " ";
        }
        cout << "||" << endl;
    }

    for (auto c : a)
    {
        vector <int> bCode = BinaryCode[c];

        for (auto it : GOverall)
        {
            int isIt = 0;
            for (int i = 0; i < informationPartLength; i++)
            {
                if (bCode[i] == it[i])
                    isIt++;
            }
            if (isIt == informationPartLength)
            {
                LinearGroupCode.insert({ c, it });
                break;
            }
        }
    }

    string strForEncode;
    vector<vector<int>> EncodedStr;

    cout << "Введите строку для кодирования: " << endl;
    getline(cin, strForEncode);
    
    for (auto c : strForEncode)
    {
        EncodedStr.push_back(LinearGroupCode[c]);
    }

    cout << "Закодированная строка: " << endl;
    for (auto it : EncodedStr)
        for (auto it : it)
            cout << it;

    cout << endl;

    cout << "Полученная строка: " << endl;
    for (auto it : EncodedStr)
        for (auto it : it)
            cout << it;

    cout << endl;

    vector<vector<int>> controlMatrix = { {1,1,1,1},{1,1,1,0},{1,1,0,1},{1,0,1,1},{0,1,1,1},{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1} };

    vector<vector<int>> DecodedStr;
    for (auto it : EncodedStr)
    {
        // Проверка
        int S1, S2, S3, S4;

        S1 = (it[0] + it[1] + it[2] + it[3] + it[5]) % 2;
        S2 = (it[0] + it[1] + it[2] + it[4] + it[6]) % 2;
        S3 = (it[0] + it[1] + it[3] + it[4] + it[7]) % 2;
        S4 = (it[0] + it[2] + it[3] + it[4] + it[8]) % 2;
        
        if (S1 + S2 + S3 + S4 != 0)
        {
            vector<int> S = { S1,S2,S3,S4 };
            int digit = 0;
            for (auto it1 : controlMatrix)
            {
                if (S == it1)
                {
                    cout << "Произошла ошибка в " << digit+1 << " разряде" << endl;
                    if (it[digit] == 0)
                        it[digit] = 1;
                    else
                        it[digit] = 0;
                }
                digit++;
            }
        }
        DecodedStr.push_back(it);
    }

    cout << "Декодированная строка: " << endl;
    for (auto it : DecodedStr)
        for (auto it1 : LinearGroupCode)
            if (it == it1.second)
                cout << it1.first;
	return 0;
}