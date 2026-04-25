#include<iostream>
#include<fstream>
using namespace std;
class Date;
class Comment;
class Post;
class User;
class Page;
class Object;
class Memory;
class Functions
{
public:
	static int strlength(const char* str)
	{
		int i = 0;
		while (str[i] != '\0')
		{
			i++;
		}
		return i;
	}
	static bool FindSubString(const char* myStr, const char* strToFind)
	{
		int length1 = strlen(myStr);
		int length2 = strlen(strToFind);
		int check = 0, count = 0;
		for (int i = 0; i < length1; i++)
		{
			if (myStr[i] == strToFind[0])
			{
				for (int j = 0, k = i; j < length2; j++, k++)
				{
					if (strToFind[j] == myStr[k])
					{
						check = 1;
						count++;
					}
					else
					{
						check = 0;
						break;
					}
				}
				if (check == 1 && count == length2)
				{
					return 1;
				}
			}
		}
		return 0;
	}
	static void strcopy(char*& str1, const char*& str2)
	{
		int i = 0;
		while (str2[i] != '\0')
		{
			str1[i] = str2[i];
			i++;
		}
		str1[i] = '\0';
	}
	static char* GetStringFromBuffer(const char* str)
	{
		int size_of_string = strlength(str);
		char* string = new char[size_of_string + 1];    // +1 for null character
		strcopy(string, str);
		return string;
	}
};
class Object
{
protected:
	Post** Timeline;//so child classes can access
private:
	char* ID;
public:
	Object();
	~Object();
	virtual void Print();
	virtual void print_name();
	void AddPosttoTimeline(Post*);
};
Object::Object()
{
	Timeline = new Post * [11];
	for (int i = 0; i < 11; i++)
	{
		Timeline[i] = nullptr;
	}
	ID = nullptr;
}
Object::~Object()
{
	cout << "Object deleted" << endl;
	if(ID!=nullptr)
		delete[]ID;
	//Posts have been deleted in User and page classes 
}
void Object::print_name()
{
	//just to call child classes
	//cout << "Object print name Called" << endl;
}
void Object::Print()
{
}
void Object::AddPosttoTimeline(Post* New_post)
{
	if (New_post != nullptr)
	{
		for (int i = 0; i < 11; i++)
		{
			if (Timeline[i] == nullptr)
			{
				Timeline[i] = New_post;
				break;
			}
		}
	}
}
class Comment
{
	char* ID;
	char* text;
	Object* CommentBy;
public:
	Comment();
	~Comment();
	void Print();
	void SetValues(char*, const char*, Object*);
};
Comment::Comment()
{
	ID = nullptr;
	text = nullptr;
	CommentBy = nullptr;
}
Comment::~Comment()
{
	cout << "Comment Destructor callled" << endl;
	if (ID != nullptr)
	{
		delete[]ID;
		ID = nullptr;
	}
	if (text != nullptr)
	{
		delete[]text;
		text = nullptr;
	}
	if (CommentBy != nullptr)
	{
		CommentBy = nullptr;

	}
}
void Comment::SetValues(char* id, const char* TEXT, Object* Commentby)//made this constant to cater for adding comment in Controller
{

	ID = id;
	text = Functions::GetStringFromBuffer(TEXT);
	CommentBy = Commentby;
}
void Comment::Print()
{
	cout << "\t\t";
	CommentBy->print_name();
	cout << ": " << text << endl;
}
class Date
{
private:
	int Day;
	int Month;
	int Year;
public:
	Date();
	Date(int, int, int);
	~Date();
	void print();
	void SetDay(int);
	void SetMonth(int);
	void SetYear(int);
	int CompareForHome(Date);
	int CompareForMemory(Date);
	static Date CurrentDate;
	static void SetCurrentDate(int, int, int);
	static Date GetCurrentDate();

};
Date::Date()
{
	Day = 0;
	Year = 0;
	Month = 0;
}
Date::Date(int D, int M, int Y)//overloaded constructor for date
{
	Day = D;
	Month = M;
	Year = Y;
}
Date::~Date()
{
}
void Date::SetDay(int D)
{
	Day = D;
}
void Date::SetMonth(int D)
{
	Month = D;
}
void Date::SetYear(int D)
{
	Year = D;
}
void Date::SetCurrentDate(int D, int M, int Y)
{
	CurrentDate.Day = D;
	CurrentDate.Month = M;
	CurrentDate.Year = Y;
}
void Date::print()
{
	cout << "(" << Day << "/" << Month << "/" << Year << ")" << endl;
}
int Date::CompareForHome(Date CD)//CD is current Date//this function checks for viewhome/timeline and returns difference of days
{
	int Difference = CD.Day - Day;
	if ((Difference <= 2) && (CD.Month == Month) && (CD.Year == Year))
	{
		return Difference;
	}
	else
		return 500;
}
int Date::CompareForMemory(Date CD)//this functions checks if a memory exists and return year difference if it does exist
{
	if (CD.Day == Day && CD.Month == Month)
	{
		return CD.Year - Year;
	}
	else 
		return 0;
}
Date Date::GetCurrentDate()
{
	return CurrentDate;
}
Date Date::CurrentDate = Date(0,0,0);
class Activity
{
	char* text;
	int Type;
public:
	Activity();
	~Activity();
	void Print();
	void SetValues(int,char*);
};
Activity::Activity()
{
	text = nullptr;
	Type = 0;
}
Activity::~Activity()
{
	cout << "Activity Destructor called" << endl;
	if (text != nullptr)
		delete[]text;
}
void Activity::Print()
{
	if (Type == 1)
		cout << " is Feeling" << text<<" ";
	else if (Type == 2)
		cout << " is Thinking about" << text<<" ";
	else if (Type == 3)
		cout << " is Making" << text<<" ";
	else
		cout << " is Celebrating" << text<<" ";
}
void Activity::SetValues(int type, char* content)
{
	Type = type;
	text = content;
}
class Post
{
	Activity* PostContent;
	char* ID;
	char* text;
	Date shared_date;
	Object* SharedBy;
	Object** LikedBy;
	Comment** Comments;
public:
	Post();
	Post(const char*, const char*, Object*);
	virtual ~Post();
	void SetSharedBy(Object*);
	void Addlike(Object*);
	virtual void PrintPost();
	void ReadDatafromfile(ifstream& fin);
	void PrintLikedBy();
	void AddComment(Comment*);
	void AddActivity(Activity*);
	char* GetPostID();
	Date GetSharedDate();
	void PrintLatest();
	Object* GetSharedBy();
	char* GetText();
};
Post::Post()
{
	ID = nullptr;
	text = nullptr;
	SharedBy = nullptr;
	PostContent = nullptr;
	LikedBy = new Object * [11];
	for (int i = 0; i < 11; i++)
	{
		LikedBy[i] = nullptr;
	}
	Comments = new Comment * [11];
	for (int i = 0; i< 11; i++)
	{
		Comments[i] = nullptr;
	}
}
Post::Post(const char* id, const char* Text, Object* Sharedby)
{
	ID = Functions::GetStringFromBuffer(id);
	text = Functions::GetStringFromBuffer(Text);
	SharedBy = Sharedby;
	LikedBy = nullptr;
	Comments = nullptr;
}
void Post::AddComment(Comment* new_comment)
{
	for (int i = 0; i < 11; i++)
	{
		if (Comments[i] == nullptr)
		{
			Comments[i] =new_comment;
			break;
		}
	}
}
void Post::AddActivity(Activity* Content)
{
	if (PostContent == nullptr)
	{
		PostContent = Content;
	}
}
Post::~Post()
{
	cout <<"Post Destructor called" << endl;
	if (ID != nullptr)
	{
		delete[]ID;
		ID = nullptr;
	}
	if (text != nullptr)
	{
		delete[]text;
		text = nullptr;
	}
	if (PostContent != nullptr)
	{
		delete PostContent;
		PostContent = nullptr;
	}
	for (int i = 0; i < 11; i++)
	{
		if (Comments != nullptr)
		{
			if (Comments[i] != nullptr)
			{
				delete Comments[i];
			}
		}
	}
	delete[]Comments;
	delete[]LikedBy;
}
char* Post::GetPostID()
{
	return ID;
}
Date Post::GetSharedDate()
{
	return shared_date;
}
Object* Post::GetSharedBy()
{
	return SharedBy;
}
char* Post::GetText()
{
	return text;
}
void Post::SetSharedBy(Object* Obj)
{
	SharedBy = Obj;
}
void Post::Addlike(Object* Obj)
{
	for (int i = 0; i < 11; i++)
	{
		if (LikedBy[i] == nullptr)
		{
			LikedBy[i] = Obj;
			break;
		}
	}
}
void Post::PrintPost()
{
	int Difference= shared_date.CompareForHome(Date::GetCurrentDate());
	if (Difference == 0)
	{
		SharedBy->print_name();
		if (PostContent != nullptr)
		{
			PostContent->Print();
		}
		
		cout << "(1h):" << endl<< text << ":" << endl;
		int i = 0;
		while (Comments[i] != nullptr)
		{
			Comments[i]->Print();
			i++;
		}
		cout << endl << endl;
	}
	else
	{
		SharedBy->print_name();
		if (PostContent != nullptr)
		{
			PostContent->Print();
		}
		shared_date.print();
		cout << text << ":" << endl;
		int i = 0;
		while (Comments[i] != nullptr)
		{
			Comments[i]->Print();
			i++;
		}
		cout << endl << endl;
	}
}
void Post::PrintLikedBy()
{
	cout << "Post Liked by:" << endl;
	int i = 0;
	while (LikedBy[i] != nullptr)
	{
		LikedBy[i]->Print();
		i++;
	}
}
void Post::PrintLatest()
{
	int Difference = shared_date.CompareForHome(Date::GetCurrentDate());
	if (Difference <= 2 && Difference >= 1)
	{
		SharedBy->print_name();
		if (PostContent != nullptr)
		{
			PostContent->Print();
		}
		cout << "(" << Difference << "d):" << endl;
		cout <<text << ":" << endl;
		int i = 0;
		while (Comments[i] != nullptr)
		{
			Comments[i]->Print();
			i++;
		}
		cout << endl << endl;
	}
	else if (Difference == 0)
	{
		SharedBy->print_name();
		if (PostContent != nullptr)
		{
			PostContent->Print();
		}
		cout << "(1h):" << endl;
		cout << text << ":" << endl;
		int i = 0;
		while (Comments[i] != nullptr)
		{
			Comments[i]->Print();
			i++;
		}
		cout << endl << endl;
	}
}
void Post::ReadDatafromfile(ifstream& fin)
{
	char* temp = new char[150];
	int* temp1 = new int;
	fin >> temp;
	ID = Functions::GetStringFromBuffer(temp);
	fin >> *temp1;
	shared_date.SetDay(*temp1);
	fin >> *temp1;
	shared_date.SetMonth(*temp1);
	fin >> *temp1;
	shared_date.SetYear(*temp1);
	delete temp1;
	fin.getline(temp, 10);
	//one extra because it was reading space and had to ignore a line 
	fin.getline(temp, 150);
	text = Functions::GetStringFromBuffer(temp);
	delete[]temp;
}
////////////////////
class Memory:public Post
{
	Post* OriginalPost;
public:
	Memory(Post* ,const char*,const char*,Object*);
	~Memory();
	void PrintPost();
};
Memory::Memory(Post* O_post, const char* ID, const char* text, Object* SharedBy):Post(ID,text,SharedBy)
{
	OriginalPost = O_post;
}
Memory::~Memory()
{
	cout << "Memory destructor called" << endl;
}
void Memory::PrintPost()
{
	Post::GetSharedBy()->print_name();
	cout << " shared a memory(1h)" << endl;
	cout << Post::GetText() << endl;
	cout <<"~~~"<< OriginalPost->GetSharedDate().CompareForMemory(Date::GetCurrentDate()) << " years ago~~~" << endl;//gets the date of the original post 
	OriginalPost->PrintPost();
}
//Page
class Page:public Object
{
	char* ID;
	char* Title;
public:
	Page();
	~Page();
	void ReadDataFromFile(ifstream& fin);
	void Print();
	char* Get_Page_ID();
	void print_name();
	void View_Page();
	void View_Recent();
};
Page::Page()
{
	ID = nullptr;
	Title = nullptr;
}
Page::~Page()
{
	cout << "\n\nDestructor called for " << ID << endl;
	delete[]ID;
	delete[]Title;
	//deleting posts here
	for (int i = 0; i < 11; i++)
	{
		if (Timeline[i] != nullptr) // checking if the pointer is not null
		{
			delete Timeline[i]; 
			//Timeline[i] = nullptr; 
		}
	}
	delete[]Timeline;
	Timeline = nullptr;
}
void Page::print_name()
{
	cout << Title;
}
void Page::ReadDataFromFile(ifstream& fin)
{
	char* temp = new char[100];
	fin >> temp;
	ID = Functions::GetStringFromBuffer(temp);
	fin.getline(temp,100);
	Title = Functions::GetStringFromBuffer(temp);
	delete[]temp;
	temp = nullptr;
}
void Page::View_Page()
{
	cout << Title << endl;
	int i = 0;
	while (Timeline[i] != nullptr)
	{
		Timeline[i]->PrintPost();
		i++;
	}
}
void Page::View_Recent()
{
	int i = 0;
	while (Timeline[i] != nullptr)
	{
		Timeline[i]->PrintLatest();
		i++;
	}
}
void Page::Print()
{
	cout << ID << "-" << Title << endl;
}
char* Page::Get_Page_ID()
{
	return ID;
}
//User
class User:public Object
{
	char* ID;
	char* Fname;
	char* Lname;
	//int no_of_friends;
	User** FriendList;//null or 10 pointers max
	Page** LikedPages;//null or 10 pointers max
	public:
	User();
	~User();
	void Print();
	void AddFriend(User*&);
	void ReadDataFromFile(ifstream&fin);
    void LikePage(Page*&);
	void ViewFriendList(); //As you displayed students of a society
	void ViewLikedPages();// iterate through pointers, call list view
	char* Get_User_ID();
	void print_name();
	void PrintTimeline();
	void ViewHome();
	void ViewMemory();
	void Sharememory(const char*, const char*, Object*);
	/*int Get_no_of_friends();
	void Set_no_of_friends();*/
};
User::User()
{
	//no_of_friends = 0;
	ID = nullptr;
	Fname = nullptr;
	Lname = nullptr;
	FriendList = new User*[11];//one extra for NUll
	for (int i = 0; i < 11; i++)
	{
		FriendList[i] = nullptr;
	}
	LikedPages = new Page * [11];//one extra for NUll
	for (int i = 0; i < 11; i++)
	{
		LikedPages[i] = nullptr;
	}
}
User::~User()
{
	cout << "\n\nDestructor called for " << ID << endl;
	if (ID != 0)
		delete[]ID;
	if (Fname != 0)
		delete[]Fname;
	if (Lname != 0)
		delete[]Lname;
	if (FriendList != NULL)
	{
		delete[]FriendList;
		FriendList = nullptr;
	}
	if (LikedPages != NULL)
	{
		delete[]LikedPages;
		LikedPages = nullptr;
	}
	//deleting timeline
	for (int i = 0; i < 11; i++)
	{
		if (Timeline[i] != nullptr) // Checking if the pointer is not null
		{
			delete Timeline[i];
			Timeline[i] = nullptr;
		}
	}
	delete[] Timeline;
	Timeline = nullptr;
}
void User::PrintTimeline()// print timeline function has been made in user and page as it was causing errors in object due to object class being above post class
{
	cout << Fname <<" " << Lname << "-Time Line" << endl<<endl;
	int i = 0;
	while (Timeline[i] != nullptr)
	{
		Timeline[i]->PrintPost();
		i++;
	}
}
void User::print_name()
{
	cout << Fname << " " << Lname;
}
void User::ReadDataFromFile(ifstream& fin)
{
	char* temp = new char[40];
	fin >> temp;
	ID = Functions::GetStringFromBuffer(temp);
	fin >> temp;
	Fname = Functions::GetStringFromBuffer(temp);
	fin >> temp;
	Lname = Functions::GetStringFromBuffer(temp);
	delete[]temp;
	temp = nullptr;
}
void User::AddFriend(User*& Friend)
{
	if (Friend != nullptr)
	{
		for (int i = 0; i < 11; i++)
		{
			if (FriendList[i] == nullptr)
			{
				FriendList[i] = Friend;
				break;
			}
		}
	}
}
void User::LikePage(Page*& New_page)
{
	if (New_page != nullptr)
	{
		for (int i = 0; i < 11; i++)
		{
			if (LikedPages[i] == nullptr)
			{
				LikedPages[i] = New_page;
				break;
			}
		}
	}
}
void User::Print()
{
	cout << ID << "-" << Fname << " " << Lname << endl;
}
void User::ViewFriendList()
{
	if (FriendList[0] == nullptr)
	{
		cout << Fname << " " << Lname << " - Friend list\n\n";
		cout << "User has no friends" << endl;
	}
	else
	{
		cout << Fname << " " << Lname << " - Friend list\n\n";
		int i = 0;
		while (FriendList[i] != nullptr)
		{
			FriendList[i]->Print();
			i++;
		}
	}
}
void User::ViewLikedPages()
{
	if (LikedPages[0] == nullptr)
	{
		cout << Fname << " " << Lname << " - Liked pages\n\n";
		cout << "No liked pages" << endl;
	}
	else
	{
		cout << Fname << " " << Lname << " - Liked pages\n\n";
		int i = 0;
		while (LikedPages[i] != nullptr)
		{
			LikedPages[i]->Print();
			i++;
		}
	}
}
void User::ViewHome()
{
	cout << Fname << " " << Lname << "-View Home\n\n";
	int i = 0;
	while (Timeline[i] != nullptr)
	{
		Timeline[i]->PrintLatest();
		i++;
	}
	cout << endl;
	for (int i = 0; i < 11; i++)
	{
		if (FriendList[i] == nullptr)
			break;
		for (int j = 0; j < 11; j++)
		{
			if (FriendList[i]->Timeline[j] != nullptr)
			{
				FriendList[i]->Timeline[j]->PrintLatest();
			}
		}
	}
	i = 0;
	while (LikedPages[i] != nullptr)
	{
		LikedPages[i]->View_Recent();
		i++;
	}
}
void User::ViewMemory()
{
	int i = 0;
	while (Timeline[i] != nullptr)
	{
		if (Timeline[i]->GetSharedDate().CompareForMemory(Date::GetCurrentDate()) != 0)//this function returns the diff of years if it finds the day and month of current date similar to a post
		{
			cout << "We hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago.\n\n";
			cout << "On this day" << endl;
			cout << Timeline[i]->GetSharedDate().CompareForMemory(Date::GetCurrentDate()) << " Years ago\n\n";
			Timeline[i]->PrintPost();
			cout << endl;
			break;
		}
		i++;
	}
}
void User::Sharememory(const char* id, const char* text, Object* sharedby)
{
	int i = 0;
	while (Timeline[i] != nullptr)
	{
		if (Timeline[i]->GetSharedDate().CompareForMemory(Date::GetCurrentDate()) != 0)
		{
			Memory* ptr = new Memory(Timeline[i], id, text, sharedby);
			sharedby->AddPosttoTimeline(ptr);
			break;
		}
		i++;
	}

}
char* User::Get_User_ID()
{
	return ID;
}
////////
class Controller {
private:
	User* CurrentUser;
	User** AllUsers;
	Page** AllPages;
	Post** AllPosts;
	static int TotalUsers;
	static int TotalPages;
	static int TotalPosts;
public:
	User* SearchUserByID(const char*);
	Page* SearchPageByID(const char*);
	Object* SearchObjByID(const char*);
	Post* SearchPostByID(const char*);
	Controller();
	~Controller();
	void LoadAllUsers(const char*);
	void LoadAllPages(const char*);
	void LoadAllPosts(const char*);
	void LoadAllComments(const char*);
	void LoadAllActivities(const char*);
	void LinkUsersAndPages(const char*);
	void LoadData();
	void Run();
	void SetCurrentUser(const char*);
};
Controller::Controller()
{
	CurrentUser = nullptr;
	AllPosts = nullptr;
	AllUsers = nullptr;
	AllPages = nullptr;
}
Controller::~Controller()
{
	CurrentUser = nullptr;
	for (int i = 0; i < TotalUsers; i++)
	{
		delete AllUsers[i];
	}
	delete[]AllUsers;
	AllUsers = NULL;
	for (int i = 0; i < TotalPages; i++)
	{
		delete AllPages[i];
	}
	delete[]AllPages;
	AllPages = NULL;
}
void Controller::LoadAllUsers(const char* users_file)
{
	ifstream fin(users_file);
	fin >> TotalUsers;
	//cout << TotalUsers;
	AllUsers = new User * [TotalUsers];
	if (fin)
	{
		for (int i = 0; i < TotalUsers; i++)
		{
			AllUsers[i] = new User();
			AllUsers[i]->ReadDataFromFile(fin);
		}
	}
	fin.close();
}
void Controller::LoadAllPages(const char*pages_file)
{
	ifstream fin(pages_file);
	fin >> TotalPages;
	/*cout << "Total:"<<TotalPages<<endl;*/
	AllPages = new Page * [TotalPages];
	if (fin)
	{
		for (int i = 0; i < TotalPages; i++)
		{
			AllPages[i] = new Page();
			AllPages[i]->ReadDataFromFile(fin);
		}
	}
	fin.close();
}
void Controller::LoadAllPosts(const char* post_file)
{
	ifstream fin(post_file);
	fin >> TotalPosts;
	//cout << "Total Post:" << TotalPosts << endl;
	AllPosts = new Post * [TotalPosts];
	if (fin)
	{
		char* temp = new char[30];
		for (int i = 0; i < TotalPosts; i++)
		{
			AllPosts[i] = new Post();
			AllPosts[i]->ReadDatafromfile(fin);
			fin >> temp;
			//cout << temp;
			Object* ptr = SearchObjByID(temp);
			AllPosts[i]->SetSharedBy(ptr);
			//cout << 99 << endl;
			ptr->AddPosttoTimeline(AllPosts[i]);
			fin >> temp;
			while (temp[0] != '-')
			{
				//Hptr = nullptr;
				ptr = SearchObjByID(temp);
				AllPosts[i]->Addlike(ptr);
				fin >> temp;
			}
		}
		delete[]temp;
	}
	fin.close();
}
void Controller::LoadAllComments(const char* Comments_File)
{
	ifstream fin(Comments_File);
	int TotalComments;
	fin >> TotalComments;
	if (fin)
	{
		char* temp = new char[100];
		char* Comment_ID;
		Object* Obj_ptr;
		for (int i = 0; i < TotalComments; i++)
		{
			//takes input of comments from file and adds them to each post
			fin >> temp;
			Comment_ID = Functions::GetStringFromBuffer(temp);
			Comment* C_ptr = new Comment;
			fin >> temp;
			Post* postptr = SearchPostByID(Functions::GetStringFromBuffer(temp));
			fin >> temp;
			Obj_ptr = SearchObjByID(Functions::GetStringFromBuffer(temp));
			fin.getline(temp, 100);
			C_ptr->SetValues(Comment_ID, Functions::GetStringFromBuffer(temp), Obj_ptr);
			postptr->AddComment(C_ptr);
			delete[]temp;
			temp = new char[100];
		}
		delete[]temp;
		temp = nullptr;
		Comment_ID = nullptr;
		//C_ptr = nullptr;
		Obj_ptr = nullptr;
	}
	fin.close();
}
void Controller::LoadAllActivities(const char* Activities_file)
{
	ifstream fin(Activities_file);
	if (fin)
	{
		int TotalActivities,type;
		fin >> TotalActivities;
		char* temp = new char[100];
		Post* ptr;
		for (int i = 0; i < TotalActivities; i++)
		{
			fin >> temp;
			ptr = SearchPostByID(Functions::GetStringFromBuffer(temp));
			fin >> type;
			fin.getline(temp, 100);
			Activity* Activity_ptr = new Activity;
			Activity_ptr->SetValues(type, Functions::GetStringFromBuffer(temp));
			ptr->AddActivity(Activity_ptr);
			delete[]temp;
			temp = new char[100];
		}
		delete[]temp;
		temp = nullptr;
		ptr = nullptr;
	}
	fin.close();
}
void Controller:: LoadData()
{
	LoadAllUsers("SocialNetworkUsers.txt");
	LoadAllPages("SocialNetworkPages.txt");
	LinkUsersAndPages("UserFriendsandLikedPages.txt");
	LoadAllPosts("SocialNetworkPosts.txt");
	LoadAllComments("SocialNetworkComments.txt");
	LoadAllActivities("SocialNetworkActivities.txt");
}
void Controller::Run()
{
	Date::SetCurrentDate(17, 4, 2024);
	cout << "Current Date:";
	Date::GetCurrentDate().print();
	SetCurrentUser("u7");
	cout << "Current User:";
	CurrentUser->print_name();
	cout << "\n----------------------------------------------------\n\n\n\n";
	cout << "Friend List:" << endl << endl;
    CurrentUser->ViewFriendList();
	cout << "-----------------------------------------------------\n\n\n\n";
	cout << "View Liked Pages:" << endl << endl;
	CurrentUser->ViewLikedPages();
	cout << "\n\n-----------------------------------------------------\n\n\n\n";
	cout << "View Timeline:" << endl << endl;
	CurrentUser->PrintTimeline();
	cout << "\n\n-----------------------------------------------------\n\n\n\n";
	cout << "View Liked list(post5):\n\n" << endl;
	SearchPostByID("post5")->PrintLikedBy();
	cout << "\n\n-----------------------------------------------------\n\n\n\n";
	cout << "Add like(post5):\n\n";
	SearchPostByID("post5")->Addlike(CurrentUser);
	cout << "View Liked list(post5):\n\n";
	SearchPostByID("post5")->PrintLikedBy();
	cout << "\n\n-----------------------------------------------------\n\n\n\n";
	cout << "ViewPage(p1):\n\n";
	SearchPageByID("p1")->View_Page();
	cout << "\n\n-----------------------------------------------------\n\n\n\n";
	CurrentUser->ViewHome();
	cout << "-----------------------------------------------------\n\n\n\n";
	cout << "Add Comment:\n\n";
	Comment* ptr = new Comment;
	ptr->SetValues(0, "Thanks for the wishes", CurrentUser);
	SearchPostByID("post8")->AddComment(ptr);
	SearchPostByID("post8")->PrintPost();
	ptr = nullptr;
	cout << "-----------------------------------------------------\n\n\n\n";
	cout << "-See memory\n\n";
	CurrentUser->ViewMemory();
	cout << "\n\n-----------------------------------------------------\n\n\n\n";
	cout << "-Share memory\n\n";
	CurrentUser->Sharememory("post10", "Never thought I will be specialist in this field...", CurrentUser);
	CurrentUser->PrintTimeline();
	cout << "\n\n-----------------------------------------------------\n\n\n\n";
}
int Controller::TotalPages = 0;
int Controller::TotalUsers = 0;
int Controller::TotalPosts = 0;
User* Controller::SearchUserByID(const char* User_ID)
{
	for (int i = 0; i < TotalUsers; i++)
	{
		if (Functions::FindSubString(AllUsers[i]->Get_User_ID(), User_ID) == 1)
		{
			return AllUsers[i];
		}
	}
	return 0;
}
Page* Controller::SearchPageByID(const char* Page_ID)
{
	for (int i = 0; i < TotalPages; i++)
	{
		if (Functions::FindSubString(AllPages[i]->Get_Page_ID(), Page_ID)==1)
		{
			return AllPages[i];
		}
	}
	return 0;
}
Post* Controller::SearchPostByID(const char* ID)
{
	for (int i = 0; i < TotalPosts; i++)
	{
		if (Functions::FindSubString(AllPosts[i]->GetPostID(),ID) == 1)
		{
			return AllPosts[i];
		}
	}
	return 0;
}
Object* Controller::SearchObjByID(const char* ID)
{
	if (SearchUserByID(ID) != nullptr)
	{
		return SearchUserByID(ID);
	}
	else if (SearchPageByID(ID) != nullptr)
	{
		return SearchPageByID(ID);
	}
	return 0;
}
void Controller::LinkUsersAndPages(const char*filename)
{
	ifstream fin(filename);
	char* temp1 = new char[40];
	fin >> temp1;
	while (temp1[0] != '-')
	{
		User* temp = SearchUserByID(temp1);
		while (temp1[0] != '-')
		{
			fin >> temp1;
			User* temp3 = SearchUserByID(temp1);
			temp->AddFriend(temp3);
			//temp3 = nullptr;
		}
		fin >> temp1;
		while (temp1[0] != '-')
		{
			Page* temp2 = SearchPageByID(temp1);
			temp->LikePage(temp2);
			fin >> temp1;
		}
		fin >> temp1;
	}
	fin.close();
}
void Controller::SetCurrentUser(const char* ID)
{
	CurrentUser= SearchUserByID(ID);
}
int main()
{
	Controller mainApp;
	mainApp.LoadData();
	mainApp.Run();
	system("PAUSE");
	return 0;
}
