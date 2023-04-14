#include "DanhSachTheDocGia.h"
#include "DanhSachTheDocGiaStyling.h"

#include "../../Graphics/graphics.h"
#include "../../Helper/Helper.h"
#include "../../Helper/ConstantsAndGlobalVariables.h"
#include "../../TheDocGia/TheDocGia.h"
#include "../../DataStructures/Stack.h"

#include <iostream>
#include <format>
#include <string>


SearchField::SearchField() {
	this->background = new ELEMENTS::Fill(HELPER::Coordinate(1305, 120), 450, 250);
	this->title = new ELEMENTS::Button(HELPER::Coordinate(1305, 120), 450, 50);
	this->title->SetPlaceholder("SEARCH");

	this->inputSearchBox = new ELEMENTS::Button(HELPER::Coordinate(1330, 200), 400, 70);
	this->inputSearchBox->SetPlaceholder("Type here to search");

	this->searchStatusBox = new ELEMENTS::Button(HELPER::Coordinate(1330, 295), 400, 50);
	this->searchStatusBox->SetPlaceholder("Result:");
}

void SearchField::Display() {
	DANH_SACH_THE_DOC_GIA_SEARCH_FIELD_STYLING::BackgroundStyling(this->background);
	DANH_SACH_THE_DOC_GIA_SEARCH_FIELD_STYLING::TitleStyling(this->title);
	DANH_SACH_THE_DOC_GIA_SEARCH_FIELD_STYLING::SearchBoxStyling(this->inputSearchBox);
	DANH_SACH_THE_DOC_GIA_SEARCH_FIELD_STYLING::StatusBoxStyling(this->searchStatusBox);

	this->background->Draw();
	this->title->Display();
	this->inputSearchBox->Display();
	this->searchStatusBox->Display();
}

NewListItemForm::NewListItemForm() {
	this->background = new ELEMENTS::Fill(HELPER::Coordinate(1305, 420), 450, 500);

	this->title = new ELEMENTS::Button(HELPER::Coordinate(1305, 420), 450, 50);
	this->title->SetPlaceholder("THE DOC GIA");

	this->maThe = new ELEMENTS::Button(HELPER::Coordinate(1330, 500), 400, 60);
	this->maThe->SetPlaceholder("Ma the");

	this->ho = new ELEMENTS::Button(HELPER::Coordinate(1330, 590), 400, 60);
	this->ho->SetPlaceholder("Ho");

	this->ten = new ELEMENTS::Button(HELPER::Coordinate(1330, 680), 400, 60);
	this->ten->SetPlaceholder("Ten");

	this->phai = new ELEMENTS::Button(HELPER::Coordinate(1330, 770), 400, 60);
	this->phai->SetPlaceholder("Phai");

	this->submit = new ELEMENTS::Button(HELPER::Coordinate(1455, 855), 150, 40);
	this->submit->SetPlaceholder("SUBMIT");

	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::BackgroundStyling(this->background);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::TitleStyling(this->title);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(this->maThe);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(this->ho);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(this->ten);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(this->phai);
	DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::SubmitButtonStyling(this->submit);
}

NewListItemForm::~NewListItemForm() {
	delete this->background;
	delete this->title;
	delete this->maThe;
	delete this->ho;
	delete this->ten;
	delete this->phai;
	delete this->submit;
}

void NewListItemForm::Display() {
	this->background->Draw();
	this->title->Display();
	this->maThe->Display();
	this->ho->Display();
	this->ten->Display();
	this->phai->Display();
	this->submit->Display();
}

