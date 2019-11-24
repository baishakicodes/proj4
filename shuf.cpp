#include <cstdio>   // printf
#include <cstdlib>  // rand
#include <time.h>   // time
#include <getopt.h> // to parse long arguments.
#include <stdlib.h>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <algorithm>
using std::swap;
using std::min;

static const char* usage =
"Usage: %s [OPTIONS]...\n"
"Limited clone of shuf.  Supported options:\n\n"
"   -e,--echo              treat each argument as an input line.\n"
"   -i,--input-range=LO-HI treat each number in [LO..HI] as an input line.\n"
"   -n,--head-count=N      output at most N lines.\n"
"   --help                 show this message and exit.\n";

int main(int argc, char *argv[]) {
	// define long options
	static int echo=0, rlow=0, rhigh=0;
	static size_t count=-1;
	bool userange = false;
	bool BB = false;
	static struct option long_opts[] = {
		{"echo",        no_argument,       0, 'e'},
		{"input-range", required_argument, 0, 'i'},
		{"head-count",  required_argument, 0, 'n'},
		{"help",        no_argument,       0, 'h'},
		{0,0,0,0}
	};
	// process options:
	char c;
	int opt_index = 0;
	while ((c = getopt_long(argc, argv, "ei:n:h", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 'e':
				echo = 1;
				break;
			case 'i':
				if (sscanf(optarg,"%i-%i",&rlow,&rhigh) != 2) {
					fprintf(stderr, "Format for --input-range is N-M\n");
					rlow=0; rhigh=-1;
				} else {
					userange = true;
				}
				break;
			case 'n':
				count = atol(optarg);
			BB = true;
				break;
			case 'h':
				printf(usage,argv[0]);
				return 0;
			case '?':
				printf(usage,argv[0]);
				return 1;
		}
	}
	/* NOTE: the system's shuf does not read stdin *and* use -i or -e.
	 * Even -i and -e are mutally exclusive... */

	/* TODO: wri te me... */

if(echo == 1){//e

vector <string> V;
int i;	// this should cover the -e function?
while (optind < argc){
    V.push_back(argv[optind++]);
}
srand(time(0)); // use current time to determine pseudorandom sequence
    // print size of vector random numbers:
if(BB && count<=V.size()){
   for(int i = 0; i<count; i++){

		int range = rand() % V.size(); //get random # from 0-size
			 //assign the number to the index thus changign it
		cout << V[range] << endl; // print out the value at the index
			V.erase(V.begin() + range);//delete the element

		}
	}
	else{
    while(!V.empty()){

		int range = rand() % V.size(); //get random # from 0-size
			//assign the number to the index thus changign it
			cout << V[range] << endl; // print out the value at the index
			V.erase(V.begin() + range);//delete the element

		}
	}
}



	if(userange == true){//i only integers and provide a range
vector <int> V;
int i;
for(int i = rlow; i<=rhigh; i++){

	V.push_back(i);
}
srand(time(0)); // use current time to determine pseudorandom sequence
    // print size of vector random numbers:
if(BB && count<=V.size()){
   for(int i = 0; i<count; i++){

		int range = rand() % V.size(); //get random # from 0-size
			 //assign the number to the index thus changign it
		cout << V[range] << endl; // print out the value at the index
			V.erase(V.begin() + range);//delete the element

		}
	}
	else{
    while(!V.empty()){

		int range = rand() % V.size(); //get random # from 0-size
			 //assign the number to the index thus changign it
			cout << V[range] << endl; // print out the value at the index
			V.erase(V.begin() + range);//delete the element

			}

		}


	}





		return 0;
	}

