#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<set>
#include<unordered_map>
#include "backprop.h"

using namespace std;

typedef vector<vector<string> > _I_DATA;
typedef vector<pair<vector<float>,int> > _NI_DATA;


/* function to seprate data in file */
vector<string> spplit(string s,char del)
{
	stringstream ss(s);
	string item;
	vector<string> res;
	while(getline(ss,item,del))
	{
		res.push_back(item);
	}

	return res;
}
// read data file
void read_file(_I_DATA& data,string file_name)
{
	ifstream ifile;
	ifile.open(file_name);
	
	string input;
	while(getline(ifile,input))
	{
		//cout << input << endl;
		vector<string> line_att= spplit(input,' ');
		data.push_back(line_att);
	}
	ifile.close();
	random_shuffle(data.begin(),data.end());
}
int normalize_data(_I_DATA& data,_NI_DATA& ni_data)
{
	if(data.size()==0) return 0;
	
	unordered_map<string,int> target_list;
	pair<int,int> init;
	init.first=INT_MIN;
	init.second=INT_MAX;
	// max , min
	vector<pair<float,float> > max_min_track(data[0].size()-1,init);
	for(vector<string> input : data)
	{
		vector<float> tmp;
		for(int i=0;i<input.size()-1;i++)
		{
			tmp.push_back(stof(input[i]));
			if(max_min_track[i].first < stof(input[i]))
			 	max_min_track[i].first = stof(input[i]);
			if(max_min_track[i].second > stof(input[i]))
				max_min_track[i].second = stof(input[i]);
		}
		int _sz=target_list.size();
		target_list.insert(make_pair(input[input.size()-1],_sz));
		ni_data.push_back(make_pair(tmp,0));		
	}
	
	assert(ni_data.size()==data.size());
	

	for(int i=0;i<ni_data.size();i++)
	{
		for(int j=0;j<ni_data[i].first.size();j++)
		{
			float div_by = (max_min_track[j].first==max_min_track[j].second) ? 1.0 : (max_min_track[j].first-max_min_track[j].second) ;
			ni_data[i].first[j]=(ni_data[i].first[j] - max_min_track[j].second)/div_by;
		}
		auto it = target_list.find(data[i][data[0].size()-1]);
		assert(it!=target_list.end());
		pair<string,int> p =*it;
		ni_data[i].second=p.second;		
	}
	return target_list.size();
}
void smooth_condition_no(_I_DATA& data) {

	// hardcode index for condition attribute  1
	for(vector<string>& input : data)
	{
		float val = stof(input[1]);
		val=log10(val);
		input[1]=to_string(val);	
				
	}
}
void print_data(_I_DATA data) {
	for(vector<string> input : data) {
		for(string s : input) {
			cout << s << "\t";
		}
		cout << endl;
	}
}
// main
int main(int argv,char *argc[])
{
	// parse file to get
	
	if(argv<5)
	{
		cout<<"INFO : exec data_file lr iteration layers\n"; 
		return 0;
	}
	_I_DATA data;
	_NI_DATA ni_data;
	float pass_per =0.0;	
	read_file(data,argc[1]);
	smooth_condition_no(data);
	//print_data(data);
	int no = normalize_data(data,ni_data);
	int ni=data[0].size()-1;
	int nh=stoi(argc[4]); // user given
	float lr = stof(argc[2]); // user given
	
	/* Uncomment for print >>  
	for(int i=0;i<ni_data.size();i++)
	{
		for(int j=0;j<ni_data[i].first.size();j++)
		{
			cout<<ni_data[i].first[j]<<"\t";
		}
		cout<<ni_data[i].second<<endl;
	}
	*/
	
	
	
	
		
	nn ob(ni,no,nh,lr,stoi(argc[3]));
	
	// divide training and text data
	// doing it for 1 fold only , can be extended for 10 folds cross validation
	int fold = data.size()*0.1;
	
	for(int i=0;i<10;i++)
	{
		_NI_DATA test_data(ni_data.begin()+(i*fold),ni_data.begin()+(i*fold)+fold);
		
		_NI_DATA train_data(ni_data.begin(),ni_data.begin()+(i*fold));
		_NI_DATA temp(ni_data.begin()+(i*fold)+fold,ni_data.end());
		
		train_data.insert(train_data.end(),temp.begin(),temp.end());
	
		//ob.backprop(train_data);
		ob.backprop(ni_data);
		//pass_per+=ob.testprop(test_data);
		pass_per+=ob.testprop(ni_data);
	}
	cout << "======== AVERAGE ====== \n";
	cout << (pass_per/10)*100 << endl;
	cout << " Data size " << data.size() << endl;	
	return 0;
}

