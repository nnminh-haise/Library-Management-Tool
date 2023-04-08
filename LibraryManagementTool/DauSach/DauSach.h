#pragma once

#include <string>

namespace SACH {
	enum TrangThaiSach {
		CHO_MUON_DUOC, DA_CO_DOC_GIA_MUON, DA_THANH_LY
	};

	class Sach {
	private:
		std::string MaSach;
		TrangThaiSach TrangThai;
		std::string ViTri;

	public:
		Sach();

		Sach(std::string MaSach, TrangThaiSach TrangThai, std::string ViTri);

		void SetMaSach(std::string MaSach);

		std::string GetMaSach();

		void SetTrangThai(TrangThaiSach TrangThai);

		TrangThaiSach GetTrangThai();

		void SetViTri(std::string ViTri);

		std::string GetViTri();
	};
}

namespace LINKED_LIST {
	struct Node {
		SACH::Sach info;
		Node* next;

		Node();

		Node(SACH::Sach info, Node* next);
	};

	typedef Node* Pointer;

	struct Controler {
		unsigned int total; //* The size of the linked list.
		unsigned int borrowed;
		unsigned int sold;
		Pointer first;
	};

	void Initialize(Controler& controller);

	bool IsEmpty(const Controler& controller);

	void InsertItemLast(Controler& controller, SACH::Sach item);
}

namespace DAU_SACH {
	class DauSach {
	private:
		std::string ISBN;
		std::string TenSach;
		unsigned int SoTrang;
		std::string TacGia;
		unsigned int NamXuatBan;
		std::string TheLoai;
		LINKED_LIST::Controler DanhMucSach;

	public:
		DauSach();

		DauSach(std::string ISBN, std::string TenSach, unsigned int SoTrang, std::string TacGia, unsigned int NamXuatBan, std::string TheLoai, LINKED_LIST::Controler DanhMucSach);

		void SetISBN(std::string ISBN);

		std::string GetISBN();

		void SetTenSach(std::string TenSach);

		std::string GetTenSach();

		void SetSoTrang(unsigned int Sotrang);

		unsigned int GetSoTrang();
		
		void SetTacGia(std::string TacGia);

		std::string GetTacGia();

		void SetNamXuatBan(unsigned int NamXuatBan);

		unsigned int GetNamXuatBan();

		void SetTheLoai(std::string TheLoai);

		std::string GetTheLoai();

		void SetDanhMucSach(LINKED_LIST::Controler DanhMucSach);

		LINKED_LIST::Controler GetDanhMucSach();
	};
}

namespace LINEAR_LIST {
	const unsigned int MAX_SIZE = 10000;

	struct LinearList {
		unsigned int numberOfNode;
		DAU_SACH::DauSach* nodes[MAX_SIZE];

		LinearList();
	};

	void Initialize(LinearList& list);

	bool IsEmpty(const LinearList& list);

	bool IsFull(const LinearList& list);

	void swap(DauSach*&, DauSach*&);

	void sortByCategory(LinearList& list);
  
	bool InsertItem(LinearList& list, DAU_SACH::DauSach* item, int position);
}
