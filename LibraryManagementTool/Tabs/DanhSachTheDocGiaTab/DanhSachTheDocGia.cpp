#include "DanhSachTheDocGia.h"
#include "DanhSachTheDocGiaStyling.h"

#include "../../Graphics/graphics.h"
#include "../../Helper/Helper.h"
#include "../../Helper/IndexGenerator.h"
#include "../../Helper/ConstantsAndGlobalVariables.h"
#include "../../TheDocGia/TheDocGia.h"
#include "../../DataStructures/Stack.h"

#include <iostream>
#include <format>
#include <string>

DanhSachTheDocGiaView::DanhSachTheDocGiaView()
{
	this->Initialize();
}

DanhSachTheDocGiaView::DanhSachTheDocGiaView(Package* package)
{
	this->package_ = package;

	this->Initialize();

	this->mainView_.SetPackage(package);
}

void DanhSachTheDocGiaView::Activate()
{
	this->status_ = true;

	this->mainView_.Activate();
}

void DanhSachTheDocGiaView::Deactivate()
{
	this->status_ = false;
	
	this->mainView_.Deactivate();

	this->Reset();
}

bool DanhSachTheDocGiaView::InActive()
{
	return this->status_ == true;
}

int DanhSachTheDocGiaView::Run()
{
	if (!this->status_) { return 0; }

	if (this->mainView_.InActive())
	{
		int mainViewRunningResult = this->mainView_.Run();
	}

	return 0;
}

void DanhSachTheDocGiaView::Reset()
{
	this->Initialize();
}

void DanhSachTheDocGiaView::Initialize()
{
	this->InitializeElements();
}

void DanhSachTheDocGiaView::InitializeElements()
{
}

READER_TAB_MEMBERS::MainView::MainView()
{
	this->readerTableSortedByNamePackage_.Deactivate();

	this->Initialize();
}

void READER_TAB_MEMBERS::MainView::SetPackage(Package* package)
{
	this->package_ = package;

	std::cerr << "[LOG] Main view's package SET! (READER_TAB_MEMBERS::MainView::SetPackage)\n";

	this->InitializeFilters();

	this->CreateSortedByNameReaderList();

	this->InitializeReaderTable();

	this->InitializeSearchBox();

	this->readerDetails_.SetPackage(this->package_);

	this->tools_.SetPackage(this->package_);
	this->tools_.SetReaderList(this->package_->readerList);

	this->bookCirculationView_.SetPackage(this->package_);

	std::cerr << "[LOG] Set package's pointer CLOSE! (READER_TAB_MEMBERS::MainView::SetPackage)\n";
}

void READER_TAB_MEMBERS::MainView::Activate()
{
	this->status_ = true;

	this->searchBox_.Activate();

	this->readerTablePackage_.Activate();

	this->tableSelectedObject_.Activate();

	this->tools_.Activate();
}

void READER_TAB_MEMBERS::MainView::Deactivate()
{
	this->status_ = false;

	this->searchBox_.Deactivate();

	this->readerTablePackage_.Deactivate();

	this->tableSelectedObject_.Deactivate();

	this->tools_.Deactivate();

	this->Reset();
}

bool READER_TAB_MEMBERS::MainView::InActive()
{
	return this->status_ == true;
}

