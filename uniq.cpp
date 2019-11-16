#include <cstdio>
#include <getopt.h> // to parse long arguments.
#include <string>
using std::string;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

static const char* usage =
"Usage: %s [OPTIONS]...\n"
"Limited clone of uniq.  Supported options:\n\n"
"   -c,--count         prefix lines by their counts.\n"
"   -d,--repeated      only print duplicate lines.\n"
"   -u,--unique        only print lines that are unique.\n"
"   --help             show this message and exit.\n";


void count();
void duplicate();
void unique();

int main(int argc, char *argv[]) {
	// define long options
	static int showcount=0, dupsonly=0, uniqonly=0;
	static struct option long_opts[] = {
		{"count",         no_argument, 0, 'c'},
		{"repeated",      no_argument, 0, 'd'},
		{"unique",        no_argument, 0, 'u'},
		{"help",          no_argument, 0, 'h'},
		{0,0,0,0}
	};
	// process options:
	char c;
	int opt_index = 0;
	while ((c = getopt_long(argc, argv, "cduh", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 'c':
				showcount = 1;
				break;
			case 'd':
				dupsonly = 1;
				break;
			case 'u':
				uniqonly = 1;
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
	if(showcount==1 && dupsonly == 1 && uniqonly ==1){
		//count();
		//duplicate();
		//unique();


	}
	else if(showcount == 1 && dupsonly == 1){
		string str = "";
		getline(cin, str);
		string prevStr = str;
		int count = 1;
		while(getline(cin, str)){
			if(prevStr != str){
				if(count>1){
					printf("%7lu ",count);
					cout << prevStr <<"\n";
					count = 1;
				}
			}
			else{
				count++;
			}
			prevStr = str;
		}
	}
	else if(showcount == 1 && uniqonly == 1){
		string str = "";
		getline(cin, str);
		string prevStr = str;
		int count = 1;
		while(getline(cin, str)){
			if(prevStr!=str){
					if(count==1){
						printf("%7lu ",count);
						cout << prevStr <<"\n";
					}
					count = 1;
			}
			else{
				count ++;
			}
			prevStr = str;
		}
		printf("%7lu ",count);
		cout << prevStr <<"\n";
	}
	else if(dupsonly == 1 && uniqonly ==1){
		//duplicate();
		//unique();
	}
	else if(showcount == 1){
		count();
	}
	else if(dupsonly == 1){
		duplicate();
	}
	else if(uniqonly==1){
		unique();
	}
	else{
		string str = "";
		getline(cin, str);
		cout<<str<<"\n";
		string newStr = str;
		while(getline(cin, str)){
			if(newStr != str){
				cout<<str<< "\n";
				newStr = str;
			}
		}
	}


	return 0;
}

void count(){
	string str = "";
		getline(cin, str);
		string prevStr = str;
		size_t count = 1;
		while(getline(cin, str)){
			if(prevStr == str){
				count++;
			}
			else{
				printf("%7lu ",count);
				cout << prevStr <<"\n";
				count = 1;

			}
			prevStr = str;

		}
		printf("%7lu ",count);
		cout << prevStr <<"\n";
}

void duplicate(){
	string str = "";
		getline(cin, str);
		string prevStr = str;
		int count = 1;
		while(getline(cin, str)){
			if(prevStr != str){
				if(count>1){
					cout << prevStr;
					cout << "\n";
					count = 1;
				}
			}
			else{
				count++;
			}
			prevStr = str;
		}
}


void unique(){
	string str = "";
		getline(cin, str);
		string prevStr = str;
		int count = 1;
		while(getline(cin, str)){
			if(prevStr!=str){
					if(count==1){
						cout<<prevStr<< "\n";
					}
					count = 1;
			}
			else{
				count ++;
			}
			prevStr = str;
		}
		cout<<prevStr<<"\n";
}