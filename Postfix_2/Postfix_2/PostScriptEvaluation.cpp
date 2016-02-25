#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

struct Dataset
{
	string chars;
	int	value;
	~Dataset() {};
};

template<class T>		//allow any type of data to be saved
class STACK 
{
private:		//create a data type containing
	struct NODE {
		T info;				// the info to be retreved / saved
		NODE *next;			// the link to the next item in the list
	};
	NODE *top;				// Current top of stack
public:
	void CreateTop() {
		NODE *temp;
		temp = new (NODE);
		temp->next = top;
		top = temp;
	}
	void PushStack(int x) {
		CreateTop();
		top->info = x;
	}
	void PushStack(int x, string var) {
		CreateTop();
		top->info.value = x;
		top->info.chars = var;
	}
	int PopStack()
	{
		NODE *temp = top;
		int x = temp->info;
		top = temp->next;
		delete temp;
		return x;
	}
	int Exists(string var) {
			NODE *temp = top;
			while (temp != NULL) {
				if (temp->info.chars == var) {
					return temp->info.value;
				}
				temp = temp->next;
			}
			return NULL;
		}
	~STACK() {
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
		STACK<int> expression;
		STACK<Dataset> vars;
		char *token;
		char sent[80];
		
		cout << "Enter a postfix expression with a $ at the end: "; cin.getline(sent, 80);
		token = strtok(sent, " ");		//tokenize this statement

		while (token != NULL) {
			if (token[0] >= '0' && token[0] <= '9'){ 
				expression.PushStack(atoi(token));		//converts charactrs to numbers
			}
			else if ((token[0] >= 'a' && token[0] <= 'z') || (token[0] >= 'A' && token[0] <= 'Z') ){
				string variable = token;
				int value = vars.Exists(variable);
				if (value != NULL) {
					expression.PushStack(value);
				}
				else {
					cout<< "\tEnter the value of " << variable << ": "; cin >> value;
					vars.PushStack(value, variable);
					expression.PushStack(value);
				}
			}
			else {
				switch (token[0])
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
			token = strtok(NULL, " ");
		}
		cout << "\tContinue (y/n)? "; cin >> cont; cont = toupper(cont);
		cout << endl;
		cin.ignore();
	} while (cont != 'N');

	system("pause");
	return 0;
}