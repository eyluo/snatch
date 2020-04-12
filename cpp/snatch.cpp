#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <chrono>

#define DICTIONARY "../test_dict.txt"
#define PROCESSING "Processing dictionary...\n"
#define USAGE "Type in a word to check: "
#define MAXLENGTH 16

using namespace std;
using namespace std::chrono;

bool is_subset(unordered_map<char, int> needle, unordered_map<char, int> haystack)
{
    for (auto elem : needle)
    {
        char ch = elem.first;
        int count = elem.second;
        if (haystack.find(ch) == haystack.end() || haystack[ch] < count)
        {
            return false;
        }
    };

    return true;
}

int main(int argc, char *argv[])
{
    // TODO: read in from JSON file instead so that this is useless!
    unordered_map<string, unordered_map<char, int>> word_to_map;

    cout << PROCESSING;

    ifstream file(DICTIONARY);
    if (file.is_open())
    {
        string word;
        while (getline(file, word))
        {
            if (word.size() < MAXLENGTH)
            {
                for (string::size_type i = 0; i < word.size(); i++)
                {
                    word_to_map[word][word[i]] = max(word_to_map[word][word[i]], 0) + 1;
                }
            }
        }
        file.close();
    }

    while (1)
    {
        string string_in;
        cout << USAGE;

        getline(cin, string_in);

        unordered_map<char, int> in_map = word_to_map[string_in];

        auto start = high_resolution_clock::now();
        int match_count = 0;
        for (auto word : word_to_map)
        {
            if (is_subset(in_map, word.second)) {
                match_count++;
            }
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<seconds>(stop - start);

        cout << "found " << match_count << " snatches in " << duration.count() << " seconds" << endl;
    }

    return 0;
}