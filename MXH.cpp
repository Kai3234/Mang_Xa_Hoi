#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cstdlib> //rng
#include <ctime>  
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struc {
    std::string username;
    std::string passcode;
};

bool read_User(std::vector<Account> &accounts) {
    std::ifstream file("User.txt"); 

    if (!file) {  
        std::cerr << "Error: Could not open credentials file." << std::endl;
        return false;
    }
 std::string line, username, passcode;

  while (getline(file, line)) {
        std::istringstream iss(line);
        iss >> username >> passcode;  // Split line into username and passcode
        accounts.push_back({username, passcode});  // Store the account in the vector
    }

    file.close();  // Close the file
    return true;
}

// Function to verify
bool verify_login(const std::string &input_username, const std::string &input_passcode, const std::vector<Account> &accounts) {
    // Loop through all accounts and check for a match
    for (const auto &account : accounts) {
        if (account.username == input_username && account.passcode == input_passcode) {
            return true;  // Login successful
        }
    }
    return false;  // No match found
}

// Function to sign up a new account and save to file
void sign_up(std::vector<USER> &users) {
    std::string new_username, new_passcode;

    std::cout << "Sign Up Page" << std::endl;
    std::cout << "Enter a new username: ";
    std::cin >> new_username;
    std::cout << "Enter a new passcode: ";
    std::cin >> new_passcode;

    // Add the new account to the vector
    users.push_back({new_username, new_passcode});

    // Open file in append mode to add the new account to the file
    std::ofstream file("User.txt", std::ios::app);
    if (file) {
        file << new_username << " " << new_passcode << "\n";
        std::cout << "Account created and saved successfully!" << std::endl;
    } else {
        std::cerr << "Error: Could not open User file to save new account." << std::endl;
    }
    file.close();
}

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
    //Hiển thị người dùng có bạn chung 
    void mutual_friend();
  
};

class USER: public FRIEND
{
protected:
    string name;
    string pass;
    vector<POST> post;
public:
    string get_name()
    {
        return name;
    }
    string get_pass()
    {
        return pass;
    }
bool read_User(std::vector<Account> &accounts) {
    std::ifstream file("User.txt"); 

    if (!file) {  
        std::cerr << "Error: Could not open credentials file." << std::endl;
        return false;
    }
 std::string line, username, passcode;

  while (getline(file, line)) {
        std::istringstream iss(line);
        iss >> name >> pass;  // Split line into username and passcode
        accounts.push_back({name, pass});  // Store the account in the vector
    }

    file.close();  // Close the file
    return true;
}

// Function to verify
bool verify_login(const std::string &input_username, const std::string &input_passcode, const std::vector<USERt> &user) {
    // Loop through all accounts and check for a match
    for (const auto &account : accounts) {
        if (account.name == input_name && account.pass == input_pass) {
            return true;  // Login successful
        }
    }
    return false;  // No match found
}

// Function to sign up a new account and save to file
void sign_up(std::vector<USER> &user) {
    std::string new_name, new_pass;

    std::cout << "Sign Up Page" << std::endl;
    std::cout << "Enter a new username: ";
    std::cin >> new_name;
    std::cout << "Enter a new passcode: ";
    std::cin >> new_pass;

    // Add the new account to the vector
    users.push_back({new_name, new_pass});

    // Open file in append mode to add the new account to the file
    std::ofstream file("User.txt", std::ios::app);
    if (file) {
        file << new_name << " " << new_pass << "\n";
        std::cout << "Account created and saved successfully!" << std::endl;
    } else {
        std::cerr << "Error: Could not open User file to save new account." << std::endl;
    }
    file.close();
}
    //Tạo file tin nhắn hoặc đọc file tin nhắn và hiển thị tin nhắn từ file
    void showMessage(USER m);
    //Nhập tin nhắn vào file
    void typeMessage(USER m);

    
};

//hàm quét file user.txt để lưu tên, mật khẩu vào vector users
void filenamepass(vector<USER> users);

//hàm đăng ký, đăng nhập
void signUp();
void login();

//hàm hiển thị người dùng có chứa word
void searchUsername(string word, vector<USER> users); 



