#include "DanhSachDauSachView.h"
#include "../../Graphics/graphics.h"
#include "../../Helper/Helper.h"
#include "../../Helper/ConstantsAndGlobalVariables.h"
#include "../../DataStructures/Stack.h"

#include <iostream>
#include <format>
#include <string>


namespace DAU_SACH_TAB {

	/*
	 * Function creates datasheet form the given list
	! This function need to be rewrite!
	*/
	void CreateDatasheetsFromList(LINEAR_LIST::LinearList* titleList, DATASHEET::Controller& controler) {
		int listSize = titleList->numberOfNode;
		controler.SetDatasheetCount(
			listSize / (CONSTANTS::MAX_ROW_COUNT - 1) + (listSize % (CONSTANTS::MAX_ROW_COUNT - 1) == 0 ? 0 : 1)
		);
		controler.InitializeDatasheets();

		for (int i = 0; i < controler.GetDatasheetCount(); ++i) {
			controler[i] = DATASHEET::Datasheet(
				controler.GetRecordCount(),
				controler.GetAttributeCount(),
				controler.GetRowHeight(),
				controler.GetTopLeft(),
				(std::string*)DAU_SACH_PROPERTIES::LABEL_PLACEHOLDERS,
				(int*)DAU_SACH_PROPERTIES::CHARACTER_LIMITS
			);
		}

		int recordIndex = 0;
		int sheetIndex = -1;

		for (int i = 0; i < titleList->numberOfNode; ++i) {

			++recordIndex;
			if (recordIndex > controler.GetRecordCount() - 1) {
				recordIndex = 1;
			}
			if (recordIndex % (controler.GetRecordCount() - 1) == 1) {
				sheetIndex += 1;
			}

			std::string* data = new std::string[controler.GetAttributeCount()];
			data[0] = std::to_string(i + 1);
			data[1] = titleList->nodes[i]->GetISBN();
			data[2] = titleList->nodes[i]->GetTitle();
			data[3] = std::to_string(titleList->nodes[i]->GetPageCount());
			data[4] = titleList->nodes[i]->GetAuthor();
			data[5] = std::to_string(titleList->nodes[i]->GetPublicationYear());
			data[6] = titleList->nodes[i]->GetCategory();

			controler[sheetIndex].UpdateNewPlaceholder(data, recordIndex);
		}
	}

	void CreateDatasheetsWithSortedCategory(BOOK_TITLE::BookTitle** sortedList, int listSize, DATASHEET::Controller& datasheetController) {
		datasheetController.SetDatasheetCount(
			listSize / (CONSTANTS::MAX_ROW_COUNT - 1) + (listSize % (CONSTANTS::MAX_ROW_COUNT - 1) == 0 ? 0 : 1)
		);
		datasheetController.InitializeDatasheets();

		for (int i = 0; i < datasheetController.GetDatasheetCount(); ++i) {
			datasheetController[i] = DATASHEET::Datasheet(
				datasheetController.GetRecordCount(),
				datasheetController.GetAttributeCount(),
				datasheetController.GetRowHeight(),
				datasheetController.GetTopLeft(),
				(std::string*)DAU_SACH_PROPERTIES::LABEL_PLACEHOLDERS, (int*)DAU_SACH_PROPERTIES::CHARACTER_LIMITS
			);
		}

		int recordIndex = 0;
		int sheetIndex = -1;

		for (int i = 0; i < listSize; ++i) {

			++recordIndex;
			if (recordIndex > datasheetController.GetRecordCount() - 1) {
				recordIndex = 1;
			}
			if (recordIndex % (datasheetController.GetRecordCount() - 1) == 1) {
				sheetIndex += 1;
			}

			std::string* data = new std::string[datasheetController.GetAttributeCount()];
			data[0] = std::to_string(i + 1);
			data[1] = sortedList[i]->GetISBN();
			data[2] = sortedList[i]->GetTitle();
			data[3] = std::to_string(sortedList[i]->GetPageCount());
			data[4] = sortedList[i]->GetAuthor();
			data[5] = std::to_string(sortedList[i]->GetPublicationYear());
			data[6] = sortedList[i]->GetCategory();

			datasheetController[sheetIndex].UpdateNewPlaceholder(data, recordIndex);
		}
	}

	/**
	* Search field
	*/
	SearchField::SearchField() {
		this->active = false;
		this->searchFound = false;

		this->background = new HELPER::Fill(HELPER::Coordinate(1405, 120), 350, 250);
		this->title = new Button(HELPER::Coordinate(1405, 120), 350, 50);
		this->title->SetPlaceholder("SEARCH");

		this->inputSearchBox = new Button(HELPER::Coordinate(1430, 200), 300, 70);
		this->inputSearchBox->SetPlaceholder("Type here to search");

		this->searchStatusBox = new Button(HELPER::Coordinate(1430, 295), 300, 50);
		this->searchStatusBox->SetPlaceholder("Result: NOT FOUND!");
	}

	void SearchField::Activate() {
		this->active = true;
	}

	void SearchField::Deactivate() {
		this->active = false;
	}

	bool SearchField::GetStatus() {
		return this->active;
	}

	void SearchField::OnAction(ELEMENTS::InputModeController* inputController) {
		if (this->inputSearchBox->IsHover()) {
			this->inputSearchBox->SetFillColor(rgb(246, 241, 241));
		}
		else if (this->inputSearchBox->LeftMouseClicked()) {
			this->searchFound = false;
			inputController->Activate(
				this->inputSearchBox,
				this->inputSearchBox,
				30,
				true,
				true,
				true
			);
		}
		else {
			DANH_SACH_DAU_SACH_SEARCH_FIELD_STYLING::SearchBoxStyling(this->inputSearchBox);
		}
	}

	void SearchField::Display() {
		if (this->active == false) {
			return;
		}

		DANH_SACH_DAU_SACH_SEARCH_FIELD_STYLING::BackgroundStyling(this->background);
		DANH_SACH_DAU_SACH_SEARCH_FIELD_STYLING::TitleStyling(this->title);
		DANH_SACH_DAU_SACH_SEARCH_FIELD_STYLING::SearchBoxStyling(this->inputSearchBox);
		DANH_SACH_DAU_SACH_SEARCH_FIELD_STYLING::StatusBoxStyling(this->searchStatusBox);

		this->background->Draw();
		this->title->Display();
		this->inputSearchBox->Display();
		this->searchStatusBox->Display();
	}


	BookCreatingSection::BookCreatingSection()
	{
		this->active_ = false;

		this->InitializeElements();
	}