int READER_TAB_MEMBERS::MainView::Run()
{
	if (!this->status_) { return 0; }

	if (this->readerTablePackage_.InActive()) //* Right clicked from the table
	{
		int readerTableRunnngResult = this->readerTablePackage_.Run();
		if (readerTableRunnngResult)
		{
			this->tools_.SetCurrentReader(this->tableSelectedObject_.GetObjectPointer());
			this->readerDetails_.Activate();
			this->readerDetails_.SetReader(this->tableSelectedObject_.GetObjectPointer());
			this->bookCirculationView_.SetReader(this->tableSelectedObject_.GetObjectPointer());
			this->bookCirculationView_.Activate();
		}
	}

	if (this->readerTableSortedByNamePackage_.InActive())
	{
		int readerTableRunnngResult = this->readerTableSortedByNamePackage_.Run();
		if (readerTableRunnngResult)
		{
			this->tools_.SetCurrentReader(this->tableSelectedObject_.GetObjectPointer());
			this->readerDetails_.Activate();
			this->readerDetails_.SetReader(this->tableSelectedObject_.GetObjectPointer());
			this->bookCirculationView_.SetReader(this->tableSelectedObject_.GetObjectPointer());
			this->bookCirculationView_.Activate();
		}
	}

	if (this->bookCirculationView_.InActive())
	{
		this->bookCirculationView_.Run();
	}

	this->SortingOptionsSelectorOnAction();

	if (this->tableSelectedObject_.InActive())
	{
		int selectedObjectIndicatorRunningResult = this->tableSelectedObject_.Run();
		if (selectedObjectIndicatorRunningResult) //* Left clicked from the indicator button
		{
			this->readerDetails_.Activate();
			this->readerDetails_.SetReader(this->tableSelectedObject_.GetObjectPointer());
			this->bookCirculationView_.SetReader(this->tableSelectedObject_.GetObjectPointer());
			this->bookCirculationView_.Activate();
		}
		this->tools_.SetCurrentReader(this->tableSelectedObject_.GetObjectPointer());
	}

	if (this->searchBox_.InActive())
	{
		int searchBoxRunningResult = this->searchBox_.Run();
		if (searchBoxRunningResult)
		{
			std::cerr << "[LOG] UPDATE READER DEFAULT TABLE!\n";
			this->readerTablePackage_.AllowCreateDatasheet();
			this->readerTablePackage_.CreateDatasheet();
		}
	}

	if (this->secondSearchBox_.InActive())
	{
		int searchBoxRunningResult = this->secondSearchBox_.Run();
		if (searchBoxRunningResult)
		{
			std::cerr << "[LOG] UPDATE READER SORTED TABLE!\n";
			this->readerTableSortedByNamePackage_.AllowCreateDatasheet();
			this->readerTableSortedByNamePackage_.CreateDatasheet();
		}
	}

	if (this->tools_.InActive())
	{
		int toolRunningResult = this->tools_.Run();
		if (toolRunningResult != 0)
		{
			switch (toolRunningResult)
			{
				case (1): {
					this->readerDetails_.SetMode(1);
					this->readerDetails_.SetReader(nullptr);
					this->readerDetails_.Activate();
					this->GetNewReaderIndex();
					break;
				}
				case (2): {
					this->readerUpdateProcess_.Activate();
					this->readerUpdateProcess_.SetReader(this->tableSelectedObject_.GetObjectPointer());
					this->readerUpdateProcess_.SetDetailCard(&this->readerDetails_);
					this->readerDetails_.SetMode(1);
					break;
				}
				case (3): {
					std::cerr << "deleting a reader!\n";
					this->readerDetails_.SetMode(2);
					this->readerDetails_.SetReader(this->tableSelectedObject_.GetObjectPointer());
					this->readerDetails_.Activate();
					break;
				}
			}
		}

		int inUsedTool = this->tools_.InUsedTool();
		if (this->searchBox_.InActive())
		{
			InUsedToolProcessingForDefaultTable(inUsedTool);
		}
		else
		{
			InUsedToolProcessingForSortedTable(inUsedTool);
		}
	}

	if (this->readerDetails_.InActive())
	{
		this->readerDetails_.Run();
	}

	return 0;
}

void READER_TAB_MEMBERS::MainView::Reset()
{
	this->tools_.Reset();

	this->readerDetails_.Reset();

	this->tableSelectedObject_.SetObjectPointer(nullptr);

	this->bookCirculationView_.Deactivate();
}

void READER_TAB_MEMBERS::MainView::Initialize()
{
	this->tools_.Reset();

	this->InitializeElements();
}

void READER_TAB_MEMBERS::MainView::InitializeElements()
{
	this->readerTableSortedByNamePackage_.Deactivate();

	this->tableSelectedObject_.Activate();

	this->tools_.Activate();
	this->tools_.SetCurrentReader(nullptr);

	this->tableSelectedObject_.AccessIndicator().SetTopLeft({406, 940});
	this->tableSelectedObject_.AccessIndicator().UpdateWithNewTopLeft();

	this->readerDetails_.Deactivate();
	this->readerDetails_.SetReader(nullptr);
}

void READER_TAB_MEMBERS::MainView::InitializeFilters()
{
	if (this->package_ == nullptr)
	{
		std::cerr << "[ERROR] Package's pointer is NULL! (READER_TAB_MEMBERS::MainView::CreateSortedByNameReaderList)\n";

		throw std::logic_error("[ERROR] Package's pointer is NULL! (READER_TAB_MEMBERS::MainView::CreateSortedByNameReaderList)\n");
	}

	int readerListSize{ 0 };
	AVL_TREE::Size(*this->package_->readerList, readerListSize);

	this->defaultReaderListFilter_.filterSize_ = readerListSize;
	this->defaultReaderListFilter_.keep_ = readerListSize;
	this->defaultReaderListFilter_.filters_ = new bool[readerListSize];
	for (int i = 0; i < readerListSize; ++i)
	{
		this->defaultReaderListFilter_.filters_[i] = true;
	}
	std::cerr << "[LOG] Created default list's filters!\n";

	this->sortedByNameReaderListFilter_.filterSize_ = readerListSize;
	this->sortedByNameReaderListFilter_.keep_ = readerListSize;
	this->sortedByNameReaderListFilter_.filters_ = new bool[readerListSize];
	for (int i = 0; i < readerListSize; ++i)
	{
		this->sortedByNameReaderListFilter_.filters_[i] = true;
	}
	std::cerr << "[LOG] Created sorted list's filters!\n";
}

