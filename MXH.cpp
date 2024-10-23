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

class FRIEND
{
protected:
    vector<string> friendname;
    
public:
    //Quét dữ liệu về bạn bè
    void fileFriend();
    //Kiểm tra có phải là bạn bè
    bool isFriend();
    //Kết bạn
    void makeFriend();
    //Hiển thị danh sách bạn bè
    void showFriends();
    //Hiển thị bạn bè không có tên trong vector otherfriend và otherUser
    void mutual_friend(vector<string> otherfriend, string otherUser);
  
};

class USER: public FRIEND
{
protected:
    string name;
    string pass;
    vector<POST> post;
public:
    void postcontent();
    string get_name()
    {

    }
    //Tạo file tin nhắn và hiện tin nhắn từ file
    void showMessage(USER m);
    //Nhập tin nhắn vào file
    void typeMessage();
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

void isNameUseable();
void insertNewName();




int main()
{
    vector<USER> users;
    //Quét các file để lưu dữ liệu vào vector users

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
        
        cout<<"--   Chao mung den ung dung   --"<<endl;
        cout<<"1. Dang nhap"<<endl<<"2. Dang ky"<<endl<<"3. Thoat"<<endl<<"--   Nhap so de lua chon (1, 2, 3): ";
        cin>>n;
        switch (n)
        {
        case 1:
            while (1)
            {
                cout<<"--   Chao mung   --";
            }
            
            break;
        case 2:
        {
            cout<<"--   Nhap ten nguoi dung: ";
            string newname, newpass;
            cin>>newname;
            //Hàm kiểm tra tên hợp lệ
            cout<<"--   Nhap mat khau: ";
            cin>>newpass;
            //Hàm điền tên và mật khẩu vào file text và lưu tên và mật khẩu vào vector users 
            break;
        }
        case 3:
            cout<<"--   Thank you and goodbye!   --";
            return 0;
        
        default: cout<<"--   Lua chon khong hop le!   --";
            break;
        }
    }
   

}
