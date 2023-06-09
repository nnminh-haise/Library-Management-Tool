#include "TheDocGia.h"
#include "../Helper/Helper.h"
#include "../DataStructures/Stack.h"

#include <string>
#include <iostream>
#include <fstream>
#include <format>
#include <ctime>

BOOK_CIRCULATION::BookCirculation::BookCirculation() {
    this->id = std::string();
    this->borrowDate = HELPER::Date();
    this->returnDate = HELPER::Date();
    this->status = BOOK_CIRCULATION::CirculationStatus::LOSTED;
}

BOOK_CIRCULATION::BookCirculation::BookCirculation(std::string id, HELPER::Date NgayMuon, HELPER::Date NgayTra, BOOK_CIRCULATION::CirculationStatus status) {
    this->id = id;
    this->borrowDate = NgayMuon;
    this->returnDate = NgayTra;
    this->status = status;
}

void BOOK_CIRCULATION::BookCirculation::SetID(std::string id) {
    this->id = id;
}

std::string BOOK_CIRCULATION::BookCirculation::GetID() {
    return this->id;
}

void BOOK_CIRCULATION::BookCirculation::SetBorrowDate(HELPER::Date NgayMuon) {
    this->borrowDate = NgayMuon;
}

HELPER::Date BOOK_CIRCULATION::BookCirculation::GetBorrowDate() {
    return this->borrowDate;
}

void BOOK_CIRCULATION::BookCirculation::SetReturnDate(HELPER::Date NgayTra) {
    this->returnDate = NgayTra;
}

HELPER::Date BOOK_CIRCULATION::BookCirculation::GetReturnDate() {
    return this->returnDate;
}

void BOOK_CIRCULATION::BookCirculation::SetStatus(BOOK_CIRCULATION::CirculationStatus status) {
    this->status = status;
}

BOOK_CIRCULATION::CirculationStatus BOOK_CIRCULATION::BookCirculation::GetStatus() {
    return this->status;
}

std::string BOOK_CIRCULATION::BookCirculation::StringfyStatus()
{
    if (this->status == BOOK_CIRCULATION::CirculationStatus::BORROWING)
    {
        return "BORROWING";
    }
    else if (this->status == BOOK_CIRCULATION::CirculationStatus::RETURNED)
    {
        return "RETURNED";
    }
    return "LOSTED";
}

bool BOOK_CIRCULATION::BookCirculation::IsOverdue()
{
    if (this->status != BOOK_CIRCULATION::CirculationStatus::BORROWING)
    {
        return false;
    }

    HELPER::Date today;
    if (today.DaysBetween(this->borrowDate) > 7)
    {
        return true;
    }
    return false;
}

int BOOK_CIRCULATION::BookCirculation::CountOverdueDate()
{
    if (!this->IsOverdue())
    {
        return 0;
    }
    return HELPER::Date().DaysBetween(this->borrowDate + 7);
}

DOUBLE_LINKED_LIST::Node::Node() {
    this->info = BOOK_CIRCULATION::BookCirculation();
    this->left = this->right = nullptr;
}

DOUBLE_LINKED_LIST::Controller::Controller() {
    this->First = this->Last = nullptr;
}

void DOUBLE_LINKED_LIST::Initialize(Controller& list) {
    list.First = list.Last = nullptr;
}

bool DOUBLE_LINKED_LIST::Empty(const Controller& list) {
    return list.First == nullptr;
}

int DOUBLE_LINKED_LIST::Size(const Controller& list) {
    if (DOUBLE_LINKED_LIST::Empty(list))
    {
        return 0;
    }

    int result = 0;
    for (DOUBLE_LINKED_LIST::Pointer p = list.First; p != nullptr; p = p->right) {
        ++result;
    }
    return result;
}

void DOUBLE_LINKED_LIST::ClearList(Controller& list) {
    DOUBLE_LINKED_LIST::Pointer p = list.First;
    while (p != nullptr) {
        DOUBLE_LINKED_LIST::Pointer deleteNode = p;
        p = deleteNode->right;
        delete deleteNode;
    }
    list.First = list.Last = nullptr;
}

void DOUBLE_LINKED_LIST::PushFront(Controller& list, BOOK_CIRCULATION::BookCirculation info)
{
    DOUBLE_LINKED_LIST::Pointer newNode = new DOUBLE_LINKED_LIST::Node;
    newNode->info = info;
    newNode->left = nullptr;
    newNode->right = list.First;

    if (DOUBLE_LINKED_LIST::Empty(list))
    {
        list.First = newNode;
        list.Last = newNode;
        return;
    }

    newNode->right = list.First;
    list.First->left = newNode;
    list.First = newNode;
}

