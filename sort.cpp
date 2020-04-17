/*
 * CSc103 Project 4: Sorting with lists
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
 * #hours: 8
 */

#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
#include <getopt.h> // to parse long arguments.
#include <string>
using std::string;

struct node {
	std::string data;
	node* next;
	node* prev;
	node(std::string data, node* next, node* prev) : data(""), next(NULL), prev(NULL) {}
};

node* printList(node* first);
void printData(std::string n);
node* getLast(node* n);
node* getFirst(node* n);
node* findSpot(node* first, node* newOne, int reverse);

int main(int argc, char *argv[]) {
	/* define long options */
	static int unique=0, reverse=0;
	static struct option long_opts[] = {
		{"unique",   no_argument,       &unique,   'u'},
		{"reverse",  no_argument,       &reverse,  'r'},
		{0,0,0,0} // this denotes the end of our options.
	};
	/* process options */
	char c; /* holds an option */
	int opt_index = 0;
	while ((c = getopt_long(argc, argv, "ur", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 'u':
				unique = 1;
				break;
			case 'r':
				reverse = 1;
				break;
			case '?': /* this will catch unknown options. */
				return 1;
		}
	}
	/* NOTE: at this point, variables 'reverse' and 'unique' have been set
	 * according to the command line.  */
	/* TODO: finish writing this.  Maybe use while(getline(cin,line)) or
	 * similar to read all the lines from stdin. */

	std::string line = "";
	node* place = new node("",NULL,NULL);
	cin >> line;
	cin.ignore();
	place->data = line;

	if(unique){
		std::vector <std::string> b;
		b.push_back(place->data);
		while(getline(cin, line)){
			node* newN = new node("", NULL, NULL);
			newN->data = line;
			bool flag = false;
			for(size_t i = 0; i < b.size(); i++){
				if(newN->data == b[i]){
					flag = true;
					//break;
				}
			}
			if(!flag){
				findSpot(getFirst(place), newN, reverse);
				b.push_back(newN->data);
			}
		}
	}else{
		while(getline(cin, line)){
			node* newN = new node("", NULL, NULL);
			newN->data = line;
			findSpot(getFirst(place), newN, reverse);
		}
	}

	printList(getFirst(place));
	return 0;
}

node* findSpot(node* n, node* newN, int reverse){
	if(reverse){
		if(n->data >= newN->data){
			if(n->next == NULL){
				n->next = newN;
				newN->prev = n;
				return newN;
			}else{
				return findSpot(n->next, newN, reverse);
			}
		}else{
			if(n->prev == NULL){
				newN->next = n;
				n->prev = newN;
				return newN;
			}else{
				newN->next = n;
				n->prev->next = newN;
				newN->prev = n->prev;
				n->prev = newN;
				return newN;
			}
		}
	}else{
		if(n->data <= newN->data){
			if(n->next == NULL){
				n->next = newN;
				newN->prev = n;
				return newN;
			}else{
				return findSpot(n->next, newN, reverse);
			}
		}else{
			if(n->prev == NULL){
				newN->next = n;
				n->prev = newN;
				return newN;
			}else{
				newN->next = n;
				n->prev->next = newN;
				newN->prev = n->prev;
				n->prev = newN;
				return newN;
			}
		}
	}
}

node* printList(node* n) {
	if (n->next == NULL) {
		printData(n->data);
		return n;
	}
	printData(n->data);
	return printList(n->next);
}

node* getLast(node* n) {
	if (n->next == NULL) return n;
	return getLast(n->next);
}

node* getFirst(node* n) {
	if (n->prev == NULL) return n;
	return getFirst(n->prev);
}

void printData(std::string n) {
	std::cout << n << std::endl;
}
