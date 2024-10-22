#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cstdlib> //rng
#include <ctime>  

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

class FRIEND
{
private:
    /* data */
public:
    FRIEND(/* args */);
    ~FRIEND();
};

void show_ad() {
    std::string ads[] = {
        "Ad 1: The City new product from Logoras Artelier",
        "Ad 2: New products from Siderial Plexus",
        "Ad 3: ACME ",
        "Ad 4: ",
        "Ad 5: "
    };

    // Randomly select one of the 5 ads
    int ad_index = std::rand() % 5;  // Generates a number between 0 and 4
    std::cout << ads[ad_index] << std::endl;
}



int main()
{
    int n = 0;
    USER user[100];

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