void DOUBLE_LINKED_LIST::PushBack(Controller& list, BOOK_CIRCULATION::BookCirculation info)
{
    DOUBLE_LINKED_LIST::Pointer newNode = new DOUBLE_LINKED_LIST::Node;
    newNode->info = info;
    newNode->left = nullptr;
    newNode->right = nullptr;

    if (DOUBLE_LINKED_LIST::Empty(list))
    {
        list.First = newNode;
        list.Last = newNode;
        return;
    }

    list.Last->right = newNode;
    newNode->left = list.Last;
    list.Last = newNode;
}

void DOUBLE_LINKED_LIST::RemoveNode(Controller& list, DOUBLE_LINKED_LIST::Pointer targetNode)
{
    if (targetNode == nullptr)
    {
        return;
    }

    if (DOUBLE_LINKED_LIST::Empty(list))
    {
        return;
    }

    if (list.First == targetNode)
    {
        list.First = targetNode->right;
    }
    
    if (list.Last == targetNode)
    {
        list.Last = targetNode->left;
    }
    
    if (targetNode->left != nullptr)
    {
        targetNode->left->right = targetNode->right;
    }

    if (targetNode->right != nullptr)
    {
        targetNode->right->left = targetNode->left;
    }

    delete targetNode;
}

READER::Reader::Reader() {
    this->id = -1;
    this->firstName = std::string();
    this->lastName = std::string();
    this->sex = READER::Gender::MALE;
    this->status = READER::ReaderStatus::BANNED;
    this->borrowedBooks = DOUBLE_LINKED_LIST::Controller();
}

READER::Reader::Reader(int MaThe, std::string Ho, std::string Ten, READER::Gender Phai, READER::ReaderStatus status, DOUBLE_LINKED_LIST::Controller DanhSachMuonTra) {
    this->id = MaThe;
    this->firstName = Ho;
    this->lastName = Ten;
    this->sex = Phai;
    this->status = status;
    this->borrowedBooks = DanhSachMuonTra;
}

void READER::Reader::SetID(int MaThe) {
    this->id = MaThe;
}

int READER::Reader::GetID() {
    return this->id;
}

void READER::Reader::SetFirstName(std::string Ho) {
    this->firstName = Ho;
}

std::string READER::Reader::GetFirstName() {
    return this->firstName;
}

void READER::Reader::SetLastName(std::string Ten) {
    this->lastName = Ten;
}

std::string READER::Reader::GetLastName() {
    return this->lastName;
}

void READER::Reader::SetGender(READER::Gender Phai) {
    this->sex = Phai;
}

READER::Gender READER::Reader::GetGender() {
    return this->sex;
}

std::string READER::Reader::GetFullName() {
    return this->firstName + " " + this->lastName;
}

std::string READER::Reader::StringifyGender() {
    return (this->sex == READER::Gender::MALE ? "MALE" : "FEMALE");
}

void READER::Reader::SetStatus(READER::ReaderStatus status) {
    this->status = status;
}

READER::ReaderStatus READER::Reader::GetStatus() {
    return this->status;
}

std::string READER::Reader::StringfyStatus() {
    return (this->status == READER::ReaderStatus::BANNED ? "BANNED" : "ACTIVE");
}

void READER::Reader::SetBooksCirculation(DOUBLE_LINKED_LIST::Controller DanhSachMuonTra) {
    this->borrowedBooks = DanhSachMuonTra;
}

DOUBLE_LINKED_LIST::Controller READER::Reader::GetBooksCirculation() {
    return this->borrowedBooks;
}

void READER::Reader::Log() {
    std::cerr << std::format("_____ THE DOC GIA _____\n");
    std::cerr << std::format("Ma the    : {}\n", this->id);
    std::cerr << std::format("firstName        : {}\n", this->firstName);
    std::cerr << std::format("lastName       : {}\n", this->lastName);
    std::cerr << std::format("sex      : {}\n", this->sex == READER::Gender::MALE ? "Nam" : "Nu");
    std::cerr << std::format("Trang thai: {}\n", this->status == READER::ReaderStatus::BANNED ? "Bi khoa" : "Hoat dong");
    if (DOUBLE_LINKED_LIST::Empty(this->borrowedBooks)) {
        std::cerr << std::format("Doc gia chua muon sach!\n");
    }
    else {
        std::cerr << std::format("Doc gia co muon sach!\n");
    }
    std::cerr << std::format("-----------------------\n");
}

