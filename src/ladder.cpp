#include "ladder.h"
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << ", " << word2 << ")" << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = str1.length(), len2 = str2.length();
    if (abs(len1 - len2) > d) return false;

    int count = 0, i = 0, j = 0;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            count++;
            if (count > d) return false;
            if (len1 > len2) i++; // deletion
            else if (len1 < len2) j++; // insertion
            else { i++; j++; } // replace
        } else {
            i++; j++;
        }
    }
    return count <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) return {};
    queue<vector<string>> ladder_queue;
    set<string> visited;

    ladder_queue.push({begin_word});
    visited.insert(begin_word);
    
    while (!ladder_queue.empty()) {
        int level_size = ladder_queue.size();
        set<string> level_visited;
        for (int i = 0; i < level_size; i++) {
            vector<string> ladder = ladder_queue.front();
            ladder_queue.pop();
            string last = ladder.back();

            for (const string& word : word_list) {
                if (is_adjacent(last, word) && !visited.count(word)) {
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word) return new_ladder;
                    ladder_queue.push(new_ladder);
                    level_visited.insert(word);
                }
            }
        }
    for (const string& w : level_visited) visited.insert(w);
    }
    return {};
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Could not open " << file_name << endl;
    }
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    cout << "Word ladder found: ";
    for (int i = 0; i < ladder.size(); i++) {
        if (i > 0) cout << " ";
        cout << ladder[i];
    }
    cout << endl;
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    
    string start, end;
    cout << "Enter start word: ";
    cin >> start;
    cout << "Enter end word: ";
    cin >> end;
    if (word_list.find(start) == word_list.end() || word_list.find(end) == word_list.end()) {
        error(start, end, "Not found");
        return;
    }
    vector<string> ladder = generate_word_ladder(start, end, word_list);
    print_word_ladder(ladder);
}