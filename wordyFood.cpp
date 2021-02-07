/****************************************
	Program: wordyFood.cpp
	By: Jcodefox
	Created: 10/5/2019  6:13 PM
	Edited: 10/8/2019 5:09pm
	Food based word game.
****************************************/
#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 
#include <string>

using namespace std;

// Class to hold the visible name, noun, and adjective for a food
class food{
	private:
		string fName;
		string fNoun;
		string fAdj;
	public:
		food(string name,string noun,string adj){
			fName=name;
			fNoun=noun;
			fAdj=adj;
		}
		string getName(){
			return fName;
		}
		string getNoun(){
			return fNoun;
		}
		string getAdj(){
			return fAdj;
		}
};

// Class to hold orders from AIs and doubles as a
// class to hold orders the player tried to fill out
class order{
	private:
		int *list;
		int count;
	public:
		order(int limit){
			this->count=limit;
			this->list=new int[this->count];
		}
		~order(){
			delete[] this->list;
		}
		
		// Function to fill out the order with random numbers
		void randomOrder(int end){
			for(int i=0;i<this->count;i++){
				this->list[i]=rand()%end;
			}
		}
		
		// Function to return a value at a given location
		int getItem(int id){
			int result=-1;
			if(id<this->count && id>=0){
				result=this->list[id];
			}else{
				printf("Invalid number given to getOrder(int id) function!");
			}
			return result;
		}
		
		// Function to return the amount of values stored in an order
		int getCount(){
			return this->count;
		}
		
		// Function to fill out an order with user given values
		void playerFillOrder(int end){
			int num=-1;
			for(int i=0;i<this->count;i++){
				do{
					printf("Enter ingredient %d(as a number 0-%d): ", i,end-1);
					scanf(" %d",&num);
					if(num<0||num>=end){
						printf("Invalid ingredient! Please enter a value between 0 and %d\n",end-1);
						while ((getchar()) != '\n');
					}
				}while(num<0||num>=end);
				this->list[i]=num;
			}
		}
		
		void display(food **foods){
			for(int i=0,c=this->getCount();i<c;i++){
			if(i<c-2){
				printf("%s-",foods[this->getItem(i)]->getAdj().c_str());
			}else{
				if(i<c-1){
					printf("%s ",foods[this->getItem(i)]->getAdj().c_str());
				}else{
					printf("%s.\n",foods[this->getItem(i)]->getNoun().c_str());
				}
			}
			}
		}
		
		// Value to compare two different orders
		int compare(order *other){
			int result=0,thisSize,otherSize;
			thisSize=this->count;
			otherSize=other->getCount();
			if(otherSize>thisSize){
				for(int i=0;i<thisSize;i++){
					if(this->list[i]==other->getItem(i)){
						result++;
					}
				}
			}else{
				for(int i=0;i<otherSize;i++){
					if(this->list[i]==other->getItem(i)){
						result++;
					}
				}
			}
			return result;
		}
};

// Print so many spaces to align items
void spaceBuffer(int strSize,int buffer){
	for(;strSize<buffer;strSize++){
		printf(" ");
	}
}

//Function to display all foods in a list
void displayIng(food **foods,int maxFoods){
	string n;
	printf("------------------------------------------------\n");
	printf("Ingredient list:\n");
	for(int f=0;f<maxFoods;f++){
		n=foods[f]->getName();
		printf("  %2d. %s",f,n.c_str());
		if(f%4!=3){
			spaceBuffer(n.length(),12);
			printf("|");
		}else{
			printf("\n");
		}
	}
	printf("------------------------------------------------\n\n");
}

// Display menu options
int menuOptions(){
	int option=-1;
	printf("-------------------\n");
	printf(" 1 - Level Mode\n");
	printf(" 2 - Endless Mode\n");
	printf("===================\n");
	printf(" 0 - Quit\n");
	printf("-------------------\n");
	do{
		printf("Choose a number(0-2): ");
		scanf(" %d", &option);
		if(option<0||option>2){
			printf("Invalid ingredient! Please enter a value between 0 and 2\n");
			while ((getchar()) != '\n');
		}
	}while(option<0||option>2);
	printf("\n");
	return option;
}

