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

static const char* usage =
"Usage: %s [OPTIONS] SET1 [SET2]\n"
"Limited clone of tr.  Supported options:\n\n"
"   -c,--complement     Use the complement of SET1.\n"
"   -d,--delete         Delete characters in SET1 rather than translate.\n"
"   --help          show this message and exit.\n";

void escape(string& s) {
	/* NOTE: the normal tr command seems to handle invalid escape
	 * sequences by simply removing the backslash (silently) and
	 * continuing with the translation as if it never appeared. */
	//Have to make some sort of if else statement which compares the values of characters.
	/* TODO: write me... */
}

int main(int argc, char *argv[])
{
	// define long options
	//possibly need to use boolean to see if characters in string and sets match???
	//vector<bool> S;
	//vector to hold all char values for before and after translation
	vector<char> setOne(256);
	//vector<char> setTwo[256];
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
	if(comp == 1){
		//do case c
		for(int i = 0; i < setOne.size(); i++){
			if(/* character in string != any character in setOne*/){
				/*change the character in the string to the character in second set */
			}
		}
	}
	else if(del == 1){
		//do case d
		for(int i = 0; i < setOne.size(); i++){
			for(int j = 0; j < str.size(); j++){

				if(str[j] == setOne[i]){
				/*remove the characters from the string */
					for(int k = j+1; k < str.size(); k++){
						str[k-1] = str[k];
					}
					str.pop_back();
					//deletes the element at j
					str.erase(str.begin() + j);
				}
				//go to next letter in string
				j++;
			}
			//go to next letter in setOne
			i++;
		}
	}

	else if(comp == 1 && del ==1){
		//do both but do we want to delete first or complement???? Right now, start with deleting.
		for(int i = 0; i < setOne.size(); i++){
			for(int j = 0; j < str.size(); j++){

				if(str[j] == setOne[i]){
				/*remove the characters from the string */
					for(int k = j+1; k < str.size(); k++){
						str[k-1] = str[k];
					}
					str.pop_back();
					//deletes the element at j
					str.erase(str.begin() + j);
				}
				//go to next letter in string
				j++;
			}
			//go to next letter in setOne
			i++;

			//complement is going to have to work within this loop!!!
		}

	}



	return 0;
}