/*
* AVL Tree session start from below
*/

AVL_TREE::Node::Node() {
	this->info = READER::Reader();
	this->balanceFactor = 0;
	this->left = this->right = nullptr;
    this->height = 0;
}

int AVL_TREE::Node::GetKey() {
    return this->info.GetID();
}

void AVL_TREE::Node::SetKey(const int key) {
    this->info.SetID(key);
}

void AVL_TREE::Initialize(AVL_TREE::Pointer& node) {
	node = nullptr;
}

bool AVL_TREE::Empty(AVL_TREE::Pointer const& node) {
	return node == nullptr;
}

void AVL_TREE::InOrderTraversal(AVL_TREE::Pointer const& node) {
	if (node != nullptr) {
		AVL_TREE::InOrderTraversal(node->left);
		std::cerr << node->info.GetID() << " ";
		AVL_TREE::InOrderTraversal(node->right);
	}
}

void AVL_TREE::Size(const AVL_TREE::Pointer& root, int& counter) {
    if (root != nullptr) {
        ++counter;
        AVL_TREE::Size(root->left, counter);
        AVL_TREE::Size(root->right, counter);
    }
}

void AVL_TREE::NonrecursiveInOrderTraversal(const AVL_TREE::Pointer& root) {
    Stack<AVL_TREE::Pointer> stk;

    AVL_TREE::Pointer p = root;

    do {
        while (p != nullptr) {
            stk.Push(p);
            p = p->left;
        }

        if (stk.Empty() == false) {
            p = stk.Pop();
            p->info.Log();
            p = p->right;
        }
        else {
            break;
        }
    } while (true);
}

AVL_TREE::Pointer AVL_TREE::RotateLeft(AVL_TREE::Pointer root) {
    if (root == nullptr) {
        std::cerr << "[ERROR] TREE IS EMPTY!\n";
        return nullptr;
    }

    if (root->right == nullptr) {
        std::cerr << "[ERROR] CANNOT ROTATE LEFT BECAUSE THERE IS NO RIGHT TREE!\n";
        return nullptr;
    }

    AVL_TREE::Pointer p = root->right;
    root->right = p->left;
    p->left = root;
    AVL_TREE::UpdateHeight(root);
    AVL_TREE::UpdateHeight(p);
    return p;
}

AVL_TREE::Pointer AVL_TREE::RotateRight(AVL_TREE::Pointer root) {
    if (root == nullptr) {
        std::cerr << "[ERROR] TREE IS EMPTY!\n";
        return nullptr;
    }

    if (root->left == nullptr) {
        std::cerr << "[ERROR] CANNOT ROTATE RIGHT BECAUSE THERE IS NO LEFT TREE!\n";
        return nullptr;
    }

    AVL_TREE::Pointer s = root->left;
    root->left = s->right;
    s->right = root;
    AVL_TREE::UpdateHeight(root);
    AVL_TREE::UpdateHeight(s);
    return s;
}

