#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <queue>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

long long total_subarray_inversions = 0;

int* count_inversions(vector<int> &a, int as, int ae) {
	if (ae - as == 1) {
		int* small_array = new int[2];
		if (a[ae] < a[as]) {
			++total_subarray_inversions;
			small_array[0] = a[ae];
			small_array[1] = a[as];
		}
		else {
			small_array[0] = a[as];
			small_array[1] = a[ae];
		}
		return small_array;
	}
	else if (ae - as == 0) {
		int* small_array = new int[1];
		small_array[0] = a[as];
		
		return small_array;
	}
	else {
		int* sub_array1 = NULL;
		int* sub_array2 = NULL;
		
		int a1s = as;
		int a1e = as + (ae - as + 1) / 2 - 1;
		int a2s = a1e + 1;
		int a2e = ae;
		
		int ar_size = ae - as + 1;
		int* combined_array = new int[ar_size];
		
		sub_array1 = count_inversions(a, a1s, a1e);
		sub_array2 = count_inversions(a, a2s, a2e);
		
		int val1 = sub_array1[0];
		int val2 = sub_array2[0];
		
		int iter1 = 0;
		int iter2 = 0;
		int iter3 = 0;
		
		while (iter1 <= a1e - a1s && iter2 <= a2e - a2s) {
			val1 = sub_array1[iter1];
			val2 = sub_array2[iter2];
			if (val1 <= val2) {
				combined_array[iter3] = val1;
				iter1++;
			}
			else {
				total_subarray_inversions = total_subarray_inversions + (a1e - a1s + 1 - iter1);
				combined_array[iter3] = val2;
				iter2++;
			}
			iter3++;
		}
		if (iter1 > a1e - a1s && iter2 <= a2e - a2s) {
			while(iter2 <= a2e - a2s) {
				val2 = sub_array2[iter2];
				iter2++;
				combined_array[iter3] = val2;
				iter3++;
			}
		}
		else if (iter1 <= a1e - a1s && iter2 > a2e - a2s) {
			while(iter1 <= a1e - a1s) {
				val1 = sub_array1[iter1];
				iter1++;
				combined_array[iter3] = val1;
				iter3++;
			}
		}
		delete sub_array1;
		delete sub_array2;
		return combined_array;
	}
}

int main(){
    int t;
    cin >> t;
    vector<long long> result_array(t);
    for(int a0 = 0; a0 < t; a0++){
        int n;
        cin >> n;
        vector<int> arr(n);
        for(int arr_i = 0;arr_i < n;arr_i++){
           cin >> arr[arr_i];
        }
        int* sorted_array = count_inversions(arr, 0, arr.size() - 1);
        result_array[a0] = total_subarray_inversions;
        total_subarray_inversions = 0;
    }
    for(int a0 = 0; a0 < t; a0++) {
    	cout << result_array[a0] << endl;
    }
    return 0;
}