	void BookCreatingSection::Activate() { this->active_ = true; }

	void BookCreatingSection::Deactivate() { this->active_ = false; }

	bool BookCreatingSection::GetStatus() { return this->active_; }

	void BookCreatingSection::Display()
	{
		if (!this->active_) { return; }

		this->background_.Draw();
		for (int i = 0; i < 5; ++i)
		{
			this->inputField_[i].Display();
		}
		this->saveButton_.Display();
	}

	// TODO: Clean up this section
	void BookCreatingSection::InitializeElements()
	{
		this->background_ = HELPER::Fill(
			HELPER::Coordinate(36, 616),
			600, 180,
			rgb(238, 238, 238),
			rgb(24, 18, 43)
		);

		HELPER::Coordinate inputFieldCoordinates[5] = {
			HELPER::Coordinate(61, 646),
			HELPER::Coordinate(398, 646),
			HELPER::Coordinate(61, 717),
			HELPER::Coordinate(229, 717),
			HELPER::Coordinate(398, 717)
		};
		std::string inputFiledPlaceholders[5] = { "Book's ID", "Book's status", "Row", "Column", "Section" };
		HELPER::Dimension inputFieldDimension[] = {
			HELPER::Dimension(308, 50),
			HELPER::Dimension(215, 50),
			HELPER::Dimension(140, 50),
			HELPER::Dimension(140, 50),
			HELPER::Dimension(140, 50)
		};

		for (int i = 0; i < 5; ++i)
		{
			this->inputField_[i] = Button(inputFieldCoordinates[i], inputFieldDimension[i]);
			this->inputField_[i].SetPlaceholder(inputFiledPlaceholders[i]);
			this->inputField_[i].SetFillColor(rgb(255, 251, 245));
			this->inputField_[i].SetBorderColor(rgb(24, 18, 43));
			this->inputField_[i].SetTextColor(rgb(24, 18, 43));
		}

		this->saveButton_ = Button(
			HELPER::Coordinate(561, 717),
			50, 50,
			rgb(24, 18, 43),
			rgb(145, 216, 228),
			rgb(24, 18, 43)
		);
		this->saveButton_.SetPlaceholder(">");
	}

	CatalogueCreatingSection::CatalogueCreatingSection()
	{
		this->titleList_ = nullptr;
		this->inputController_ = nullptr;

		this->active = false;
		this->items = nullptr;
		this->itemsCount = 0;
		this->activeField = -1;
	}

	CatalogueCreatingSection::CatalogueCreatingSection(LINEAR_LIST::LinearList* titleList, ELEMENTS::InputModeController* inputController)
	{
		this->titleList_ = titleList;
		this->inputController_ = inputController;

		this->active = false;
		this->items = nullptr;
		this->itemsCount = 0;
		this->activeField = -1;

		this->InitializeElements();
	}

	// @CatalogueCreatingSection::Destructor
	CatalogueCreatingSection::~CatalogueCreatingSection()
	{
		delete[this->itemsCount] this->items;
	}

	void CatalogueCreatingSection::InitializeCatalogue(int catalogueSize, std::string ISBN)
	{
		this->itemsCount = catalogueSize;
		this->items = new DAU_SACH_TAB::BookCreatingSection[catalogueSize];
		this->activeField = 0;

		for (int i = 1; i <= catalogueSize; ++i)
		{
			this->items[i - 1].inputField_[0].SetPlaceholder(ISBN + "-" + std::to_string(i));
			this->items[i - 1].inputField_[1].SetPlaceholder("AVAILABLE");
		}
	}

	void CatalogueCreatingSection::InputFieldOnUpdate()
	{
		if (!this->active) { return; }

		for (int i = 2; i < 5; ++i)
		{
			if (this->items[this->activeField].inputField_[i].IsHover())
			{
				this->items[this->activeField].inputField_[i].SetFillColor(rgb(233, 248, 249));
				this->items[this->activeField].inputField_[i].SetBorderColor(rgb(83, 127, 231));
			}
			else if (this->items[this->activeField].inputField_[i].LeftMouseClicked())
			{
				//!DELAY_SECTION
				delay(150);
				this->inputController_->Activate(
					&this->items[this->activeField].inputField_[i],
					&this->items[this->activeField].inputField_[i],
					2,
					false,
					true,
					false
				);
			}
			else
			{
				this->items[this->activeField].inputField_[i].SetFillColor(rgb(255, 251, 245));
				this->items[this->activeField].inputField_[i].SetBorderColor(rgb(24, 18, 43));
			}
		}
	}

	void CatalogueCreatingSection::SaveButtonOnUpdate()
	{
		if (!this->active) { return; }

		if (this->items[this->activeField].saveButton_.IsHover())
		{
			this->items[this->activeField].saveButton_.SetFillColor(rgb(0, 255, 202));
		}
		else if (this->items[this->activeField].saveButton_.LeftMouseClicked())
		{
			//!DELAY_SECTION
			delay(150);
			if (this->activeField == this->itemsCount - 1)
			{
				this->activeField = 0;

				//TODO: Throw error log here
				//std::cerr << std::format("[INFO] Press Save to save data into the list!\n");
			}
			else
			{
				this->activeField++;
			}
		}
		else
		{
			this->items[this->activeField].saveButton_.SetFillColor(rgb(145, 216, 228));
		}
	}

	void CatalogueCreatingSection::IndexChangeButtonOnAction()
	{
		if (!this->active) { return; }

		int movement[2] = { -1, +1 };
		for (int i = 0; i < 2; ++i)
		{
			if (this->indexChangeButtons[i].IsHover())
			{
				this->indexChangeButtons[i].SetFillColor(rgb(130, 170, 227));
			}
			else if (this->indexChangeButtons[i].LeftMouseClicked())
			{
				//!DELAY_SECTION
				delay(150);
				this->activeField = (this->activeField + movement[i] + this->itemsCount) % this->itemsCount;
			}
			else
			{
				this->indexChangeButtons[i].SetFillColor(rgb(236, 242, 255));
			}
		}
	}

	void CatalogueCreatingSection::Activate() { this->active = true; }

	void CatalogueCreatingSection::Deactivate() { this->active = false; }

	bool CatalogueCreatingSection::GetStatus() { return this->active; }

	void CatalogueCreatingSection::Display()
	{
		if (!this->active) { return; }

		this->items[this->activeField].Activate();
		this->items[this->activeField].Display();

		for (int i = 0; i < 2; ++i)
		{
			this->indexChangeButtons[i].Display();
		}
	}