void READER_TAB_MEMBERS::MainView::InitializeReaderTable()
{
	if (this->package_ == nullptr)
	{
		std::cerr << "[ERROR] Package's pointer is NULL! (READER_TAB_MEMBERS::MainView::CreateSortedByNameReaderList)\n";

		throw std::logic_error("[ERROR] Package's pointer is NULL! (READER_TAB_MEMBERS::MainView::CreateSortedByNameReaderList)\n");
	}

	std::cerr << "[LOG] Creating reader TABLE!\n";

	this->readerTablePackage_.Activate();
	this->readerTablePackage_.SetDataList(this->package_->readerList);
	this->readerTablePackage_.SetDataFilter(&this->defaultReaderListFilter_);
	this->readerTablePackage_.SetSelectedObjectContainer(&this->tableSelectedObject_);
	this->readerTablePackage_.AllowCreateDatasheet();
	this->readerTablePackage_.CreateDatasheet();

	this->readerTableSortedByNamePackage_.SetDataList(&this->sortedByNameReaderList_);
	this->readerTableSortedByNamePackage_.SetDataFilter(&this->defaultReaderListFilter_);
	this->readerTableSortedByNamePackage_.SetSelectedObjectContainer(&this->tableSelectedObject_);

	std::cerr << "[LOG] Created reader TABLE!\n";
}

void READER_TAB_MEMBERS::MainView::InitializeSearchBox()
{
	if (this->package_ == nullptr)
	{
		std::cerr << "[ERROR] Package's pointer is NULL! (READER_TAB_MEMBERS::MainView::CreateSortedByNameReaderList)\n";

		throw std::logic_error("[ERROR] Package's pointer is NULL! (READER_TAB_MEMBERS::MainView::CreateSortedByNameReaderList)\n");
	}

	std::cerr << "[LOG] Creating search box!\n";

	this->searchBox_.SetPackage(this->package_);
	this->searchBox_.SetReaderDatasheetPackage(&this->readerTablePackage_);
	this->searchBox_.SetSearchData(this->package_->readerList);
	this->searchBox_.Activate();

	this->secondSearchBox_.SetPackage(this->package_);
	this->secondSearchBox_.SetReaderDatasheetPackage(&this->readerTableSortedByNamePackage_);
	this->secondSearchBox_.SetSearchData(&this->sortedByNameReaderList_);
	this->secondSearchBox_.Deactivate();

	std::cerr << "[LOG] Created search box!\n";
}

void READER_TAB_MEMBERS::MainView::CreateSortedByNameReaderList()
{
	if (this->package_ == nullptr)
	{
		std::cerr << "[ERROR] Package's pointer is NULL! (READER_TAB_MEMBERS::MainView::CreateSortedByNameReaderList)\n";

		throw std::logic_error("[ERROR] Package's pointer is NULL! (READER_TAB_MEMBERS::MainView::CreateSortedByNameReaderList)\n");
	}

	std::cerr << "[LOG] Creating reader list sorted by name!\n";

	int readerListSize{ 0 };
	AVL_TREE::Size(*this->package_->readerList, readerListSize);
	this->sortedByNameReaderList_ = LinearList<AVL_TREE::Pointer>(readerListSize);

	Stack<AVL_TREE::Pointer> pointerStack;
	AVL_TREE::Pointer currentNode = *this->package_->readerList;
	do {
		while (currentNode != nullptr) {
			pointerStack.Push(currentNode);
			currentNode = currentNode->left;
		}

		if (pointerStack.Empty() == false) {
			currentNode = pointerStack.Pop();

			this->sortedByNameReaderList_.PushBack(currentNode);

			currentNode = currentNode->right;
		}
		else {
			break;
		}
	} while (true);

	std::string fullnameI{}, fullnameJ{};
	for (int i = 0; i < readerListSize - 1; ++i)
	{
		for (int j = i + 1; j < readerListSize; ++j)
		{
			fullnameI = this->sortedByNameReaderList_[i]->info.GetLastName() + " " + this->sortedByNameReaderList_[i]->info.GetFirstName();
			fullnameJ = this->sortedByNameReaderList_[j]->info.GetLastName() + " " + this->sortedByNameReaderList_[j]->info.GetFirstName();

			if (fullnameI.compare(fullnameJ) > 0)
			{
				std::swap(this->sortedByNameReaderList_[i], this->sortedByNameReaderList_[j]);
			}
		}
	}

	std::cerr << "[LOG] Created reader list sorted by name!\n";
}