USER* searchUsers(vector<USER> users, string username)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].get_name() == username)
        {
            return &users[i];
        }
    }
    return nullptr;
}

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
        {
             if (choice == 1) {
        // Log In
        std::string input_name, input_pass;
        std::cout << "Login" << std::endl;
        std::cout << "Enter username: ";
        std::cin >> input_name;
        std::cout << "Enter passcode: ";
        std::cin >> input_pass;

        // Check if the login is successful
        if (verify_login(input_name, input_pass, users)) {
            std::cout << "Login successful!" << std::endl;
            main_menu();
        } else {
            std::cout << "Invalid username or passcode!" << std::endl;
        }

    } else if (choice == 2) {
        // Sign Up
        sign_up(users);

    } else {
        std::cout << "Invalid choice!" << std::endl;
    }
            string loginName;
            void login();
            USER *loginUser = searchUsers(users, loginName);   
            int choice = 0;
            while (choice != 6)
            {
                cout<<"-- Xin chao ["<<loginUser->get_name()<<"]:   --"; 
                cout<<"1. Dang bai"<<endl;
                cout<<"2. Bai viet cua minh"<<endl;
                cout<<"3. Ban be"<<endl;
                cout<<"4. Goi y ban be"<<endl;
                cout<<"5. Tim kiem"<<endl;
                cout<<"6. Dang xuat"<<endl;
                cout<<"--   Nhap lua chon cua ban: ";
                cin>>choice;
                switch (choice)
                {
                case 1: //Đăng bài
                {
                    break;
                }
                case 2: //Bài viết của mình
                {
                    break;
                }
                case 3: //Bạn bè
                {
                    int choice3 = 0;
                    //Hiển thị danh sách bạn bè
                    loginUser->showFriends();
                    cout<<"--   Lua chon   --"<<endl;
                    cout<<"1. Lua chon ban be"<<endl;
                    cout<<"2. Thoat"<<endl;
                    cout<<"--   Nhap lua chon: ";
                    cin>>choice3;
                    while (choice3 != 2)
                    {
                        switch (choice3)
                        {
                        case 1:
                        {
                            string fname;
                            cout<<"--   Nhap ten nguoi dung: ";
                            cin>>fname;
                            USER *friendUser = searchUsers(users, fname);
                            int choice31 = 0;
                            cout<<"--   Lua chon   --"<<endl;
                            cout<<"1. Xem bai viet"<<endl;
                            cout<<"2. Nhan tin"<<endl;
                            cout<<"3. Thoat"<<endl;
                            cout<<"--   Nhap lua chon: ";
                            while (choice31 != 3)
                            {
                                switch (choice31)
                                {
                                case 1:
                                {
                                    break;
                                }
                                case 2:
                                {
                                    //Hiển thị tin nhắn và yêu cầu nhập tin nhắn mới
                                    loginUser->showMessage(*friendUser);
                                    loginUser->typeMessage(*friendUser);
                                    break;
                                }
                                case 3:
                                {
                                    break;
                                }
                                default:
                                    cout<<"--   Lua chon khong hop le!   --"<<endl;
                                    break;
                                }
                            }
                            break;
                        }
                        case 2:
                            break;                   
                        default:
                            cout<<"--   Lua chon khong hop le!   --"<<endl;
                            break;
                        }
                    }  
                    break;
                }
                case 4:  //gợi ý bạn bè
                {
                    cout<<"--   Goi y   --"<<endl;
                    //Hiển thị người có bạn chung
                    loginUser->mutual_friend();
                    cout<<"--   Lua chon   --"<<endl;
                    cout<<"1. Lua chon nguoi dung ket ban"<<endl;
                    cout<<"2. Thoat"<<endl;
                    cout<<"-- Nhap lua chon: "<<endl;
                    int choice4 = 0;
                    cin>>choice4;
                    while (choice4 != 2)
                    {
                        switch (choice4)
                        {
                        case 1:
                        {
                            cout<<"--   Nhap ten nguoi dung: ";
                            string mfname;
                            cin>>mfname;
                            //Kết bạn với người dùng mfname
                            loginUser->makeFriend();
                            break;
                        }
                        case 2:
                            break;
                            
                        
                        default:
                            cout<<"--   Lua chon khong hop le!   --"<<endl;
                            break;
                        }
                    }
                    
                    break;
                }
                case 5: //tìm kiếm
                {
                    cout<<"--   Nhap tu tim kiem: ";
                    string word;
                    cin.ignore(1);
                    getline(cin, word);
                    //hiển thị danh sách tìm kiếm
                    searchUsername(word, users);

                    cout<<"--   Lua chon   --"<<endl;
                    cout<<"1. Lua chon nguoi dung"<<endl;
                    cout<<"2. Thoat"<<endl;
                    cout<<"-- Nhap lua chon: "<<endl;
                    int choice5;
                    cin>>choice5;
                    while (choice5 != 2)
                    {
                        switch (choice5)
                        {
                        case 1:
                        {
                            cout<<"--   Nhap ten nguoi dung: ";
                            string findname;
                            cin>>findname;
                            USER *findUser = searchUsers(users, findname);
                            int choice51 = 0;
                            cout<<"--   Lua chon   --"<<endl;
                            cout<<"1. Xem bai viet"<<endl;
                            cout<<"2. Nhan tin"<<endl;
                            cout<<"3. Thoat"<<endl;
                            cout<<"--   Nhap lua chon: ";
                            while (choice51 != 4)
                            {
                                switch (choice51)
                                {
                                case 1:
                                {
                                    break;
                                }
                                case 2:
                                {
                                    //Hiển thị tin nhắn và yêu cầu nhập tin nhắn mới
                                    loginUser->showMessage(*findUser);
                                    loginUser->typeMessage(*findUser);
                                    break;
                                }
                                case 3: //Kết bạn
                                {
                                    
                                    loginUser->makeFriend();
                                    break;
                                }
                                case 4:
                                {
                                    break;
                                }
                                default:
                                    cout<<"--   Lua chon khong hop le!   --"<<endl;
                                    break;
                                }
                            }
                            break;
                        }
                        case 2:
                            break;
                            
                        
                        default:
                            cout<<"--   Lua chon khong hop le!   --"<<endl;
                            break;
                        }
                    }
                    break;
                }
                case 6: // đăng xuất
                {
                    cout<<"--   Tam biet ["<<loginUser->get_name()<<"]!   --";
                    break;
                }
                    
                
                default:
                    cout<<"--   Lua chon khong hop le!   --";
                    break;
                }
            }
            
            break;
        }
        case 2:
        {
            void signUp();
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
