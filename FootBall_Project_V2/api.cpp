#include <vector>
#include <string>

#include "api.h"

using namespace std;

vector<string> separate(string s, int cols)
{
    vector<string> ans;
    vector<string> words;
    string cur = "";
    for (int i = 0; i < s.size(); i++)
        if (s[i] != ' ')
            cur += s[i];
        else
        {
            words.push_back(cur);
            cur = "";
        }
    words.push_back(cur);
    for (string word : words)
        if (ans.size() == 0 || word.size() + ans.back().size() > cols)
            ans.push_back(word);
        else
            ans.back() += " " + word;
    return ans;
}

bool valid(string password)
{
    fstream input("passwords.txt");
    bool ans = false;
    hash<string> hasher;
    long long x, y = hasher(password);
    while (input >> x)
    {
        if (x == y)
        {
            ans = true;
            break;
        }
    }
    input.close();
    return ans;
}

vector<string> load_continent(string continent)
{
    ifstream input(continent);
    vector<string> ans;
    string s;
    while (input >> s)
    {
        ans.push_back(s);
    }
    input.close();
    return ans;
}

vector<string> load_players(string continent)
{
    ifstream input(continent);
    vector<string> ans;
    string s;
    while (getline(input, s))
    {
        ans.push_back(s);
    }
    input.close();
    return ans;
}

void save_groups(vector<string> groups, string name)
{
    ofstream output(name, ios::out);
    for (auto group : groups)
    {
        output << group << endl;
    }
    output.close();
}

vector<string> load_group(string group)
{
    ifstream input(group);
    vector<string> ans;
    string s;
    while (input >> s)
    {
        ans.push_back(s);
    }
    input.close();
    return ans;
}

vector<string> load_winners(string winner)
{
    ifstream input(winner);
    vector<string> ans;
    string s;
    while (input >> s)
    {
        ans.push_back(s);
    }
    input.close();
    return ans;
}

vector<string> separate(string s)
{
    vector<string> words;
    string cur = "";
    for (int i = 0; i < s.size(); i++)
        if (s[i] != ';')
            cur += s[i];
        else
        {
            words.push_back(cur);
            cur = "";
        }
    words.push_back(cur);
    return words;
}

vector<string> separate_sus(string s, int )
{
    vector<string> words;
    string cur = "";
    for (int i = 0; i < s.size(); i++)
        if (s[i] != ';')
            cur += s[i];
        else
        {
            words.push_back(cur);
            cur = "";
        }
    words.push_back(cur);
    return words;
}

void save_winners(vector<string> winners, string name) {
    ofstream output(name, ios::app);
    for (auto winner : winners)
    {
        output << winner << endl;
    }
    output.close();
}

void save_runners(string line) {
    bool exists = false;
    ifstream input("C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/runners.txt", ios::in);
    string s;
    while (input >> s && exists == false)
    {
        if (s == line) exists = true;
    }
    input.close();

    if (!exists) {
        ofstream output("C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/runners.txt", ios::app);
        output << line << endl;
        output.close();
    }
}

void load_runners(vector<string>& vec_winners, vector<string>& vec_runners) {
    ifstream input("C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/runners.txt", ios::in);
    string s;
    vector<string> s_sep;
    while (input >> s)
    {
        s_sep=separate(s);
        vec_winners.push_back(s_sep[0]);
        vec_runners.push_back(s_sep[1]);
    }
    input.close();
}

void save_teamstats(string line) {
    bool exists = false;
    ifstream input("C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/teamstats.txt", ios::in);
    string s;
    while (input >> s )
    {
        if (line == s) exists = true;
    }
    input.close();

    if (!exists) {
        ofstream output("C:/Users/S B S/source/repos/FootBall_Project_V2/FootBall_Project_V2/newcompetition2020/teamstats.txt", ios::app);
        output << line << endl;
        output.close();
    }
}

vector<string> separate_space(string s) {
    vector<string> words;
    string cur = "";
    for (int i = 0; i < s.size(); i++)
        if (s[i] != ' ')
            cur += s[i];
        else
        {
            words.push_back(cur);
            cur = "";
        }
    words.push_back(cur);
    return words;
}