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
using std::cout;
#include <string>
using std::string;
#include <set>
using std::set;
#include <getopt.h> // to parse long arguments.
#include <cstdio> // printf


static const char* usage =
"Usage: %s [OPTIONS]...\n"
"Limited clone of wc.  Supported options:\n\n"
"   -c,--bytes            print byte count.\n"
"   -l,--lines            print line count.\n"
"   -w,--words            print word count.\n"
"   -L,--max-line-length  print length of longest line.\n"
"   -u,--uwords           print unique word count.\n"
"   --help          show this message and exit.\n";

int main(int argc, char *argv[])
{
	// define long options
	static int charonly=0, linesonly=0, wordsonly=0, uwordsonly=0, longonly=0;
	static struct option long_opts[] = {
		{"bytes",           no_argument,   0, 'c'},
		{"lines",           no_argument,   0, 'l'},
		{"words",           no_argument,   0, 'w'},
		{"uwords",          no_argument,   0, 'u'},
		{"max-line-length", no_argument,   0, 'L'},
		{"help",            no_argument,   0, 'h'},
		{0,0,0,0}
	};
	// process options:
	char c;
	int opt_index = 0;
	while ((c = getopt_long(argc, argv, "clwuLh", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 'c':
				charonly = 1;
				break;
			case 'l':
				linesonly = 1;
				break;
			case 'w':
				wordsonly = 1;
				break;
			case 'u':
				uwordsonly = 1;
				break;
			case 'L':
				longonly = 1;
				break;
			case 'h':
				printf(usage,argv[0]);
				return 0;
			case '?':
				printf(usage,argv[0]);
				return 1;
		}
	}

	/* TODO: write me... */
	//this big while loop should take care of everything
	int state = 0;//just read a white space
	char a;
	int wordCount = 0;
	int charCount = 0;
	int longestCount = 0;
	int lineCount = 0;
	int byteCount = 0;
	set<string> uniqueWords;
	string str = "";
	while(fread(&a, 1, 1, stdin)){
		byteCount++;
		if(state == 0){
			if(a != ' ' && a != '\t'){
				if( a == '\n'){
					state  = 0;
				}
				else{
					state = 1;
					wordCount++;
					str = str+a;
				}
			}
		}
		else{
			if( a != ' ' && a != '\t' && a != '\n'){
				str = str+a;
			}
			if(a == ' ' || a == '\t' || a == '\n'){
				state = 0;
				uniqueWords.insert(str);
				str = "";
			}
		}
		if( a == '\n'){
			lineCount++;
			if( charCount > longestCount){
				longestCount = charCount;
			}
			charCount = 0;
		}
		else if ( a == '\t'){
			charCount += (8 - charCount%8);
		}
		else{
			charCount++;
		}
	}
	if( a != '\n' && a != '\t' && a != ' '){
		uniqueWords.insert(str);
	}
	//cout << '\n';
	//for(set<string>:: iterator i = uniqueWords.begin(); i != uniqueWords.end(); i++){
	//	cout << *i << "\n";
	//}









	//checking for flags
	if(charonly == 1 && wordsonly == 1 && linesonly == 1 && longonly == 1){
		cout << lineCount << " " << wordCount << " " << byteCount << " " << longestCount<< "\n";

	}
	else if(linesonly == 1 && wordsonly == 1 && longonly == 1){
		cout << lineCount << " " << wordCount << " " << longestCount<< "\n";

	}
	else if(charonly == 1 && wordsonly == 1 && longonly == 1){
		cout<< wordCount << " " << byteCount <<" " <<longestCount<< "\n";

	}
	else if(wordsonly == 1 && longonly == 1){
		cout << wordCount << " " << longestCount<< "\n";

	}
	else if(linesonly == 1 && charonly == 1 && longonly == 1){
		cout << lineCount << " " << byteCount << " " << longestCount<< "\n";
	}
	else if(linesonly == 1 && longonly == 1){
		cout << lineCount << " " << longestCount<< "\n";
	}
	else if(charonly == 1 && longonly == 1){
		cout << byteCount <<" " << longestCount<< "\n";
	}
	else if(linesonly == 1 && wordsonly == 1 && charonly == 1){
		cout << lineCount << " " << wordCount << " " << byteCount<< "\n";
	}
	else if(linesonly == 1 && wordsonly == 1){
		cout << lineCount << " " << wordCount<< "\n";
	}
	else if(charonly == 1 && wordsonly == 1){
		cout << wordCount << " " << byteCount<< "\n";

	}
	else if(linesonly == 1 && charonly == 1){
		cout << lineCount << " " << byteCount<< "\n";

	}
	else if(uwordsonly == 1){
		cout << uniqueWords.size() << '\n';
	}
	else if(charonly == 1){
		cout << byteCount<< "\n";
	}
	else if(wordsonly == 1){
		cout << wordCount << "\n";
	}
	else if(linesonly == 1){
		cout << lineCount << "\n";
	}
	else if(longonly == 1){
		cout << longestCount << "\n";
	}
	else{
		cout << lineCount << " " << wordCount << " " << byteCount<< "\n" ;

	}

	//maxLength();
	return 0;
}