	void CatalogueCreatingSection::InitializeElements()
	{
		HELPER::Coordinate buttonCoordinates[] = {
			HELPER::Coordinate(36, 811),
			HELPER::Coordinate(86, 811)
		};
		std::string placeholder[] = { "<", ">" };

		for (int i = 0; i < 2; ++i)
		{
			this->indexChangeButtons[i] = Button(buttonCoordinates[i], 50, 30);
			this->indexChangeButtons[i].SetPlaceholder(placeholder[i]);
			this->indexChangeButtons[i].SetFillColor(rgb(236, 242, 255));
			this->indexChangeButtons[i].SetBorderColor(rgb(24, 18, 43));
			this->indexChangeButtons[i].SetTextColor(rgb(24, 18, 43));
		}
	}

	TitleCreatingSection::TitleCreatingSection()
	{
		this->active = false;
		this->sachAddFieldDisplay = false;
	}

	TitleCreatingSection::TitleCreatingSection(Package* package)
	{
		this->package_ = package;

		this->active = false;
		this->sachAddFieldDisplay = false;

		this->InitializeElements();
	}

	bool TitleCreatingSection::InputFieldOnUpdate()
	{
		if (this->active == false) { return false; }

		int characterLimits[] = { 4, 50, 50, 30, 4, 4, 5 };
		bool acceptAlphas[] = { true, true, true, true, false, false, false };
		bool acceptNums[] = { false, true, true, true, true, true, true };
		bool acceptSpaces[] = { false, true, true, true, false, false, false };

		for (int i = 0; i < 7; ++i)
		{
			if (this->inputField_[i].IsHover())
			{
				this->inputField_[i].SetBorderColor(rgb(83, 127, 231));
				this->inputField_[i].SetFillColor(rgb(233, 248, 249));
			}
			else if (this->inputField_[i].LeftMouseClicked())
			{
				delay(100);
				this->package_->inputController->Activate(
					&this->inputField_[i],
					&this->inputField_[i],
					characterLimits[i],
					acceptAlphas[i],
					acceptNums[i],
					acceptSpaces[i]
				);
			}
			else
			{
				this->inputField_[i].SetFillColor(rgb(255, 251, 245));
				this->inputField_[i].SetBorderColor(rgb(24, 18, 43));
			}
		}

		std::string defaultInputValues[7] = {
			" ISBN ", " Title ", " Author ", " Category ", " Page number ", " Public year ", " Catalogue's size "
		};
		bool userInputed = true;
		std::string userInputValue{};
		for (int i = 0; i < 7; ++i)
		{
			userInputValue = this->inputField_[i].GetPlaceholder();
			if (userInputValue.compare(defaultInputValues[i]) == 0 || userInputValue.length() == 0)
			{
				userInputed = false;
				break;
			}
		}

		this->ISBNCheckProcessResult_ = this->ISBNInputFieldCheckProcess();

		this->catalogueSizeProcessResult_ = this->CatalogueSizeCheckProcess();

		if (this->ISBNCheckProcessResult_ && this->catalogueSizeProcessResult_ && userInputed)
		{
			this->goodInputFieldCheckResult_ = true;
			return true;
		}

		this->goodInputFieldCheckResult_ = false;
		return false;
	}

	bool TitleCreatingSection::CreateCatalogueButtonOnUpdate()
	{
		if (this->active == false) { return false; }

		if (!this->goodInputFieldCheckResult_) { return false; }

		this->alertField_[1].SetTextColor(rgb(104, 185, 132));
		this->alertField_[1].SetPlaceholder("Press the [V] button to create title's catalogue!");

		if (this->createCatalogueButton_.IsHover())
		{
			this->createCatalogueButton_.SetFillColor(rgb(89, 206, 143));
		}
		else if (this->createCatalogueButton_.LeftMouseClicked())
		{
			delay(100);

			const std::string& catalogueSize = this->inputField_[6].GetPlaceholder();
			const std::string& titleISBN = this->inputField_[0].GetPlaceholder();
			this->catalogueCreatingSection = DAU_SACH_TAB::CatalogueCreatingSection(this->package_->titleList, this->package_->inputController);
			this->catalogueCreatingSection.Activate();
			this->catalogueCreatingSection.InitializeCatalogue(std::stoi(catalogueSize), titleISBN);

			return true;
		}
		else
		{
			this->createCatalogueButton_.SetFillColor(rgb(145, 216, 228));
		}

		return false;
	}

	bool TitleCreatingSection::SubmitButtonOnUpdate()
	{
		if (this->active == false) { return false; }

		if (!this->allowCreatingNewTitle_) { return false; }

		if (this->submit.IsHover())
		{
			this->submit.SetFillColor(rgb(89, 206, 143));
		}
		else if (this->submit.LeftMouseClicked())
		{
			delay(100);

			BOOK_TITLE::BookTitle* newTitle = new BOOK_TITLE::BookTitle;

			newTitle->SetISBN(this->inputField_[0].GetPlaceholder());
			newTitle->SetTitle(this->inputField_[1].GetPlaceholder());
			newTitle->SetAuthor(this->inputField_[2].GetPlaceholder());
			newTitle->SetCategory(this->inputField_[3].GetPlaceholder());
			newTitle->SetPublicationYear(std::stoi(this->inputField_[4].GetPlaceholder()));
			newTitle->SetPageCount(std::stoi(this->inputField_[5].GetPlaceholder()));

			if (std::stoi(this->inputField_[6].GetPlaceholder()) == 0)
			{
				newTitle->SetCatalogue(LINKED_LIST::Controller());
			}
			else
			{
				LINKED_LIST::Controller newBookList;
				LINKED_LIST::Initialize(newBookList);

				for (int i = 0; i < this->catalogueCreatingSection.itemsCount; ++i)
				{
					BOOK::Book newBook;
					newBook.SetID(this->catalogueCreatingSection.items[i].inputField_[0].GetPlaceholder());
					newBook.SetStatus(BOOK::Status::AVAILABLE);
					newBook.SetDescription(std::format("ROW {} COL {} SECTION {}",
						this->catalogueCreatingSection.items[i].inputField_[2].GetPlaceholder(),
						this->catalogueCreatingSection.items[i].inputField_[3].GetPlaceholder(),
						this->catalogueCreatingSection.items[i].inputField_[4].GetPlaceholder()
					));

					LINKED_LIST::PushBack(newBookList, newBook);
				}

				newTitle->SetCatalogue(newBookList);
			}

			LINEAR_LIST::InsertOrder(*this->package_->titleList, newTitle);

			//TODO: Add a notification window here
			std::cerr << "[INFO] Successfully insert a new item into title list!\n";

			this->alertField_[1].SetTextColor(rgb(104, 185, 132));
			this->alertField_[1].SetPlaceholder("New title has created successfully!");

			int defaultWindowID = getcurrentwindow();

			ELEMENTS::Window notificationWindow(HELPER::Dimension(500, 150), "NOTIFICATION");
			notificationWindow.backgroundColor = WHITE;
			int notificationWindowID = notificationWindow.Activate();
			notificationWindow.RenderBackground();

			Button notification(HELPER::Coordinate(100, 70), HELPER::Dimension(100, 70));
			notification.SetTextColor(rgb(104, 185, 132));
			notification.SetBorderColor(WHITE);
			notification.SetFillColor(WHITE);
			notification.SetPlaceholder("SUCCESSFULLY CREATED A NEW TITLE!");
			notification.Display();

			getch();

			notificationWindow.Deactivate();

			setcurrentwindow(defaultWindowID);

			return true;
		}
		else
		{
			this->submit.SetFillColor(rgb(145, 216, 228));
		}


		return false;
	}