/**
 * This method is written in the non-recursive way!
*/
bool AVL_TREE::Insert(AVL_TREE::Pointer& root, READER::Reader info) {

    /*
     * currentNode represent the node which is being manipulated.
     * currentNodeParent is the parent node of the currentNode.
     * currentNodeChild is the child of the currentNode.
     * imbalancedNode is the node before the currentNode which can be an imbalanced node in the AVL Tree.
     * imbalancedNodeParent is the parent of the imbalancedNode.
     * imbalancedNodeChild is the child node of imbalancedNode which could be imbalanced in the AVL Tree.
    */

    AVL_TREE::Pointer currentNode = root;
    AVL_TREE::Pointer currentNodeParent = nullptr;
    AVL_TREE::Pointer currentNodeChild = nullptr;
    AVL_TREE::Pointer imbalancedNode = currentNode;
    AVL_TREE::Pointer imbalancedNodeParent = nullptr;
    AVL_TREE::Pointer imbalancedNodeChild = nullptr;

    int imbalancedFactor = 0;

    /*
    * We first find the parent node of the currentNode.
    * Fint the imbalancedNode, the parent of the imbalancedNode.
    */
    while (currentNode != nullptr) {

        //* If the parameterized key is similar with the currentNode's key, then the parameterized key is not valid.
        if (info.GetID() == currentNode->GetKey()) {
            return false;
        }

        //* If the parameterized key is smaller than the currentNode's key, then we move to the left child tree of the currentNode.
        if (info.GetID() < currentNode->GetKey()) {
            currentNodeChild = currentNode->left;
        }
        //* Otherwise we move to the right child tree of the currentNode.
        else {
            currentNodeChild = currentNode->right;
        }

        //! This if statement logic can be rewrite.
        if (currentNodeChild != nullptr) {
            //* If the currentNode's child is an imbalanced node.
            if (currentNodeChild->balanceFactor != 0) {
                imbalancedNodeParent = currentNode;
                imbalancedNode = currentNodeChild;
            }
        }

        currentNodeParent = currentNode;
        currentNode = currentNodeChild;
    }

    /*
     * Add a new node with the parameterized key and info as a child node of the currentNodeParent.
    */
    currentNodeChild = new AVL_TREE::Node;
    currentNodeChild->info = info;
    currentNodeChild->left = currentNodeChild->right = nullptr;
    if (info.GetID() < currentNodeParent->GetKey()) {
        currentNodeParent->left = currentNodeChild;
    }
    else {
        currentNodeParent->right = currentNodeChild;
    }

    /*
     * We modify the balance factor of all the node between the imbalanced node and the currentNodeChild.
     * If they were to the left, then all the balance factor of them are 1 and -1 in the otherhand.
    */
    if (info.GetID() < imbalancedNode->GetKey()) {
        currentNode = imbalancedNode->left;
    }
    else {
        currentNode = imbalancedNode->right;
    }
    imbalancedNodeChild = currentNode;

    while (currentNode != currentNodeChild) {
        if (info.GetID() < currentNode->GetKey()) {
            currentNode->balanceFactor = 1;
            currentNode = currentNode->left;
        }
        else {
            currentNode->balanceFactor = -1;
            currentNode = currentNode->right;
        }
    }

    /*
     * Detecting the imbalanced direction, which means that the tree is left heavy or right heavy.
    */
    if (info.GetID() < imbalancedNode->GetKey()) {
        imbalancedFactor = 1; //* Left heavy
    }
    else {
        imbalancedFactor = -1; //* Right heavy
    }

    if (imbalancedNode->balanceFactor == 0) {
        imbalancedNode->balanceFactor = imbalancedFactor;
        return false;
    }

    if (imbalancedNode->balanceFactor != imbalancedFactor) {
        imbalancedNode->balanceFactor = 0;
        return false;
    }

    /*
     * After inserting a new node, if the tree is imbalanced, we will balance it again.
     * Case where we only need to rotate once.
    */
    if (imbalancedNodeChild->balanceFactor == imbalancedFactor) {

        //* Rotate right
        if (imbalancedFactor == 1) {
            currentNode = AVL_TREE::RotateRight(imbalancedNode);
        }
        //* rotate left
        else {
            currentNode = AVL_TREE::RotateLeft(imbalancedNode);
        }

        imbalancedNode->balanceFactor = 0;
        imbalancedNodeChild->balanceFactor = 0;
    }
    //* Case where we need to rotate twice
    else {
        //* Rotate Left and Right
        if (imbalancedFactor == 1) {
            imbalancedNode->left = AVL_TREE::RotateLeft(imbalancedNodeChild);
            currentNode = AVL_TREE::RotateRight(imbalancedNode);
        }
        //* Rotate Right and Left
        else {
            imbalancedNode->right = AVL_TREE::RotateRight(imbalancedNodeChild);
            currentNode = AVL_TREE::RotateLeft(imbalancedNode);
        }

        //* If currentNode is the inserted node
        if (currentNode->balanceFactor == 0) {
            imbalancedNode->balanceFactor = 0;
            imbalancedNodeChild->balanceFactor = 0;
        }
        else {
            if (currentNode->balanceFactor == imbalancedFactor) {
                imbalancedNode->balanceFactor = -imbalancedFactor;
                imbalancedNodeChild->balanceFactor = 0;
            }
            else {
                imbalancedNode->balanceFactor = 0;
                imbalancedNodeChild->balanceFactor = imbalancedFactor;
            }
        }
        currentNode->balanceFactor = 0;
    }

    if (imbalancedNodeParent == nullptr) {
        root = currentNode;
    }
    else {
        if (imbalancedNode == imbalancedNodeParent->right) {
            imbalancedNodeParent->right = currentNode;
        }
        else {
            imbalancedNodeParent->left = currentNode;
        }
    }

    return true;
}

AVL_TREE::Pointer AVL_TREE::SearchByKey(const AVL_TREE::Pointer& root, const int& key) {
    AVL_TREE::Pointer p = root;

    while (p != nullptr && p->GetKey() != key) {
        if (p->GetKey() < key) {
            p = p->right;
        }
        else {
            p = p->left;
        }
    }
    return p;
}

