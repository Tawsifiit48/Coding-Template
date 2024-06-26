
#define MAX_N 100010 // second approach: O(n log n)
string T; // the input string, up to 100K characters
int n; // the length of input string
int RA[MAX_N], tempRA[MAX_N]; // rank array and temporary rank array
int SA[MAX_N], tempSA[MAX_N]; // suffix array and temporary suffix array
int c[MAX_N]; // for counting/radix sort

// SA[i] deontes the starting index of the i-th suffix in sorted order. For example, for the string
// abaab:
// SA[0] = 2 aab
// SA[1] = 3 ab
// SA[2] = 0 abaab
// SA[3] = 4 b
// SA[4] = 1 baab
// so len - B[i] = length of the i-th suffix in sorted order
// len - B[0] = 3 aab
// len - B[1] = 2 ab
// len - B[2] = 5 abaab
// len - B[3] = 1 b
// len - B[4] = 4 baab
// LCP[i] deontes the longest common prefix of the i-th and (i-1)th suffix in sorted order.
// LCP[0] = 0	aab		distinct substrings: aab aa a, no common prefix
// 			null	k = (len - SA[i]) - LCP[i] = 3 - 0 = 3
			
// LCP[1] = 1 	ab		distinct substrings: ab, common prefix: a; so a not counted
// 			aab		k = (len - SA[i]) - LCP[i] = 2 - 1 = 1
			
// LCP[2] = 2	abaab	distinct substrings: abaab abaa aba, common prefix: ab; so ab, a not counted
// 			ab		k = (len - SA[i]) - LCP[i] = 5 - 2 = 3
			
// LCP[3] = 0	b		distinct substrings: b, no common prefix
// 			abaab	k = (len - SA[i]) - LCP[i] = 1 - 0 = 1
			
// LCP[4] = 1	baab	distinct substrings: baab baa ba, common prefix: b; so b not counted
// 			b		k = (len - SA[i]) - LCP[i] = 4 - 1 = 3
			
// So total distinct substrings = 3+1+3+1+3 = 11.
// All you need to do is now filter out the substrings which are not in the specified range (less then
// p or greater then q). So the code becomes:
// for(i = 0; i < len; i++)
// {
//     k = min(len - SA[i], q) - max(LCP[i], p-1);
//     if(k > 0) sum += k;
// }


int Phi[MAX_N]; // longest common prefix
int LCP[MAX_N];
int PLCP[MAX_N]; // stores lcp between prev and current T + SA[i - 1], T + SA[i]
void countingSort(int k) { // O(n)
	int i, sum, maxi = max(300, n); // up to 255 ASCII chars or length of n
	memset(c, 0, sizeof c); // clear frequency table
	for (i = 0; i < n; i++) // count the frequency of each integer rank
		c[i + k < n ? RA[i + k] : 0]++;
	for (i = sum = 0; i < maxi; i++) {
		int t = c[i]; c[i] = sum; sum += t; 
	}
	for (i = 0; i < n; i++) // shuffle the suffix array if necessary
		tempSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
	for (i = 0; i < n; i++) // update the suffix array SA
		SA[i] = tempSA[i];
}

void constructSA() { // this version can go up to 100000 characters
	int i, k, r;
	for (i = 0; i < n; i++) RA[i] = T[i]; // initial rankings
	for (i = 0; i < n; i++) SA[i] = i; // initial SA: {0, 1, 2, ..., n-1}
	for (k = 1; k < n; k <<= 1) { // repeat sorting process log n times
		countingSort(k); // actually radix sort: sort based on the second item
		countingSort(0); // then (stable) sort based on the first item
		tempRA[SA[0]] = r = 0; // re-ranking; start from rank r = 0
		for (i = 1; i < n; i++) // compare adjacent suffixes
			tempRA[SA[i]] = (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
		// if same pair => same rank r; otherwise, increase r
		for (i = 0; i < n; i++) // update the rank array RA
			RA[i] = tempRA[i];
		if (RA[SA[n-1]] == n-1) break; // nice optimization trick
	} 
}

void computeLCP() {
	int i, L;
	Phi[SA[0]] = -1; // default value
	for (i = 1; i < n; i++) // compute Phi in O(n)
		Phi[SA[i]] = SA[i-1]; // remember which suffix is behind this suffix
	for (i = L = 0; i < n; i++) { // compute Permuted LCP in O(n)
		if (Phi[i] == -1) { PLCP[i] = 0; continue; } // special case
		while (T[i + L] == T[Phi[i] + L]) L++; // L increased max n times
			PLCP[i] = L;
		L = max(L-1, 0); // L decreased max n times
	}
	for (i = 0; i < n; i++) // compute LCP in O(n)
		LCP[i] = PLCP[SA[i]]; // put the permuted LCP to the correct position
}
