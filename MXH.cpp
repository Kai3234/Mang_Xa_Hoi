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


class COMMENT
{
protected:
    string user;
    string content;
public:
    COMMENT(string name, string cont)
    {
        user = name;
        content = cont;
    }
    string get_comment_user()
    {
        return user;
    }
    string get_comment_content()
    {
        return content;
    }
};


class POST
{
protected:
    string idpost;
    string user;
    string content;
    
public:
    vector<COMMENT> comments;
    POST(int order, string name, string cont)
    {
        idpost = to_string(order);
        user = name;
        content = cont;
    }
    string get_content()
    {
        return content;
    }

    void showComment()
    {
        cout<<"     +) Binh luan:"<<endl;
        for(int i = 0; i < comments.size(); i++)
        {
            cout<<"     ["<<comments[i].get_comment_user()<<"]: ";
            cout<<comments[i].get_comment_content()<<endl;
        }
        cout<<endl;
    }
    void filecomment()
    {
        fstream fcomment;
        fcomment.open("Post/Comment/" + user + idpost + ".txt", ios::in | ios::out);
        if(!fcomment)
        {
            fcomment.open("Post/Comment/" + user + idpost + ".txt", ios::in | ios::out | ios::trunc);
        }
        else
        {
            fcomment.seekg(0, ios::beg);
            string name;
            string cont;
            while (getline(fcomment, name) && getline(fcomment, cont))
            {   
                COMMENT c(name, cont);
                comments.push_back(c);
            }
        }
        fcomment.close();
    }
    

 
};

/*
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
*/
class USER//: public FRIEND
{
protected:
    string name;
    string pass;
    vector<POST> posts;
public:
    USER(string username, string passcode)
    {
        name = username;
        pass = passcode;
    }
    string get_name()
    {
        return name;
    }
    string get_pass()
    {
        return pass;
    }
    

    void filePost()
    {
        fstream fpost;
        fpost.open("Post/" + name + ".txt", ios::in | ios::out);
        if(!fpost)
        {
            fpost.open("Post/" + name + ".txt", ios::in | ios::out | ios::trunc);
        }
        else
        {
            fpost.seekg(0, ios::beg);
            string cont;
            while (getline(fpost, cont))
            {   
                POST p(posts.size(), name, cont);
                posts.push_back(p);
            }
        }
        fpost.close();
        for (int i = 0; i < posts.size(); i++)
        {
            posts[i].filecomment();
        }
        
    }

    

    void addPost()
    {
        cout<<"-- Nhap noi dung bai viet: ";
        string cont;
        cin.ignore(1); getline(cin, cont);
        POST curPost(posts.size(), name, cont);
        posts.push_back(curPost);
        fstream fpost;
        fpost.open("Post/" + name + ".txt", ios::in | ios::out | ios::app);
        if(!fpost)
        {
            fpost.open("Post/" + name + ".txt", ios::in | ios::out | ios::trunc);
        }    
        fpost<<cont<<"\n";
        fpost.close();
    }

    void addComment(USER *curUser, int postOrder)
    {
        cout<<"-- Nhap noi dung binh luan: ";
        string cont;
        cin.ignore(1); getline(cin, cont);
        COMMENT newCom(name, cont);
        curUser->posts[postOrder].comments.push_back(newCom);
        fstream fcomment;
        string idpo = to_string(postOrder);
        fcomment.open("Post/Comment/" + name + idpo + ".txt", ios::in | ios::out | ios::app);
        if(!fcomment)
        {
            fcomment.open("Post/Comment/" + name + idpo + ".txt", ios::in | ios::out | ios::trunc);
        }
        fcomment<<name<<"\n";
        fcomment<<cont<<"\n";
        fcomment.close();   
    }

    void showPost(USER *curUser)
    {
        static int postOrder = 0;
        int m = 0;
        if (posts.size() > 0)
        {
            cout<<"--   Bai viet 1   --"<<endl;
            cout<<"["<<get_name()<<"]"<<endl;
            cout<<posts[0].get_content()<<endl<<endl;
            posts[0].showComment();
            while(m != 4)
            { 
                cout<<"--   Lua chon   --"<<endl;
                cout<<"1. Binh luan"<<endl<<"2. Truoc"<<endl<<"3. Sau"<<endl<<"4. Thoat"<<endl;
                cout<<"Nhap so: "; cin>>m;
            switch (m)
            {

            case 1:
            {
                addComment(curUser, postOrder);
            }
            case 2:
            {
                if(postOrder > 0)
                {
                    postOrder--;
                }
                cout<<"--   Bai viet "<<postOrder + 1<<"   --"<<endl;
                cout<<"["<<get_name()<<"]"<<endl;                        
                cout<<posts[postOrder].get_content()<<endl<<endl;
                posts[postOrder].showComment();

                break;
            } 
            case 3:
            {
                if(postOrder < posts.size() - 1)                    
                {
                    postOrder++;
                }
                cout<<"--   Bai viet "<<postOrder + 1<<"   --"<<endl;
                cout<<"["<<get_name()<<"]"<<endl;                        
                cout<<posts[postOrder].get_content()<<endl<<endl;
                posts[postOrder].showComment();
                break;
            } 
            case 4:
                break;
            }
            }
        }
        else
        {
            cout<<"--   "<<name<<" khong co bai viet nao!   --"<<endl;
        }   
    }

    
    //Tạo file tin nhắn hoặc đọc file tin nhắn và hiển thị tin nhắn từ file
    void showMessage(USER m);
    //Nhập tin nhắn vào file
    void typeMessage(USER m);

    
};