AVL_TREE::Pointer AVL_TREE::GetMinValueNode(AVL_TREE::Pointer const& node) {
    if (node == nullptr || node->left == nullptr) {
        return node;
    }

    return AVL_TREE::GetMinValueNode(node->left);
}

int AVL_TREE::GetHeight(Pointer node)
{
    if (node == nullptr) { return 0; }
    return node->height;
}

void AVL_TREE::UpdateHeight(Pointer node)
{
    int leftHeight = node->left == nullptr ? 0 : node->left->height;
    int rightHeight = node->right == nullptr ? 0 : node->right->height;
    node->height = 1 + max(leftHeight, rightHeight);
}

AVL_TREE::Pointer AVL_TREE::FindMinNode(Pointer node)
{
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

AVL_TREE::Pointer AVL_TREE::Balance(Pointer node)
{
    int leftHeight = GetHeight(node->left);
    int rightHeight = GetHeight(node->right);
    int balanceFactor = leftHeight - rightHeight;

    if (balanceFactor > 1) {
        if (GetHeight(node->left->left) >= GetHeight(node->left->right))
            node = RotateRight(node);
        else {
            node->left = RotateLeft(node->left);
            node = RotateRight(node);
        }
    }
    else if (balanceFactor < -1) {
        if (GetHeight(node->right->right) >= GetHeight(node->right->left))
            node = RotateLeft(node);
        else {
            node->right = RotateRight(node->right);
            node = RotateLeft(node);
        }
    }

    return node;
}

AVL_TREE::Pointer AVL_TREE::RemoveNode(AVL_TREE::Pointer root, const int& key)
{
    if (root == nullptr)
        return root;

    if (key < root->GetKey())
        root->left = RemoveNode(root->left, key);
    else if (key > root->GetKey())
        root->right = RemoveNode(root->right, key);
    else
    {
        if (root->left == nullptr || root->right == nullptr) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == nullptr)
            {
                temp = root;
                root = nullptr;
            }
            else {
                *root = *temp;
            }
            delete temp;
        }
        else {
            Node* minRightNode = FindMinNode(root->right);
            root->SetKey(minRightNode->GetKey());
            root->right = RemoveNode(root->right, minRightNode->GetKey());
        }
    }

    if (root == nullptr)
        return root;

    UpdateHeight(root);
    root = Balance(root);

    return root;
}

/**
* READ DATA FROM FILE BASED DATABASE!
*
* 1. Create a file buffer reader.
* 2. Filter out the case where we cannot open the file!
*/
//bool READER_MODULES::LoadDanhSachTheDocGiaFromDB(const std::string& filename, AVL_Tree<READER::Reader, int>* tree)
//{
//    std::filebuf databaseBuffer{};
//
//    if (!databaseBuffer.open(filename, std::ios::in))
//    {
//        throw std::logic_error(std::format("[ERROR] Can not open file {}\n", filename));
//    }
//
//    std::istream database(&databaseBuffer);
//    while (database)
//    {
//        std::string titleData{};
//        std::getline(database, titleData);
//
//        if (titleData.length() == 0)
//        {
//            continue;
//        }
//
//        std::string* data = nullptr;
//        int dataCount = 0;
//        STR::Extract(titleData, ", ", data, dataCount);
//
//        READER::Reader newReader;
//
//        for (int i = 0; i < dataCount; ++i)
//        {
//            switch (i)
//            {
//            case (0): {
//                newReader.SetID(std::stoi(data[i]));
//                break;
//            }
//            case (1): {
//                newReader.SetFirstName(data[i]);
//                break;
//            }
//            case (2): {
//                newReader.SetLastName(data[i]);
//                break;
//            }
//            case (3): {
//                newReader.SetGender(data[i] == "MALE" ? READER::Gender::MALE : READER::Gender::FEMALE);
//                break;
//            }
//            case (4): {
//                newReader.SetStatus(data[i] == "BANNED" ? READER::ReaderStatus::BANNED : READER::ReaderStatus::ACTIVE);
//                break;
//            }
//            case (5): {
//                int borrowedBooksCount = std::stoi(data[i]);
//                if (borrowedBooksCount == 0) //* Case where the reader did not borrowed any book!
//                {
//                    newReader.SetBooksCirculation(DOUBLE_LINKED_LIST::Controller());
//                }
//                else //* Case where the reader borrowed at least one book!
//                {
//                    DOUBLE_LINKED_LIST::Controller newBorrowedBooksList;
//                    DOUBLE_LINKED_LIST::Initialize(newBorrowedBooksList);
//
//                    while (database && borrowedBooksCount--) {
//                        BOOK_CIRCULATION::BookCirculation newBorrowedBook{};
//
//                        std::string borrowedBookData{};
//                        std::getline(database, borrowedBookData);
//
//                        if (borrowedBookData.length() == 0) {
//                            std::cerr << std::format("[ERROR] Empty book list data in database!\n");
//                            exit(1);
//                        }
//
//                        std::string* items = nullptr;
//                        int itemCount = 0;
//                        STR::Extract(borrowedBookData, ", ", items, itemCount);
//
//                        newBorrowedBook.SetID(items[0]);
//                        newBorrowedBook.SetBorrowDate(HELPER::Date(items[1]));
//                        newBorrowedBook.SetReturnDate(HELPER::Date(items[2]));
//
//                        if (items[3] == "BORROWING")
//                        {
//                            newBorrowedBook.SetStatus(BOOK_CIRCULATION::CirculationStatus::BORROWING);
//                        }
//                        else if (items[3] == "RETURNED")
//                        {
//                            newBorrowedBook.SetStatus(BOOK_CIRCULATION::CirculationStatus::RETURNED);
//                        }
//                        else if (items[3] == "LOSTED")
//                        {
//                            newBorrowedBook.SetStatus(BOOK_CIRCULATION::CirculationStatus::LOSTED);
//                        }
//                        DOUBLE_LINKED_LIST::PushBack(newBorrowedBooksList, newBorrowedBook);
//                    }
//
//                    newReader.SetBooksCirculation(newBorrowedBooksList);
//                }
//                break;
//            }
//            }
//        }
//
//        tree->Insert(newReader.GetID(), newReader);
//    }
//
//    databaseBuffer.close();
//
//    return true;
//}

