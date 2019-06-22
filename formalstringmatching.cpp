/******************************************************************/
/******************************************************************/
/* Created by Berk Cetinsaya on 2016/04/27                        */
/* Copyright (c) 2016 Berk Cetinsaya. All rights reserved.        */
/* Edited: June 22, 2019                                          */
/******************************************************************/
/******************************************************************/

#include "formalstringmatching.h"
//#define DEBUG_MESSAGES // For debug mesagges you can uncomment this line

string print_type = "N"; // "D" // For the exact position of the string, you can uncomment this line, For print just line numbers and occurences
string filename = "text.txt";
string input;

int total_occurences = 0;

Formal_string_matching::Formal_string_matching(){}
Formal_string_matching::~Formal_string_matching(){}

int Formal_string_matching::naive_string_matcher(string text, string pat){
	int count = 0;
	int pat_length = pat.size();
	int text_length = text.size();
	int matched_count = 0;

	#ifdef DEBUG_MESSAGES
			cout << "Text : " << text << endl << "Pattern : " << pat << endl << "Text Length : " << text_length << endl << "Pattern Length : " << pat_length << endl;
	#endif
	//Text = "This is an example text"
	//Text size = 23
	//Pattern = "example"
	//Pattern size = 7
	for (int a = 0; a <= text_length - pat_length; a++){ // 0..16
		for (int b = 0; b < pat_length; b++) { // 0..7
			#ifdef DEBUG_MESSAGES
				cout << "a : " << a << endl;
				cout << "b : " << b << endl;
				cout << "text.at(a + b) : " << text.at(a + b) << " " << "pat.at(b) : " << pat.at(b) << endl;
			#endif
			if (text.at(a + b) == pat.at(b)) {
				// 'This is' an example text
				// 'example'			------> beginning
				// T'his is 'an example text
				//  'example'
				// Th'is is a'n example text
				//   'example'
				// Thi's is an' example text
				//    'example'
				//      ................
				// This is an 'example' text
				// 			  'example'	------> e==e , x==x , a==a, m==m , p==p , l==l , e==e --> count = 7
				//        ................
				// This is an examp'le text'
				// 				   'example' -> end
				count++;
				#ifdef DEBUG_MESSAGES
					cout << "Count++ : " << count << endl;
				#endif
			}
		}
		#ifdef DEBUG_MESSAGES
			cout << "count : " << count << " " << "pat_length : " << pat_length << endl;
		#endif
		if (count == pat_length)
		{
			//count = 7 && pattern size = 7 for example, so it is matched.
			matched_count++;
			#ifdef DEBUG_MESSAGES
				cout << " Matched Count : " << matched_count << endl;
			#endif
		}
		count = 0;
	}
	return matched_count;
}
int Formal_string_matching::finite_automaton_matcher(char *pat, char *txt, int **transition){
	int pattern_size = strlen(pat);
	int text_size = strlen(txt);

	int count = 0;
	int state = 0;

	for (int i = 0; i < text_size; i++)
	{
		//Text = "This is an example text"
		//Pattern = "example"
		// test is each character of text. e.g. txt[0] = 84 because it is integer so the ascii code of T is 84
		int test = txt[i];
		// state = transition[0][84] so state is 0 because all rows in transition[0] are 0 except first char of pattern
		// if state = transition[0][101]e , state will be 1
		// if state = transition[1][120]x , state will be 2
		// ..............
		// if state = transition[6][101]e , state will be 7
		state = transition[state][txt[i]];
		#ifdef DEBUG_MESSAGES
			cout << "Test Char : " << test << " State : " << state << endl;
		#endif
		if (state == pattern_size)
		{
			// if state is 7 and pattern size is 7 for this example, it is on accept state and count will be increased.
			count++;
			#ifdef DEBUG_MESSAGES
				cout << "State == Pattern Size : " << pattern_size << " Count : " << count << endl;
			#endif
		}
	}
	return count;
}
int** Formal_string_matching::create_transition_table(char *pattern, char alphabet[], int size){
	int longest_prefix_suffix = 0;
	int size_of_pattern = strlen(pattern);
	int temp = 0;

	#ifdef DEBUG_MESSAGES
			cout << "Pattern size : " << size_of_pattern << endl;
			cout << "Alphabet Size : " << size << endl;
	#endif

	// we find max ascii character in this loop
	for (int i = 0; i < size; i++){
		if ((int)alphabet[i] > temp) {
			temp = (int)alphabet[i]; // for our alphabet the max ascii is "}" its code is 125 so temp = 125.
			#ifdef DEBUG_MESSAGES
				cout << "Alphabet[" << i << "] : " << alphabet[i] << endl;
			#endif
		}
	}

	// Create an dynamic array whose size is pattern size + 1 so now it is
	// transtition_table[8]
	int** transition_table = new int*[size_of_pattern + 1];
	// in this loop we add a new column for this array whose size is our max ascii code


	for (int i = 0; i < size_of_pattern + 1; ++i){
		transition_table[i] = new int[temp];
		// it will be like this
		// transitition_table[0][125]
		// transitition_table[1][125]
		// transitition_table[2][125]
		// transitition_table[3][125]
		// .............
		//transitition_table[8][125]
		#ifdef DEBUG_MESSAGES
			cout << "transition_table[" << size_of_pattern << "][125]  was created." << endl;
			cout << "pattern[] " << pattern[i] << endl;
		#endif
	}
	// In the first row, everything should be equal to 0 also longest prefix suffix equals to 0
	for (int x = 0; x < temp; x++) {
		transition_table[0][x] = 0;
	}
	// In here, we assign 1 to first character of pattern in the first row.
	transition_table[0][pattern[0]] = 1; 
	#ifdef DEBUG_MESSAGES
		cout << "transition_table[0][" << (int)pattern[0] << "] : " << transition_table[0][pattern[0]] << endl;
		cout << "longest_prefix_suffix : " << longest_prefix_suffix << endl;
	#endif
	// The main idea behind the algorithm is that we take minimum of q+2 from minimum pattern size + 1. It means we need to think to decrease k until the last index.

	for (int i = 1; i <= size_of_pattern; i++)
	{
		for (int x = 0; x < temp; x++){
			transition_table[i][x] = transition_table[longest_prefix_suffix][x];
		}

		// Update state and go to next state
		transition_table[i][pattern[i]] = i + 1;
		#ifdef DEBUG_MESSAGES
			cout << "transition_table[" << i << "][" << (int)pattern[i] << "] = " << i + 1 << endl;
		#endif

		// Update longest_prefix_suffix 
		
		if (i < size_of_pattern){
			longest_prefix_suffix = transition_table[longest_prefix_suffix][pattern[i]];
			#ifdef DEBUG_MESSAGES
				cout << "longest_prefix_suffix : " << longest_prefix_suffix << endl;
			#endif
		}
	}
	#ifdef DEBUG_MESSAGES
		cout << "Transition Table is completed..." << endl;
	#endif
	return transition_table;
}

