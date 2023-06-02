#include<iostream>

class Book {
	char name[100];
	int date;
	bool state;
public:
	Book(char n[100], int d, bool st);	//constructor
	Book();								//defualt constructor
	//private-access function
	void show()const {std::cout << name << " " << date << " " << state << std::endl;};
	int getdate()const { return date; };
	char* getname() { return name; };
	//borrow this book
	bool borrow()const;			
};

Book::Book(char n[100], int d, bool st) {	
	//copy the string
	int i;
	for (i = 0; n[i] != '\0'; i++)
		name[i] = n[i];
	name[i] = '\0';
	date = d;
	state = st;
}

Book::Book() {
	date = 0;
	state = 0;
}

bool Book::borrow()const {
	//return value is the end condition of while-loop
	if (state) {
		std::cout << "Succeed!\n";
		return 1;
	}
	else {
		std::cout << "Sorry, the book is not available. Try again:\n";
		return 0;
	}
}

class Subject {
	int count=0;
	Book list[100];
public:
	void add(const Book& b);	//add a book to the subject
	void show()const;			//show all the book of the subject
	void sort();				//sort the book of the subject
};

void Subject::add(const Book& b) {
	list[count++] = b;
}

void Subject::show()const {
	for (int i = 0; i < count; i++) 
		list[i].show();
}

void Subject::sort() {
	for (int i = 0; i < count - 1; i++) {
		for (int j = count - 1; j > i; j--) {
			if (list[j].getdate() > list[j - 1].getdate()) {
				Book temp = list[j];
				list[j] = list[j - 1];
				list[j - 1] = temp;
			}
		}
	}
}

class Library {
	char name[100];
	//has-a relationship, can also use private inherance
	Subject Art;
	Subject Science;
	Subject History;

	Book* all;			//use dynamic array "all" to record all the book
	int count = 0;		//count is the size of "all" array
public:
	Library(const Subject& A, const Subject& B, const Subject& C,int len);//constructor
	Library();//defualt constructors
	~Library();//destructor to delete the dynamic array
	void getbook(const Book& b, char* sub);//store a book into the library
	void lendbook();//lend service
	void show();	//show all the book in the library
};

Library::Library(const Subject& A, const Subject& B, const Subject& C,int len) {
	Art = A;
	Science = B;
	History = C;
	all = new Book[len];		//initialize the dynamic array
}

Library::Library() {
	all = new Book[1];//for the delete in the destructor
}

Library::~Library() {
	delete[]all;
	all = nullptr;
}

void Library::getbook(const Book& b,char* sub){
	all[count++] = b;
	switch (*sub) {
	case 'A':
		Art.add(b);
		break;
	case 'S':
		Science.add(b);
		break;
	case'H':
		History.add(b);
		break;
	}

}

void Library::show() {
	Art.sort();
	Science.sort();
	History.sort();
	std::cout << "Books in the library:\n";
	std::cout << "Art:\n";
	Art.show();
	std::cout << "Science:\n";
	Science.show();
	std::cout << "History:\n";
	History.show();
}

void Library::lendbook() {
	std::cout << "Input the name of the book you want to borrow:\n";
	int i;
	//use do while to exit the program only success
	do {
		char n[100];
		std::cin >> n;
		int j;
		//use for-loop to check the book in the library
		for (i = 0; i < count; i++) {
			int isok = 1;
			for (j = 0; *(all[i].getname() + j) != '\0'; j++) {
				if (*(all[i].getname() + j) != n[j]) {
					isok = 0;
					break;
				}
			}
			if (isok)
				break;
		}
	} while (!all[i].borrow());

}

int main() {
	using namespace std;
	int len;
	cout << "Input the number of books:\n";
	cin >> len;
	cout << "Input the information of books (name, date, state, subject):\n";
	Subject A, S, H;
	Library lib(A,S,H,len);
	for (int i = 0; i < len; i++) {
		char name[100];
		int d;
		bool s;
		char sub[100];
		cin >> name >> d >> s >> sub;
		Book b(name, d, s);
		lib.getbook(b, sub);
	}
	lib.show();
	lib.lendbook();
	return 0;
}