#include <cstdio>
#include <getopt.h> // to parse long arguments.
#include <string>
using std::string;
#include <iostream>
#include <sstream>
#include <bits/stdc++.h>
using std::cin;
using std::cout;
#include <set>
using std::set;
using std::multiset;
#include <strings.h>
using namespace std;

static const char* usage =
"Usage: %s [OPTIONS]...\n"
"Limited clone of sort.  Supported options:\n\n"
"   -r,--reverse        Sort descending.\n"
"   -f,--ignore-case    Ignore case.\n"
"   -u,--unique         Don't output duplicate lines.\n"
"   --help              Show this message and exit.\n";


struct node {
	string data;
	node* next;
};


struct igncaseComp{
  bool operator()(const string& s1, const string s2){
    return (strcasecmp(s1.c_str(),s2.c_str()) < 0);
  }
};


void printList(node*& L){
	node* p = L->next;
	while (p != NULL) {
		cout << p->data <<endl;
		p = p->next;
	}
}

void printListd(node*& L){
	node* p = L->next;
	cout<<L->data<<endl;
	while (p->next != NULL) {
		cout << p->data <<endl;
		p = p->next;
	}
}


void uniquee(node* L){
node* p = L->next;

	while (p != NULL){
		while(p->next != NULL  && p->next->data == p->data){
			node* q = p->next;
			p->next = q->next;
			delete q;
		}
		p = p->next;
	}
}




int main(int argc, char *argv[]) {
	// define long options
	static int descending=0, ignorecase=0, unique=0;
	static struct option long_opts[] = {
		{"reverse",       no_argument,   0, 'r'},
		{"ignore-case",   no_argument,   0, 'f'},
		{"unique",        no_argument,   0, 'u'},
		{"help",          no_argument,   0, 'h'},
		{0,0,0,0}
	};
	// process options:
	char c;
	int opt_index = 0;
	while ((c = getopt_long(argc, argv, "rfuh", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 'r':
				descending = 1;
				break;
			case 'f':
				ignorecase = 1;
				break;
			case 'u':
				unique = 1;
				break;
			case 'h':
				printf(usage,argv[0]);
				return 0;
			case '?':
				printf(usage,argv[0]);
				return 1;
		}
	}

  string x;
  node* L = new node;
  L->next = NULL;


while (getline(cin,x)) {
	if (descending == 1){

		node* q = L;
		node* p = NULL;

		if(ignorecase == 1){
       	while (q != NULL && (strcasecmp(q->data.c_str(),x.c_str()) > 0)) {
				p = q;
				q = q->next;
    }
  }
			else{
				while (q->next != NULL && q->data > x) {
					p = q;
					q = q->next;
    }
  }
		node* n = new node;
		n->data = x;
		n->next = q;
		if (p == NULL) {
			L = n;
		} else {
			p->next = n;
		}
}
else{
		node* q = L;
		node* p = NULL;
 if(ignorecase == 1){
       	while (q != NULL && (strcasecmp(q->data.c_str(),x.c_str()) < 0)) {
			p = q;
			q = q->next;
    }
  }
  else{
		while (q != NULL && q->data < x) {
      p = q;
			q = q->next;
    }
  }
		node* n = new node;
		n->data = x;
		n->next = q;
		if (p == NULL) {
			L = n;
		} else {
			p->next = n;
		}

}


if (unique == 1)
	uniquee(L);

}
if (descending == 1){
printListd(L);
}
else
printList(L);
	return 0;
}
