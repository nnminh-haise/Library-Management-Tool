#pragma once

#include <string>

namespace BOOK 
{
	enum Status { AVAILABLE, UNAVAILABLE, SOLD };

	class Book 
	{
	public:
		Book();

		Book(std::string id, Status status, std::string description);

		Book(const Book& other);

		Book& operator=(const Book& other);

		void SetID(std::string id);

		std::string GetID();

		void SetStatus(Status status);

		Status GetStatus();

		std::string StringfyStatus();

		void SetDescription(std::string description);

		std::string GetDescription();

	private:
		std::string id;
		Status status = AVAILABLE;
		std::string description;
	};
}

namespace LINKED_LIST 
{
	struct Node 
	{
		BOOK::Book info;
		Node* next;

		Node();

		Node(BOOK::Book info, Node* next);
	};

	typedef Node* Pointer;

	void Initialize(Pointer& first);

	bool Empty(const Pointer& first);

	int Size(const Pointer& first);

	void PushFront(Pointer& first, BOOK::Book item);

	void PushBack(Pointer& first, BOOK::Book item);

	void Append(Pointer& first, Pointer& target);

	bool DeleteAt(Pointer& first, BOOK::Book item);

	BOOK::Book* SearchByID(Pointer& first, const std::string& id);
}

namespace BOOK_TITLE 
{
	class BookTitle 
	{
	private:
		std::string isbn;
		std::string title;
		int pageCount;
		std::string author;
		int publiationYear;
		std::string category;
		LINKED_LIST::Pointer catalogue;

	public:
		BookTitle();

		BookTitle(std::string isbn, std::string title, int pageCount, std::string author, int publiationYear, std::string category, LINKED_LIST::Pointer catalogue);

		void SetISBN(std::string isbn);

		std::string GetISBN();

		void SetTitle(std::string title);

		std::string GetTitle();

		void SetPageCount(int sotrang);

		int GetPageCount();
		
		void SetAuthor(std::string author);

		std::string GetAuthor();

		void SetPublicationYear(int publiationYear);

		int GetPublicationYear();

		void SetCategory(std::string category);

		std::string GetCategory();

		void SetCatalogue(LINKED_LIST::Pointer catalogue);

		LINKED_LIST::Pointer GetCatalogue();

		void Log();
	};
}

namespace LINEAR_LIST 
{
	const unsigned int MAX_SIZE = 10000;

	struct LinearList 
	{
		unsigned int numberOfNode;
		BOOK_TITLE::BookTitle* nodes[MAX_SIZE];

		LinearList();
	};

	void Initialize(LinearList& list);

	bool Empty(const LinearList& list);

	bool IsFull(const LinearList& list);

	bool PushFront(LinearList& list, BOOK_TITLE::BookTitle* item);

	bool InsertItem(LinearList& list, BOOK_TITLE::BookTitle* item, int position);

	bool PushBack(LinearList& list, BOOK_TITLE::BookTitle* item);

	bool InsertOrder(LinearList& list, BOOK_TITLE::BookTitle* item);

	void Traversal(const LinearList& list);

	BOOK_TITLE::BookTitle* SearchByName(const LinearList& list, const std::string& titleName);

	BOOK_TITLE::BookTitle* SearchByISBN(const LinearList& list, const std::string& isbn);
}

namespace DAU_SACH_MODULES 
{
	bool LoadDanhSachDauSachFromDB(std::string filename, LINEAR_LIST::LinearList& danhSachDauSach);

	bool UpdateListToDatabase(const std::string& filename, const LINEAR_LIST::LinearList& titleList);

	void DuplicateList(const LINEAR_LIST::LinearList& titleList, LINEAR_LIST::LinearList& destinationList);

	
}
