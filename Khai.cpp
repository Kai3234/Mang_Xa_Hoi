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
    string content;
    vector<COMMENT> comments;
public:
    //Trả về nội dung bài viết
    string get_content();
    void typePost();
    void addComment(string com);
    void showComment();

 
};
class USER
{
protected:
    string name;
    string pass;
    vector<POST> post;
public:
    void postcontent();
    string get_name()
    {
        return name;
    }
    string get_pass()
    {
        return pass;
    }
};


int main()
{
    vector<USER> users;
    //Quét các file để lưu dữ liệu vào vector users

    USER *curUser;
    int n = 0;
    while (1)
    {
        
    }
    
   

}