bool NewListItemForm::SubmitForm(AVL_TREE::Pointer& dsTheDocGia, ELEMENTS::InputModeController& InputController) {
	ELEMENTS::Button* formInputField[3] = { this->ho, this->ten, this->phai };
	int fieldCharacterLimit[3] = { 30, 15, 3 };

	int nextIndex = THE_DOC_GIA_MODULES::GetIndex(CONSTANTS::THE_DOC_GIA_INDEX, dsTheDocGia);
	this->maThe->SetPlaceholder(std::to_string(nextIndex));

	for (int i = 0; i < 3; ++i) {
		if (formInputField[i]->IsPointed() && formInputField[i]->LeftMouseClicked() == false) {
			DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxHoverProperties(formInputField[i]);
		}
		else if (formInputField[i]->LeftMouseClicked()) {
			InputController.Activate(formInputField[i], formInputField[i], fieldCharacterLimit[i], true, false, true);
		}
		else {
			DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::InputBoxStyling(formInputField[i]);
		}
	}

	if (this->submit->IsHover()) {
		DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::SubmutButtonHoverStyling(this->submit);
	}
	else if (this->submit->LeftMouseClicked()) {
		THE_DOC_GIA::TheDocGia newItem;

		newItem.SetMaThe(nextIndex);
		newItem.SetHo(STR::Trim(this->ho->GetPlaceholder()));
		newItem.SetTen(STR::Trim(this->ten->GetPlaceholder()));
		newItem.SetPhai(this->phai->GetPlaceholder() == "NAM" ? THE_DOC_GIA::GioiTinh::NAM : THE_DOC_GIA::GioiTinh::NU);
		newItem.SetTrangThai(THE_DOC_GIA::TrangThaiThe::THE_HOAT_DONG);
		newItem.SetDanhSachMuonTra(DOUBLE_LINKED_LIST::Controler());
		delay(100);

		std::cerr << std::format("mathe: \"{}\"\n", newItem.GetMaThe());
		std::cerr << std::format("ho: \"{}\"\n", newItem.GetHo());
		std::cerr << std::format("ten: \"{}\"\n", newItem.GetTen());
		std::cerr << std::format("phai: \"{}\"\n", newItem.GetStringfyPhai());
		std::cerr << std::format("trangthai: \"{}\"\n", newItem.GetStringfyTrangThai());

		bool res = AVL_TREE::Insert(dsTheDocGia, newItem);

		std::cerr << std::format("res = {}\n", res);
		delay(10000);

		return true;
	}
	else {
		DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING::SubmitButtonStyling(this->submit);
	}

	return false;
}

void DanhSachTheDocGiaView::CreateDatasheetsFromList(AVL_TREE::Pointer& danhSachThedocGia, DATASHEET::Controler* datasheetController) {

	int recordCount = 0;
	AVL_TREE::CountNode(danhSachThedocGia, recordCount);
	datasheetController->datasheetCount = recordCount / (CONSTANTS::MAX_ROW_COUNT - 1) + (recordCount % (CONSTANTS::MAX_ROW_COUNT - 1) == 0 ? 0 : 1);
	datasheetController->sheets = new DATASHEET::Datasheet[datasheetController->datasheetCount];
	datasheetController->activeSheet = 0;

	for (int i = 0; i < datasheetController->datasheetCount; ++i) {
		datasheetController->sheets[i] = DATASHEET::Datasheet(
			datasheetController->rowCount,
			datasheetController->columnCount,
			datasheetController->rowHeight,
			datasheetController->topLeft,
			(std::string*)THE_DOC_GIA_PROPERTIES::LABEL_PLACEHOLDERS, (int*)THE_DOC_GIA_PROPERTIES::CHARACTER_LIMITS
		);
	}

	STACK::Stack stk;
	STACK::Initialize(stk);
	AVL_TREE::Pointer currentNode = danhSachThedocGia;
	int rowIndicator = 0;
	int sheetIndicator = -1;

	do {
		while (currentNode != nullptr) {
			STACK::Push(stk, currentNode);
			currentNode = currentNode->left;
		}

		if (STACK::IsEmpty(stk) == false) {
			currentNode = STACK::Pop(stk);
			
			//* Logic stays here
			++rowIndicator;
			if (rowIndicator % CONSTANTS::MAX_ROW_COUNT == 1) {
				++sheetIndicator;
			}

			std::string* data = new std::string[datasheetController->columnCount];
			data[0] = std::to_string(rowIndicator);
			data[1] = std::to_string(currentNode->info.GetMaThe());
			data[2] = currentNode->info.GetHo();
			data[3] = currentNode->info.GetTen();
			data[4] = currentNode->info.GetStringfyPhai();
			data[5] = currentNode->info.GetStringfyTrangThai();
			data[6] = "SACH DANG MUON";

			datasheetController->sheets[sheetIndicator].UpdateNewPlaceholder(data, rowIndicator % CONSTANTS::MAX_ROW_COUNT);

			//---

			currentNode = currentNode->right;
		}
		else {
			break;
		}
	} while (true);
}

