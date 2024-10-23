#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cstdlib> //rng
#include <ctime>  
#include <vector>
#include <string>
#include <fstream>

using namespace std;


class COMMENT
{
protected:
    string content;
public:
    void typeComment();
  
};


class POST
{
protected:
    string user;
    string content;
    vector<COMMENT> comments;
public:
    //Trả về nội dung bài viết
    POST(string name, string cont)
    {

    }
    string get_content();
    
    void push_back_post(POST newpost)
    {

    }
    void addComment(string com);
    void showComment();

 
};
class USER
{
protected:
    string name;
    
public:
    vector<POST> posts;
    USER(string username)
    {
        name = username;
    }
    string get_name()
    {
        return name;
    }
    void addpost()
    {
        cout<<"-- Nhap noi dung bai viet: ";
        string cont;
        cin.ignore(1); getline(cin, cont);
        POST curPost(name, cont);
        posts.push_back(curPost);

    }
};


int main()
{
    vector<USER> users;
    USER curUser("Hieu");
    while (1)
    {
        int n;
        cout<<"1. Dang bai"<<endl<<"2. Xem bai viet cua minh"<<endl<<"Nhap: ";
        cin>>n;
        switch (n)
        {
        case 1: 
        {
            curUser.addpost();
            break;
        }
        case 2:
        {
            for (int i = 0; i < curUser.posts.size(); i++)
            {
                cout<<endl<<curUser.posts[i].get_content();
            }
            
            break;
        }
        case 3:
            cout<<"--   Thank you and goodbye!   --";
            return 0;
        }
    }
    
    

    
   

}