vector<string> split(string str, char delimiter) {
	vector<string> internal;
  	stringstream ss(str);
  	string tok;
  
  	while(getline(ss, tok, delimiter)) {
    	internal.push_back(tok);
  	} 
  	return internal;
}

void Formal_string_matching::execute_algorithm(){
	if (c_naive==true){
		char* pat = strdup(pattern_text.c_str());
		ifstream file(filename);
		#ifdef DEBUG_MESSAGES
			cout << filename << endl;
		#endif
		vector<string> line;
		vector<int> occurences;
		string mystr;
		
		while (getline(file, mystr))
		{
			line.push_back(mystr);
		}
		clock_t naive_time;
		double duration = 0; 
		
		for (int i = 0; i < line.size(); i++){
			string str = line.at(i);
			char *result = strdup(str.c_str());

			naive_time = clock();
			int occurence = naive_string_matcher(result, pat);
			duration = duration + ( (clock() - naive_time) / (double)CLOCKS_PER_SEC);

			occurences.push_back(occurence);
			if(occurence != 0)
				total_occurences = total_occurences + occurence;
		}
		
		int counter = 0;
		for (int k = 0; k < occurences.size(); k++){
			if(occurences.at(k)==0)
				counter++;
			if(print_type.compare("N") == 0){
				if(occurences.at(k)!=0){
					if(occurences.at(k)==1){
						cout << "Line " << k + 1 << " : " << occurences.at(k) << " occurence" << endl;
	 				}
					
					else{
						cout << "Line " << k + 1 << " : " << occurences.at(k) << " occurences" << endl;
					}
				}
			}
			if(print_type.compare("D") == 0){
				if(occurences.at(k)!=0){
					string myCSV = line.at(k);
	 				vector<string> sep = split(myCSV, ' ');
	 				int pos = find(sep.begin(), sep.end(), input) - sep.begin();
					if(occurences.at(k)==1)
					{
						cout << "Line " << k + 1 << " : " << occurences.at(k) << " occurence" << " - ";
						for(int q = 0 ; q < sep.size() ; q++ ){
	 					if(q == pos)
	 						cout << "->" <<sep.at(q) << " ";
	 					else
	 						cout << sep.at(q) << " ";
	 				}
	 				cout << endl;
					}
					else{
						cout << "Line " << k + 1 << " : " << occurences.at(k) << " occurences" << " - ";
					for(int x = 0 ; x < sep.size() ; x++ ){
	 					if(x == pos)
	 						cout << "->" <<sep.at(x) << " ";
	 					else
	 						cout << sep.at(x) << " ";
	 				}
	 				cout << endl;
					}
				}
			}
		}
		if(counter == line.size()){
			cout << "There is not any occurences. Please search different string." << endl;
			counter = 0;
		}
		if(total_occurences != 1 || total_occurences != 0)
			cout << "Total: " << total_occurences << " occurences" << endl;
		total_occurences = 0;
		cout << "Time needed for the naive search algorithm is : " << duration << " seconds" << endl;
		duration = 0;
	}
	if (c_finite_state_automata == true){
		char* pat = strdup(pattern_text.c_str());
		//cout << pat << endl;
		ifstream file(filename);
		//cout << filename << endl;
		vector<string> line;
		vector<int> occurences;
		string mystr;
		int max = 0;

		while (getline(file, mystr))
		{
			line.push_back(mystr);
		}
		int size = strlen(pat);
		
		char example_alphabet[] = {'}','{',' ','0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','R','S','T','U','V','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',',','.','?','!','\'','-','[',']','(',')','"','|',':',';'};
		
		for (int i = 0; i < sizeof(example_alphabet); i++){
			if ((int)example_alphabet[i] > max){
				max = example_alphabet[i];
			}
		}

		clock_t trans;
		double duration_tf = 0;
		trans = clock();
		int **transition_table = create_transition_table(pat, example_alphabet, sizeof(example_alphabet));
		duration_tf = (clock() - trans) / (double)CLOCKS_PER_SEC;

		clock_t finite_time;
		double duration = 0;

		for (int i = 0; i < line.size(); i++){
			string str = line.at(i);
			#ifdef DEBUG_MESSAGES
				cout << "STRING : " << str << endl;
			#endif
			char *result = strdup(str.c_str());

			finite_time = clock();
			int occurence = finite_automaton_matcher(pat, result, transition_table);
			duration = duration + ((clock() - finite_time) / (double)CLOCKS_PER_SEC);

			occurences.push_back(occurence);
			if(occurence != 0)
				total_occurences = total_occurences + occurence;
		}

		int counter = 0;
		for (int k = 0; k < occurences.size(); k++){
			if(occurences.at(k)==0)
				counter++;
			if(print_type.compare("N") == 0){
				if(occurences.at(k)!=0){
					if(occurences.at(k)==1){
						cout << "Line " << k + 1 << " : " << occurences.at(k) << " occurence" << endl;
	 				}
					
					else{
						cout << "Line " << k + 1 << " : " << occurences.at(k) << " occurences" << endl;
					}
				}
			}
			if(print_type.compare("D") == 0){
				if(occurences.at(k)!=0){
					string myCSV = line.at(k);
	 				vector<string> sep = split(myCSV, ' ');
	 				int pos = find(sep.begin(), sep.end(), input) - sep.begin();
					if(occurences.at(k)==1)
					{
						cout << "Line " << k + 1 << " : " << occurences.at(k) << " occurence" << " - ";
						for(int q = 0 ; q < sep.size() ; q++ ){
	 					if(q == pos)
	 						cout << "->" <<sep.at(q) << " ";
	 					else
	 						cout << sep.at(q) << " ";
	 				}
	 				cout << endl;
					}
					else{
						cout << "Line " << k + 1 << " : " << occurences.at(k) << " occurences" << " - ";
					for(int x = 0 ; x < sep.size() ; x++ ){
	 					if(x == pos)
	 						cout << "->" <<sep.at(x) << " ";
	 					else
	 						cout << sep.at(x) << " ";
	 				}
	 				cout << endl;
					}
				}
			}
		}
		if(counter == line.size()){
			cout << "There is not any occurences. Please search different string." << endl;
			counter = 0;
		}
		#ifdef DEBUG_MESSAGES
			cout << "The max ascii character : " << max << " - " << static_cast<char>(max) << endl;
		#endif
		if(total_occurences != 1 || total_occurences != 0)
			cout << "Total: " << total_occurences << " occurences" << endl;
		total_occurences = 0;
		cout << "Time needed for the search with Automata algorithm is : " << duration + duration_tf << " seconds" << endl;
	}
}


