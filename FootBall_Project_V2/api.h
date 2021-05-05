#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
void save_teamstats(string line);

vector<string> separate(string s, int cols);

vector<string> load_continent(string continent);

void save_groups(vector<string> groups, string name);

void save_winners(vector<string> winners, string name);

vector<string> separate(string s);
vector<string> separate_sus(string s, int i=0);

vector<string> load_group(string group);

vector<string> load_winners(string winner = "winners.txt");

void save_runners(string);

void load_runners(vector<string>&, vector<string>&);

vector<string> load_players(string continent);

vector<string> separate_space(string s);