int main(){
	// Gemeral constants
	const int MAXFOODS=32;
	const int ORDERSIZEMIN=2;
	const int ORDERSIZEMAX=8;
	
	// Level mode specific variables
	const int TURNSPERLEVEL=5;
	const int RECIPESPERLEVEL=4;
	
	// General variables
	food *foods[MAXFOODS];
	order *cOrder,*fillOut;
	int orderSize=0;
	
	// Program control variables
	int mode=-1;
	char running=' ';
	
	// Score variables
	int turnScore=0, score=0, multiplier=1;
	bool match=false;
	
	// Level mode specific variables
	int level=1;
	int turn=0;
	int recipes=4;
	
	srand(time(0)); 
	
	// Create all ingrediants
	// Level 1
	foods[0]=new food("Bun","Bun","Doughy");
	foods[1]=new food("Patty","Burger","Meaty");
	foods[2]=new food("Cheese","Cheese","Milky");
	foods[3]=new food("Bacon","Bacon","Crispy");
	// Level 2
	foods[4]=new food("Mustard","Mustard","Yellow");
	foods[5]=new food("Mayonaise","Mayo","Eggy");
	foods[6]=new food("Ketchup","Ketchup","Saucey");
	foods[7]=new food("Lettuce","Lettuce","Leafy");
	// Level 3
	foods[8]=new food("Tomato","Tomato","Red");
	foods[9]=new food("Egg","Egg","Yolky");
	foods[10]=new food("Pickle","Pickle","Dilly");
	foods[11]=new food("Chicken","Poultry","Flightless");
	// Level 4
	foods[12]=new food("Fries","Fries","French");
	foods[13]=new food("Pop","Pop","Fizzy");
	foods[14]=new food("HotSauce","HotSauce","Spicy");
	foods[15]=new food("PlasticFork","Fork","Plastic");
	
	// Level 5
	foods[16]=new food("Onion","Onion","Layered");
	foods[17]=new food("BBQSauce","BBQSauce","BBQ");
	foods[18]=new food("Salt","SodiumChloride","Salty");
	foods[19]=new food("Pepper","Pepper","Peppery");
	// Level 6
	foods[20]=new food("Guacamole","G.uacamole","Green");
	foods[21]=new food("Salsa","Salsa","Mild");
	foods[22]=new food("Avacado","Avacado","Fresh");
	foods[23]=new food("Fish","Fish","Marine");
	// Level 7
	foods[24]=new food("Ranch","Ranch","YeeHaw");
	foods[25]=new food("Water","Water","Wet");
	foods[26]=new food("HashBrown","HashBrown","Hashed");
	foods[27]=new food("Pancake","Pancake","Flat");
	// Level 8
	foods[28]=new food("GlazedDonut","Donut","Glazed");
	foods[29]=new food("IceCream","IceCream","Icy");
	foods[30]=new food("Chocolate","Chocolate","Rich");
	foods[31]=new food("Cherry","Cherry","Tart");
	do{
		mode = menuOptions();
		switch(mode){
			// Level mode
			case(1):{
				turnScore=0;
				score=0;
				multiplier=1;
				do{
					for(int i=0;i<TURNSPERLEVEL;i++){
						// Give ingrediants, score multiplier, and score.
						displayIng(foods,recipes);
						printf("Level: %d.%d\n", level, i+1);
						printf("Score Multiplier: %d\n",multiplier);
						printf("Score: %d\n\n",score);
						
						// Create the NPC's order
						orderSize=rand()%(ORDERSIZEMAX-ORDERSIZEMIN + 1) + ORDERSIZEMIN;
						cOrder=new order(orderSize);
						cOrder->randomOrder(recipes);
						
						// Display the NPC's order
						printf("I would like a:\n");
						cOrder->display(foods);
						
						// Ask user what the NPC ordered
						fillOut=new order(orderSize);
						printf("\nWhat did he order?\n");
						fillOut->playerFillOrder(recipes);
						
						turnScore=cOrder->compare(fillOut);
						match=turnScore==cOrder->getCount();
						
						// Tell the user how many multipliers were rewarded,
						// along with earned score.
						printf("\n");
						if(match){
							multiplier++;
							printf("+1 Multiplier!");
						}else{
							multiplier=1;
							printf("Multiplier lost!");
						}
						printf("\n+%d points!\n",turnScore*multiplier);
						score+=turnScore*multiplier;
						
						// Display the comparison
						printf("They%smatch:\n",(match)?" ":" do not ");
						printf("Yours:  ");
						fillOut->display(foods);
						printf("Theirs: ");
						cOrder->display(foods);
						// Cleanup ram
						delete fillOut;
						delete cOrder;
					}
					level++;
					if(recipes!=MAXFOODS){
						printf("Ingredients unlocked:\n");
						for(int f=recipes;f<recipes+RECIPESPERLEVEL && f!=MAXFOODS;f++){
							printf("  %d. %s\n",f,foods[f]->getName().c_str());
						}
					}
					recipes=(recipes+RECIPESPERLEVEL<MAXFOODS)?recipes+RECIPESPERLEVEL:MAXFOODS;
					// Ask the user if he would like to make another
					printf("\n");
					printf("Would you like to do another level?(Y/N): ");
					scanf(" %c",&running);
					printf("\n");
				}while(running!='N'&&running!='n');
				printf("\n");
				//Display final score
				printf("Final score: %d\n", score);
				break;
			}
			// Endless mode
			case(2):{
				turnScore=0;
				score=0;
				multiplier=1;
				do{
					// Give ingrediants, score multiplier, and score.
					displayIng(foods,MAXFOODS);
					printf("Score Multiplier: %d\n",multiplier);
					printf("Score: %d\n\n",score);
					
					// Create the NPC's order
					orderSize=rand()%(ORDERSIZEMAX-ORDERSIZEMIN + 1) + ORDERSIZEMIN;
					cOrder=new order(orderSize);
					cOrder->randomOrder(MAXFOODS);
					
					// Display the NPC's order
					printf("I would like a:\n");
					cOrder->display(foods);
					
					// Ask user what the NPC ordered
					fillOut=new order(orderSize);
					printf("\nWhat did he order?\n");
					fillOut->playerFillOrder(MAXFOODS);
					
					turnScore=cOrder->compare(fillOut);
					match=turnScore==cOrder->getCount();
					
					// Tell the user how many multipliers were rewarded,
					// along with earned score.
					printf("\n");
					if(match){
						multiplier++;
						printf("+1 Multiplier!");
					}else{
						multiplier=1;
						printf("Multiplier lost!");
					}
					printf("\n+%d points!\n",turnScore*multiplier);
					score+=turnScore*multiplier;
		
					// Display the comparison
					printf("They%smatch:\n",(match)?" ":" do not ");
					printf("Yours:  ");
					fillOut->display(foods);
					printf("Theirs: ");
					cOrder->display(foods);
		
					// Ask the user if he would like to make another
					printf("\n");
					printf("Make another?(Y/N): ");
					scanf(" %c",&running);
					printf("\n");
		
					// Cleanup ram
					delete fillOut;
					delete cOrder;
				}while(running!='N'&&running!='n');
				//Display final score
				printf("Final score: %d\n", score);
				break;
			}
		}
	}while(mode!=0);
	return 0;
}
