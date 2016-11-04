#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>


using namespace std;

vector<string> split(string input,char del) {

	vector<string> res;
	
}
int main(int argv,char *argc[]) {
	
	ifstream ifile;
	ofstream ofile;
	if(argv < 2) return 0;
	ifile.open(argc[1]);
	string input;	
	while(getline(ifile,input)) {
		cout << input << endl;
	}
	
	
	return 0;
}
