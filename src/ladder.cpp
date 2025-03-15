#include "ladder.h"
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << ", " << word2 << ")" << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    if (str1.length() != str2.length()) return false;

    int count = 0;
    for (int i = 0; i < str1.length(); i++) {
        if (str1[i] != str2[i]) {
            count++;
            if (count > d) return false;
        }
    }
    return count <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) return {begin_word};
    queue<stack<string>> ladder_queue;
    set<string> visited;
    stack<string> initial;

    initial.push(begin_word);
    ladder_queue.push(initial);
    visited.insert(begin_word);
    
    while (!ladder_queue.empty()) {
        int level_size = ladder_queue.size();
        set<string> level_visited;
        for (int i = 0; i < level_size; i++) {
            stack<string> ladder = ladder_queue.front();
            ladder_queue.pop();
            string last = ladder.top();

            for (const string& word : word_list) {
                if (is_adjacent(last, word) && visited.find(word) == visited.end()) {
                    stack<string> new_ladder = ladder;
                    new_ladder.push(word);
                    if (word == end_word) {
                        vector<string> result;
                        while (!new_ladder.empty()) {
                            result.push_back(new_ladder.top());
                            new_ladder.pop();
                        }
                        reverse(result.begin(), result.end());
                        return result;
                    }
                    ladder_queue.push(new_ladder);
                    level_visited.insert(word);
                }
            }
        }
        for (const string& w : level_visited) {
            visited.insert(w);
        }
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
        cout << "Empty" << endl;
        return;
    }
    for (int i = 0; i < ladder.size(); i++) {
        if (i > 0) cout << " -> ";
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