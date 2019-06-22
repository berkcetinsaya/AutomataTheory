/******************************************************************/
/******************************************************************/
/* Created by Berk Cetinsaya on 2016/04/27                        */
/* Copyright (c) 2016 Berk Cetinsaya. All rights reserved.        */
/* Edited: June 22, 2019                                          */
/******************************************************************/
/******************************************************************/

#ifndef FORMALSTRINGMATCHING_H
#define FORMALSTRINGMATCHING_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

class Formal_string_matching
{

public:
	Formal_string_matching();
	~Formal_string_matching();

	bool c_naive;
	bool c_finite_state_automata;
	string pattern_text;

	int naive_string_matcher(string text, string pat);	
	int finite_automaton_matcher(char *pat, char *txt, int **transition);
	int** create_transition_table(char *pat, char abc[], int size);
	
	void execute_algorithm();


};

#endif
