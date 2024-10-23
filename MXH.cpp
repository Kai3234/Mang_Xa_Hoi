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
    void showComment();

 
};

class USER
{
protected:
    string name;
    string pass;
    vector<POST> post;
    vector<FRIEND> friend;
public:
    void postcontent();
};

class FRIEND
{
private:
    
public:
 
};





int main()
{
    
    int n = 0;
    while (1)
    {
        std::srand(std::time(0)); //ads rng
        int random_number = std::rand() % 2 + 1; //ads dice
        
        if (random_number == 1) {
        show_ad();
    } else {
        std::cout << "No ad" << std::endl;
    }
        
        cout<<"Chao mung den ung dung:"<<endl;
        cout<<"1. Dang nhap"<<endl<<"2. Dang ky"<<endl<<"3. Thoat"<<endl<<"--   Nhap so de lua chon (1, 2, 3): ";
        cin>>n;
        switch (n)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            cout<<"--   Thank you and goodbye!   --";
            return 0;
        
        default: cout<<"Lua chon khong hop le";
            break;
        }
    }
   

}
