#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
#include<unordered_map>
#include<cmath>
#include<cassert>
#include<algorithm>
using namespace std;

vector<string> split(string input,char del) {
	stringstream ss(input);
	vector<string> res;
	string tmp;
	while(getline(ss,tmp,del)) {
		res.push_back(tmp);
	}
	return res;
}
float get_avg(vector<string> tmp,string& max_val,string& min_val) {
	
	max_val = *max_element(tmp.begin(),tmp.end());
	min_val = *min_element(tmp.begin(),tmp.end());
	float res = 0.0;
	for(string s : tmp) {
		res += stof(s);
	}
	res=res/(tmp.size()*1.0);
	return res;
}
int main(int argc,char *argv[]) {

	if(argc<2) return 0;

	ifstream ifile;
	ofstream ofile;
	ofile.open("approx_stats.txt",ofstream::out | ofstream::app);
	ofile << "===========\n";
	ofile << argv[1] << endl;
	ifile.open(argv[1]);
	string input;
	unordered_map<string,vector<string> > data_size[6];
	unordered_map<string,vector<string> > condition_number[6];
	unordered_map<string,vector<string> > approx_bit[6];
	vector<pair<string,int> > case1;
	case1.push_back(make_pair("2-3",20));
	case1.push_back(make_pair("3-4",20));
	case1.push_back(make_pair("5-6",20));
	case1.push_back(make_pair("2-3",16));
	case1.push_back(make_pair("3-4",16));
	case1.push_back(make_pair("5-6",16));
	vector<pair<int,int>  > case2;
	case2.push_back(make_pair(512,20));
	case2.push_back(make_pair(1024,20));
	case2.push_back(make_pair(128,20));
	case2.push_back(make_pair(512,16));
	case2.push_back(make_pair(1024,16));
	case2.push_back(make_pair(128,16));
	vector<pair<string,int> > case3;
	case3.push_back(make_pair("2-3",512));
	case3.push_back(make_pair("3-4",512));
	case3.push_back(make_pair("5-6",512));
	case3.push_back(make_pair("2-3",1024));
	case3.push_back(make_pair("3-4",1024));
	case3.push_back(make_pair("5-6",1024));
	
	while(getline(ifile,input)) {
		vector<string> tmp = split(input,' ');
		int cond_num  = stoi(tmp[1]);	
		cond_num= log10(cond_num);
		string s_cond;
		if(cond_num<1) {
			s_cond="0-1";
		} else if(cond_num >=1 && cond_num < 2) {	
			s_cond="1-2";
		} else if (cond_num >=2 && cond_num < 3) {	
			s_cond="2-3";
		} else if (cond_num >=3 && cond_num < 4) {	
			s_cond="3-4";
		} else if (cond_num >=4 && cond_num < 5) {	
			s_cond="4-5";
		} else if (cond_num >=5 && cond_num <= 6) {	
			s_cond="5-6";
		} else {
			//cout << cond_num << endl;
			assert(0);
		}
		int ct=0;
		for(pair<string,int> p : case1) {
			if(s_cond.compare(p.first)==0 && stoi(tmp[3])==p.second) {	
				data_size[ct][tmp[0]].push_back(tmp[2]);
			}
			ct++;
		}
		ct=0;
		for(pair<int,int> p : case2) {
			if(stoi(tmp[0])==p.first && stoi(tmp[3])==p.second) {
				condition_number[ct][s_cond].push_back(tmp[2]);
			}
			ct++;
		}
		ct =0;
		for(pair<string,int> p : case3) {
			if(s_cond.compare(p.first)==0 && stoi(tmp[0])==p.second) {
				approx_bit[ct][tmp[3]].push_back(tmp[2]);
			}
			ct++;
		}	
	}
	ofile << " ==== DATA Size ======= \n";
	// get average for data size
	for(int i=0;i<6;i++) {
		ofile << "Case "<<"CN : " <<case1[i].first <<"\t"<<"AB : "<<case1[i].second << endl;
		for(pair<string,vector<string> > p : data_size[i]) {
			string max_val,min_val;
			ofile << p.first << "\t" << get_avg(p.second,max_val,min_val) <<"\t"<<"Max : " <<max_val << "\t" <<"Min : " <<min_val<< endl;
		}
	}	
	ofile << " === Condition Number ===== \n";
	// get average for condition number
	for(int i=0;i<6;i++) {	
		ofile << "Case "<<"DS : " <<case2[i].first <<"\t"<<"AB : "<<case2[i].second << endl;
		for(pair<string,vector<string> > p : condition_number[i]) {	
			string max_val,min_val;
			ofile << p.first << "\t" << get_avg(p.second,max_val,min_val) <<"\t"<<"Max : " <<max_val << "\t" <<"Min : " <<min_val<< endl;
		}
	}	
	ofile <<  " === Approx bits ==== \n";
	// get average for approx bits
	for(int i=0;i<6;i++) {	
		ofile << "Case "<<"CN : " <<case3[i].first <<"\t"<<"DS : "<<case3[i].second << endl;
		for(pair<string,vector<string> > p : approx_bit[i]) {	
			string max_val,min_val;
			ofile << p.first << "\t" << get_avg(p.second,max_val,min_val) <<"\t"<<"Max : " <<max_val << "\t" <<"Min : " <<min_val<< endl;
		}
	}
	ofile << "====================\n";
	ofile << "====================\n";
	ofile << "====================\n";
	ofile.close();
	ifile.close();	
	return 0;
}
