/*
 * CSc103 Project 3: unix utilities
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 *
 *
 * Finally, please indicate approximately how many hours you spent on this:
 * #hours:
 */

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <algorithm>
using std::sort;
#include <string.h> // for c-string functions.
#include <getopt.h> // to parse long arguments.
#include <iterator>
using std::iterator;
#include <map>
using std::map;


static const char* usage =
"Usage: %s [OPTIONS] SET1 [SET2]\n"
"Limited clone of tr.  Supported options:\n\n"
"   -c,--complement     Use the complement of SET1.\n"
"   -d,--delete         Delete characters in SET1 rather than translate.\n"
"   --help          show this message and exit.\n";

void subString(string& s, string set1);
map<char, char> complementFunc(string set1, string set2);
map<char, char> noOpt(string s1, string s2);
void bothOpt(string& ss, string set1);

void escape(string& s) {
	/* NOTE: the normal tr command seems to handle invalid escape
	 * sequences by simply removing the backslash (silently) and
	 * continuing with the translation as if it never appeared. */
	//Have to make some sort of if else statement which compares the values of characters.
	/* TODO: write me... */
	string str = "";
	if(s.length() <= 0){
		s = str;
	}else{
		for(int i = 0; i < s.length(); i++){
			if(s[i] == '\\'){
				if(s[i+1] == '\\'){
					str = str + '\\';
					i++;
				}
				else if(s[i+1] == 'n'){
					str = str + '\n';
					i++;
				}
				else if(s[i+1] == 't'){
					str = str + '\t';
					i++;
				}
			}
			else{
				str = str + s[i];
			}
		}
	}
	s = str;




}

int main(int argc, char *argv[])
{

	static int comp=0, del=0;
	static struct option long_opts[] = {
		{"complement",      no_argument,   0, 'c'},
		{"delete",          no_argument,   0, 'd'},
		{"help",            no_argument,   0, 'h'},
		{0,0,0,0}
	};
	// process options:
	char c;
	int opt_index = 0;
	while ((c = getopt_long(argc, argv, "cdh", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 'c':
				comp = 1;
				break;
			case 'd':
				del = 1;
				break;
			case 'h':
				printf(usage,argv[0]);
				return 0;
			case '?':
				printf(usage,argv[0]);
				return 1;
		}
	}
	if (del) {
		if (optind != argc-1) {
			fprintf(stderr, "wrong number of arguments.\n");
			return 1;
		}
	} else if (optind != argc-2) {
		fprintf(stderr,
				"Exactly two strings must be given when translating.\n");
		return 1;
	}
	string s1 = argv[optind++];
	string s2 = (optind < argc)?argv[optind]:"";
	/* process any escape characters: */
	escape(s1);
	escape(s2);

	/* TODO: finish this... */
	if(comp == 1 && del ==1){

		string s = "";
		char c;
		while(fread( &c, 1, 1, stdin)){
			if(c == '\n'){
				s += c;
				bothOpt(s, s1);
				cout << s;
				s = "";
			}
			else
			{
				s += c;
			}

	}
	bothOpt(s, s1);
	cout << s;

}else if(del == 1){
		//do case d
		string s = "";
		char c;
		while(fread( &c, 1, 1, stdin)){
			if(c == '\n'){
				s += c;
				subString(s, s1);
				cout << s;
				s = "";
			}
			else
			{
				s += c;
			}

	}
	subString(s, s1);
	cout << s;

}else if(comp == 1){
		//do case c

		map<char, char> k = complementFunc(s1, s2);
		string str = "";
		char ch;
		//fill with trivial values
		while(fread( &c, 1, 1, stdin)){
			if(ch == '\n'){
				str += ch;
				for(int j = 0; j < str.length(); j++){
					for(map<char,char>::iterator i = k.begin(); i != k.end(); i++){
						if(str[j] == i->first)
						{
							cout << (*i).second;
							break;
						}
					}
				}
				str = "";
			}
			else
			{
				str += c;
			}
		}

		for(int j = 0; j < str.length(); j++){
					for(map<char,char>::iterator i = k.begin(); i != k.end(); i++){
						if(str[j] == i->first)
						{
							cout << (*i).second;
							break;
						}
					}
				}






}else{

		string str = "";
		char c;
		map<char,char> alone = noOpt(s1, s2);
		while(fread( &c, 1, 1, stdin)){
			if(c == '\n'){
				str += c;
				for(int j = 0; j < str.length(); j++){
					for(map<char,char>::iterator i = alone.begin(); i != alone.end(); i++){
						if(str[j] == i->first)
						{
							cout << (*i).second;
							break;
						}
					}
				}
				str = "";
			}
			else{
				str += c;
			}
		}

		for(int j = 0; j < str.length(); j++){
					for(map<char,char>::iterator i = alone.begin(); i != alone.end(); i++){
						if(str[j] == i->first)
						{
							cout << (*i).second;
							break;
						}
					}
				}
			}



	return 0;
}


//this is used for -d
void subString(string& s, string set1){
	bool match = false;
	string newString = "";
	if(set1.length() > 0){
		for(int i = 0; i < s.length(); i++){
			match = false;
			for(int j = 0; j < set1.length(); j++){
				if(s[i] == set1[j]){
					match = true;
					break;
				}

			}

			if(match == false){
				newString = newString + s[i];
			}
		}
		s = newString;
	}
}

void bothOpt(string& ss, string set1){
	string newString = "";
	if(set1.length() > 0){
		for(int i = 0; i < ss.length(); i++){
			for(int j = 0; j < set1.length(); j++){
				if(ss[i] == set1[j]){
					newString = newString + ss[i];
					break;
				}
			}
		}
	}
	ss = newString;
}

map<char, char> complementFunc(string set1, string set2){
	map<char, char> m;
	for(int i = 0; i < 256; i++){
		if(i >= set2.length()){
			m[i] = set2[set2.length()-1];
		}
		else
		{
			m[i] = set2[i];
		}
	}
	for(map<char,char>::iterator i = m.begin(); i != m.end(); i++){
		for(int j = 0; j < set1.length(); j++){
			if(i->first == set1[j]){
				i->second = set1[j];
				break;
			}
		}
	}

	return m;
}

map<char, char> noOpt(string s1, string s2){
	map<char, char> m;
	for(int i = 0; i < 256; i++){
		m[i] = i;
		//m[s1[i]] = s2[i];
	}

	if(s1.length() > s2.length()){
		//for(int i = 0; i < s1.length(); i++){
			for(int j = 0; j < s2.length(); j++){
				m[s1[j]] = s2[j];
			}

			for(int j = s2.length(); j < s1.length(); j++){
				m[s1[j]] = s2[s2.length()-1];
			}
		//}
	}
	else{
		for(int i = 0; i < s1.length(); i++){
			m[s1[i]] = s2[i];
		}
	}

	return m;
}











