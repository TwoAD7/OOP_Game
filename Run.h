#include <iostream>

class Object{
private:
    int propertyValue; 
    
public:
    Object(int number): propertyValue(number) {}; // {propertyValue = number;}
    ~Object() {}
    
    int getPropertyValue() const;
    void setPropertyValue(const int propertyValue);
};


class Key: public Object{
private:
    string password;
public:
    Key(string back): Object(3), password(string(back)) {}; // { password = string(back);}
    ~Key() {}

    string getPassword() const {return password;}
    void setPassword(string new_pass) {password = new_pass;};
}; 

class Door : public Object{
private:
    string back;
    Key* required;
public: 
    Door(Key* _required, string _back)
    :Object(2), back(_back), required(_required) {}; //{back = _back; required = _required;}
    
    ~Door() {delete required;}

    string getback() const {return back;}
    void setback(string _back) {back = _back;}

    Key* getRequired() const {return required;} 
    void setRequired(Key* new_required) {required = new_required;}
    bool checkRequired(Key* attempt) const {return attempt == required;}

};

class Player {
  
private:
    string currentLocation;
    std::vector<Object*> *objects; //Player's objects 
    
public:
    //The colon is used as an initialization list 
    Player(string initialLocation) : currentLocation(initialLocation) /*, objects(new std::vector<Object*>) */{/*currentLocation = initialLocation;*/ this->objects = new vector<Object*>;} //constructor 
    virtual ~Player() {delete this->objects;}       //destructor. Use the "this" call because we are refering the actual object 
    
    void setCurrentLocation(string loc) {currentLocation = loc;}
    string getCurrentLocation() const{return currentLocation;}
    
    void pickUpObject(Object* obj);
    void dropObject(Object* obj);
    bool hasObject(Object* obj) const;
    void removeObject(Object* obj);
    vector<Object*> *getObjects() const;

    const std::string toString();

};

class NPC{
private:
    string currentLoc;
    std::vector<string> *responses;// = new std::vector<string>; //have multiple responses 
public:
    NPC(string initialLocation) {currentLoc = initialLocation; responses = new std::vector<string>;} //could use an initialization list here 
    ~NPC() {}

    string getCurrentLocation() const {return currentLoc;}
    void setCurrentLocation(string new_loc) {this->currentLoc = new_loc;}

    string respond(int i) const {return responses->at(i);}
    void set_response(string new_response) {responses->push_back(new_response);}
    //std::vector<string> *grab_responses() const {return responses;}
    //std::vector<string> *set_response(std::vector<string>* resp) {responses = resp; return responses;} //return the memory address of the vector containing strings 
    //void set_response(std::vector<string>* resp) {responses = resp;} //return the memory address of the vector containing strings
};

//We can use the factory method for the initializer 
//Need to include NPC, door objects, and keys for each room 
//base class for each location 
class location { 
  public:
    //virtual std::vector<std::string> *set_objects(Object* obj(int i, std::string w, std::string c)) =0; //set the objects for each room differently 
    //using static function because we want it to be initialized once and then not modified. Also, by making it static we are restricting it to only this class object 
    static location *make_loc(string name); //we could change the parameters to be int, or just single choice

};
 
//let the rooms inherit from the location class to use the "constructor"
class room1 : public location{
  private: 
    NPC* npcroom1;  //fix this to instantitate the NPC
    Door* Door1;
    Door* Door2;
    Door* Door3;
    std::vector<string> *resp_room1;
    //has a relationship is defined by 
    Key* key1;
    Key* key2;
    Key* key3;

    string surroundings;

  public:
    room1();
    ~room1(){delete Door1; delete Door2; delete Door3; delete npcroom1; delete key1; delete key2, delete key3;} //destructor for our object 
    std::string get_surroundings() { return surroundings;} 
    NPC* get_NPC() {return npcroom1;}
    string first = "> Welcome to the internals of Athene! Here is where all code, good and bad, comes to be tested, and it\n> looks like your code didn't make the cut. Luckily, we have an extra piece around here that you can use\n> to fix the problem, take a look around and see if you can find it. Here's a key to the first room, maybe\n> try looking in there?\n";
    //One of these responses needs to say "here is key" and then give the player a key
    string second="> Keep up the good work!"; //the second string 
    string third =""; //third string 
    string ifwrong=""; //if the user gets this wrong