	bool TitleCreatingSection::Run()
	{
		bool goodTitleData = this->InputFieldOnUpdate();
		bool allowCreateCatalogue = this->CreateCatalogueButtonOnUpdate();
		bool goodCatalogueData = this->CatalogueInputFieldCheckProcess();
		bool newTittleCreated = this->SubmitButtonOnUpdate();

		if (goodTitleData && allowCreateCatalogue && goodCatalogueData && newTittleCreated) { return true; }

		return false;
	}

	void TitleCreatingSection::Activate() { this->active = true; }

	void TitleCreatingSection::Deactivate() { this->active = false; }

	bool TitleCreatingSection::GetStatus() { return this->active; }

	void TitleCreatingSection::Display()
	{
		if (this->active == false) { return; }

		this->background.Draw();
		this->title.Display();
		for (int i = 0; i < 7; ++i)
		{
			this->inputField_[i].Display();
		}
		this->createCatalogueButton_.Display();

		for (int i = 0; i < 2; ++i) { this->alertField_[i].Display(); }

		if (this->catalogueCreatingSection.GetStatus() == true)
		{
			this->catalogueCreatingSection.Display();
			this->catalogueCreatingSection.IndexChangeButtonOnAction();
			this->catalogueCreatingSection.InputFieldOnUpdate();
			this->catalogueCreatingSection.SaveButtonOnUpdate();
		}

		if (this->allowCreatingNewTitle_)
		{
			this->submit.Display();
		}
		this->goBackButton.Display();
	}

	void TitleCreatingSection::InitializeElements()
	{
		this->background = HELPER::Fill(
			HELPER::Coordinate(36, 121),
			600, 480,
			rgb(238, 238, 238),
			rgb(24, 18, 43)
		);

		this->title = Button(HELPER::Coordinate(36, 121), 600, 50);
		this->title.SetPlaceholder("CREATING NEW TITLE");
		this->title.SetFillColor(rgb(87, 108, 188));
		this->title.SetBorderColor(rgb(24, 18, 43));
		this->title.SetTextColor(rgb(239, 245, 245));

		HELPER::Coordinate inputFieldCoordinates[7] = {
			HELPER::Coordinate(61, 196),
			HELPER::Coordinate(61, 267),
			HELPER::Coordinate(61, 338),
			HELPER::Coordinate(61, 409),
			HELPER::Coordinate(61, 480),
			HELPER::Coordinate(229, 480),
			HELPER::Coordinate(398, 480)
		};
		HELPER::Dimension inputFieldDimensions[7] = {
			HELPER::Dimension(200, 50),
			HELPER::Dimension(550, 50),
			HELPER::Dimension(550, 50),
			HELPER::Dimension(550, 50),
			HELPER::Dimension(140, 50),
			HELPER::Dimension(140, 50),
			HELPER::Dimension(140, 50)
		};
		std::string inputFiledPlaceholders[7] = {
			" ISBN ", " Title ", " Author ", " Category ", " Page number ", " Public year ", " Catalogue's size "
		};
		for (int i = 0; i < 7; ++i)
		{
			this->inputField_[i] = Button(inputFieldCoordinates[i], inputFieldDimensions[i]);
			this->inputField_[i].SetPlaceholder(inputFiledPlaceholders[i]);
			this->inputField_[i].SetFillColor(rgb(255, 251, 245));
			this->inputField_[i].SetBorderColor(rgb(24, 18, 43));
			this->inputField_[i].SetTextColor(rgb(24, 18, 43));
		}

		this->createCatalogueButton_ = Button(
			HELPER::Coordinate(561, 480),
			50, 50,
			rgb(24, 18, 43),
			rgb(145, 216, 228),
			rgb(24, 18, 43)
		);
		this->createCatalogueButton_.SetPlaceholder("V");

		this->submit = Button(
			HELPER::Coordinate(211, 861),
			250, 60,
			rgb(24, 18, 43),
			rgb(145, 216, 228),
			rgb(24, 18, 43)
		);
		this->submit.SetPlaceholder("CREATE NEW TITLE");

		HELPER::Coordinate alertFieldCoordinates[] = {
			HELPER::Coordinate(273, 201),
			HELPER::Coordinate(61, 551)
		};
		HELPER::Dimension alertFieldDimensions[] = {
			HELPER::Dimension(338, 40),
			HELPER::Dimension(550, 40)
		};
		for (int i = 0; i < 2; ++i)
		{
			this->alertField_[i] = Button(alertFieldCoordinates[i], alertFieldDimensions[i]);
			this->alertField_[i].SetFillColor(rgb(238, 238, 238));
			this->alertField_[i].SetBorderColor(rgb(238, 238, 238));
			this->alertField_[i].SetTextColor(rgb(120, 122, 145));
		}
		this->alertField_[0].SetPlaceholder("Input a unique ISBN code for the new title!");
		this->alertField_[1].SetPlaceholder("Fill out all input field then press [V] to create catalogue!");

		this->goBackButton = Button(
			HELPER::Coordinate(36, 937),
			70, 40,
			rgb(24, 18, 43),
			rgb(236, 242, 255),
			rgb(24, 18, 43)
		);
		this->goBackButton.SetPlaceholder("<");
	}

