#include<iostream>
#include<string>

using namespace std;

void reduce_space(string &s) {
        
        int space=0;
        for(int i=0;i<s.size();i++) {
            if(i>0 && s[i]==' ' && s[i-1]==' ') space++;
            s[i-space]=s[i];
        }
        s=s.substr(0,s.size()-space);
    }
int main() {
	string s = "    Abhishek         Nayyar     tamu";
	reduce_space(s);
	cout << s << endl;
	return 0;
}
