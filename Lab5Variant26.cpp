/*****************************************
 * Автор:   Хан Кирилл                    *
 * Задание: Строки, векторы и словари     *
 * Вариант: 26                            *
 *****************************************/

#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main() {
  const int maxCount = 100, maxValue = 1000;
  const size_t maxLength = 200, maxKeyLength = 40, titleLength = 12;
  const unsigned char maxAscii = 127;
  int valid = 1, count = 0;
  string part;
  vector<string> result;

  getline(cin, part);
  if (part != "A" && part != "B" && part != "C" && part != "D") {
    valid = 0;
  }
  if (valid == 1 && part != "A") {
    if (!(cin >> count) || count < 0 || count > maxCount) {
      valid = 0;
    }
  }

  if (valid == 1 && part == "A") {
    string text, target;
    int matches = 0;
    if (!getline(cin, text) || !getline(cin, target) || text.size() > maxLength || target.size() != 1) {
      valid = 0;
    }
    for (size_t symbolIndex = 0; valid == 1 && symbolIndex < target.size(); ++symbolIndex) {
      unsigned char symbol = target[symbolIndex];
      if (symbol > maxAscii) {
        valid = 0;
      }
    }
    for (size_t symbolIndex = 0; valid == 1 && symbolIndex < text.size(); ++symbolIndex) {
      unsigned char symbol = text[symbolIndex];
      if (symbol > maxAscii) {
        valid = 0;
      }
      if (text[symbolIndex] == target[0]) {
        ++matches;
      }
    }
    result.push_back(to_string(matches));
  } else if (valid == 1 && part == "B") {
    vector<int> numbers;
    int value, temporary;
    string line;
    for (int numberIndex = 0; valid == 1 && numberIndex < count; ++numberIndex) {
      if (!(cin >> value) || value < -maxValue || value > maxValue) {
        valid = 0;
      } else {
        numbers.push_back(value);
      }
    }
    for (size_t numberIndex = 0; numberIndex + 1 < numbers.size(); numberIndex += 2) {
      temporary = numbers[numberIndex];
      numbers[numberIndex] = numbers[numberIndex + 1];
      numbers[numberIndex + 1] = temporary;
    }
    for (size_t numberIndex = 0; numberIndex < numbers.size(); ++numberIndex) {
      if (numberIndex > 0) {
        line += " ";
      }
      line += to_string(numbers[numberIndex]);
    }
    if (!numbers.empty()) {
      result.push_back(line);
    }
  } else if (valid == 1 && part == "C") {
    map<string, int> values;
    string key;
    int value;
    for (int pairIndex = 0; valid == 1 && pairIndex <= count; ++pairIndex) {
      if (!(cin >> key >> value) || key.size() > maxKeyLength || value < -maxValue || value > maxValue) {
        valid = 0;
      }
      for (size_t symbolIndex = 0; valid == 1 && symbolIndex < key.size(); ++symbolIndex) {
        unsigned char symbol = key[symbolIndex];
        if (symbol > maxAscii || symbol <= ' ') {
          valid = 0;
        }
      }
      if (valid == 1) {
        if (pairIndex < count) {
          values[key] = value;
        } else {
          values[key] += value;
        }
      }
    }
    for (auto entry = values.begin(); entry != values.end(); ++entry) {
      result.push_back(entry->first + " " + to_string(entry->second));
    }
  } else if (valid == 1 && part == "D") {
    vector<map<string, string>> records;
    string title, section;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int recordIndex = 0; valid == 1 && recordIndex < count; ++recordIndex) {
      if (!getline(cin, title) || !getline(cin, section)) {
        valid = 0;
      } else {
        records.push_back({{"title", title}, {"section", section}});
      }
    }
    for (size_t recordIndex = 0; recordIndex < records.size(); ++recordIndex) {
      if (records[recordIndex].find("title") == records[recordIndex].end() || records[recordIndex].find("section") == records[recordIndex].end()) {
        valid = 0;
      } else {
        vector<string> fields = {records[recordIndex].at("title"), records[recordIndex].at("section")};
        for (size_t fieldIndex = 0; fieldIndex < fields.size(); ++fieldIndex) {
          string text = fields[fieldIndex];
          if (text.empty() || text.size() > maxLength) {
            valid = 0;
          } else if (text[0] == ' ' || text[text.size() - 1] == ' ') {
            valid = 0;
          }
          for (size_t symbolIndex = 0; symbolIndex < text.size(); ++symbolIndex) {
            unsigned char symbol = text[symbolIndex];
            if (symbol > maxAscii) {
              valid = 0;
            }
          }
        }
      }
    }
    for (size_t recordIndex = 0; valid == 1 && recordIndex < records.size(); ++recordIndex) {
      title = records[recordIndex].at("title");
      section = records[recordIndex].at("section");
      if (title.size() > titleLength) {
        title = title.substr(0, titleLength) + "...";
      }
      result.push_back("[" + section + "] " + title);
    }
  }

  if (valid == 0) {
    cout << "INVALID\n";
  } else if (result.empty()) {
    cout << "EMPTY\n";
  } else {
    for (size_t lineIndex = 0; lineIndex < result.size(); ++lineIndex) {
      cout << result[lineIndex] << "\n";
    }
  }
  return 0;
}
