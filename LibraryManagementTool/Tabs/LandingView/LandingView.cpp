#include "LandingView.h"
#include "../../Helper/Helper.h"
#include "../../Helper/ConstantsAndGlobalVariables.h"

#include <iostream>
#include <string>
#include <format>
#include <ctime>



void LandingView::ConstructGraphicWindow()
{
	this->graphicWindow = new ELEMENTS::Window { WINDOW_PROPERTIES::DIMENSION, WINDOW_PROPERTIES::TITLE };
	this->graphicWindow->backgroundColor = WHITE;
}

void LandingView::ConstructNavigationBar()
{
	this->navigationBarBackground = HELPER::Fill
	(
		NAVIGATION_BAR_PROPERTIES::COORDINATE, 
		NAVIGATION_BAR_PROPERTIES::DIMENSION.width, NAVIGATION_BAR_PROPERTIES::DIMENSION.height,
		NAVIGATION_BAR_PROPERTIES::FILL_COLOR, NAVIGATION_BAR_PROPERTIES::BORDER_COLOR
	);

	this->programTitle = Button{
		NAVIGATION_BAR_PROPERTIES::PROGRAM_TITLE_COORDINATE, NAVIGATION_BAR_PROPERTIES::PROGRAM_TITLE_DIMENSION
	};
	this->programTitle.SetFillColor(NAVIGATION_BAR_PROPERTIES::PROGRAM_TITLE_FILL_COLOR);
	this->programTitle.SetBorderColor(NAVIGATION_BAR_PROPERTIES::PROGRAM_TITLE_BORDER_COLOR);
	this->programTitle.SetTextColor(NAVIGATION_BAR_PROPERTIES::PROGRAM_TITLE_TEXT_COLOR);
	this->programTitle.SetPlaceholder(NAVIGATION_BAR_PROPERTIES::PROGRAM_TITLE_PLACEHOLDER);

	for (int i = 0; i < 3; ++i)
	{
		this->tabs[i] = Button(
			NAVIGATION_BAR_PROPERTIES::TAB_COORDINATE[i], NAVIGATION_BAR_PROPERTIES::TAB_DIMENSION
		);
		this->tabs[i].SetPlaceholder(NAVIGATION_BAR_PROPERTIES::TAB_PLACEHOLDER[i]);
		this->tabs[i].SetFillColor(NAVIGATION_BAR_PROPERTIES::TAB_DEFAULT_FILL_COLOR);
		this->tabs[i].SetBorderColor(NAVIGATION_BAR_PROPERTIES::TAB_DEFAULT_BORDER_COLOR);
		this->tabs[i].SetTextColor(NAVIGATION_BAR_PROPERTIES::TAB_DEFAULT_TEXT_COLOR);
	}
	this->currentTab = 0;
	this->tabs[this->currentTab].SetFillColor(NAVIGATION_BAR_PROPERTIES::TAB_ACTIVE_FILL_COLOR);
	this->tabs[this->currentTab].SetBorderColor(NAVIGATION_BAR_PROPERTIES::TAB_ACTIVE_BORDER_COLOR);
	this->tabs[this->currentTab].SetTextColor(NAVIGATION_BAR_PROPERTIES::TAB_ACTIVE_TEXT_COLOR);

	this->closeBtn = ELEMENTS::CloseButton(
		NAVIGATION_BAR_PROPERTIES::CLOSE_BUTTON_COORDINATE, 
		NAVIGATION_BAR_PROPERTIES::CLOSE_BUTTON_DIMENSION.width,
		NAVIGATION_BAR_PROPERTIES::CLOSE_BUTTON_DIMENSION.height
	);
	this->closeBtn.SetPlaceholder(NAVIGATION_BAR_PROPERTIES::CLOSE_BUTTON_PLACEHOLDER);
	this->closeBtn.SetFillColor(NAVIGATION_BAR_PROPERTIES::CLOSE_BUTTON_DEFAULT_FILL_COLOR);
	this->closeBtn.SetBorderColor(NAVIGATION_BAR_PROPERTIES::CLOSE_BUTTON_DEFAULT_BORDER_COLOR);
}

void LandingView::TabsOnUpdate()
{
	for (int i = 0; i < 3; ++i)
	{
		if (i != this->currentTab)
		{
			if (this->tabs[i].IsHover())
			{
				this->tabs[i].SetFillColor(NAVIGATION_BAR_PROPERTIES::TAB_HOVER_FILL_COLOR);
				this->tabs[i].SetBorderColor(NAVIGATION_BAR_PROPERTIES::TAB_HOVER_BORDER_COLOR);
				this->tabs[i].SetTextColor(NAVIGATION_BAR_PROPERTIES::TAB_HOVER_TEXT_COLOR);
			}
			else if (this->tabs[i].LeftMouseClicked())
			{
				delay(100);
				this->currentTab = i;

				switch (this->currentTab)
				{
					case (0): {
						
						break;
					}
					case (1): {
						break;
					}
					case (2): {

						this->thongKeView->Reset();
						break;
					}
				}
			}
			else
			{
				this->tabs[i].SetFillColor(NAVIGATION_BAR_PROPERTIES::TAB_DEFAULT_FILL_COLOR);
				this->tabs[i].SetBorderColor(NAVIGATION_BAR_PROPERTIES::TAB_DEFAULT_BORDER_COLOR);
				this->tabs[i].SetTextColor(NAVIGATION_BAR_PROPERTIES::TAB_DEFAULT_TEXT_COLOR);
			}
		}
	}
}

