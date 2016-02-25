//------------------------------------------------------------------------------------------
//          Name		Candelario D. Eguia
//          Course		CMPS-455
//          Project		No.2
//          Due date	Feb. 26, 2015
//          Professor	Ray Ahmadnia
//
// This program displays:
//       Evaluate postfix expressions with multiple letter variables
//------------------------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

struct Dataset								// Store string and associated integers
{
	char *chars;
	int	value;
	~Dataset() {};
};

template<class T>							// allow any type of data to be saved
class STACK									// Create a Linklist Stack for the evaluation
{
private:					
	struct NODE {							// Create a data type containing
		T info;								// the info to be retreved / saved
		NODE *next;							// the link to the next item in the list
	};
	NODE *top;								// Holds the current top of stack
public:
	void CreateTop() {						// Creates a new Node
		NODE *temp;
		temp = new (NODE);
		temp->next = top;
		top = temp;
	}
	void PushStack(int x) {					// Used to push a new integer onto the stack
		CreateTop();
		top->info = x;
	}
	void PushStack(int x, char *var) {		// Used to push a new variable and value
		CreateTop();
		top->info.value = x;
		top->info.chars = var;
	}
	int PopStack()							// Returns Value deletes node
	{
		NODE *temp = top;
		int x = temp->info;
		top = temp->next;					// Replaces the top of stack node 
		delete temp;						// Deletes the old node on top of stack
		return x;							// Returns value
	}
	int Exists(char *var) {				// Returns NULL or variable value
		NODE *temp = top;
		while (temp != NULL) {			// Loops through nodes
			if (*temp->info.chars == *var) { // * used to compare contents
				return temp->info.value;	// Returns value
			}
			temp = temp->next;			// sets the next node in the stack
		}
		return NULL;					// Returns NULL if not found
	}
	~STACK() {								// Deletes any nodes left in the stack
		NODE *temp = top;
		while (temp != NULL) {
			temp = temp->next;
			delete top;
			top = temp;
		}
	}
};

int main() {
	char cont;

	do
	{
		STACK<int> expression;				// Stores integers and calculation results
		STACK<Dataset> vars;				// Stores the Variable and integer set
		char *token;						// Pointer to character array
		char sent[80];						// Holds the Expression
		
		cout << "Enter a postfix expression with a $ at the end: "; cin.getline(sent, 80);
		token = strtok(sent, " ");			//tokenize this statement

		while (token != NULL) {
			if (token[0] >= '0' && token[0] <= '9'){ 
				expression.PushStack(atoi(token));		// Converts charactrs to numbers
			}
			else if ((token[0] >= 'a' && token[0] <= 'z') || (token[0] >= 'A' && token[0] <= 'Z') ){
				int value = vars.Exists(token);		// gets token int or NULL
				if (value != NULL) {					
					expression.PushStack(value);		// Places value on the stack
				}
				else {
					cout<< "\tEnter the value of " << token << ": "; cin >> value;
					vars.PushStack(value, token);	// Pushes character(s) and interger
					expression.PushStack(value);		// Pushes integer to the stack
				}
			}
			else {
				switch (token[0])			// Preformes Calculations based on opperator
				{
					int first, second, num, den;
				case '+':
					expression.PushStack(expression.PopStack() + expression.PopStack());
					break;
				case '-':
					second = expression.PopStack();
					first = expression.PopStack();
					expression.PushStack(first - second);
					break;
				case '*':
					expression.PushStack(expression.PopStack() * expression.PopStack());
					break;
				case '/':
					den = expression.PopStack();
					num = expression.PopStack();
					expression.PushStack(num / den);
					break;
				case '$':
					cout << "\t\tFinal value = " << expression.PopStack() << endl;
					break;
				default:
					cout << "Opperation not recognized\n";
					break;
				}
			}
			token = strtok(NULL, " ");				// gets the next char array
		}
		cout << "\tContinue (y/n)? "; cin >> cont; cont = toupper(cont);
		cout << endl;
		cin.ignore();
	} while (cont != 'N');

	system("pause");
	return 0;
}
/*---------------------------- OUTPUT ------------------------------------------------------
Enter a postfix expression with a $ at the end: ab 22 * c + $
        Enter the value of ab: 2
        Enter the value of c: 4
                Final value = 48
        Continue (y/n)? y

Enter a postfix expression with a $ at the end: tom jerry 123 + tom * - $
        Enter the value of tom: 2
        Enter the value of jerry: 3
                Final value = -250
        Continue (y/n)? n

Press any key to continue . . .
------------------------------------------------------------------------------------------*/