/**
* Tab's constructor
* 
* All the code in this method only run once in the program runtime!
*/
DanhSachTheDocGiaView::DanhSachTheDocGiaView(AVL_TREE::Pointer& danhSachTheDocGia) {
	this->active = false;
	
	HELPER::Coordinate datasheetTopLeft(36, 120);
	HELPER::Coordinate toLeftBtnTopLeft(36, 935);
	HELPER::Coordinate toRightBtnTopLeft(86, 935);

	this->controler = DATASHEET::Controler(
		CONSTANTS::MAX_ROW_COUNT, THE_DOC_GIA_PROPERTIES::PROPERTIES_COUNT, 
		THE_DOC_GIA_PROPERTIES::ROW_HEIGHT, datasheetTopLeft
	);
	this->CreateDatasheetsFromList(danhSachTheDocGia, &this->controler);

	this->sheetChange[0] = ELEMENTS::Button(toLeftBtnTopLeft, 50, 30);
	this->sheetChange[1] = ELEMENTS::Button(toRightBtnTopLeft, 50, 30);
	this->sheetChange[0].SetPlaceholder("<");
	this->sheetChange[1].SetPlaceholder(">");
	for (int i = 0; i < 2; ++i) {
		DANH_SACH_THE_DOC_GIA_STYLING::DefaultDatasheetChangeButtonProperties(this->sheetChange[i]);
	}

	//* List manipulation buttons
	this->listManipulationButtonStatus = -1;
	std::string listManipulateButtonPlaceholders[] = { "New", "Edit", "Remove" };
	HELPER::Coordinate listManipulateButtonCoordinate[] = {
		HELPER::Coordinate(380, 940),
		HELPER::Coordinate(565, 940),
		HELPER::Coordinate(750, 940)
	};
	for (int i = 0; i < 3; ++i) {
		this->listManipulateButton[i] = ELEMENTS::Button(listManipulateButtonCoordinate[i], 150, 30);
		this->listManipulateButton[i].SetPlaceholder(listManipulateButtonPlaceholders[i]);
		DANH_SACH_THE_DOC_GIA_STYLING::ListManipulateButtonDefaultProperties(this->listManipulateButton[i]);
	}
}

/**
* Tab's frame logic.
* 
* Code in this method will be run many time.
* Each time the program render a frame, this code will be run once, therefore the element's logic will be in here!
*/
void DanhSachTheDocGiaView::Run(AVL_TREE::Pointer& danhSachTheDocGia, ELEMENTS::InputModeController& InputController) {
	
	//* Display datasheet
	this->controler.Display();
	
	//* Display datasheet page move button
	for (int i = 0; i < 2; ++i) {
		this->sheetChange[i].Display();
	}

	//* Display function button
	for (int i = 0; i < 3; ++i) {
		this->listManipulateButton[i].Display();
	}

	//* Display Search field
	this->searchField.Display();

	//* Detect if there is a function got activated
	if (this->listManipulationButtonStatus != -1) {
		switch (this->listManipulationButtonStatus) {
		case (0): {
			//* Display form
			this->newItemForm.Display();
			bool formSubmitted = this->newItemForm.SubmitForm(danhSachTheDocGia, InputController);
			std::cerr << std::format("form submitted: {}\n", formSubmitted);

			if (formSubmitted) {
				DanhSachTheDocGiaView::CreateDatasheetsFromList(danhSachTheDocGia, &this->controler);
			}
			break;
		}
		case (1): {
			break;
		}
		case (2): {
			break;
		}
		}
	}

	//* Sheet's changes button logic
	for (int i = 0; i < 2; ++i) {
		if (this->sheetChange[i].IsPointed() && this->sheetChange[i].LeftMouseClicked() == false) {
			DANH_SACH_THE_DOC_GIA_STYLING::DatasheetChangeButtonNHoverProperties(this->sheetChange[i]);
		}
		else if (this->sheetChange[i].LeftMouseClicked()) {
			if (i == 0) {
				if (this->controler.activeSheet == 0) {
					this->controler.activeSheet = this->controler.datasheetCount - 1;
				}
				else {
					--this->controler.activeSheet;
				}
			}
			else {
				if (this->controler.activeSheet == this->controler.datasheetCount - 1) {
					this->controler.activeSheet = 0;
				}
				else {
					++this->controler.activeSheet;
				}
			}
			delay(100);
		}
		else {
			DANH_SACH_THE_DOC_GIA_STYLING::DefaultDatasheetChangeButtonProperties(this->sheetChange[i]);
		}
	}

	//* List manipulate button logic
	for (int i = 0; i < 3; ++i) {

		if (this->listManipulateButton[i].IsPointed() && this->listManipulateButton[i].LeftMouseClicked() == false) {
			DANH_SACH_THE_DOC_GIA_STYLING::ListManipulateButtonHoverProperties(this->listManipulateButton[i]);
		}
		else if (this->listManipulateButton[i].LeftMouseClicked()) {
			switch (i) {
				case (0): {//* Pressed new button
					this->listManipulationButtonStatus = 0;
					break;
				}
				case (1): {
					this->listManipulationButtonStatus = 1;
					break;
				}
				case (2): {
					this->listManipulationButtonStatus = 2;
					break;
				}
			}

			delay(100);
		}
		else {
			if (i != this->listManipulationButtonStatus) {
				DANH_SACH_THE_DOC_GIA_STYLING::ListManipulateButtonDefaultProperties(this->listManipulateButton[i]);
			}
		}
	}
}