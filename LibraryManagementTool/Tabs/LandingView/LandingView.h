#pragma once

#ifndef LANDING_VIEW
#define LANDING_VIEW

#include "../DanhSachTheDocGiaTab/DanhSachTheDocGia.h"
#include "../DanhSachDauSachTab/DanhSachDauSachView.h"
#include "../ThongKeTab/ThongKeView.h"
#include "LandingViewStyling.h"

class LandingView {
private:
	ELEMENTS::Window* graphicWindow;
	HELPER::Fill* navigationBarBackground;
	Button* programTitle;
	Button* tabs;
	ELEMENTS::CloseButton* closeBtn;

	DauSachTab* dauSachView;
	DanhSachTheDocGiaView* theDocGiaView;
	ThongKeView* thongKeView;

	ELEMENTS::InputModeController inpController;

private:
	void ConstructGraphicWindow();

	void ConstructNavigationBar();

public:
	LandingView(AVL_TREE::Pointer& danhSachTheDocGia, LINEAR_LIST::LinearList& danhSachDauSach);

	~LandingView();

	void Run(AVL_TREE::Pointer& dsTheDocGia, LINEAR_LIST::LinearList& dsDauSach);
};



#endif // !LANDING_VIEW