    //pointer to vector containing strings 
    std::vector<string>* fill_responses(){

        std::vector<string> *a = new std::vector<string>;

        a->push_back(first);
        a->push_back(second);
        a->push_back(third);
        a->push_back(ifwrong);
        return a;
    }

    string respond(int i){return (resp_room1->at(i));}

    Door* get_Door1() {return Door1;}
    Door* get_Door2() {return Door2;}
    Door* get_Door3() {return Door3;}
};

class room2: public location {
  private: 
    NPC *npcroom2; 
    std::string surroundings;
    std::vector<string> *resp_room2;
  public:
    room2();
    ~room2(){}
    std::string get_surroundings() {return surroundings;}
    NPC* get_NPC() {return npcroom2;}
    string first = "> I am the riddle master! If you want the missing pieces of your code, you must answer me these riddles!\n";
    string second="> Riddle the first: who teaches OOP?";
    string third ="> Not bad, now here is a harder one: which was the worst programming assignment in OOP?";
    string ifwrong="> Fool! that is not the correct answer. Please try again.\n";
    string ifwin="> You truly are talented enough to PERHAPS get your assignment back.\nHere's the key to the next room, which may or may not contain what you are looking for.\n";
	string onward="> With the key in your hands, you feel the next door may be the best place to go.\n";
	string again="> Back for more questions? Too bad, you already emptied my question bank.\n";

    std::vector<string>* fill_responses(){

    std::vector<string> *a = new std::vector<string>;
    a->push_back(first);
    a->push_back(second);
    a->push_back(third);
    a->push_back(ifwrong);
    a->push_back(ifwin);
    a->push_back(onward);
    a->push_back(again);
    return a;
    }
};

class room3: public location {
  private: 
    std::string surroundings;
    NPC *npcroom3;
    std::vector<string> *resp_room3;
  public:
    room3();
    ~room3(){}
    std::string get_surroundings() {return surroundings;}
    NPC* get_NPC() {return npcroom3;}
    string first = "> Hello there, normally I would be happy to help, but I am in a bit of a jam. Could you please help me out?\n";
    string second="Enter a command: (Push free, Use object)";
    string third ="> You try to push the roomba free, but it is jammed good.\n";
    string ifobject ="> You only have the key, but it looks tough enough to pry the robot out.\n(Key)";
    string ifuseobject ="> You used the key as a crowbar to pry the roomba out. Just as the key snaps in half, the roomba rolls free.\n";
    string ifwin="> You freed me! Thank you! In return for your services, take this brand new key! I also have a picture on\n this piece of paper, it looks like an important person\n";
    string onward="> You look at the piece of paper and key, the last two tools you hope you will need to find what you are looking for.\n";
    string again="> Got a lot of fixing to do in here, all kinds of mishaps to stich together. Thank you for helping me however!\n";

    std::vector<string>* fill_responses(){

    std::vector<string> *a = new std::vector<string>;
    a->push_back(first);
    a->push_back(second);
    a->push_back(third);
    a->push_back(ifobject);
    a->push_back(ifuseobject);
    a->push_back(ifwin);
    a->push_back(onward);
    a->push_back(again);
    return a;
    }
};

class room4: public location {
  private: 
    NPC *npcroom4;
    std::string surroundings;
    std::vector<string> *resp_room4;

  public:
    room4();
    ~room4(){}

    std::string get_surroundings() {return surroundings;}
    NPC* get_NPC() {return npcroom4;}
    string first = "> Request for piece denied. Facial recognition required.";
    string second="> Facial Recognition confirmed. Distributing piece now.";
    string third ="> Capacity of objects has been depleted, please return in 24 hours.";
	string paper ="Enter a command: (Show Paper)";
	