bool READER_MODULES::LoadDanhSachTheDocGiaFromDB(const std::string& filename, AVL_TREE::Pointer& root)
{
    std::filebuf databaseBuffer{};

    if (!databaseBuffer.open(filename, std::ios::in))
    {
        throw std::logic_error(std::format("[ERROR] Can not open file {}\n", filename));
    }

    std::istream database(&databaseBuffer);
    while (database)
    {
        std::string titleData{};
        std::getline(database, titleData);

        if (titleData.length() == 0)
        {
            continue;
        }

        std::string* data = nullptr;
        int dataCount = 0;
        STR::Extract(titleData, ", ", data, dataCount);

        READER::Reader newReader;

        for (int i = 0; i < dataCount; ++i)
        {
            switch (i)
            {
            case (0): {
                newReader.SetID(std::stoi(data[i]));
                break;
            }
            case (1): {
                newReader.SetFirstName(data[i]);
                break;
            }
            case (2): {
                newReader.SetLastName(data[i]);
                break;
            }
            case (3): {
                newReader.SetGender(data[i] == "MALE" ? READER::Gender::MALE : READER::Gender::FEMALE);
                break;
            }
            case (4): {
                newReader.SetStatus(data[i] == "BANNED" ? READER::ReaderStatus::BANNED : READER::ReaderStatus::ACTIVE);
                break;
            }
            case (5): {
                int borrowedBooksCount = std::stoi(data[i]);
                if (borrowedBooksCount == 0) //* Case where the reader did not borrowed any book!
                {
                    newReader.SetBooksCirculation(DOUBLE_LINKED_LIST::Controller());
                }
                else //* Case where the reader borrowed at least one book!
                {
                    DOUBLE_LINKED_LIST::Controller newBorrowedBooksList;
                    DOUBLE_LINKED_LIST::Initialize(newBorrowedBooksList);

                    while (database && borrowedBooksCount--) {
                        BOOK_CIRCULATION::BookCirculation newBorrowedBook{};

                        std::string borrowedBookData{};
                        std::getline(database, borrowedBookData);

                        if (borrowedBookData.length() == 0) {
                            std::cerr << std::format("[ERROR] Empty book list data in database!\n");
                            exit(1);
                        }

                        std::string* items = nullptr;
                        int itemCount = 0;
                        STR::Extract(borrowedBookData, ", ", items, itemCount);

                        newBorrowedBook.SetID(items[0]);
                        newBorrowedBook.SetBorrowDate(HELPER::Date(items[1]));
                        newBorrowedBook.SetReturnDate(HELPER::Date(items[2]));

                        if (items[3] == "BORROWING")
                        {
                            newBorrowedBook.SetStatus(BOOK_CIRCULATION::CirculationStatus::BORROWING);
                        }
                        else if (items[3] == "RETURNED")
                        {
                            newBorrowedBook.SetStatus(BOOK_CIRCULATION::CirculationStatus::RETURNED);
                        }
                        else if (items[3] == "LOSTED")
                        {
                            newBorrowedBook.SetStatus(BOOK_CIRCULATION::CirculationStatus::LOSTED);
                        }
                        DOUBLE_LINKED_LIST::PushBack(newBorrowedBooksList, newBorrowedBook);
                    }

                    newReader.SetBooksCirculation(newBorrowedBooksList);
                }
                break;
            }
            }
        }

        if (root == nullptr)
        {
            root = new AVL_TREE::Node;
            root->info = newReader;
        }
        else
        {
            AVL_TREE::Insert(root, newReader);
        }
    }

    databaseBuffer.close();

    return true;
}

