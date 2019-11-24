/*
 * CSc103 Project 3: unix utilities
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:Professor Vasas
 *
 *
 * Finally, please indicate approximately how many hours you spent on this:
 * #hours: 2 days
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
#include <map>
using std::map;
using std::make_pair;
#include <iterator>
using std::iterator;


void substring(string& s, string set1); //this function is for the -d option
map<char, char> complement(string set1, string set2); // this function is for the -c option
map<char, char> noOpt(string s1, string s2); // this function is for tr with no options
void bothOpt(string& ss, string set1); // this function is for -cd

static const char* usage =
"Usage: %s [OPTIONS] SET1 [SET2]\n"
"Limited clone of tr.  Supported options:\n\n"
"   -c,--complement     Use the complement of SET1.\n"
"   -d,--delete         Delete characters in SET1 rather than translate.\n"
"   --help          show this message and exit.\n";


// escape function that handles the escape sequences
void escape(string& s) {
	/* NOTE: the normal tr command seems to handle invalid escape
	 * sequences by simply removing the backslash (silently) and
	 * continuing with the translation as if it never appeared. */
	/* TODO: write me... */
	string str = "";
	if( s.length() <= 0){
		s = str;
	}
	else{
		for(int i = 0; i<s.length(); i++){
			if(s[i] == '\\'){
				if(s[i+1] == '\\'){
					str = str + '\\';
					i++;//increment i because we already looked at s[i+1]
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
	// define long options
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
	//This if statement deals with -cd
	if( comp == 1 && del == 1){
		string str = "";
		char c;
		while(fread( &c, 1, 1, stdin)){ //read one character at a time
			if( c == '\n'){ // if newline is found...
				str += c; // add to the string
				bothOpt(str,s1); // do the function for -cd
				cout << str; //print the changed string out (str is changed because i put it inside the function by reference
				str = ""; // make str empty again for the next line
			}
			else{
				str += c; // if c isn't a newline just continue to add the current character to the string
			}
		}
		bothOpt(str,s1); // sometimes the last line of a file might not end with a newline tand break out of the loop before entering the if statment so it won't print the string out therefore we must take care of it here
		cout << str;
	}
	//this is for -d option
	else if( del == 1){
		string str = "";
		char c;
		while(fread( &c, 1, 1, stdin)){
			if( c == '\n'){
				str += c;
				substring(str,s1);
				cout << str;
				str = "";
			}
			else{
				str += c;
			}
		}
		substring(str,s1);
		cout << str;
	}
	//this is for -c option
	else if(comp == 1){
		map<char, char> k = complement(s1, s2); // put the result of complement(s1, s2) to k
		string str = "";
		char c;
		while(fread( &c, 1, 1, stdin)){
			if( c == '\n'){
				str += c;
				/*the for loops checks each value in str and sees what value
				it has in the map and returns that value.
				Maps have two components :a value and a key.
				if you do j->first it gives you the key and j->second
				gives you the value with the associated key.
				another way to write j->second is (j*).second*/

				for(int i = 0; i<str.length(); i++){
					for (map<char,char>::iterator j=k.begin(); j!=k.end(); j++) {
						if( str[i] == j->first){ //if the character at i in str is the same as the key in j then just print out it's value or
							cout << (*j).second;
							break;//i've already found the match, no need to go through the rest of the map
						}
					}
				}
				str = ""; //make the str empty again for the next line of input
			}
			else{
				str += c;
			}

		}
		//see comments from the -c and -d if statment body from above
		for(int i = 0; i<str.length(); i++){
			for (map<char,char>::iterator j=k.begin(); j!=k.end(); j++) {
				if( str[i] == j->first){
						cout << (*j).second;
						break;
				}
			}
		}
	}
	//this else takes care of tr with no options
	else{
		map<char, char> k = noOpt(s1, s2);
		string str = "";
		char c;
		while(fread( &c, 1, 1, stdin)){
			if( c == '\n'){
				str += c;
				for(int i = 0; i<str.length(); i++){
					for (map<char,char>::iterator j=k.begin(); j!=k.end(); j++) {
						if( str[i] == j->first){
							cout << (*j).second;
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
		for(int i = 0; i<str.length(); i++){
			for (map<char,char>::iterator j=k.begin(); j!=k.end(); j++) {
				if( str[i] == j->first){
						cout << (*j).second;
						break;
				}
			}
		}
	}

	return 0;
}

//function for -d option
void substring(string& s, string set1){
	bool match = false; // this boolean flag is to check whether a character in the string s is in set1.
	string newStr = ""; // this string holds the newstring after all the necessary characters are deleted
	if(set1.length() > 0){ // need to make sure that set1 is not empty
		for(int i = 0; i<s.length(); i++){//go through the input string
			match = false; // assume that s[i] does not appear int set1
			for(int j = 0; j<set1.length(); j++){
				if(s[i] == set1[j]){//if s[i] does appear in set1
					match = true; //set match to true
					break; // and go to the next i, we don't add s[i] to newStr because we want it to be deleted if it does appear in set1 and newStr is supposed to hold all the values in s that do not appear in set1
				}
			}
			if( match == false){ // if match is false that means s[i] does not appear in set1 so we add it to the newStr
				newStr = newStr + s[i];
			}
		}
		s = newStr; // set s to newStr
	}
}

//function for -c option
map<char, char> complement(string set1, string set2){
	map<char, char> m; // create a new map m
	for( int i = 0; i< 256; i++){ // fill up m
		if( i >= set2.length() ){ //if i is greater than the length of set2 just fill the rest of the map with the last character in set2
			m[i] = set2[set2.length()-1];
		}
		else{ //else fill it m[i] with the corresponding value in set2
			m[i] = set2[i];
		}
	}
	//now go through m again
	for( map<char, char>:: iterator i = m.begin(); i != m.end(); i++){
		for(int j = 0; j<set1.length(); j++){ //check each key in the map m with the charcters in set1
			if(i->first == set1[j]){ // if the key matches with a character with set1 we want the value to equal to it. Remember complement only changes everything other than what is in set1
				i->second = set1[j];
				break; //we found a match, no need to look further, move to the next i
			}
		}
	}

	//the commented out for loop helped me debug, you can ignore it, it's not part of the code
	//for (map<char,char>::iterator i=m.begin(); i!=m.end(); i++) {
		//cout << (*i).first << ":\t" << (*i).second << "\n";
		/*        key                      value         */
	//}
	return m; //return the map m
}

//for tr with no options
map<char, char> noOpt(string s1, string s2){
	map<char, char> m;
	for( int i = 0; i< 256; i++){ //fill up m with trivial values
		m[i] = i; //the syntax m[i] gives the value at the key i
	}
	if( s1.length() > s2.length()){ // if s1 (set 1) has more characters than set2...
		for(int i = 0; i<s2.length(); i++){//then march through s2 (set 2)
			m[s1[i]] = s2[i]; //and set the value at key s1[i] with the corresponding value in s2 because you want to translate s1[i] with s2[i]
		}
		for( int j = s2.length(); j<s1.length(); j++){
			m[s1[j]] = s2[s2.length()-1]; //since s1 is longer than s2 just fill the values at the rest of the characters in s1 with the last character in s2
		}
	}
	else{ //if s1 is shorter or equal to s2 just fill the corresponding character in s1 with s2.
		for( int i = 0; i< s1.length(); i++){
			m[s1[i]] = s2[i];
		}
	}
	return m;
}

//similar to the substring function.this is for -cd option
void bothOpt(string& ss, string set1){
	string newStr = "";
	if(set1.length() > 0){
		for(int i = 0; i<ss.length(); i++){
			for(int j = 0; j<set1.length(); j++){
				if(ss[i] == set1[j]){ //check to see if the character at ss[i] appears in set1
					newStr = newStr + ss[i]; //newStr should only hold values that are in set1 since everything else is being deleted
					break; // no need to go through the rest of the loop so break and go to the next i
				}
			}
		}
	}
	ss = newStr;
}