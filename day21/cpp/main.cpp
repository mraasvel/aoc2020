#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <set>

#define PATHNAME "../sample.txt"

using namespace std;

std::map<string, set<string>> allergens;
map<string, int> all_ingredients;

char		**ft_split_set(const char *src, const char *set);

vector<string> string_split(const string &str, char delimiter) {
	stringstream ss(str);
	vector<string> lines;
	string temp;
	while (getline(ss, temp, delimiter)) {
		lines.push_back(temp);
	} // WHILE
	return (lines);
}

void	parse_line(string line)
{
	vector<string>			words;
	set<string>	ingredients;
	size_t					i;
	bool					found;

	words = string_split(line, ' ');
	i = 0;
	found = false;
	for (auto &word: words) {
		if (word == "(contains") {
			found = true;
		} else if (!found) {
			if (all_ingredients.find(word) == all_ingredients.end()){
				all_ingredients[word] = 1;
			} else{
				all_ingredients[word]++;
			}
			ingredients.insert(word);
		} else {
			auto allergen = word.substr(0, word.size() - 1);
			auto entry = allergens.find(allergen);
			if (entry == allergens.end()){
				allergens[allergen] = ingredients;
			}
			else {
				auto list = entry->second;
				for(auto &old_ingredient: list){
					if (ingredients.find(old_ingredient) == ingredients.end()){
						entry->second.erase(old_ingredient);
					}
				}
			}
		}
	}
}

void check_ingredients()
{
	for(auto &entry: allergens) {
		for (auto &candidate: entry.second){
			all_ingredients.erase(candidate);
		}
	}
	size_t	i = 0;
	for (auto &ingredient: all_ingredients){
		i += ingredient.second;
	}
	cout << "Result: " << i << endl;
}

void filter_ingredients(set<string> &already_taken){
	for (auto &entry: allergens) {
		if (already_taken.find(entry.first) == already_taken.end() && entry.second.size() == 1){
			already_taken.insert(entry.first);
			auto ingredient = *entry.second.begin();
			for (auto &entry2: allergens){
				if (entry.first != entry2.first){
					entry2.second.erase(ingredient);
				}
			}
			filter_ingredients(already_taken);
			return ;
		}
	}
}

void print_ingredients()
{
	for(auto &entry: allergens) {
		for (auto &ingredient: entry.second){
			cout << ingredient << ",";
		}
	}
}

int	main(void)
{
	ifstream myfile;
	string line;
	set<string> already_taken;

	myfile.open(PATHNAME);
	while (getline(myfile,line))
    {
		parse_line(line);
    }
	check_ingredients();
	filter_ingredients(already_taken);
	print_ingredients();
    myfile.close();
	return (0);
}
