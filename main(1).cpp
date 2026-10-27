/**************************************
 * Автор:   Михайлов Даниил           *
 * Задание: Строки, векторы и словари *
 * Вариант: 16                        *
 **************************************/

#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main() {
  const int maxElementCount = 100;
  const int maxAbsoluteValue = 1000;
  const int maxPrice = 1000;
  const int maxAsciiCode = 127;
  const size_t maxTextLength = 200;
  const size_t maxKeyLength = 40;

  string partLetter;

  if (!getline(cin, partLetter)) {
    cout << "INVALID\n";
    return 1;
  }

  if (!partLetter.empty() && partLetter.back() == '\r') {
    partLetter.pop_back();
  }

  if (partLetter == "A") {
    // Часть A: обратный порядок слов.
    string text;
    string currentWord;
    string result;
    vector<string> words;
    size_t symbolIndex;
    size_t wordIndex;
    unsigned char symbolCode;

    // Блок ввода
    if (!getline(cin, text)) {
      cout << "INVALID\n";
      return 1;
    }

    if (!text.empty() && text.back() == '\r') {
      text.pop_back();
    }

    if (text.size() > maxTextLength) {
      cout << "INVALID\n";
      return 1;
    }

    for (symbolIndex = 0; symbolIndex < text.size(); ++symbolIndex) {
      symbolCode = static_cast<unsigned char>(text[symbolIndex]);
      if (symbolCode > maxAsciiCode) {
        cout << "INVALID\n";
        return 1;
      }
    }

    // Блок расчёта
    for (symbolIndex = 0; symbolIndex < text.size(); ++symbolIndex) {
      if (text[symbolIndex] == ' ') {
        if (!currentWord.empty()) {
          words.push_back(currentWord);
          currentWord.clear();
        }
      } else {
        currentWord += text[symbolIndex];
      }
    }

    if (!currentWord.empty()) {
      words.push_back(currentWord);
    }

    for (wordIndex = words.size(); wordIndex > 0; --wordIndex) {
      if (!result.empty()) {
        result += " ";
      }
      result += words[wordIndex - 1];
    }

    // Блок вывода
    if (words.empty()) {
      cout << "EMPTY\n";
    } else {
      cout << result << "\n";
    }

    return 0;
  }

  if (partLetter == "B") {
    // Часть B: удаление элемента по позиции.
    int elementCount = 0;
    int value = 0;
    int position = 0;
    size_t valueIndex;
    size_t deleteIndex;
    vector<int> values;
    vector<int> result;

    // Блок ввода
    if (!(cin >> elementCount) || elementCount < 0 ||
        elementCount > maxElementCount) {
      cout << "INVALID\n";
      return 1;
    }

    for (valueIndex = 0; valueIndex < static_cast<size_t>(elementCount);
         ++valueIndex) {
      if (!(cin >> value) || value < -maxAbsoluteValue ||
          value > maxAbsoluteValue) {
        cout << "INVALID\n";
        return 1;
      }
      values.push_back(value);
    }

    if (!(cin >> position) || position < 1 || position > elementCount) {
      cout << "INVALID\n";
      return 1;
    }

    // Блок расчёта
    deleteIndex = static_cast<size_t>(position - 1);

    for (valueIndex = 0; valueIndex < values.size(); ++valueIndex) {
      if (valueIndex != deleteIndex) {
        result.push_back(values[valueIndex]);
      }
    }

    // Блок вывода
    if (result.empty()) {
      cout << "EMPTY\n";
    } else {
      cout << result[0];
      for (valueIndex = 1; valueIndex < result.size(); ++valueIndex) {
        cout << " " << result[valueIndex];
      }
      cout << "\n";
    }

    return 0;
  }

  if (partLetter == "C") {
    // Часть C: ключ минимального значения.
    int pairCount = 0;
    int pairIndex;
    int value = 0;
    size_t symbolIndex;
    unsigned char symbolCode;
    string key;
    map<string, int> pairs;
    map<string, int>::iterator pairIterator;
    map<string, int>::iterator minPairIterator;

    // Блок ввода
    if (!(cin >> pairCount) || pairCount < 0 || pairCount > maxElementCount) {
      cout << "INVALID\n";
      return 1;
    }

    for (pairIndex = 0; pairIndex < pairCount; ++pairIndex) {
      if (!(cin >> key >> value) || value < -maxAbsoluteValue ||
          value > maxAbsoluteValue || key.size() > maxKeyLength) {
        cout << "INVALID\n";
        return 1;
      }

      for (symbolIndex = 0; symbolIndex < key.size(); ++symbolIndex) {
        symbolCode = static_cast<unsigned char>(key[symbolIndex]);
        if (symbolCode > maxAsciiCode) {
          cout << "INVALID\n";
          return 1;
        }
      }

      // Повторный ключ заменяет прежнее значение.
      pairs[key] = value;
    }

    // Блок расчёта
    if (!pairs.empty()) {
      minPairIterator = pairs.begin();
      for (pairIterator = pairs.begin(); pairIterator != pairs.end();
           ++pairIterator) {
        if (pairIterator->second < minPairIterator->second) {
          minPairIterator = pairIterator;
        }
      }
    }

    // Блок вывода
    if (pairs.empty()) {
      cout << "NONE\n";
    } else {
      cout << minPairIterator->first << " " << minPairIterator->second << "\n";
    }

    return 0;
  }

  if (partLetter == "D") {
    // Часть D: сумма чека.
    int recordCount = 0;
    int priceValue = 0;
    long long total = 0;
    bool isValid = true;
    size_t recordIndex;
    size_t fieldIndex;
    size_t symbolIndex;
    size_t priceIndex;
    size_t lineIndex;
    unsigned char symbolCode;
    string itemName;
    string priceText;
    vector<map<string, string>> records;
    vector<string> fields;
    vector<int> prices;
    vector<string> result;
    map<string, string>::iterator itemIterator;
    map<string, string>::iterator priceIterator;

    // Блок ввода
    if (!(cin >> recordCount) || recordCount < 0 ||
        recordCount > maxElementCount) {
      cout << "INVALID\n";
      return 1;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (recordIndex = 0; recordIndex < static_cast<size_t>(recordCount);
         ++recordIndex) {
      if (!getline(cin, itemName) || !getline(cin, priceText)) {
        cout << "INVALID\n";
        return 1;
      }

      if (!itemName.empty() && itemName.back() == '\r') {
        itemName.pop_back();
      }

      if (!priceText.empty() && priceText.back() == '\r') {
        priceText.pop_back();
      }

      records.push_back({{"item", itemName}, {"price", priceText}});
    }

    for (recordIndex = 0; isValid && recordIndex < records.size();
         ++recordIndex) {
      itemIterator = records[recordIndex].find("item");
      priceIterator = records[recordIndex].find("price");

      if (itemIterator == records[recordIndex].end() ||
          priceIterator == records[recordIndex].end()) {
        isValid = false;
      } else {
        fields.clear();
        fields.push_back(itemIterator->second);
        fields.push_back(priceIterator->second);
      }

      for (fieldIndex = 0; isValid && fieldIndex < fields.size();
           ++fieldIndex) {
        if (fields[fieldIndex].empty() ||
            fields[fieldIndex].size() > maxTextLength) {
          isValid = false;
        } else if (fields[fieldIndex].front() == ' ' ||
                   fields[fieldIndex].back() == ' ') {
          isValid = false;
        }

        for (symbolIndex = 0; isValid && symbolIndex < fields[fieldIndex].size();
             ++symbolIndex) {
          symbolCode = static_cast<unsigned char>(fields[fieldIndex][symbolIndex]);
          if (symbolCode > maxAsciiCode) {
            isValid = false;
          }
        }
      }
    }

    // Цена — число от 0 до maxPrice без ведущих нулей.
    for (recordIndex = 0; isValid && recordIndex < records.size();
         ++recordIndex) {
      priceText = records[recordIndex].at("price");
      priceValue = 0;

      if (priceText.size() > 1 && priceText[0] == '0') {
        isValid = false;
      }

      for (symbolIndex = 0; isValid && symbolIndex < priceText.size();
           ++symbolIndex) {
        if (priceText[symbolIndex] < '0' || priceText[symbolIndex] > '9') {
          isValid = false;
        } else {
          priceValue = priceValue * 10 + (priceText[symbolIndex] - '0');
          // Граница проверяется на каждом шаге, длинная строка не вызовет переполнения.
          if (priceValue > maxPrice) {
            isValid = false;
          }
        }
      }

      prices.push_back(priceValue);
    }

    if (!isValid) {
      cout << "INVALID\n";
      return 1;
    }

    // Блок расчёта
    for (priceIndex = 0; priceIndex < prices.size(); ++priceIndex) {
      total += prices[priceIndex];
    }

    result.push_back("TOTAL " + to_string(total));

    // Блок вывода
    for (lineIndex = 0; lineIndex < result.size(); ++lineIndex) {
      cout << result[lineIndex] << "\n";
    }

    return 0;
  }

  cout << "INVALID\n";
  return 1;
}
