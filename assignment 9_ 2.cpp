#include<iostream>
using namespace std;

struct node{
	int data;
	node* next; 
}; 
//Tao danh sach nguoi choi 
node* danhsachnguoichoi(int n){
	node* head = new node;
	head->data=1;
	node* temp = head;
	for(int i=2; i<=n; i++){
		temp->next=new node;
		temp = temp->next;
		temp->data=i; 
	} 
	temp->next=head;
	return head; 
} 
//Giai thuat tim nguoi chien thang Josephus
int timkiem(int n, int m){ 
 	node* head = danhsachnguoichoi(n);
	node* prev = NULL;
	node* curr = head;
	//Kiem tra truong hop dac biet : m=1
	if(m==1){
		 while(curr->next!= curr){
		 	prev = curr;
			curr=curr->next;
			delete prev; 
		 } 
		 int nguoicuoicung = curr->data; 
	    delete curr;
	    return nguoicuoicung; 
	}
	while(curr->next!= curr){
		for(int i=1; i<m; i++){
			prev = curr;
			curr=curr->next; 
		} 
		prev->next= curr->next;
		node* temp = curr;
		curr=curr->next;
		delete temp; 
	} 
	int nguoicuoicung = curr->data;
	delete curr;
	return nguoicuoicung; 
 } 
 
 int main(){
 	int n,m;
	cout <<"Nhap lan luot n va m: ";
	cin >> n >> m;
	cout << "vi tri cua nguoi chien thang la: "<< timkiem(n,m);
	return 0; 
 } 