//bool READER_MODULES::UpdateListToDatabase(const std::string& filename, AVL_Tree<READER::Reader, int>* tree)
//{
//    std::cerr << "[LOG] Updating reader list to database!\n";
//
//    std::filebuf databaseBuffer{};
//
//    if (!databaseBuffer.open(filename, std::ios::out))
//    {
//        throw std::logic_error(std::format("[ERROR] Can not open file {}\n", filename));
//    }
//
//    std::ostream database(&databaseBuffer);
//
//    Stack<AVL_Tree<READER::Reader, int>::Node*> stk;
//
//    AVL_Tree<READER::Reader, int>::Node* p = tree->GetRoot();
//
//    do {
//        while (p != nullptr) {
//            stk.Push(p);
//            p = p->left_;
//        }
//
//        if (stk.Empty() == false) {
//            p = stk.Pop();
//
//            database << p->info_.GetID() << ", ";
//            database << p->info_.GetFirstName() << ", ";
//            database << p->info_.GetLastName() << ", ";
//            database << p->info_.StringifyGender() << ", ";
//            database << p->info_.StringfyStatus() << ", ";
//
//            if (DOUBLE_LINKED_LIST::Empty(p->info_.GetBooksCirculation())) {
//                database << 0 << "\n";
//            }
//            else {
//                DOUBLE_LINKED_LIST::Controller lst = p->info_.GetBooksCirculation();
//                int listSize = DOUBLE_LINKED_LIST::Size(lst);
//                database << listSize << "\n";
//                for (DOUBLE_LINKED_LIST::Pointer currentNode = lst.First; currentNode != nullptr; currentNode = currentNode->right)
//                {
//                    database << currentNode->info.GetID() << ", " << currentNode->info.GetBorrowDate().Stringify() << ", " << currentNode->info.GetReturnDate().Stringify() << ", " << currentNode->info.StringfyStatus() << "\n";
//                }
//            }
//
//            p = p->right_;
//        }
//        else {
//            break;
//        }
//    } while (true);
//
//    databaseBuffer.close();
//    return true;
//}

bool READER_MODULES::UpdateListToDatabase(const std::string& filename, AVL_TREE::Pointer& root)
{
    std::cerr << "[LOG] Updating reader list to database!\n";

    std::filebuf databaseBuffer{};

    if (!databaseBuffer.open(filename, std::ios::out))
    {
        throw std::logic_error(std::format("[ERROR] Can not open file {}\n", filename));
    }

    std::ostream database(&databaseBuffer);

    Stack<AVL_TREE::Pointer> stk;

    AVL_TREE::Pointer p = root;

    do {
        while (p != nullptr) {
            stk.Push(p);
            p = p->left;
        }

        if (stk.Empty() == false) {
            p = stk.Pop();

            database << p->info.GetID() << ", ";
            database << p->info.GetFirstName() << ", ";
            database << p->info.GetLastName() << ", ";
            database << p->info.StringifyGender() << ", ";
            database << p->info.StringfyStatus() << ", ";

            if (DOUBLE_LINKED_LIST::Empty(p->info.GetBooksCirculation())) {
                database << 0 << "\n";
            }
            else {
                DOUBLE_LINKED_LIST::Controller lst = p->info.GetBooksCirculation();
                int listSize = DOUBLE_LINKED_LIST::Size(lst);
                database << listSize << "\n";
                for (DOUBLE_LINKED_LIST::Pointer currentNode = lst.First; currentNode != nullptr; currentNode = currentNode->right)
                {
                    database << currentNode->info.GetID() << ", " << currentNode->info.GetBorrowDate().Stringify() << ", " << currentNode->info.GetReturnDate().Stringify() << ", " << currentNode->info.StringfyStatus() << "\n";
                }
            }

            p = p->right;
        }
        else {
            break;
        }
    } while (true);

    databaseBuffer.close();
    return true;
}

