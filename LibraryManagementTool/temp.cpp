//
//#include <iostream>
//#include <string>
//#include <format>
//#include <thread>
//#include "Graphics/graphics.h"
//#pragma comment(lib, "Graphics/graphics.lib")
//
//#include "Helper/Helper.h"
//#include "Views/Elements.h"
//#include "DauSach/DauSach.h"
//#include "Views/LandingView.h"
//
//
///*
//bool validInput(std::string input) {
//	return input.length() <= 10;
//}
//
//bool validKey(char key) {
//	return isalpha(key);
//}
//
//#include "DanhSachTheDocGia.h"
//#include "Elements.h"
//#include "../Graphics/graphics.h"
//#include "../Helper/Helper.h"
//#include "../Helper/ConstantsAndGlobalVariables.h"
//#include "../TheDocGia/TheDocGia.h"
//
//#include <iostream>
//#include <format>
//#include <string>
//
//struct Row {
//	HELPER::Coordinate topLeft;
//	HELPER::Coordinate bottomRight;
//	ELEMENTS::Cell columns[7];
//	int rowHeight = 0;
//	int colIndicator = 1;
//	std::string defaultPlaceholder = "...";
//
//	Row() {
//		this->topLeft = HELPER::Coordinate();
//		this->bottomRight = HELPER::Coordinate();
//	}
//
//	Row(HELPER::Coordinate startPosition, int rowHeight) {
//		this->topLeft = startPosition;
//		this->rowHeight = rowHeight;
//	}
//
//	void Initialize(std::string* placeholders, int* characterLimits) {
//		for (int i = 0; i < 7; ++i) {
//			if (i == 0) {
//				columns[i] = ELEMENTS::Cell(ELEMENTS::Cell::Mode::READ_MODE, placeholders[i], topLeft, -1, rowHeight, characterLimits[i]);
//			}
//			else {
//				columns[i] = ELEMENTS::Cell(
//					ELEMENTS::Cell::Mode::READ_MODE, placeholders[i],
//					HELPER::Coordinate(columns[i - 1].GetPosition().x + columns[i - 1].GetDimension().width, columns[i - 1].GetPosition().y),
//					-1, rowHeight,
//					characterLimits[i]
//				);
//			}
//		}
//		this->bottomRight.x = columns[6].GetPosition().x + columns[6].GetDimension().width;
//		this->bottomRight.y = this->topLeft.y + this->rowHeight;
//	}
//
//	void Initialize(int* columnWidth, int* characterLimits) {
//		for (int i = 0; i < 7; ++i) {
//			if (i == 0) {
//				columns[i] = ELEMENTS::Cell(
//					ELEMENTS::Cell::Mode::READ_MODE,
//					this->defaultPlaceholder,
//					topLeft,
//					columnWidth[i], rowHeight,
//					characterLimits[i]
//				);
//			}
//			else {
//				columns[i] = ELEMENTS::Cell(
//					ELEMENTS::Cell::Mode::READ_MODE, this->defaultPlaceholder,
//					HELPER::Coordinate(columns[i - 1].GetPosition().x + columns[i - 1].GetDimension().width, columns[i - 1].GetPosition().y),
//					columnWidth[i], rowHeight,
//					characterLimits[i]
//				);
//			}
//		}
//		this->bottomRight.x = columns[6].GetPosition().x + columns[6].GetDimension().width;
//		this->bottomRight.y = this->topLeft.y + this->rowHeight;
//	}
//
//	void Render() {
//		for (int i = 0; i < 7; ++i) {
//			columns[i].ReadMode();
//		}
//	}
//};
//
//void LabelsProperties(Row& labelsRow) {
//	for (int i = 0; i < 7; ++i) {
//		labelsRow.columns[i].SetHorizontalAlign(ELEMENTS::Align::CENTER);
//		labelsRow.columns[i].SetVerticalAlign(ELEMENTS::Align::MIDDLE);
//		labelsRow.columns[i].SetBackgroundColor(rgb(243, 222, 186));
//		labelsRow.columns[i].SetBorderColor(rgb(77, 77, 77));
//	}
//}
//
//void InputFieldProperties(Row& row, int order) {
//	for (int i = 0; i < 7; ++i) {
//		row.columns[i].SetHorizontalAlign(ELEMENTS::Align::CENTER);
//		row.columns[i].SetVerticalAlign(ELEMENTS::Align::MIDDLE);
//		row.columns[i].SetBackgroundColor(rgb(255, 244, 224));
//		row.columns[i].SetBorderColor(rgb(77, 77, 77));
//	}
//	row.columns[0].LoadContent(std::to_string(order));
//}
//
///**
//* The Menu structure provides a overall better control over the input field and the label and bring a lot more convenient in the
//* development process and future project maintain and scale.
//*/
//struct Menu {
//	std::string placeholders[7] = { "STT", "MA THE", "HO", "TEN", "PHAI", "TRANG THAI", "SACH DANG MUON" };
//	int characterLimits[7] = { 3, 6, 30, 10, 3, 9, 10 };
//	HELPER::Coordinate menuTopLeft;
//	HELPER::Coordinate menuBottomRight;
//	HELPER::Dimension menuDimension;
//	const int rowCount = 15;
//	int rowHeight = 0;
//	Row table[16];
//
//	Menu(HELPER::Coordinate topLeft, int rowHeight) {
//		this->menuTopLeft = topLeft;
//		this->rowHeight = rowHeight;
//	}
//
//	void Initialize() {
//		//* Setup table
//		table[0] = Row(this->menuTopLeft, rowHeight);
//		table[0].Initialize(placeholders, characterLimits);
//		LabelsProperties(table[0]);
//
//		int columnWidth[7]{};
//		for (int i = 0; i < 7; ++i) {
//			columnWidth[i] = table[0].columns[i].GetDimension().width;
//		}
//
//		for (int i = 1; i <= rowCount; ++i) {
//			table[i] = Row(HELPER::Coordinate(table[i - 1].topLeft.x, table[i - 1].bottomRight.y), this->rowHeight);
//			table[i].Initialize(columnWidth, characterLimits);
//			InputFieldProperties(table[i], i);
//		}
//
//		this->menuBottomRight.x = table[0].columns[6].GetPosition().x + table[0].columns[6].GetDimension().width;
//		this->menuBottomRight.y = table[0].columns[6].GetPosition().y + table[0].columns[6].GetDimension().height;
//	}
//
//	void Render() {
//		for (int i = 0; i <= rowCount; ++i) {
//			this->table[i].Render();
//		}
//	}
//};
//
//void DANH_SACH_THE_DOC_GIA_VIEW::Run(AVL_TREE::Pointer& danhSachTheDocGia) {
//
//	//* Setup background
//	setfillstyle(SOLID_FILL, WHITE);
//	bar(0, 0, CONSTANTS::WINDOW_DIMENSION.width, CONSTANTS::WINDOW_DIMENSION.height);
//
//	//* Setup UI elements
//	Menu menu(HELPER::Coordinate(1, 61), 50);
//	menu.Initialize();
//
//	ELEMENTS::Cell titleBox(ELEMENTS::Cell::Mode::READ_MODE, "DANH SACH THE DOC GIA", HELPER::Coordinate(1, 1), HELPER::Dimension(menu.menuBottomRight.x - menu.menuTopLeft.x, 60), 0);
//	titleBox.SetHorizontalAlign(ELEMENTS::Align::CENTER);
//	titleBox.SetVerticalAlign(ELEMENTS::Align::MIDDLE);
//	titleBox.SetBackgroundColor(rgb(103, 93, 80));
//	titleBox.SetTextColor(WHITE);
//
//	std::string placeholders[7] = { "STT", "MA THE", "HO", "TEN", "PHAI", "TRANG THAI", "SACH DANG MUON" };
//	int characterLimits[7] = { 3, 6, 30, 10, 3, 9, 10 };
//
//	//* Setup view loop
//	char inputKey{};
//	while (inputKey != ELEMENTS::SpecialKey::ESCAPE) {
//
//		//* UI elements display
//		titleBox.ReadMode();
//		menu.Render();
//
//		//* Key register
//		inputKey = getch();
//
//		//* View's logic
//	}
//
//	//* Clear View
//	setfillstyle(SOLID_FILL, WHITE);
//	bar(0, 0, CONSTANTS::WINDOW_DIMENSION.width, CONSTANTS::WINDOW_DIMENSION.height);
//}
//
//
//*/
////! Do not delete the above code!