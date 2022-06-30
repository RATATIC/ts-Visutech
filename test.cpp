//#include "gtest/gtest.h"
#include "pch.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

constexpr auto ONE = 1;

void delete_word(std::vector<std::string>& file_strings, const std::string& word);
void sort_file(std::vector<std::string>& file_strings);
void read_file(std::vector<std::string>& file_strings, const std::string& filename);
void write_file(std::vector<std::string>& file_strings, const std::string& out_file);
void change_strings(const std::string& in_filename, const std::string& out_filename, const std::string& word);

TEST(TestChangeStrings, TestDeleteWord1) {
	std::vector<std::string> str_vec = {
		"asd dfsghn ferfiuphnds asdclkjca qwad ADSD as vdsaf zxc cxd" ,
		"asdrifj asdasd zxczxc zxczxc tyrur qwerty cvbnvcbn jkl uioooiiiiii hgfdg zxc",
		"acdrifj asd zxczxc zxczxc tyrur qwerty cvbnvcbn jkl uioooiiiiii hgfdg asd"
	};

	std::vector<std::string> ans_vec = {
		"dfsghn ferfiuphnds asdclkjca qwad ADSD as vdsaf zxc cxd" ,
		"asdrifj asdasd zxczxc zxczxc tyrur qwerty cvbnvcbn jkl uioooiiiiii hgfdg zxc",
		"acdrifj zxczxc zxczxc tyrur qwerty cvbnvcbn jkl uioooiiiiii hgfdg "
	};
	std::string word("asd");
	delete_word(str_vec, word);

	EXPECT_EQ(str_vec, ans_vec);
}
TEST(TestChangeStrings, TestDeleteWord2) {
	std::vector<std::string> str_vec = { "For failed tests the message displays details that help to diagnose the cause Right click on the failing test for a pop up menu" };

	std::vector<std::string> ans_vec = { "For failed tests message displays details that help to diagnose cause Right click on failing test for a pop up menu" };
	std::string word("the");

	delete_word(str_vec, word);

	EXPECT_EQ(str_vec, ans_vec);
}

TEST(TestChangeStrings, TestSortFile) {
	std::vector<std::string> str_vec = {
		"asdrifj asduuuBfakAISdhkAKLSJd zxczxc" ,
		"AAABmnasdioan asdilhfaksj asdflhjewfnsdac gg",
		"Cdfsasde asdjk alsdfjaskf",
		"AAABmnasdioan hfnsfas asdgewhrlfa d",
		"aaabmnasdioan d"
	};

	std::vector<std::string> ans_vec = {
		"AAABmnasdioan asdilhfaksj asdflhjewfnsdac gg" ,
		"aaabmnasdioan d",
		"AAABmnasdioan hfnsfas asdgewhrlfa d",
		"asdrifj asduuuBfakAISdhkAKLSJd zxczxc",
		"Cdfsasde asdjk alsdfjaskf"
	};
	sort_file(str_vec);
	
	EXPECT_EQ(str_vec, ans_vec);
}

int main(int argc, char** argv)
{
	std::string					in_filename("strings.txt");
	std::string					out_filename("new_strings.txt");
	std::string					word("");

	if (argc == 2) {
		in_filename = argv[1];
	}
	else if (argc == 3) {
		in_filename = argv[1];
		out_filename = argv[2];
	}
	else if (argc == 4) {
		in_filename = argv[1];
		out_filename = argv[2];
		word = argv[3];
	}
	change_strings(in_filename, out_filename, word);

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

void change_strings(const std::string& in_filename, const std::string& out_filename, const std::string& word) {
	std::vector<std::string>	file_strings;

	read_file(file_strings, in_filename);

	delete_word(file_strings, word);
	sort_file(file_strings);

	write_file(file_strings, out_filename);
}

void delete_word(std::vector<std::string>& file_strings, const std::string& word) {
	if (word.empty())
		return;

	std::size_t pos = 0;

	for (auto& it : file_strings) {
		pos = it.find(word, pos);
		while (pos != it.npos) {
			if ((it[pos + word.size()] == ' ' || pos + word.size() == it.size()) && (pos > 0 ? it[pos - 1] == ' ' : true)) {
				it.erase(pos, word.size());

				if (it[pos] == ' ') {
					it.erase(pos, ONE);
				}
			}
			else {
				pos += word.size();
			}
			pos = it.find(word, pos);
		}
		pos = 0;
	}
}

void sort_file(std::vector<std::string>& file_strings) {
	auto cmp = [&](const std::string str1, const std::string str2) {
		std::string str1_low(str1);
		std::string str2_low(str2);

		std::transform(str1.begin(), str1.end(), str1_low.begin(), tolower);
		std::transform(str2.begin(), str2.end(), str2_low.begin(), tolower);
		return str1_low < str2_low;
	};
	std::sort(file_strings.begin(), file_strings.end(), cmp);
}

void write_file(std::vector<std::string>& file_strings, const std::string& out_file) {
	std::ofstream outfile(out_file);
	if (!outfile.is_open())
		return;

	for (const auto& it : file_strings) {
		outfile << it << std::endl;
	}
}

void read_file(std::vector<std::string>& file_strings, const std::string& filename) {
	std::ifstream infile(filename, std::ios::in);
	if (!infile.is_open())
		return;

	while (!infile.eof()) {
		std::string str;
		std::getline(infile, str);

		file_strings.push_back(str);
		str.clear();
	}
}