//int READER_MODULES::GetIndex(const std::string& filename, AVL_Tree<READER::Reader, int>* tree)
//{
//    std::filebuf databaseBuffer{};
//
//    if (!databaseBuffer.open(filename, std::ios::in))
//    {
//        std::cerr << std::format("[ERROR] Can not open file {}\n", filename);
//        return false;
//    }
//
//    int attributeCount = tree->Size();
//    std::istream database(&databaseBuffer);
//
//    for (int i = 0, tmp = 0; i < attributeCount; ++i, database >> tmp);
//    std::string nextIndex{};
//    database >> nextIndex;
//
//    databaseBuffer.close();
//    return std::stoi(nextIndex);
//}

int READER_MODULES::GetIndex(const std::string& filename, AVL_TREE::Pointer root)
{
    std::filebuf databaseBuffer{};

    if (!databaseBuffer.open(filename, std::ios::in))
    {
        std::cerr << std::format("[ERROR] Can not open file {}\n", filename);
        return false;
    }

    int attributeCount = 0;
    AVL_TREE::Size(root, attributeCount);
    std::istream database(&databaseBuffer);

    for (int i = 0, tmp = 0; i < attributeCount; ++i, database >> tmp);
    std::string nextIndex{};
    database >> nextIndex;

    databaseBuffer.close();
    return std::stoi(nextIndex);
}

void READER_MODULES::SortByName(const AVL_TREE::Pointer& root, LinearList<AVL_TREE::Pointer>& readerPointersArr)
{
    int treeSize{ 0 };
    AVL_TREE::Size(root, treeSize);

    readerPointersArr = LinearList<AVL_TREE::Pointer>(treeSize);

    Stack<AVL_TREE::Pointer> stk;
    AVL_TREE::Pointer p = root;
    do {
        while (p != nullptr) {
            stk.Push(p);
            p = p->left;
        }

        if (stk.Empty() == false) {
            p = stk.Pop();
            readerPointersArr.PushBack(p);
            p = p->right;
        }
        else {
            break;
        }
    } while (true);

    std::string valueA{}, valueB{};
    for (int i = 0; i < treeSize - 1; ++i)
    {
        for (int j = i + 1; j < treeSize; ++j)
        {
            valueA = readerPointersArr[i]->info.GetLastName() + " " + readerPointersArr[i]->info.GetFirstName();
            valueB = readerPointersArr[j]->info.GetLastName() + " " + readerPointersArr[j]->info.GetFirstName();

            if (valueA.compare(valueB) > 0)
            {
                std::swap(readerPointersArr[i], readerPointersArr[j]);
            }
        }
    }
}

/*
* The algorithm is that we first create an array contains the pointer of all the node of the tree.
* Then we sort the array by comparing the value which the pointer pointed to and interchange the position of the element in the array
* without changing the positon of the node of the tree.
*
! Currently, Selection sort is used! Therefore the time complexcity if very high!
*/
//void READER_MODULES::SortByName(const AVL_Tree<READER::Reader, int>& tree, LinearList<AVL_Tree<READER::Reader, int>::Node*>& readerPointersArr)
//{
//    tree.CastToLinearList(readerPointersArr);
//
//    int arrSize = readerPointersArr.Size();
//    std::string valueA{}, valueB{};
//    for (int i = 0; i < arrSize - 1; ++i)
//    {
//        for (int j = i + 1; j < arrSize; ++j)
//        {
//            valueA = readerPointersArr[i]->info_.GetLastName() + " " + readerPointersArr[i]->info_.GetFirstName();
//            valueB = readerPointersArr[j]->info_.GetLastName() + " " + readerPointersArr[j]->info_.GetFirstName();
//
//            if (valueA.compare(valueB) > 0)
//            {
//                std::swap(readerPointersArr[i], readerPointersArr[j]);
//            }
//        }
//    }
//}

int BOOK_CIRCULATION_MODULES::CountBorrowedBooks(const DOUBLE_LINKED_LIST::Controller& list)
{
    int counter = 0;
    for (DOUBLE_LINKED_LIST::Pointer p = list.First; p != nullptr; p = p->right)
    {
        if (p->info.GetStatus() == BOOK_CIRCULATION::CirculationStatus::BORROWING)
        {
            ++counter;
        }
    }
    return counter;
}