bool READER_TAB_MEMBERS::MainView::ReaderDetailInputValidation()
{
	Button& firstNameField = this->readerDetails_.AccessFields(0).content_;
	Button& lastNameField = this->readerDetails_.AccessFields(1).content_;
	std::string firstName = firstNameField.GetPlaceholder();
	std::string lastName = lastNameField.GetPlaceholder();

	if (firstName.compare("Nguyen Van") == 0 || firstName.length() == 0)
	{
		return false;
	}

	if (lastName.compare("Vu") == 0 || lastName.length() == 0)
	{
		return false;
	}

	return true;
}

void READER_TAB_MEMBERS::MainView::GetNewReaderIndex()
{
	IndexGenerator gen(100000);
	int usedIndexCount = gen.GetUsedIndexCount(CONSTANTS::READER_INDICIES);
	this->newIndex_ = gen.FromFileGetIndexAt(CONSTANTS::READER_INDICIES, usedIndexCount + 1);
	gen.SetUsedIndexCount(CONSTANTS::READER_INDICIES, usedIndexCount + 1);

	this->readerDetails_.AccessFields(2).content_.SetPlaceholder(std::to_string(this->newIndex_));
	this->readerDetails_.AccessFields(3).content_.SetPlaceholder("ACTIVE");
}

void READER_TAB_MEMBERS::MainView::CreateNewReaderProcess()
{
	READER::Reader newReader;
	newReader.SetFirstName(this->readerDetails_.AccessFields(0).content_.GetPlaceholder());
	newReader.SetLastName(this->readerDetails_.AccessFields(1).content_.GetPlaceholder());
	newReader.SetGender(this->readerDetails_.AccessFields(4).content_.GetPlaceholder() == "MALE" ? READER::Gender::MALE : READER::Gender::FEMALE);
	newReader.SetID(this->newIndex_);
	newReader.SetStatus(READER::ReaderStatus::ACTIVE);

	AVL_TREE::Pointer newNode = new AVL_TREE::Node;
	newNode->info = newReader;

	int nullTree = AVL_TREE::Empty(*this->package_->readerList);
	if (nullTree)
	{
		AVL_TREE::Pointer newNode = new AVL_TREE::Node;
		newNode->info = newReader;
		newNode->balanceFactor = 0;
		newNode->height = 1;
		newNode->left = newNode->right = nullptr;

		*this->package_->readerList = newNode;
	}
	else
	{
		AVL_TREE::Insert(*this->package_->readerList, newReader);
	}
}

void READER_TAB_MEMBERS::MainView::SortingOptionsSelectorOnAction()
{
	if (!this->status_) { return; }

	if (this->readerTableSortedByNamePackage_.InActive())
	{
		Button& readerID = this->readerTableSortedByNamePackage_.AccessCurrentDatasheet()[0][1];
		if (readerID.IsHover())
		{
			readerID.SetTextColor(rgb(241, 246, 249));
			readerID.SetFillColor(rgb(33, 42, 62));
			readerID.SetBorderColor(rgb(33, 42, 62));
		}
		else if (readerID.LeftMouseClicked())
		{
			delay(130);

			std::cerr << "[LOG] SWITCH TO DEFAULT READER TABLE!\n";
			this->readerTablePackage_.SetDataFilter(&this->defaultReaderListFilter_);
			this->readerTablePackage_.SetDataList(this->package_->readerList);
			this->readerTablePackage_.AllowCreateDatasheet();
			this->readerTablePackage_.CreateDatasheet();
			this->readerTablePackage_.Activate();
			this->searchBox_.Activate();
			this->readerTableSortedByNamePackage_.Deactivate();
			this->secondSearchBox_.Deactivate();
		}
		else
		{
			readerID.SetTextColor(BLACK);
			readerID.SetFillColor(rgb(210, 218, 255));
			readerID.SetBorderColor(BLACK);
		}
	}

	if (this->readerTablePackage_.InActive())
	{
		Button& readerName = this->readerTablePackage_.AccessCurrentDatasheet()[0][3];
		if (readerName.IsHover())
		{
			readerName.SetTextColor(rgb(241, 246, 249));
			readerName.SetFillColor(rgb(33, 42, 62));
			readerName.SetBorderColor(rgb(33, 42, 62));
		}
		else if (readerName.LeftMouseClicked())
		{
			delay(130);

			std::cerr << "[LOG] SWITCH TO SORTED BY NAME READER TABLE!\n";
			this->readerTableSortedByNamePackage_.Activate();
			this->readerTableSortedByNamePackage_.SetDataFilter(&this->sortedByNameReaderListFilter_);
			this->readerTableSortedByNamePackage_.SetDataList(&this->sortedByNameReaderList_);
			this->readerTableSortedByNamePackage_.AllowCreateDatasheet();
			this->readerTableSortedByNamePackage_.CreateDatasheet();
			this->secondSearchBox_.Activate();
			this->readerTablePackage_.Deactivate();
			this->searchBox_.Deactivate();
		}
		else
		{
			readerName.SetTextColor(BLACK);
			readerName.SetFillColor(rgb(210, 218, 255));
			readerName.SetBorderColor(BLACK);
		}
	}
}

