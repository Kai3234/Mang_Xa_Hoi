#include <iostream>
#include <iomanip>
#include <conio.h>

using namespace std;


class COMMENT
{
protected:
    string content;
public:
    COMMENT(/* args */);
    ~COMMENT();
};


class POST
{
protected:
    string title;
    string content;
    COMMENT comment[100];

public:
    POST(/* args */);
    ~POST();
};

class USER
{
protected:
    string name;
    string pass;
public:
    POST post[100];
};



int main()
{
    int n = 0;
    while (1)
    {
        cout<<"Chao mung den ung dung:"<<endl;
        cout<<"1. Dang nhap"<<endl<<"2. Dang ky"<<endl<<"3. Thoat"<<endl<<"--   Nhap lua chon (1, 2, 3): ";
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