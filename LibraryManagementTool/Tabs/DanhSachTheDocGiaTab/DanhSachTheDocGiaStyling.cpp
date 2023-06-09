
#include "DanhSachTheDocGiaStyling.h"

namespace DANH_SACH_THE_DOC_GIA_SEARCH_FIELD_STYLING {
	void BackgroundStyling(HELPER::Fill* background) {
		background->fillColor = rgb(238, 238, 238);
		background->borderColor = BLACK;
	}

	void TitleStyling(Button* title) {
		title->SetFillColor(rgb(87, 108, 188));
		title->SetBorderColor(BLACK);
		title->SetTextColor(rgb(247, 247, 247));
	}

	void SearchBoxStyling(Button* bx) {
		bx->SetFillColor(rgb(255, 251, 245));
		bx->SetBorderColor(BLACK);
		bx->SetTextColor(rgb(57, 62, 70));
	}

	void StatusBoxStyling(Button* bx) {
		bx->SetFillColor(rgb(238, 238, 238));
		bx->SetBorderColor(bx->GetFillColor());
		bx->SetTextColor(rgb(57, 62, 70));
	}
}

namespace DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING {
	void BackgroundStyling(HELPER::Fill* background) {
		background->fillColor = rgb(238, 238, 238);
		background->borderColor = BLACK;
	}

	void TitleStyling(Button* title) {
		title->SetFillColor(rgb(87, 108, 188));
		title->SetBorderColor(BLACK);
		title->SetTextColor(rgb(247, 247, 247));
	}

	void InputBoxStyling(Button* btn) {
		btn->SetFillColor(rgb(255, 251, 245));
		btn->SetBorderColor(BLACK);
		btn->SetTextColor(rgb(57, 62, 70));
	}

	void SubmitButtonStyling(Button* btn) {
		btn->SetFillColor(rgb(3, 201, 136));
		btn->SetBorderColor(btn->GetFillColor());
		btn->SetTextColor(rgb(57, 62, 70));
	}

	void SubmutButtonHoverStyling(Button* btn) {
		btn->SetFillColor(rgb(217, 248, 196));
		btn->SetBorderColor(rgb(122, 168, 116));
		btn->SetTextColor(rgb(26, 18, 11));
	}

	void InputBoxHoverProperties(Button* btn) {
		btn->SetBorderColor(rgb(70, 73, 255));
		btn->SetFillColor(rgb(234, 253, 252));
	}
}

namespace DANH_SACH_THE_DOC_GIA_STYLING {
	void ListManipulateButtonDefaultProperties(Button& btn) {
		btn.SetFillColor(rgb(219, 223, 253));
		btn.SetBorderColor(btn.GetFillColor());
		btn.SetTextColor(rgb(57, 62, 70));
	}

	void ListManipulateButtonHoverProperties(Button& btn) {
		btn.SetFillColor(rgb(155, 163, 235));
		btn.SetBorderColor(rgb(36, 47, 155));
		btn.SetTextColor(rgb(234, 253, 252));
	}

	void NewItemButtonActiveProperties(Button& btn) {
		btn.SetFillColor(rgb(130, 170, 227));
		btn.SetBorderColor(rgb(57, 62, 70));
		btn.SetTextColor(rgb(57, 62, 70));
	}

	void DatasheetLabelsButtonHoverStyling(Button* btn) {
		btn->SetFillColor(rgb(116, 141, 166));
		btn->SetTextColor(rgb(249, 249, 249));
	}

	void DatasheetLabelsButtonDefaultStyling(Button* btn) {
		btn->SetFillColor(rgb(210, 218, 255));
		btn->SetTextColor(rgb(25, 24, 37));
		btn->SetBorderColor(rgb(25, 24, 37));
	}

	void DatasheetChangeButtonNHoverProperties(Button& btn) {
		btn.SetFillColor(rgb(130, 170, 227));
	}

	void DefaultDatasheetChangeButtonProperties(Button& btn) {
		btn.SetFillColor(rgb(236, 242, 255));
		btn.SetBorderColor(rgb(25, 24, 37));
		btn.SetTextColor(rgb(25, 24, 37));
	}
}