void READER_TAB_MEMBERS::MainView::InUsedToolProcessingForDefaultTable(int inUsedTool)
{
	switch (inUsedTool)
	{
		case (1): {
			this->readerUpdateProcess_.Deactivate();

			int saveSignal = this->readerDetails_.SaveButtonOnAction();

			//* CREATE new reader processs
			if (saveSignal && this->ReaderDetailInputValidation())
			{
				this->CreateNewReaderProcess();
				auto tmp = AVL_TREE::SearchByKey(*this->package_->readerList, this->newIndex_);
				this->tableSelectedObject_.SetObjectPointer(tmp);
				this->readerDetails_.SetReader(tmp);

				//* Reset and deactivate tool
				this->tools_.SetInUsedTool(-1);

				//* Re-create table
				std::cerr << "[LOG] AFTER UPDATED READER INFO: UPDATE READER TABLE!\n";
				this->readerTablePackage_.SetDataList(this->package_->readerList);
				this->InitializeFilters();
				this->readerTablePackage_.AllowCreateDatasheet();
				this->readerTablePackage_.CreateDatasheet();
			}

			break;
		}
		case (2): {
			this->readerUpdateProcess_.Run();
			int savesignal = this->readerDetails_.SaveButtonOnAction();

			//* READER's detail UPDATE process
			if (savesignal)
			{
				//* Saving infomation
				AVL_TREE::Pointer targetingReader = this->tableSelectedObject_.GetObjectPointer();
				std::string newFirstName = this->readerDetails_.AccessFields(0).content_.GetPlaceholder();
				std::string newLastName = this->readerDetails_.AccessFields(1).content_.GetPlaceholder();
				targetingReader->info.SetFirstName(newFirstName);
				targetingReader->info.SetLastName(newLastName);
				targetingReader->info.SetGender(this->readerDetails_.AccessFields(4).content_.GetPlaceholder() == "MALE" ? READER::Gender::MALE : READER::Gender::FEMALE);

				//* Reset and deactivate tool
				this->readerUpdateProcess_.Deactivate();
				this->tools_.SetInUsedTool(-1);

				//* Re-create table
				std::cerr << "[LOG] AFTER UPDATED READER INFO: UPDATE READER TABLE!\n";
				this->readerTablePackage_.AllowCreateDatasheet();
				this->readerTablePackage_.CreateDatasheet();
			}
			break;
		}
		case (3): {
			std::cerr << "DELETE!\n";
			this->readerUpdateProcess_.Deactivate();
			this->readerDetails_.SetMode(2);
			int saveSignal = this->readerDetails_.SaveButtonOnAction();

			//* DELETE reader process
			if (saveSignal)
			{
				int targetedID = this->tableSelectedObject_.GetObjectPointer()->GetKey();
				AVL_TREE::NonrecursiveInOrderTraversal(*this->package_->readerList);
				(*this->package_->readerList) = AVL_TREE::RemoveNode((*this->package_->readerList), targetedID);
				AVL_TREE::NonrecursiveInOrderTraversal(*this->package_->readerList);

				
				std::cerr << "[LOG] AFTER DELETE READER INFO: UPDATE READER TABLE!\n";
				this->InitializeFilters();
				this->readerTablePackage_.SetDataFilter(&this->defaultReaderListFilter_);
				this->readerTablePackage_.SetDataList(this->package_->readerList);
				this->readerTablePackage_.AllowCreateDatasheet();
				this->readerTablePackage_.CreateDatasheet();

				this->bookCirculationView_.Deactivate();
				this->tools_.Reset();
				this->readerDetails_.SetReader(nullptr);
				this->readerDetails_.Deactivate();
				this->tableSelectedObject_.SetObjectPointer(nullptr);
				//this->bookCirculationView_.SetReader(nullptr);
			}

			break;
		}
		default: {
			this->readerUpdateProcess_.Deactivate();
			this->readerDetails_.SetMode(0);
		}
	}
}

