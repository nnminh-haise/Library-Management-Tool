#pragma once

#include "ReaderListTable.hpp"
#include "SearchBox.hpp"
#include "ReaderDetail.hpp"
#include "UpdateReaderProcess.hpp"
#include "../UI/Button.h"
#include "../UI/Elements.h"
#include "../UI/Datasheet.h"
#include "../UI/Component.hpp"
#include "../../Helper/Package.h"
#include "../../DauSach/DauSach.h"
#include "../../TheDocGia/TheDocGia.h"
#include "../../DataStructures/LinearList.h"


namespace READER_TAB_MEMBERS
{
	class ToolSets : public View
	{
	public:
		ToolSets();

		void Activate();

		void Deactivate();

		bool InActive();

		int Run() override;

		void Reset();

		void SetCurrentReader(AVL_TREE::Pointer currentReader);

		AVL_TREE::Pointer GetCurrentReader();

		void SetReaderList(AVL_TREE::Pointer* readerList);

		AVL_TREE::Pointer* GetReaderList();

		void SetPackage(Package* package);

		void SetInUsedTool(int tool);

		int InUsedTool();

	private:
		void Initialize();

		void InitializeElements();

		int Display();

		int ToolButtonsOnAction();

	private:
		bool status_ = false;

		int inUsedTool_ = -1;

		Button toolButtons_[3];

		AVL_TREE::Pointer currentReader_ = nullptr;

		AVL_TREE::Pointer* readerList_ = nullptr;

		Package* package_ = nullptr;
	};

	class MainView : public View
	{
	public:
		MainView();

		void SetPackage(Package* package);

		void Activate();

		void Deactivate();

		bool InActive();

		int Run() override;

		void Reset();

	private:
		void Initialize();

		void InitializeElements();

		void InitializeFilters();

		void InitializeReaderTable();

		void InitializeSearchBox();

		void CreateSortedByNameReaderList();

		void Log();

		void LogSortedList();

	private:
		bool status_ = false;

		Package* package_ = nullptr;

	private:
		DataFilter defaultReaderListFilter_;

		LinearList<AVL_TREE::Pointer> sortedByNameReaderList_;

		DataFilter sortedByNameReaderListFilter_;

	private:
		READER_SEARCH_BOX::SearchBox searchBox_;

		READER_TABLE::DatasheetProcessor readerTablePackage_;

		SelectedObject<AVL_TREE::Pointer> tableSelectedObject_;

		ToolSets tools_;

		ReaderDetails readerDetails_;

	private:
		UpdateReaderProcess readerUpdateProcess_;
	};
}

class DanhSachTheDocGiaView : public View
{
public:
	DanhSachTheDocGiaView();

	DanhSachTheDocGiaView(Package* package);

	void Activate();

	void Deactivate();

	bool InActive();

	int Run() override;

	void Reset();

private:
	void Initialize();

	void InitializeElements();

private:
	bool status_ = false;

	Package* package_ = nullptr;

	READER_TAB_MEMBERS::MainView mainView_;
};