	bool TitleCreatingSection::CatalogueSizeCheckProcess()
	{
		std::string catalogueSizeStringValue = this->inputField_[6].GetPlaceholder();
		if (catalogueSizeStringValue.length() == 0)
		{
			this->alertField_[1].SetFillColor(rgb(238, 238, 238));
			this->alertField_[1].SetBorderColor(rgb(238, 238, 238));
			this->alertField_[1].SetTextColor(rgb(120, 122, 145));
			this->alertField_[1].SetPlaceholder("Don't let the catalogue's size input field empty!");

			return false;
		}

		if (VALIDATOR::OnlyDigit(catalogueSizeStringValue))
		{
			int catalogueSize = std::stoi(catalogueSizeStringValue);

			return true;
		}

		this->alertField_[1].SetFillColor(rgb(238, 238, 238));
		this->alertField_[1].SetBorderColor(rgb(238, 238, 238));
		this->alertField_[1].SetTextColor(rgb(120, 122, 145));
		this->alertField_[1].SetPlaceholder("Fill out all input field then press [V] to create catalogue!");

		return false;
	}

	bool TitleCreatingSection::GoBackButtonOnAction()
	{
		if (this->active == false) { return false; }

		if (this->goBackButton.IsHover())
		{
			this->goBackButton.SetFillColor(rgb(130, 170, 227));
		}
		else if (this->goBackButton.LeftMouseClicked())
		{
			delay(100);
			this->active = false;
			this->catalogueCreatingSection.Deactivate();
			return true;
		}
		else
		{
			this->goBackButton.SetFillColor(rgb(236, 242, 255));
		}
		return false;
	}

	bool TitleCreatingSection::ISBNInputFieldCheckProcess()
	{
		if (!this->active) { return false; }

		std::string inputISBN = this->inputField_[0].GetPlaceholder();
		if (inputISBN.length() == 4) // ISBN Input value at input field of index 0
		{
			if (this->package_->titleMap->At(inputISBN) != nullptr)
			{
				this->alertField_[0].SetTextColor(rgb(231, 70, 70));
				this->alertField_[0].SetBorderColor(rgb(231, 70, 70));
				this->alertField_[0].SetPlaceholder("DUPLICATED ISBN!");

				return false;
			}
			else
			{
				this->alertField_[0].SetFillColor(rgb(95, 208, 104));
				this->alertField_[0].SetTextColor(WHITE);
				this->alertField_[0].SetBorderColor(rgb(95, 208, 104));
				this->alertField_[0].SetPlaceholder("QUALIFIED ISBN!");

				return true;
			}
		}
		else if (inputISBN.length() != 4)
		{
			this->alertField_[0].SetFillColor(rgb(238, 238, 238));
			this->alertField_[0].SetBorderColor(rgb(238, 238, 238));
			this->alertField_[0].SetTextColor(rgb(120, 122, 145));
			this->alertField_[0].SetPlaceholder("Input a unique ISBN code for the new title!");

			return false;
		}

		return false;
	}

	bool TitleCreatingSection::CatalogueInputFieldCheckProcess()
	{
		if (!this->active) { return false; }

		if (!this->catalogueSizeProcessResult_) { return false; }

		if (this->catalogueCreatingSection.itemsCount == 0) { return false; }

		std::string defaultValues[] = { "Row", "Column", "Section" };

		for (int i = 0; i < this->catalogueCreatingSection.itemsCount; ++i)
		{
			bool allFilled = true;
			for (int j = 2; j < 5; ++j)
			{
				if (this->catalogueCreatingSection.items[i].inputField_[j].GetPlaceholder().length() == 0 ||
					this->catalogueCreatingSection.items[i].inputField_[j].GetPlaceholder().compare(defaultValues[j - 2]) == 0)
				{
					allFilled = false;
					break;
				}
			}

			if (!allFilled)
			{
				this->alertField_[1].SetFillColor(rgb(238, 238, 238));
				this->alertField_[1].SetBorderColor(rgb(238, 238, 238));
				this->alertField_[1].SetTextColor(rgb(120, 122, 145));
				this->alertField_[1].SetPlaceholder("Fill out all input field of title's catalogue then press CREATE button!");

				this->allowCreatingNewTitle_ = false;

				return false;
			}
		}

		this->alertField_[1].SetTextColor(rgb(104, 185, 132));
		this->alertField_[1].SetPlaceholder("Press CREATE button to create new title!");

		this->allowCreatingNewTitle_ = true;

		return true;
	}

	TitleDetailDisplayField::TitleDetailDisplayField() {
		this->active = false;

		this->targetedTitle = nullptr;

		this->background = HELPER::Fill(HELPER::Coordinate(1105, 120), 650, 700, rgb(238, 238, 238), BLACK);

		this->title = Button(
			HELPER::Coordinate(1105, 120), HELPER::Dimension(650, 80),
			WHITE, //* text color
			rgb(87, 108, 188), //* Background color
			BLACK //* Border color
		);

		HELPER::Coordinate titleDetailsCoordinates[] = {
			HELPER::Coordinate(1130, 232),
			HELPER::Coordinate(1130, 314),
			HELPER::Coordinate(1130, 397),
			HELPER::Coordinate(1130, 480),
			HELPER::Coordinate(1130, 563),
		};
		for (int i = 0; i < 5; ++i) {
			this->titleDetails[i] = Button(
				titleDetailsCoordinates[i], HELPER::Dimension(600, 60),
				BLACK, //* Text color
				WHITE, //* Fill color
				BLACK  //* Border color
			);
		}

		this->goBackBtn = Button(
			HELPER::Coordinate(1685, 930), 70, 40,
			rgb(24, 18, 43), rgb(236, 242, 255), rgb(24, 18, 43)
		);
		this->goBackBtn.SetPlaceholder("<");

		this->bookListDatasheetController = DATASHEET::Controller(
			16, 4, 50, HELPER::Coordinate(36, 120)
		);

		this->deleteBookBtn = Button(
			HELPER::Coordinate(229, 945), 150, 40,
			rgb(57, 62, 70),
			rgb(219, 223, 253),
			rgb(219, 223, 253)
		);
		this->deleteBookBtn.SetPlaceholder("DELETE");
		this->deleteBook = nullptr;
	}

	void TitleDetailDisplayField::Destructor() {
		this->bookListDatasheetController = DATASHEET::Controller();
	}