void READER_TAB_MEMBERS::MainView::InUsedToolProcessingForSortedTable(int inUsedTool)
{
	switch (inUsedTool)
	{
		case (1): {
			this->readerUpdateProcess_.Deactivate();

			int saveSignal = this->readerDetails_.SaveButtonOnAction();

			//* CREATE new reader processs
			if (saveSignal && this->ReaderDetailInputValidation())
			{
				this->CreateNewReaderProcess();
				auto tmp = AVL_TREE::SearchByKey(*this->package_->readerList, this->newIndex_);
				this->tableSelectedObject_.SetObjectPointer(tmp);
				this->readerDetails_.SetReader(tmp);

				//* Reset and deactivate tool
				this->tools_.SetInUsedTool(-1);

				//* Re-create table
				std::cerr << "[LOG] AFTER UPDATED READER INFO: UPDATE READER TABLE!\n";
				this->readerTableSortedByNamePackage_.SetDataList(&this->sortedByNameReaderList_);
				this->InitializeFilters();
				this->readerTableSortedByNamePackage_.AllowCreateDatasheet();
				this->readerTableSortedByNamePackage_.CreateDatasheet();
			}

			break;
		}
		case (2): {
			this->readerUpdateProcess_.Run();
			int savesignal = this->readerDetails_.SaveButtonOnAction();

			//* READER's detail UPDATE process
			if (savesignal)
			{
				//* Saving infomation
				AVL_TREE::Pointer targetingReader = this->tableSelectedObject_.GetObjectPointer();
				std::string newFirstName = this->readerDetails_.AccessFields(0).content_.GetPlaceholder();
				std::string newLastName = this->readerDetails_.AccessFields(1).content_.GetPlaceholder();
				targetingReader->info.SetFirstName(newFirstName);
				targetingReader->info.SetLastName(newLastName);
				targetingReader->info.SetGender(this->readerDetails_.AccessFields(4).content_.GetPlaceholder() == "MALE" ? READER::Gender::MALE : READER::Gender::FEMALE);

				//* Reset and deactivate tool
				this->readerUpdateProcess_.Deactivate();
				this->tools_.SetInUsedTool(-1);

				//* Re-create table
				std::cerr << "[LOG] AFTER UPDATED READER INFO: UPDATE READER TABLE!\n";
				this->readerTableSortedByNamePackage_.AllowCreateDatasheet();
				this->readerTableSortedByNamePackage_.CreateDatasheet();
			}
			break;
		}
		case (3): {
			std::cerr << "DELETE!\n";
			this->readerUpdateProcess_.Deactivate();
			this->readerDetails_.SetMode(2);
			int saveSignal = this->readerDetails_.SaveButtonOnAction();

			//* DELETE reader process
			if (saveSignal)
			{
				AVL_TREE::RemoveNode(*this->package_->readerList, this->tableSelectedObject_.GetObjectPointer()->GetKey());
				std::cerr << "[LOG] AFTER DELETE READER INFO: UPDATE READER TABLE!\n";
				this->readerTableSortedByNamePackage_.AllowCreateDatasheet();
				this->readerTableSortedByNamePackage_.CreateDatasheet();
			}

			break;
		}
		default: {
			this->readerUpdateProcess_.Deactivate();
			this->readerDetails_.SetMode(0);
		}
	}
}

void READER_TAB_MEMBERS::MainView::Log()
{
	std::cerr << "Package pointer status: " << (this->package_ != nullptr) << "\n";
}

void READER_TAB_MEMBERS::MainView::LogSortedList()
{
	for (int i = 0; i < this->sortedByNameReaderList_.Size(); ++i)
	{
		std::cerr << this->sortedByNameReaderList_[i]->info.GetID() << "\n";
		std::cerr << this->sortedByNameReaderList_[i]->info.GetFullName() << "\n";
	}
}

READER_TAB_MEMBERS::ToolSets::ToolSets()
{
	this->Initialize();
}

