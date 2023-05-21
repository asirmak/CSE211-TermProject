// Ali Sencer Irmak
// 20200702096

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class LList{

public:	
	LList(){
		headName = headAge = 0;
	}
	void add(string name, int age);
	void printbyAge();
	void printbyName();
	bool remove(string name);
	void update(string name, int age);
	void loadFile(string filename);
	void saveToFileByAge(string filename);
	void saveToFileByName(string filename);
	
private:
	struct LLNode{
		string name;
		LLNode *nextName;
		int age;
		LLNode *nextAge;
	};
	LLNode *headName; 
	LLNode *headAge;
};

void LList::add(string name, int age){ //adds new person to database

	LLNode *newPerson = new LLNode;
	newPerson->name = name;
	newPerson->age = age;
	newPerson->nextName = NULL;
	newPerson->nextAge = NULL;
	    
	if(headName == NULL || headAge == NULL){ // if there isn't anyone in database			 				 
		headName = newPerson;
		headAge = newPerson;
	}
	else{
		//adds person, sorted by age
		LLNode *curPerson = headAge;
		LLNode *prevPerson = NULL;
		while(curPerson && curPerson->age < age){ // determine the person where to put (sorted by age)
			prevPerson = curPerson;
			curPerson = curPerson->nextAge;
		}	
		
		if(curPerson == 0){ // insert at the end of the list
			prevPerson->nextAge = newPerson;
		}
		
		else if(prevPerson == 0){ // insert at the beginning
			newPerson->nextAge = headAge;
			headAge = newPerson;
		}
		
		else{ // insert somewhere except for other conditions
			prevPerson->nextAge = newPerson;
			newPerson->nextAge = curPerson;
		}
		
		//adds person, sorted by name
		curPerson = headName;
		prevPerson = 0;
		
		while(curPerson && curPerson->name < name){  // determine the person where to put (sorted by name)
			prevPerson = curPerson;
			curPerson = curPerson->nextName;
		}
			
		if(curPerson == 0){ // insert at the end of the list
			prevPerson->nextName = newPerson;
		}
		
		else if(prevPerson == 0){ // insert at the beginning
			newPerson->nextName = headName;
			headName = newPerson;
		}
		
		else{ // insert somewhere except for other conditions
			prevPerson->nextName = newPerson;
			newPerson->nextName = curPerson;
		}
	}
}

void LList::printbyAge(){ // prints database sorted by age
	cout<<"Database sorted by age"<<endl;
	LLNode *curPerson = headAge;
	while(curPerson){
		cout<< curPerson->name << " " << curPerson->age <<endl;
		curPerson = curPerson->nextAge;
	}
	cout<<endl;
}

void LList::printbyName(){ //prints database sorted by name
	cout<<"Database sorted by name"<<endl;
	LLNode *curPerson = headName;
	while(curPerson){
		cout<< curPerson->name << " " << curPerson->age <<endl;
		curPerson = curPerson->nextName;
	}
	cout<<endl;
}

bool LList::remove(string name){ // removes a person with it is name if it exists.

	LLNode *curPersonN = headName;
	LLNode *prevPersonN = 0;
	LLNode *curPersonA = headAge;
	LLNode *prevPersonA = 0;
	
	if(headName->name == name){ // reinitialize headName if we want to remove 1st one
		headName = curPersonN->nextName;
	}
	else{ // remove name anywhere
		prevPersonN = curPersonN;
		curPersonN = curPersonN->nextName;
		while(curPersonN){
			if(curPersonN->name == name){
				prevPersonN->nextName = curPersonN->nextName;		
				break;
			}
			else{
				prevPersonN = curPersonN;
				curPersonN = curPersonN->nextName;
			}
		}
	}
	
	while(curPersonA != curPersonN){ //finds the address of age that should be removed
		prevPersonA = curPersonA;
		curPersonA = curPersonA->nextAge;
	}
	
	if (prevPersonA == 0){ // reinitialize headAge if we want to remove 1st one
		headAge = curPersonA->nextAge;
		curPersonA = 0;  // removes their connection between other nodes
		curPersonN = 0;
		return 1;
	}
	
	else{
		prevPersonA->nextAge = curPersonA->nextAge; // remove name anywhere
		curPersonA = 0;		// removes their connection between other nodes
		curPersonN = 0;
		return 1;
	}
	return 0;

}

void LList::update(string name, int age){ // removes the person with old age
									   	 // and adds the person with updated age
	remove(name);
	add(name, age);
}

void LList::loadFile(string filename){ // loads a database 
	
	ifstream file;
	file.open(filename);
	
	string name;
	int age;
	
	while(file>>name){
		file>>age;
		add(name,age);
	}
}

void LList::saveToFileByAge(string filename){ // saves the sorted person database according to age 
											// to the same directory of the input file
	ofstream file;
	file.open(filename);
	LLNode *curPersonA = headAge;
	while(curPersonA){
		file << curPersonA->name << " " << curPersonA->age <<endl;
		curPersonA = curPersonA->nextAge;
	}
}

void LList::saveToFileByName(string filename){ // saves the sorted person database according to name 
											// to the same directory of the input file
	ofstream file;
	file.open(filename);
	LLNode *curPersonN = headName;
	while(curPersonN){
		file << curPersonN->name << " " << curPersonN->age <<endl;
		curPersonN = curPersonN->nextName;
	}
}