	string face = "%((((*****/*(/#/,.,.   ..,.,*,,.*,***** ** .#***###%##%#%%%%%%%%%%##############%%&%&&@@@\n/#* .,**,,/**/*/.*,,,**/,*/,/**,.. ,. ,#/.,..*/./*%%#%%%%%%%%%###%###########%%%%@@&@@@@@\n....,*(&*/.,*.,,,,*/(/*(*//(/(*,//,/**/.,(/.,.....*,#%%%%%%&&@###%#%#%####%%%%&@@@&@@@@@@\n(*/#*(((#*,,**//*///((##((((/,**/((#(((/**//*,,/*/(%%#%(#&&&&@%%#%%%%#%###&&&&&@@@@@@@@@@\n((#/#*/(,,*/(/((//(#(##((((#(((##(((*///.***/***,./#%%&&&&&(&%#%%&&&&&%&@@@@@@@@@@@@@@@@@\n#%%#(#(((//*(/(//(((((((##(((/(((/(/(#(##(((((*/((**(@%@((((#%%%&%%%&@@@@@@@@@@@@@@@@@@@@\n%#&&%%%/((#%###((((((/(((((//*///(((((((((*((#((#((/.((##%%%%&&%%@@@@@@@@@@@@@@@@@@@@@@@@\n%%%%%%%%#%%####(((////(/((/(//////(///(////(///(/*(((*#/@@&&&&@@@@@@@@@@@@@@@@@@@@@@@@@&*\n%%&%#%%%%%%%((##(/((/////////////(///(////(((((((#(##//@&&&@@@@@@@@@@@@@@@@@@@@@@@@&&&&%/\n%%%%%%%%#%##((#(((((///(/////**/*//**/////(#((####((((/#%&%@@@@@@@@@@@@@@@@@@@@&&&&&&&&&*\n%%%&&%%&%###(#(#(#(//(//////******/**/////(/(((###((#/#/*(%@@@@@@@@@@@@@@@@@@&&&@&&&&%&@&\n%&&%&%%%%#((((((##((/(//**/***,*,*,,,**//*(/(/(#%##((((((%%@@@@@@@@@@@@@@@@@@@@@@&&&&&&@&\n&&&%%%%%##(((/###((///**/**,,,.,,.,,,*,***/*//(#%##(######%@@@@@@@@@@@@@@@@@#%&@@@&&&&&@&\n&&&%%%%###((((#(//*****,,,,,.............,,,,,*(#%#(##%((%%@@@@@@@@@@@@@@@&@&@@@@@&&&&&@@\n&%&%%%#(#(((((//***,,,.,,,,,,,,...............,,(%(%#((((/%&@@@@@@@@@@@@@@&&@@@@@@&&&&&@@\n&&%&%#(((((((((((((((/(/((#(/***,,,,.,..........,//%%((##%%@@@@@@@@@@@@@@%@&@%&@@@&&&&&&&\n%#&%#(///(((######(#(#######%#(/*********,......,*%%%((#%&%@@@@@@@@@@@@&&&@&@#@&@@&&&&&&&\n%%(////((#(#(((#%((/(##%####((/****/((((((////(/#%#((%&@%@@@@@@@@@@@@&&&&&&%%&@@&&&&&&&\n%&%(/////((((##%%%(&&@%#(#(###(/*,.,*((((((((//*/(%##%(@@@#&@@@@@@@@@@@&@@@&@&%%@@&&&&&&&\n&%%(///////(((###(/(&%%**/((((//*...*((#&%(&((/**/&&%%%@@@#&&@@@@@@@@@@@@&&&%@@@&&&&&&&\n&&%(//////*///(/(//////******//*,,..,/((%##%*##(**/&%&&@@@%%@@@@@@@@@@@@&%%@(@@@@@&&&&&&%\n&%#((//////***//***////****/*///*,,.,,,**/***///*,,#%%%&@@%#@@@@@&@@@@@@@@@@@@@&&%%%&@@&&\n&%##((///***************,*//////*,..,,,,,****,,,,,,%%%%@@@&&@@@@@@@@@@@&&&&&&&%&&%&\n##%#(((//****,**,,,*,,****//////*,..,,,.,..,,,,,,,*#&&&@#%%#&&@@&@@@@@@@&&&&&&&&%&%&(%&\n((##(((//****,,,,,,,,,,,**//////*,..,,,,........,,/#&&&@&@@#&&@@&&&@@@&&&/*@&&&&&&%#&&&\n((#(((//*****,,,,,.....,,*/(((//*,...,*.......,,,,&&@@@@@@@#&&@@@&&&&&(%(/*@&&&&&&&&%(&%#\n*##((((///******,,,,..,,,/(/////**...,,.......,..,@@@@@@@@@#&&@@%&&&@@#*/@&&&%@&&&/%#\n*(#((#(((/*/*/**,,,,,,,,*(//////**,..,,,,,....,,.,@@@%%%%###&&@@&(@&&&%%%*#@@&@&&&//(\n#%#((((((/////***,,,,,***((((((/**.,,.**,,,....,,,@@@%%%%%%#&&@@&(//&&&(*%%@@@@########&@\n%%##((((((((//**********/#%&%%%#(***/**..,.....,,*@@@%######&&@@%%&&###%#&@@@@@@@@@@@@@\n%%###((((((//****/(////((#%#%#%%###(#(/*,,,,,,,,,**//(#////#&%&@@@@@@@@@@@@@@@@@@@@@@@@@@\n%(%#((((((//***(((((##(%#%%(########(**//*,.,,*%&/////*(&&@@@@@@@@@@@@@@@@@@@@@@@&@@@\n(&@@###((((((/*,*/#(#%#%##%%%#((/((/#(#(((//,.,*/#%/#,*/*,*(%&&&@%@#%&@@@@@@@@@@@&&@@@@@@\n&&@%######((((/**(########%%#(((((/*//((###/*,,*#%((#,*****##&&&%###%//%%@@@@&&%%%%&%&@@&\n&&/%###%###((((///#(/**///////**,**,**,.,*(/***%*/,*/,,*,,*,,.,&%%*,*,,/(#%@%%/#&&&&&%@%@\n*(########((((((#((/**////**//**//*,,,.//(//,*/%,***,**/***,,,@@@&&&&&&%(/,((/((##(((##\n((#(#########(((((%#(((//((((((#(/(//(*,**/#**,*/%*,*,,,,,/,.*,,,,@@@@@@@@@@@@@@@@@@@@@@@\n///(#######%##((#%%%###((((((/(((/(((/*/(((*/(*//%**,,,*,*#,,**,,,.,*@@@@@@@@@@@@@@@@@@@@\n*/.##############%%%####((((/(((((//**/((###(/***#/,*///**%/*,*,,,,,,,.@@@@@@@@@@@@@@@@@@\n//,(##(((#######%%%%&%%%(##(##((/(/((#((%%%##/**/(#*///(//%(****,**,,,,,.&&@@@@@&&&&@@@@@\n/**,#(((((#(######&&&%%#%#######(##%##(%%%((#/*/#,/*////#*#%/*,**//,/,,**,.@@@@@@@@@@@@@@\n&.*,/((((((((#####%%&%&%%%#%%%###%%##%%&%%((#/*/((#/(//#%*(%#///////*,*/,**,@@@@@@@@@@@@@\n%.,,,/((((((((((((#%&&&%&%&%%%%%&%%(%#(#/((/*/(((#%/((%((##//*((//*///,*/,/,(&&&&&&&&&&\n%..,,,(/((((((((((((((###%%%%(%#(%#/.(##//(/*/(##(////%#*#%(/*/(/(*(*/*/,/**,*&&&&&&&&&";
	
    
    std::vector<string>* fill_responses(){

    std::vector<string> *a = new std::vector<string>;
    a->push_back(first);
    a->push_back(second);
    a->push_back(third);
    a->push_back(face);
    a->push_back(paper);
    return a;
    }
};