void READER_TAB_MEMBERS::ToolSets::Activate()
{
	this->status_ = true;
}

void READER_TAB_MEMBERS::ToolSets::Deactivate()
{
	this->Reset();
	this->status_ = false;
	this->currentReader_ = nullptr;
}

bool READER_TAB_MEMBERS::ToolSets::InActive()
{
	return this->status_ == true;
}

int READER_TAB_MEMBERS::ToolSets::Run()
{
	if (readerList_ == nullptr)
	{
		std::cerr << "[ERROR] Reader list's pointer is NULL!\n";

		throw std::logic_error("[ERROR] Reader list's pointer is NULL!\n");
	}

	if (package_ == nullptr)
	{
		std::cerr << "[ERROR] Package's pointer is NULL!\n";

		throw std::logic_error("[ERROR] Package's pointer is NULL!\n");
	}

	if (!this->status_) { return 0; }

	this->Display();

	int selectedTool = this->ToolButtonsOnAction();
	if (selectedTool != 0)
	{
		return selectedTool;
	}

	return 0;
}

void READER_TAB_MEMBERS::ToolSets::Reset()
{
	this->Initialize();

	this->inUsedTool_ = -1;

	this->currentReader_ = nullptr;
}

void READER_TAB_MEMBERS::ToolSets::SetCurrentReader(AVL_TREE::Pointer currentReader)
{
	if (currentReader == nullptr)
	{
		this->currentReader_ = nullptr;
		return;
	}

	this->currentReader_ = currentReader;
}

AVL_TREE::Pointer READER_TAB_MEMBERS::ToolSets::GetCurrentReader()
{
	return this->currentReader_;;
}

void READER_TAB_MEMBERS::ToolSets::SetReaderList(AVL_TREE::Pointer* readerList)
{
	if (readerList == nullptr)
	{
		std::cerr << "[LOG] Tools Set SET [NULL] reader list!\n";

		this->readerList_ = nullptr;
		return;
	}

	std::cerr << "[LOG] Tools Set SET reader list!\n";

	this->readerList_ = readerList;
}

AVL_TREE::Pointer* READER_TAB_MEMBERS::ToolSets::GetReaderList()
{
	return this->readerList_;
}

void READER_TAB_MEMBERS::ToolSets::SetPackage(Package* package)
{
	if (package == nullptr)
	{
		std::cerr << "[ERROR] Package's pointer is NULL!\n";

		throw std::logic_error("[ERROR] Package's pointer is NULL!\n");
	}

	std::cerr << "[LOG] Tools Set SET package!\n";

	this->package_ = package;
}

void READER_TAB_MEMBERS::ToolSets::SetInUsedTool(int tool)
{
	this->inUsedTool_ = tool;
}

int READER_TAB_MEMBERS::ToolSets::InUsedTool()
{
	return this->inUsedTool_ + 1;
}

void READER_TAB_MEMBERS::ToolSets::Initialize()
{
	this->InitializeElements();
}

void READER_TAB_MEMBERS::ToolSets::InitializeElements()
{
	HELPER::Coordinate topLefts[] = {
		{1016, 210}, {1016, 267}, {1016, 324}
	};
	std::string placeholders[] = { "NEW", "EDIT", "DELETE" };
	for (int i = 0; i < 3; ++i)
	{
		this->toolButtons_[i] = Button(topLefts[i], {80, 47});
		this->toolButtons_[i].SetPlaceholder(placeholders[i]);
		this->toolButtons_[i].SetTextColor(rgb(241, 246, 249));
		this->toolButtons_[i].SetFillColor(rgb(155, 164, 181));
		this->toolButtons_[i].SetBorderColor(rgb(155, 164, 181));
	}
}

int READER_TAB_MEMBERS::ToolSets::Display()
{
	if (!this->status_) { return 0; }

	for (int i = 0; i < 3; ++i)
	{
		this->toolButtons_[i].Display();
	}

	return 0;
}

