#include<iostream>
#include<vector>

using namespace std;

int main() {
	int arr[]= {2,0,1,0,0,3,4,9};
	vector<int> nums(arr,arr+sizeof(arr)/sizeof(int));
	int zero=0;
	for(int i=0;i<nums.size();i++) {
		if(nums[i]==0) {
			zero++;
			continue;
		}
		nums[i-zero]=nums[i];
		
	}
	for(int i=nums.size()-zero;i<nums.size();i++) {	
		nums[i]=0;
	}
	for(int i : nums) cout << i <<"\t";
	cout<<endl;	
	return 0;
}
