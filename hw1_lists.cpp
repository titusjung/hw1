#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct Item {
  Item(int v, Item* n) { val = v; next = n; }
  int val;
  Item* next;
};

Item* concatenate(Item* head1, Item* head2);  // returns head pointer to new list
void removeEvens(Item*& head);
double findAverage(Item* head);
void readLists(char* filetarg, Item*& head1, Item*& head2);
void print_all(Item*& start);
double averagehelper(Item* head, int sum, int n); //helper function for average
void removeEvenshelper(Item*& head); //helper function for evenshelper
void cleanup(Item* head); //deletes lists
void printList(ostream& ofile, Item* head); 


int main(int argc, char* argv[])
{
	Item* head1, *head2, *head3;
	readLists(argv[1], head1, head2);
	ofstream out_file(argv[2]);

	head3= concatenate(head1, head2);
	printList(out_file,head1);
	printList(out_file,head2);
	printList(out_file,head3);
	removeEvens(head3);

	printList(out_file,head3);
	double x = findAverage(head3);
	out_file<<endl<<x;
	out_file.close();

	cleanup(head1);

	cleanup(head2);
	cleanup(head3);

	return 0;
}

void readLists(char* filetarg, Item*& head1, Item*& head2)
{
	//stores lines into string streams and places integers into vectors
	// puts the integers in vectors into lists
	ifstream infile(filetarg);
	string list1, list2;
	getline(infile, list1); getline(infile,list2);
	istringstream line; istringstream line2;
	line.str(list1); line2.str(list2);
	int val=0;
	vector<int> storage, storage2;
	while(!line.fail()){
		line>>val;
		if(line.fail())break;
		storage.push_back(val);
	}
	while(!line2.fail()){
		line2>>val;
		if(line2.fail())break;
		storage2.push_back(val);
	}
	head1 = new Item(storage[0], NULL);
	Item* tempitem = head1;
	for(unsigned int i=1; i<storage.size(); i++){
		tempitem->next = new Item(storage[i], NULL);
		tempitem = tempitem->next;
	}
	head2 = new Item(storage2[0], NULL);
 	tempitem = head2;
	for(unsigned int i=1; i<storage2.size(); i++){
		tempitem->next = new Item(storage2[i], NULL);
		tempitem = tempitem->next;
	}
	infile.close();

}

void print_all(Item*& start){
	Item* tempitem = start;
	while(tempitem!= NULL){
		cout<<tempitem->val<<" ";
		tempitem= tempitem->next;
	}
	cout<<endl;

	return;
}

Item* concatenate(Item* head1, Item* head2)
{
	Item* tempitem = new Item(head1->val, head1->next);
	if(tempitem->next == NULL && head2 == NULL){
		return tempitem;	 
	}
	else if( tempitem->next == NULL && head2!= NULL){
		tempitem->next = concatenate(head2,NULL );
		return tempitem;
	}
	else{
		tempitem->next = concatenate(tempitem->next,  head2);
		return tempitem;
	}
}
void removeEvens(Item*& head)
{
	if(head ==NULL) return;
	if((head->val)%2==0 && head != NULL){

		Item* oldhead = head;
		Item* newhead = head->next;
		delete oldhead;
		head = newhead;
		removeEvens(head);
	}
	else{
		removeEvenshelper(head);
	}
	return;
}

void removeEvenshelper(Item*& head){
	if( head->next ==NULL){ 
		return;
	}
	else{
		Item* nextitem= head->next;	// 
		if((nextitem->val)%2 ==0){
			Item* newnext= nextitem->next;// do delete stuff heere
			delete nextitem;
			head->next = newnext; 
			removeEvenshelper(head);
		}
		else{

			removeEvenshelper(head->next);
		}
		return;
	}
}
double findAverage(Item* head)
{
	if( head == NULL) return 0;
	return averagehelper(head, 0 , 0);
}

double averagehelper(Item* head, int sum, int n){
	if(head== NULL){
		
		return (double)sum/(n);
	}
	else{
		sum+=head->val;


		return averagehelper(head->next,sum,++n);
	}

}

void cleanup(Item* head){
	if( head == NULL) return;
	Item* temp = head->next; 
	Item* oldtemp, *newtemp;
	while(temp!=NULL){
		oldtemp = temp;
		newtemp = temp->next;
		delete temp;
		temp = newtemp;
	}
	delete head;
	return;
}

void printList(ostream& ofile, Item* head)
{
  if(head == NULL)
    ofile << std::endl;
  else {
    ofile << head->val << " ";
    printList(ofile, head->next);    
  }
}