	void TitleDetailDisplayField::Initialize(BOOK_TITLE::BookTitle* title) {
		this->targetedTitle = title;

		this->title.SetPlaceholder(this->targetedTitle->GetTitle());

		this->titleDetails[0].SetPlaceholder(std::format("isbn: {}", this->targetedTitle->GetISBN()));
		this->titleDetails[1].SetPlaceholder(std::format("Category: {}", this->targetedTitle->GetCategory()));
		this->titleDetails[2].SetPlaceholder(std::format("Author: {}", this->targetedTitle->GetAuthor()));
		this->titleDetails[3].SetPlaceholder(std::format("Page number: {}", std::to_string(this->targetedTitle->GetPageCount())));
		this->titleDetails[4].SetPlaceholder(std::format("Public: {}", std::to_string(this->targetedTitle->GetPublicationYear())));

		this->CreateBookListDatasheet();
	}

	void TitleDetailDisplayField::CreateBookListDatasheet() {
		std::string labels[] = { "STT", "MA BOOK", "TRANG THAI", "VI TRI" };
		int chrLimits[] = { 3, 8, 18, 20 };

		int listSize = LINKED_LIST::Size(this->targetedTitle->GetCatalogue());

		this->bookListDatasheetController.SetDatasheetCount(
			max(1, listSize / (CONSTANTS::MAX_ROW_COUNT - 1) + (listSize % (CONSTANTS::MAX_ROW_COUNT - 1) == 0 ? 0 : 1))
		);
		this->bookListDatasheetController.InitializeDatasheets();

		for (int i = 0; i < this->bookListDatasheetController.GetDatasheetCount(); ++i) {
			this->bookListDatasheetController[i] = DATASHEET::Datasheet(
				this->bookListDatasheetController.GetRecordCount(),
				this->bookListDatasheetController.GetAttributeCount(),
				this->bookListDatasheetController.GetRowHeight(),
				this->bookListDatasheetController.GetTopLeft(),
				labels, chrLimits
			);
		}

		if (listSize == 0) {
			return;
		}

		int recordIndex = 0;
		int sheetIndex = -1;
		int order = 0;
		for (LINKED_LIST::Pointer p = this->targetedTitle->GetCatalogue().first; p != nullptr; p = p->next) {
			++recordIndex;
			if (recordIndex > this->bookListDatasheetController.GetRecordCount() - 1) {
				recordIndex = 1;
			}
			if (recordIndex % (this->bookListDatasheetController.GetRecordCount() - 1) == 1) {
				sheetIndex += 1;
			}

			std::string* data = new std::string[this->bookListDatasheetController.GetAttributeCount()];
			data[0] = std::to_string(++order);
			data[1] = p->info.GetID();
			data[2] = p->info.StringfyStatus();
			data[3] = p->info.GetDescription();

			this->bookListDatasheetController[sheetIndex].UpdateNewPlaceholder(data, recordIndex);
		}
	}

	void TitleDetailDisplayField::Activate() {
		this->active = true;
	}

	void TitleDetailDisplayField::Deactivate() {
		this->active = false;
	}

	bool TitleDetailDisplayField::GetStatus() {
		return this->active;
	}

	void TitleDetailDisplayField::Display() {
		if (this->active == false) {
			return;
		}

		this->background.Draw();
		this->title.Display();
		for (int i = 0; i < 5; ++i) {
			this->titleDetails[i].Display();
		}

		this->bookListDatasheetController.Display();

		if (this->deleteBookBtn.IsActive() == true) {
			this->deleteBookBtn.Display();

			if (this->deleteBookBtn.IsHover()) {
				this->deleteBookBtn.SetFillColor(rgb(155, 163, 235));
				this->deleteBookBtn.SetBorderColor(rgb(36, 47, 155));
				this->deleteBookBtn.SetTextColor(rgb(234, 253, 252));
			}
			else if (this->deleteBookBtn.LeftMouseClicked()) {
				//todo: LINKED_LIST::DeleteAt function is not working!

				LINKED_LIST::Controller buffer = this->targetedTitle->GetCatalogue();
				if (LINKED_LIST::DeleteAt(buffer, this->deleteBook->info)) {
					std::cerr << "delete!\n";
					this->targetedTitle->SetCatalogue(buffer);
					this->CreateBookListDatasheet();
				}
				else {
					std::cerr << "not delete\n";
				}
			}
			else {
				this->deleteBookBtn.SetFillColor(rgb(219, 223, 253));
				this->deleteBookBtn.SetBorderColor(rgb(219, 223, 253));
				this->deleteBookBtn.SetTextColor(rgb(57, 62, 70));
			}
		}

		this->goBackBtn.Display();
	}

	void TitleDetailDisplayField::DeleteBookButtonOnAction() {
		if (this->bookListDatasheetController.GetDatasheetCount() == 0) {
			return;
		}

		for (int i = 1; i < this->bookListDatasheetController.GetRecordCount(); ++i) {
			Button& bookIdButton = this->bookListDatasheetController[this->bookListDatasheetController.CurrentActiveDatasheet()][i][1];

			if (bookIdButton.IsHover()) {
				bookIdButton.SetFillColor(rgb(244, 249, 249));
			}
			else if (bookIdButton.LeftMouseClicked()) {
				delay(100);
				for (LINKED_LIST::Pointer p = this->targetedTitle->GetCatalogue().first; p != nullptr; p = p->next) {
					if (p->info.GetID().compare(bookIdButton.GetPlaceholder()) == 0) {
						this->deleteBook = p;
						break;
					}
				}
				this->deleteBookBtn.Deactivate();
			}
			else {
				if (i % 2 != 0) {
					bookIdButton.SetFillColor(rgb(255, 251, 245));
				}
				else {
					bookIdButton.SetFillColor(rgb(238, 238, 238));
				}
			}
		}

		if (this->deleteBookBtn.IsHover()) {
			this->deleteBookBtn.SetFillColor(rgb(155, 163, 235));
			this->deleteBookBtn.SetBorderColor(rgb(36, 47, 155));
			this->deleteBookBtn.SetTextColor(rgb(234, 253, 252));
		}
		else if (this->deleteBookBtn.LeftMouseClicked()) {
			delay(100);
		}
		else {
			this->deleteBookBtn.SetFillColor(rgb(219, 223, 253));
			this->deleteBookBtn.SetBorderColor(this->deleteBookBtn.GetFillColor());
			this->deleteBookBtn.SetTextColor(rgb(57, 62, 70));
		}
	}

	void TitleDetailDisplayField::ResetDeleteBookButton() {
		this->deleteBookBtn = Button(
			HELPER::Coordinate(229, 945), 150, 40,
			rgb(57, 62, 70),
			rgb(219, 223, 253),
			rgb(219, 223, 253)
		);
		this->deleteBookBtn.SetPlaceholder("DELETE");
		this->deleteBook = nullptr;
	}