int READER_TAB_MEMBERS::ToolSets::ToolButtonsOnAction()
{
	if (!this->status_) { return 0; }

	std::string placeholders[] = { "NEW", "EDIT", "DELETE" };

	if (this->currentReader_ == nullptr)
	{
		if (inUsedTool_ != -1)
		{
			for (int i = 0; i < 3; ++i)
			{
				if (i == this->inUsedTool_) { continue; }

				this->toolButtons_[i].SetPlaceholder(placeholders[i]);
				this->toolButtons_[i].SetTextColor(rgb(241, 246, 249));
				this->toolButtons_[i].SetFillColor(rgb(155, 164, 181));
				this->toolButtons_[i].SetBorderColor(rgb(155, 164, 181));
			}

			if (this->toolButtons_[inUsedTool_].IsHover())
			{
				this->toolButtons_[inUsedTool_].SetFillColor(rgb(57, 72, 103));
			}
			else if (this->toolButtons_[inUsedTool_].LeftMouseClicked())
			{
				delay(130);

				this->toolButtons_[inUsedTool_].SetPlaceholder(placeholders[inUsedTool_]);

				this->inUsedTool_ = -1;

				return 0;
			}
			else
			{
				this->toolButtons_[inUsedTool_].SetPlaceholder("Cancel");
				this->toolButtons_[inUsedTool_].SetTextColor(rgb(241, 246, 249));
				this->toolButtons_[inUsedTool_].SetFillColor(rgb(57, 72, 103));
				this->toolButtons_[inUsedTool_].SetBorderColor(rgb(57, 72, 103));
			}
		}
		else
		{
			if (this->toolButtons_[0].IsHover())
			{
				this->toolButtons_[0].SetFillColor(rgb(57, 72, 103));
			}
			else if (this->toolButtons_[0].LeftMouseClicked())
			{
				delay(130);
				this->inUsedTool_ = 0;
				return this->inUsedTool_ + 1;
			}
			else
			{
				this->toolButtons_[0].SetPlaceholder(placeholders[0]);
				this->toolButtons_[0].SetTextColor(rgb(241, 246, 249));
				this->toolButtons_[0].SetFillColor(rgb(155, 164, 181));
				this->toolButtons_[0].SetBorderColor(rgb(155, 164, 181));
			}

			this->inUsedTool_ = -1;
		}

		return 0;
	}

	if (this->inUsedTool_ != -1)
	{
		std::string placeholders[] = { "NEW", "EDIT", "DELETE" };

		for (int i = 0; i < 3; ++i)
		{
			if (i == this->inUsedTool_) { continue; }

			this->toolButtons_[i].SetPlaceholder(placeholders[i]);
			this->toolButtons_[i].SetTextColor(rgb(241, 246, 249));
			this->toolButtons_[i].SetFillColor(rgb(155, 164, 181));
			this->toolButtons_[i].SetBorderColor(rgb(155, 164, 181));
		}

		if (this->toolButtons_[inUsedTool_].IsHover())
		{
			this->toolButtons_[inUsedTool_].SetFillColor(rgb(57, 72, 103));
		}
		else if (this->toolButtons_[inUsedTool_].LeftMouseClicked())
		{
			delay(130);

			this->toolButtons_[inUsedTool_].SetPlaceholder(placeholders[inUsedTool_]);

			this->inUsedTool_ = -1;

			return 0;
		}
		else
		{
			this->toolButtons_[inUsedTool_].SetPlaceholder("Cancel");
			this->toolButtons_[inUsedTool_].SetTextColor(rgb(241, 246, 249));
			this->toolButtons_[inUsedTool_].SetFillColor(rgb(57, 72, 103));
			this->toolButtons_[inUsedTool_].SetBorderColor(rgb(57, 72, 103));
		}

		return 0;
	}

	for (int i = 0; i < 3; ++i)
	{
		if (i == 2)
		{
			if (this->ReaderDeleteCapabilityValidation() == false)
			{
				continue;
			}
		}

		if (this->toolButtons_[i].IsHover())
		{
			this->toolButtons_[i].SetFillColor(rgb(57, 72, 103));
		}
		else if (this->toolButtons_[i].LeftMouseClicked())
		{
			delay(130);
			this->inUsedTool_ = i;
			return this->inUsedTool_ + 1;
		}
		else
		{
			this->toolButtons_[i].SetPlaceholder(placeholders[i]);
			this->toolButtons_[i].SetTextColor(rgb(241, 246, 249));
			this->toolButtons_[i].SetFillColor(rgb(155, 164, 181));
			this->toolButtons_[i].SetBorderColor(rgb(155, 164, 181));
		}
	}

	this->inUsedTool_ = -1;

	return 0;
}

bool READER_TAB_MEMBERS::ToolSets::ReaderDeleteCapabilityValidation()
{
	if (this->currentReader_ == nullptr)
	{
		throw std::logic_error("[ERROR] Reader's pointer is NULL! (READER_TAB_MEMBERS::ToolSets::ReaderDeleteCapabilityValidation)");
	}

	auto bookCirculations = this->currentReader_->info.GetBooksCirculation();
	if (DOUBLE_LINKED_LIST::Empty(bookCirculations))
	{
		return true;
	}

	return false;
}
