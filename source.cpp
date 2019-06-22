/******************************************************************/
/******************************************************************/
/* Created by Berk Cetinsaya on 2016/04/27                        */
/* Copyright (c) 2016 Berk Cetinsaya. All rights reserved.        */
/*                                                                */
/******************************************************************/
/******************************************************************/

#include "formalstringmatching.cpp"

int selection = 0;
int choice;
bool flag = true;

int main(int arg1, char **arg2)
{
    switch(arg1)
    {
        case 5: print_type = arg2[4];
            if(print_type.compare("N") == 0 || print_type.compare("n") == 0)
                print_type = "N";
            else if(print_type.compare("D") == 0 || print_type.compare("d") == 0)
                print_type = "D";
            else{
                print_type = "N";
                cout << "Your selection of print type is invalid. For default: It is Normal Print -> N" << endl;
            }
        case 4: filename = arg2[3];
        case 3: input = arg2[2];
        case 2:
            flag = false;
            choice = atoi(arg2[1]);
            while (choice < 1 || choice > 2)
            {
                cout << "1: String Matching by Naive Algorithm\n"
                        "2: String Matching by Finite State Automata\n"
                        "Enter a valid number: ";   
                cin >> choice;
            }
            break;
        case 1:
            cout << "\n\tWarning! You are using defaults!\n"
                    "You will be notified for algorithm id and text pattern...\n"
                    "For specifying text pattern you can use:\n"
                    << arg2[0] << 
                    " [algorithm_id] [pattern_text] [file_name] [print_type]\n"
                    " --> press ENTER to continue, CTRL+C to ABORT!: " << endl;
            string input;
            getline(cin,input);
    }
   
    Formal_string_matching *w = new Formal_string_matching();
    
    do{
        if(flag){
            cout <<"\nPlease select one of the following options:  \n";
            cout << "1: String Matching by Naive Algorithm\n"
                    "2: String Matching by Finite State Automata\n"
                    "3: Change filename (current: " << filename << ")\n"
                    "4: Select Print Type (current: " << print_type << ")\n"
                    "0: Quit\n";
            cout << "Enter your selection (1, 2, 3, 4 or 0): ";
            cin >> choice;
            if(choice == 1 || choice == 2)
            {
                cout << "Please Enter a string in order to search : ";
                cin.ignore();
                getline(cin, input);
            }
        }
        flag = true;
        switch (choice)
         {
            case 1:
                cout << "You have chosen String Mathing by Naive Algorithm \n" << endl;        
                w->pattern_text = input; 
                w->c_finite_state_automata = false;
                w->c_naive = true;
                w->execute_algorithm();
            break;
            case 2:
                cout << "You have chosen String Mathing by Finite State Automata \n" << endl;
                w->pattern_text = input; 
                w->c_naive = false;
                w->c_finite_state_automata = true;
                w->execute_algorithm();
            break; 
            case 3:
                cout << "Enter the file name: ";
                cin >> filename;
            break;
            case 4:
                cout << "Enter Print Type Normal or Detailed (N/D) : ";
                cin >> print_type;
                if(print_type.compare("N") == 0 || print_type.compare("n") == 0){
                    print_type = "N";
                    cout << "Print Type is Normal Print" << endl;
                }
                else if(print_type.compare("D") == 0 || print_type.compare("d") == 0){
                    print_type = "D";
                    cout << "Print Type is Detailed Print" << endl;                    
                }
                else{
                    print_type = "N";
                    cout << "Your selection of print type is invalid. For default: It is Normal Print -> N" << endl;
                }
                
            break;
            case 0:
                cout << "You have chosen Quit, Goodbye." << endl;
            break;
            default:
                cout<< "Your selection must be between 0 and 4!\n";
            }
    }while(choice!=0);

    return 0;
}