bool read_User(vector<USER>& users) 
{
    ifstream file("User.txt"); 
    if (!file) 
    {  
        cerr << "Error: Could not open credentials file." << endl;
        return false;
    }
    string line, name, pass;
    while (getline(file, line)) 
    {
        istringstream iss(line);
        iss >> name >> pass;  // Split line into username and passcode
        users.push_back({name, pass});  // Store the account in the vector
    }
    file.close();  // Close the file
    return true;
}
// Function to verify
bool verify_login(string input_name, string input_pass, vector<USER> users) 
{
    // Loop through all accounts and check for a match
    for (auto &user : users) 
    {
        if (user.get_name() == input_name && user.get_pass() == input_pass) {
            return true;  // Login successful
        }
    }
    return false;  // No match found
}

    // Function to sign up a new account and save to file
void sign_up(vector<USER> &users) 
{
    string new_name, new_pass;
    cout << "--   Dang ky   --" << std::endl;
    cout << "--   Nhap ten nguoi dung: ";
    cin >> new_name;
    for (auto &user : users) 
    {
        if (user.get_name() == new_name) 
        {
            cout<<"--   Ten nguoi dung da ton tai   --"<<endl;
            return;  
        }
    }
    cout << "--   Nhap mat khau: ";
    cin >> new_pass;
    // Add the new account to the vector
    USER p(new_name, new_pass);
    users.push_back(p);
    // Open file in append mode to add the new account to the file
    ofstream file("User.txt", ios::app);
    if (file) {
        file << new_name << " " << new_pass << "\n";
        cout << "--   Dang ky thanh cong!" << endl;
    } else {
        cerr << "--   Khong the mo User.txt de luu tai khoan   --" << endl;
    }
    cout<<endl<<users.size()<<endl;
    file.close();
}

//hàm hiển thị người dùng có chứa word
void searchUsername(string word, vector<USER> users); 



USER* searchUsers(vector<USER>& users, string username)
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
    read_User(users);
    //Quét các file để lưu dữ liệu vào vector users
    for(int i = 0; i < users.size(); i++)
    {
        users[i].filePost();
    }
    

    int n = 0;
    while (1)
    {
        srand(time(0)); //ads rng
        int random_number = rand() % 2 + 1; //ads dice
        
        if (random_number == 1) 
        {
            show_ad();
        } 
        else 
        {
            cout << "No ad" << endl;
        }
        
        cout<<"--   Chao mung den ung dung   --"<<endl;
        cout<<"1. Dang nhap"<<endl<<"2. Dang ky"<<endl<<"3. Thoat"<<endl<<"--   Nhap so de lua chon (1, 2, 3): ";
        cin>>n;
        switch (n)
        {
            case 1:
            {
                // Log In
                string input_name, input_pass;
                cout << "--   Dang nhap   --" << endl;
                cout << "--   Nhap ten nguoi dung: ";
                cin >> input_name;
                cout << "--   Nhap mat khau: ";
                cin >> input_pass;

                // Check if the login is successful
                if (verify_login(input_name, input_pass, users)) 
                {
                    cout << "--   Dang nhap thanh cong!   --" << endl;
                } 
                else 
                {
                    cout << "--   Ten nguoi dung hoac mat khau sai!   --" << endl;
                    break;
                }
                USER *loginUser = searchUsers(users, input_name);   
                int choice = 0;
                while (choice != 6)
                {
                    cout<<"-- Xin chao ["<<loginUser->get_name()<<"]:   --"<<endl; 
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
                        loginUser->addPost();
                        break;
                    }
                    case 2: //Bài viết của mình
                    {
                        loginUser->showPost(loginUser);
                        break;
                    }
                    case 3: //Bạn bè
                    {   
                        /*
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
                            */
                        break;
                    }  
                        
                    case 4:  //gợi ý bạn bè
                    {
                        /*
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
                        */
                        
                        break;
                    }
                    case 5: //tìm kiếm
                    {
                        /*
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
                        */
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
                // Sign Up
                sign_up(users);
                break;
            }
            case 3:
            {
                cout<<"--   Thank you and goodbye!   --";
                return 0;
            }
                
            default: cout<<"--   Lua chon khong hop le!   --";
                break;
    }
}
   

}
