#pragma once

#include "../../Helper/ConstantsAndGlobalVariables.h"
#include "../../Helper/Helper.h"
#include "Elements.h"
#include "Button.h"

namespace DATASHEET {
    class Row {
    private:
        int attributeCount;
        int rowHeight;
        HELPER::Coordinate topLeft;
        HELPER::Coordinate bottomRight;
        Button* items;

    public:
        Row();

        Row(int attributeCount, int rowHeight, HELPER::Coordinate topLeft, std::string* data, int* characterLimits);

        Button& operator[] (int index);

        HELPER::Coordinate GetTopLeft();

        HELPER::Coordinate GetBottomRight();

        int GetItemCount();

        void UpdateRowData(std::string* data);

        void Display();

        int IsHover();

        int LeftMouseClicked();

        //void Destructor();
    };

    class Datasheet {
    private:
        int attributeCount;
        int recordCount;
        int rowHeight;
        HELPER::Coordinate topLeft;
        HELPER::Coordinate bottomRight;
        Row* records;

    public:
        void DefaultLabelsProperties(Row& tbx);

        void DefaultDataFieldProperties(Row& tbx, int order);

        Datasheet();

        Datasheet(int recordCount, int attributeCount, int rowHeight, HELPER::Coordinate topLeft, std::string* data, int* characterLimits);

        Row& operator[] (int index);

        void UpdateNewPlaceholder(std::string* newPlaceholder, int rowIndicator);

        int GetRecordCount();

        void Display();

        HELPER::Coordinate GetBottomRight();

        //void Destructor();
    };

    class Controller {
    private:
        bool active;
        int recordCount;
        int attributeCount;
        int rowHeight;
        int activeSheet;
        HELPER::Coordinate topLeft;
        int datasheetCount;
        Datasheet* sheets;
        Button datasheetChangeButton[2];

        void DatasheetChangeBTNHover(Button& btn);

        void DatasheetChangeBTNProperties(Button& btn);

    public:
        Controller();

        Controller(int recordCount, int attributeCount, int rowHeight, HELPER::Coordinate topLeft, HELPER::Coordinate changeButtonTopLeft = {36, 940});

        //~Controller();

        void ActivateDatasheets();

        void DeactivateDatasheets();

        Datasheet& operator[] (int index);

        void InitializeDatasheets();

        void SetDatasheetCount(int amount);

        int GetDatasheetCount();

        int GetAttributeCount();

        int GetRecordCount();

        int GetRowHeight();

        HELPER::Coordinate GetBottomRight();

        int CurrentActiveDatasheet();

        void SetActiveDatasheet(int index);

        HELPER::Coordinate GetTopLeft();

        void SetDatasheetChangeButtonTopLeft(HELPER::Coordinate topLeft);

        void UpdateActiveSheet(int indicator);

        void DatasheetChangeButtonUpdate();

        bool DisplayStatus();

        void Display(bool displayDatasheetChangeButton = true);

        Button& NavigateIndicator(int index);
    };
}