void LandingView::CloseButtonOnUpdate()
{
	if (this->closeBtn.IsPointed() && this->closeBtn.LeftMouseClicked() == false)
	{
		this->closeBtn.SetFillColor(NAVIGATION_BAR_PROPERTIES::CLOSE_BUTTON_HOVER_FILL_COLOR);
	}
	else if (closeBtn.LeftMouseClicked())
	{
		delay(100);
		this->programStopFlag = true;
	}
	else
	{
		this->closeBtn.SetFillColor(NAVIGATION_BAR_PROPERTIES::CLOSE_BUTTON_DEFAULT_FILL_COLOR);
		this->closeBtn.SetBorderColor(NAVIGATION_BAR_PROPERTIES::CLOSE_BUTTON_DEFAULT_BORDER_COLOR);
	}
}

//* View Run function
void LandingView::Run()
{
	while (this->programStopFlag == false) 
	{
		while (!kbhit() && this->programStopFlag == false)
		{
			//* Draw elements begin below
			setactivepage(1 - getactivepage());

			//* Draw elements
			this->graphicWindow->RenderBackground();
			this->navigationBarBackground.Draw();
			this->programTitle.Display();
		
			for (int i = 0; i < 3; ++i)
			{
				this->tabs[this->currentTab].SetFillColor(NAVIGATION_BAR_PROPERTIES::TAB_ACTIVE_FILL_COLOR);
				this->tabs[this->currentTab].SetBorderColor(NAVIGATION_BAR_PROPERTIES::TAB_ACTIVE_BORDER_COLOR);
				this->tabs[this->currentTab].SetTextColor(NAVIGATION_BAR_PROPERTIES::TAB_ACTIVE_TEXT_COLOR);

				this->tabs[i].Display();
			}

			this->closeBtn.Display();

			switch (this->currentTab)
			{
				case (0):
					this->dauSachView->Activate();
					this->theDocGiaView->Deactivate();
					this->thongKeView->Deactivate();

					this->dauSachView->Run();
					break;
				case (1):
					this->dauSachView->Deactivate();
					this->theDocGiaView->Activate();
					this->thongKeView->Deactivate();

					this->theDocGiaView->Run();
					break;
				case (2):
					this->dauSachView->Deactivate();
					this->theDocGiaView->Deactivate();
					this->thongKeView->Activate();

					this->thongKeView->Run();
					break;
			}

			this->TabsOnUpdate();
			this->CloseButtonOnUpdate();

			setvisualpage(getactivepage());
			//* Draw elements end above

			//* Clear mouseclick
			clearmouseclick(VK_LBUTTON);
			clearmouseclick(VK_RBUTTON);
		}

		//* Input processing start in this if statement
		if (programStopFlag == false && this->inpController.InInputMode())
		{
			char tmp = std::toupper(getch());
			this->inpController.ActionOnKey(tmp);
		}
		//* This currently filter out the case where input mode is not on but user still press some key.
		else if (programStopFlag == false)
		{
			char emptychr = getch();//take an empty char then do nothing
		}
	}
}

void LandingView::CreateTitleHashMap()
{
	this->titleMap_ = HashMap<BOOK_TITLE::BookTitle*>(456976, nullptr);

	std::string key{};
	for (int i = 0; i < this->titleList->numberOfNode; ++i)
	{
		key = this->titleList->nodes[i]->GetISBN();
		this->titleMap_.Insert(key, this->titleList->nodes[i]);
	}

	std::cerr << "[LOG] TITLE MAP CREATED!\n";
}

void LandingView::CreatePackage()
{
	this->package_.inputController = &this->inpController;
	this->package_.titleList = this->titleList;
	this->package_.readerList = this->readerList;
	this->package_.titleMap = &this->titleMap_;
}

LandingView::LandingView(AVL_TREE::Pointer* readerList, LINEAR_LIST::LinearList* titleList)
{
	this->currentTab = 0;
	this->programStopFlag = false;

	this->readerList = readerList;
	this->titleList = titleList;

	READER_MODULES::LoadDanhSachTheDocGiaFromDB(CONSTANTS::READER_DATABASE, *this->readerList);
	DAU_SACH_MODULES::LoadDanhSachDauSachFromDB(CONSTANTS::TITLES_DATABASE, *this->titleList);

	this->CreateTitleHashMap();
	this->CreatePackage();

	this->ConstructGraphicWindow();
	this->graphicWindow->Activate();

	this->ConstructNavigationBar();

	this->dauSachView = new DauSachTab(&this->package_);
	this->theDocGiaView = new DanhSachTheDocGiaView(&this->package_);
	this->thongKeView = new StatisticTab(&this->package_);
}

//* View destructor
LandingView::~LandingView()
{
	this->graphicWindow->Deactivate();
	delete this->dauSachView;
	delete this->theDocGiaView;
	delete this->thongKeView;
}