	bool TitleDetailDisplayField::GoBackButtonOnAction() {
		if (this->active == false) {
			return true;
		}

		if (this->goBackBtn.IsHover()) {
			this->goBackBtn.SetFillColor(rgb(130, 170, 227));
		}
		else if (this->goBackBtn.LeftMouseClicked()) {
			delay(100);
			this->active = false;
			return true;
		}
		else {
			this->goBackBtn.SetFillColor(rgb(236, 242, 255)
			);
		}
		return false;
	}
}

namespace CATEGORY_LINKED_LIST {
	Node::Node(std::string info, Node* next) {
		this->info = info;
		this->next = next;
	}

	void Initialzie(Pointer& First) {
		First = nullptr;
	}

	bool Empty(const Pointer& First) {
		return First == nullptr;
	}

	void PushFront(Pointer& First, std::string info) {
		Pointer newNode = new Node(info, First);
		First = newNode;
	}

	void InsertOrder(Pointer& First, std::string info) {
		Pointer newNode = new Node(info, nullptr);

		//* Case the list does not have any item.
		if (Empty(First)) {
			First = newNode;
			return;
		}

		//* If info is less than or equal then insert to the first element of the list.
		if (First->info.compare(info) >= 0) {
			PushFront(First, info);
			return;
		}

		//* Case the list has one item and the info is for sure greater then the first element.
		if (First->next == nullptr) {
			First->next = newNode;
			return;
		}

		//* From now on the list must has more than one (or at least two elements) and the inserting item is greater than the first one.
		Pointer previousNode = First;
		for (; previousNode->next != nullptr && previousNode->next->info.compare(info) <= 0; previousNode = previousNode->next);

		if (previousNode->next != nullptr) {
			newNode->next = previousNode->next;
			previousNode->next = newNode;
		}
		else {
			previousNode->next = newNode;
		}
	}

	void Traversal(const Pointer& First) {
		Pointer p = First;
		for (; p != nullptr; p = p->next) {
			std::cout << p->info << " ";
		}
		std::cout << "\n";
	}
}


DauSachTab::DauSachTab(Package* package)
{
	//* Initialize data
	this->package_ = package;
	this->titleList = package->titleList;
	this->inputController = package->inputController;

	this->titleListSortedByCategory = nullptr;
	this->datasheetDisplayFlag = true;
	this->active = false;

	this->datasheetController = DATASHEET::Controller(
		CONSTANTS::MAX_ROW_COUNT,
		DAU_SACH_PROPERTIES::PROPERTIES_COUNT,
		DAU_SACH_PROPERTIES::ROW_HEIGHT,
		HELPER::Coordinate(36, 120)
	);

	//* Create datasheet form the list
	DAU_SACH_TAB::CreateDatasheetsFromList(this->titleList, this->datasheetController);
	this->datasheetController.ActivateDatasheets(); //* Activate datasheet by default.

	//* Creating Button for adding or editting or removing item of the list
	HELPER::Coordinate listManipulateButtonCoordinates[] = {
		HELPER::Coordinate(380, 940),
		HELPER::Coordinate(565, 940),
		HELPER::Coordinate(750, 940)
	};
	HELPER::Dimension listManipulateButtonDimension(150, 30);
	std::string listManipulateButtonPlaceholders[] = { "NEW", "EDIT", "REMOVE" };
	for (int i = 0; i < 3; ++i) {
		this->functionalButtons[i] = Button(listManipulateButtonCoordinates[i], listManipulateButtonDimension);
		this->functionalButtons[i].SetPlaceholder(listManipulateButtonPlaceholders[i]);
		DANH_SACH_DAU_SACH_STYLING::ListManipulateButtonDefaultProperties(this->functionalButtons[i]);
	}
}

void DauSachTab::Destructor() {
	delete[] this->titleListSortedByCategory;
	delete this->inputController;
	delete this->titleList;
}

void DauSachTab::SortByCategory() {
	CATEGORY_LINKED_LIST::Pointer categories;
	CATEGORY_LINKED_LIST::Initialzie(categories);

	CATEGORY_LINKED_LIST::PushFront(categories, this->titleList->nodes[0]->GetCategory());
	bool flag = true;
	int categoryCount = 1;
	for (int i = 1; i < this->titleList->numberOfNode; ++i) {
		flag = true;
		for (int j = 0; j < i; ++j) {
			if (this->titleList->nodes[j]->GetCategory().compare(this->titleList->nodes[i]->GetCategory()) == 0) {
				flag = false;
				break;
			}
		}

		if (flag) {
			CATEGORY_LINKED_LIST::InsertOrder(categories, this->titleList->nodes[i]->GetCategory());
			++categoryCount;
		}
	}

	this->titleListSortedByCategory = new BOOK_TITLE::BookTitle * [this->titleList->numberOfNode];
	int index = 0;
	for (CATEGORY_LINKED_LIST::Pointer p = categories; p != nullptr; p = p->next) {
		for (int i = 0; i < this->titleList->numberOfNode; ++i) {
			if (this->titleList->nodes[i]->GetCategory().compare(p->info) == 0) {
				this->titleListSortedByCategory[index++] = this->titleList->nodes[i];
			}
		}
	}

	//for (int i = 0; i < this->titleList->numberOfNode; ++i) {
	//	std::cerr << this->titleListSortedByCategory[i]->GetTitle() << " - " << this->titleListSortedByCategory[i]->GetCategory() << "\n";
	//}

	delete categories;
}

