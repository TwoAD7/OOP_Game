#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

#include "Run.h"

/*
The "this" key word is a pointer to the object's "stuff" inside it it is in (i.e. calling member functions/variables within the classs(our object) \)
*/

void Player::pickUpObject(Object* obj) {
    this->objects->push_back(obj);
}

void Player::dropObject(Object *obj) {
    bool found = false;
    for (int i = 0; i < this->objects->size() && !found; i++) {
        // OK to compare pointers
        if (this->objects->at(i) == obj) {
            this->objects->erase(this->objects->begin()+i);
            found = true;
        }
    }
}

bool Player::hasObject(Object *obj) const {
    bool found = false;
    for (int i = 0; i < this->objects->size() && !found; i++) {
        // OK to compare pointers
        if (this->objects->at(i) == obj) {
            found = true;
        }
    }
    return found;
}
void Player::removeObject(Object *obj) {
    bool deleted = false;
    for (int i = 0; i < this->objects->size() && !deleted; i++) {
        if (this->objects->at(i) == obj) {
            this->objects->erase(this->objects->begin() + i);
            deleted = true;
        }
    }
}

vector<Object*>* Player::getObjects() const {
    return this->objects;
}

//defining our function to make our rooms, using the "is-a" relationship with the rooms 
//since they are derived from the "location" class
location* location::make_loc(string name){
 if(name == "Room1")
  return new room1;
 if(name == "Room2")
  return new room2;
 if(name == "Room3")
  return new room3;
 else
  return new room4;
 };

/*vector<string> *room1::set_objects(Object *obj(int number, string word, string comment)) {
obj ->push_back(obj1(number,word,comment)); //might need to reference the objects we pass 
return obj;
}*/


//VOID SURROUNDINGS FUNCTION IS NEEDED (DEFINE IT HERE)

 room1::room1(){
 	surroundings = "Room 1 description holder";
 	npcroom1 = new NPC("Room1");

 	Key* key1 = new Key("Room2");
 	Key* key2 = new Key("Room3");
 	Key* key3 = new Key("Room4");

 	Door* Door1 = new Door(key1, "Room2");
 	Door* Door2 = new Door(key2, "Room3");
 	Door* Door3 = new Door(key3, "Room4");
 }

 room2::room2(){
 	surroundings = "Room 2 description holder";
 	npcroom2 = new NPC("Room2");
 }

 room3::room3(){
 	surroundings = "Room 3 description holder";
 	npcroom3 = new NPC("Room3");
 }

 room4::room4(){
 	surroundings = "Room 4 description holder";
 	npcroom4 = new NPC("Room4");
 }
/*
 string PromptCommand(Player User)
{
	cout<< "Type a command: (talk, move, look around)" << endl;
	string input;
	cin >> input;
	if(input == "talk"){
		return "";
	}
	else if (input == "move"){
		return "";
	}
	else if (input == "look around"){
		return "";
	}
	else{
		return "Error: Invalid Command";
	}
}
*/

string PromptOptions()
{
	cout<< "Type a command: (talk, move, look around)" << endl;
	string input;
	cin >> input;
	return input;
}

int main(){
	
	//Game(); *Starts Game up
	
	string ans;
	
	cout<<"It is 8:46 AM, you have completed your adventure project. Fighting  \n";
	cout<<"every urge to fall asleep you click on 'choose file' and select your\n";
	cout<<"project. You click submit, the screen flashes to its 'refresh' page,\n";
	cout<<"and you feverishly pick at the F5 key. The screen reappears over and\n";
	cout<<"again, each time making you more impatient to find the answer. Finally\n";
	cout<<"a new page, 'error found on line 2&%*(( 3*%#@#((4!))'. More confused \n";
	cout<<"than frustrated, you realize Athene has an issue with itself. Taking\n";
	cout<<"your backpack and plugging in your cross-computer-universe USB \n";
	cout<<"(or CCUUSB), you travel inside your computer to solve the problem \n";
	cout<<"yourself.\n";
	
	Player User("Room1"); //initialize our player by being in Room 1

	room1 Room1;
	//since room1 is inhereted from the location class, we can call "make_loc" from location class
	Room1.make_loc("Room1");
	NPC* room1npc = Room1.get_NPC();
	room1npc->set_response("Hello. Here is a key.");

	room2 Room2;
	Room2.make_loc("Room2");
	NPC* room2npc = Room2.get_NPC();
	room2npc->set_response("Hello. Here is a key.");

	room3 Room3;
	Room2.make_loc("Room3");
	NPC* room3npc = Room3.get_NPC();
	room3npc->set_response("Hello. Here is a key.");

	room4 Room4;
	Room4.make_loc("Room4");
	NPC* room4npc = Room4.get_NPC();
	room4npc->set_response("Congrats. You have won.");

	//string input;
	//cin >> input;

	//if(input == "talk")
		//cout<< "I talked";
 /*while(true) //*While true loop that will continue to ask for input from player until game is complete, will extend brackets when functional
	{
	
		cout<<"Enter command: "; //has a criteria of commands, for instance "verb" , "location" (move door one, talk to robot")
		getline(cin, ans);
		
		stringstream i(ans);		
		string arr[10];
		int index = 0;
		
		for(int index = 0; index < 10; index++)
		{
			i >> arr[index];
		}
		
		if(arr[0] == "Move" || arr[0] == "move")
		{
			break;
		}
			
		else if(arr[0] == "Talk" || arr[0] == "talk")
		{
			cout<<"hi";
			break;
		}
	
		else if(arr[0] == "Inventory" || arr[0] == "inventory")
		{
			break;
		}
		
		else if(arr[0] == "Use" || arr[0] == "use")
		{
			break;
		}
		break;
	}		



/*		
	Player User("Room1");
	Key* key_test = new Key("Room2");
	User.pickUpObject(key_test);
	NPC Computer("Room1");
	Computer.set_response("Hey.");
	//cout<< Computer.respond() << endl;

	room1 Room1;
	Room1.make_loc("Room1");
	NPC* room1npc = Room1.get_NPC();
	room1npc->set_response("Hey. I'm in Room 1.");
	//cout<< room1npc->respond() << endl;

	room2 Room2;
	Room2.make_loc("Room2");
	NPC* room2npc = Room2.get_NPC();
	room2npc->set_response("Hey. I'm in Room 2.");
	//cout<< room2npc->respond() << endl;
	
	room3 Room3;
	Room2.make_loc("Room3");
	NPC* room3npc = Room3.get_NPC();
	room3npc->set_response("Hey. I'm in Room 3.");
	//cout<< room3npc->respond() << endl;

	room4 Room4;
	Room4.make_loc("Room4");
	NPC* room4npc = Room4.get_NPC();
	room4npc->set_response("Hey. I'm in Room 4.");
	//cout<< room4npc->respond() << endl;
*/
	

}