void DauSachTab::Run() {

	/**
	 * * The tab will displays the Titles's datasheets by default.
	 * * Follow up with the avalable function such as CREATE/UPDATE/DELETE to the Titles database.
	 * * There will be a Search session for users to search for the needed title by searching by it's name.
	 * * User can press the datasheet's label in order to sort the items by the corresponding label.
	 *
	 * ! Currently, the datasheets are sorted by the title's names and can be sorted by the title's category.
	*/
	if (this->datasheetController.DisplayStatus() == true) {

		//* Display datasheets
		this->datasheetController.Display();
		this->datasheetController.DatasheetChangeButtonUpdate();

		//* Display functional buttons
		for (int i = 0; i < 3; ++i) {
			this->functionalButtons[i].Display();
		}

		//* Display search field
		this->searchField.Activate();
		this->searchField.Display();
		this->searchField.OnAction(this->inputController);
		BOOK_TITLE::BookTitle* searchResult = LINEAR_LIST::SearchByName(*this->titleList, this->searchField.inputSearchBox->GetPlaceholder());

		//* Title search logic
		if (searchResult != nullptr) {
			this->searchField.searchStatusBox->SetPlaceholder("SHOW DETAILS");
			this->searchField.searchStatusBox->SetFillColor(rgb(97, 177, 90));
			this->searchField.searchStatusBox->SetBorderColor(rgb(182, 227, 136));
			this->searchField.searchStatusBox->SetTextColor(WHITE);
			this->searchField.searchStatusBox->Display();

			//* Shor detail button logic
			if (this->searchField.searchStatusBox->IsHover()) {
				this->searchField.searchStatusBox->SetFillColor(rgb(199, 242, 164));
			}
			else if (this->searchField.searchStatusBox->LeftMouseClicked()) {
				this->searchField.targetDetails.Activate();
				this->searchField.targetDetails.Initialize(searchResult);
			}
			else {
				this->searchField.searchStatusBox->SetFillColor(rgb(97, 177, 90));
			}
		}
		else {
			this->searchField.targetDetails.Deactivate();
			this->datasheetController.ActivateDatasheets();
			DANH_SACH_DAU_SACH_SEARCH_FIELD_STYLING::StatusBoxStyling(this->searchField.searchStatusBox);
		}

		//* Sort by name (default option)
		Button& titleLabelButton = this->datasheetController[this->datasheetController.CurrentActiveDatasheet()][0][2];
		if (titleLabelButton.IsHover()) {
			titleLabelButton.SetFillColor(rgb(83, 127, 231));
			titleLabelButton.SetTextColor(rgb(233, 248, 249));
		}
		else if (titleLabelButton.LeftMouseClicked()) {
			delay(100);
			DAU_SACH_TAB::CreateDatasheetsFromList(this->titleList, this->datasheetController);
		}
		else {
			titleLabelButton.SetFillColor(rgb(210, 218, 255));
			titleLabelButton.SetTextColor(BLACK);
		}

		//* Sort by category logic
		Button& categoryLabelButton = this->datasheetController[this->datasheetController.CurrentActiveDatasheet()][0][6];
		if (categoryLabelButton.IsHover()) {
			categoryLabelButton.SetFillColor(rgb(83, 127, 231));
			categoryLabelButton.SetTextColor(rgb(233, 248, 249));
		}
		else if (categoryLabelButton.LeftMouseClicked()) {
			delay(100);
			this->SortByCategory();
			DAU_SACH_TAB::CreateDatasheetsWithSortedCategory(this->titleListSortedByCategory, this->titleList->numberOfNode, this->datasheetController);
		}
		else {
			categoryLabelButton.SetFillColor(rgb(210, 218, 255));
			categoryLabelButton.SetTextColor(BLACK);
		}

		/**
		 * * Book list on action logic
		 * * When hovering the mouse on the title's name, change the pointing button's fill color.
		 * * When pressed at the title's name button, display the title's details.
		 *
		 * ! Currently, the UI design of this function is not very good!
		*/
		for (int i = 1; i < this->datasheetController.GetRecordCount(); ++i) {
			Button& titleNameButton = this->datasheetController[this->datasheetController.CurrentActiveDatasheet()][i][2];

			if (titleNameButton.IsHover()) {
				titleNameButton.SetFillColor(rgb(244, 249, 249));
			}
			else if (titleNameButton.LeftMouseClicked()) {
				delay(100);
				this->datasheetController.DeactivateDatasheets();
				this->titleDetailField.Activate();
				this->titleDetailField.Initialize(
					this->titleList->nodes[this->datasheetController.CurrentActiveDatasheet() * 15 + i - 1]
				);
			}
			else {
				if (i % 2 != 0) {
					titleNameButton.SetFillColor(rgb(255, 251, 245));
				}
				else {
					titleNameButton.SetFillColor(rgb(238, 238, 238));
				}
			}
		}

		/**
		 * * Functional buttons on action logic
		 * * When hovering the mouse on the functional buttons, highlight the corresponding button by changing the fill color.
		 * * Pressed at each button will activate the corresponding function.
		*/
		for (int i = 0; i < 3; ++i) {
			Button& currentBtn = this->functionalButtons[i];

			if (currentBtn.IsHover()) {
				DANH_SACH_DAU_SACH_STYLING::ListManipulateButtonHoverProperties(currentBtn);
			}
			else if (currentBtn.LeftMouseClicked()) {
				switch (i) {
					delay(100);
					case (0):
						this->datasheetController.DeactivateDatasheets();
						this->titleCreatingSection = DAU_SACH_TAB::TitleCreatingSection(this->package_);
						this->titleCreatingSection.Activate();
						break;
					case (1):
						std::cerr << "edit item!\n";
						break;
					case (2):
						std::cerr << "remove item!\n";
						break;
				}
			}
			else {
				DANH_SACH_DAU_SACH_STYLING::ListManipulateButtonDefaultProperties(currentBtn);
			}
		}
	}

	//* Displaying founded search target
	if (this->searchField.targetDetails.GetStatus()) {
		this->datasheetController.DeactivateDatasheets();
		this->searchField.targetDetails.Display();
		this->searchField.targetDetails.DeleteBookButtonOnAction();

		if (this->searchField.targetDetails.GoBackButtonOnAction()) {
			this->datasheetController.ActivateDatasheets();
			this->searchField.targetDetails.Deactivate();
			this->searchField.inputSearchBox->SetPlaceholder("Type here to search");
			this->searchField.searchStatusBox->SetPlaceholder("Result: NOT FOUND!");
			DANH_SACH_DAU_SACH_SEARCH_FIELD_STYLING::StatusBoxStyling(this->searchField.searchStatusBox);
		}
	}

	//* Displaying title's details field
	if (this->titleDetailField.GetStatus() == true) {
		this->titleDetailField.Display();
		if (this->titleDetailField.GoBackButtonOnAction() == true) {
			this->datasheetController.ActivateDatasheets();
		}
		else {
			this->datasheetController.DeactivateDatasheets();
		}
	}

	//* Displaying the ADD function.
	if (this->titleCreatingSection.GetStatus() == true) {
		this->titleCreatingSection.Display();

		if (this->titleCreatingSection.GoBackButtonOnAction()) {
			this->titleCreatingSection.Deactivate();
			this->datasheetController.ActivateDatasheets();
		}

		//WORKING
		bool newTitleListCreated = this->titleCreatingSection.Run();
		if (newTitleListCreated)
		{
			DAU_SACH_TAB::CreateDatasheetsFromList(this->titleList, this->datasheetController);
		}
	}


}
