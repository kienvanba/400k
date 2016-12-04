#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <conio.h>
#include <algorithm>
#include <Windows.h>

#include "hamthem.h"
#include "hanghoa.h"
#include "nhanvien.h"
#include "hoadon.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define menuchinh 0
#define indshangtonkho 1
#define nhapnv 2
#define indsnhanvien 3
#define laphd 4
#define inhoadon 5
#define thongkehd 6
#define topnv 7
#define infile 8
#define thoat 9

#define CHU 999
#define SO 888
#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define BACKSPACE 010
#define ENTER 13
#define ESCAPE 27


void gdMenuChinh(){
	xoaManHinh();
	cout<< "QUAN LY XUAT NHAP HANG"<< endl << endl;
	cout << "1.In danh sach hang ton kho." << endl;
	cout << "2.Nhap nhan vien." << endl;
	cout << "3.In danh sach nhan vien theo thu tu tang dan." << endl;
	cout << "4.Lap hoa don." << endl;
	cout << "5.In hoa don." << endl;
	cout << "6.Thong ke hoa don." << endl;
	cout << "7.Top 10 nhan vien co so phieu xuat cao nhat." << endl;
	cout << "8.Ghi file." << endl;
	cout << "9.Thoat." << endl;
	cout << "Moi ban chon menu tu 1->9: ";
	string s="9";
	do{
		s = nhap(SO,1);
		if(s=="thoat" || s=="0"){
			return;
		}else{
			break;
		}
	}while(1);
	flag = toInt(s);
}

void gdDanhSachHangTon(){
	xoaManHinh();
	cout << "CHI TIET CAC MAT HANG TRONG KHO" << endl << endl;
	inDSHangTonKho(wherex(),wherey(),tcHangHoa);
	cout << "\n\nNhan phim bat ki de thoat...";
	getch();
	flag = menuchinh;
}

void gdNhapNhanvien(){
	int c=0;
	do{
		xoaManHinh();
		in(70,0,"| Tat ca cac nhan vien\n");
		gotoxy(70,wherey());
		inDSNhanVien(70,tcNhanVien);
		
		gotoxy(0,0);
		NhanVien nv;
		cout << "NHAP NHAN VIEN" << endl;
		string manv="";
		do{
			cout << "\nMa nhan vien: ";
			manv = nhap(CHU,10);
			if(manv=="thoat")return;
			if(layNhanVien(manv,tcNhanVien)!=NULL){
				cout << "\nNhan vien nay da ton tai, vui long nhap lai!";
			}else{
				break;
			}
		}while(1);
		nv.mnv = manv;
		
		cout << "\nHo nhan vien: ";
		string res = nhap(CHU,30);
		if(res=="thoat")return;
		nv.ho=res;
		
		cout << "\nTen nhan vien: ";
		res = nhap(CHU,30);
		if(res=="thoat")return;
		nv.ten=res;
		
		do{
			cout << "\nPhai <nam> hoac <nu>: ";
			res = nhap(CHU,10);
			if(res=="thoat")return;
			if(res!="nam" && res!="nu"){
				cout << "\nPhai la nam hoac nu! vui long nhap lai...";
			}else{
				break;
			}
		}while(1);
		nv.phai=res;
		nv.shd=0;
		
		themNhanVien(tcNhanVien,nv);
		
		int lasty = wherey();
		in(70,0,"| Tat ca cac nhan vien\n");
		gotoxy(70,wherey());
		inDSNhanVien(70,tcNhanVien);
		
		
		in(0,lasty,"\n\nThem thanh cong!");
		cout << "\nNhan phim bat ki de nhap tiep, Escape de thoat...";
		c = getch();
	}while(c!=ESCAPE);
	flag = menuchinh;
}

void gdDanhSachNhanVien(){
	xoaManHinh();
	sapXepNV(tcNhanVien);
	sapXepNV(tcNhanVien);
	cout << "CAC NHAN VIEN SAP XEP THEO TEN\n" << endl << endl;
	inDSNhanVien(wherex(),wherey(),tcNhanVien);
	cout << "\n\nNhan phim bat ki de thoat...";
	getch();
	flag = menuchinh;
}

void gdChiTietHoaDonNhap(DSHD hd){
	int c=0;
	do{
		xoaManHinh();
		in(70,0,"| Tat ca cac mat hang\n");
		gotoxy(70,wherey());
		inTatCaHangHoa(70,tcHangHoa);
		
		gotoxy(0,0);
		HangHoa hh;
		CTHoaDon cthd;
		cout << "CHI TIET HOA DON NHAP HANG" << endl;
		string mahh="",res="";
		cout << "\nMa hang hoa: ";
		mahh = nhap(SO,10);
		if(mahh=="thoat")return;
		cthd.mahh = toFloat(mahh);
		DSHH h = layHangHoa(toFloat(mahh),tcHangHoa);
		if(h!=NULL){
			cout << "\nTen hang hoa: " << h->hanghoa.tenhh;
			cout << "\nDon vi tinh: " << h->hanghoa.dvt;
			cout << "\nSo luong ton: " << h->hanghoa.slt;
			cout << "\nSo luong them: ";
			res = nhap(SO,10);
			if(res=="thoat")return;
			h->hanghoa.slt+=toInt(res);
			
			cthd.soluong = toInt(res);
		}else{
			cout << "\nTen hang hoa: ";
			res = nhap(CHU,30);
			if(res=="thoat")return;
			hh.tenhh=res;
			
			cout << "\nDon vi tinh: ";
			res = nhap(CHU,10);
			if(res=="thoat")return;
			hh.dvt=res;
			
			cout << "\nSo luong: ";
			res = nhap(SO,10);
			if(res=="thoat")return;
			hh.slt = toInt(res);
			
			cthd.soluong = toInt(res);
			
			themHangHoa(tcHangHoa,toFloat(mahh),hh);
		}
		cout << "\nDon gia: ";
		res = nhap(SO,10);
		if(res=="thoat")return;
		cthd.dongia = toFloat(res);
		
		cout << "\n% VAT: ";
		res = nhap(SO,10);
		if(res=="thoat")return;
		cthd.vat = toFloat(res);
		
		themCTHoaDon(hd->hoadon.cthd,cthd);
		
		int lasty = wherey();
		in(70,0,"| Tat ca cac mat hang\n");
		gotoxy(70,wherey());
		inTatCaHangHoa(70,tcHangHoa);
		
		
		in(0,lasty,"\n\nThem thanh cong!");
		cout << "\nNhan phim bat ki de nhap tiep, Escape de thoat...";
		c = getch();
	}while(c!=ESCAPE);
	flag = menuchinh;
}

void gdChiTietHoaDonXuat(DSHD hd){
	int c=0;
	do{
		xoaManHinh();
		in(70,0,"| Tat ca cac mat hang\n");
		gotoxy(70,wherey());
		inTatCaHangHoa(70,tcHangHoa);
		
		gotoxy(0,0);
		CTHoaDon cthd;
		cout << "CHI TIET HOA DON XUAT HANG" << endl;
		string mahh="",res="";
		DSHH hh;
		do{
			cout << "\nMa hang hoa: ";
			mahh = nhap(SO,10);
			if(mahh=="thoat")return;
			hh = layHangHoa(toFloat(mahh),tcHangHoa);
			if(hh==NULL){
				cout << "\nHang hoa nay KHONG ton tai, vui long nhap lai...";
			}else{
				break;
			}
		}while(1);
		cthd.mahh = toFloat(mahh);
		cout << "\nTen hang hoa: " << hh->hanghoa.tenhh;
		cout << "\nDon vi tinh: " << hh->hanghoa.dvt;
		cout << "\nSo luong ton: " << hh->hanghoa.slt;
		do{
			cout << "\nSo luong hang xuat ra: ";
			res = nhap(SO,10);
			if(res=="thoat")return;
			if(toInt(res)>hh->hanghoa.slt){
				cout << "So luong xuat lon hon so luong ton, vui long nhap lai...";
			}else{
				break;
			}
		}while(1);
		
		cthd.soluong = toInt(res);
		hh->hanghoa.slt-=toInt(res);
		
		cout << "\nDon gia: ";
		res = nhap(SO,10);
		if(res=="thoat")return;
		cthd.dongia = toFloat(res);
		
		cout << "\n% VAT: ";
		res = nhap(SO,10);
		if(res=="thoat")return;
		cthd.vat = toFloat(res);
		
		themCTHoaDon(hd->hoadon.cthd,cthd);
				
		int lasty = wherey();
		in(70,0,"| Tat ca cac mat hang\n");
		gotoxy(70,wherey());
		inTatCaHangHoa(70,tcHangHoa);
		
		in(0,lasty,"\n\nThem thanh cong!");
		cout << "\nNhan phim bat ki de nhap tiep, Escape de thoat...";
		c = getch();
	}while(c!=ESCAPE);
	flag = menuchinh;
}

void gdLapHoaDon(){
	int c=0;
	do{
		xoaManHinh();
		in(70,0,"| Tat ca cac hoa don\n");
		gotoxy(70,wherey());
		inTatCaHoaDon(70,tcHoaDon);
		
		gotoxy(0,0);
		HoaDon hd;
		cout << "NHAP HOA DON" << endl;
		string sohd="";
		do{
			cout << "\nSo hoa don: ";
			sohd = nhap(CHU,10);
			if(sohd=="thoat")return;
			if(layHoaDon(sohd,tcHoaDon)!=NULL){
				cout << "\nHoa don nay da ton tai, vui long nhap lai...";
			}else{
				break;
			}
		}while(1);
		hd.sohd = sohd;
		
		cout << "\nNgay:  /  /";
		gotoxy(5,wherey());
		string res = nhap(SO,2);
		if(res=="thoat")return;
		hd.ngay.ngay=toInt(res);
		gotoxy(8,wherey());
		res = nhap(SO,2);
		if(res=="thoat")return;
		hd.ngay.thang=toInt(res);
		gotoxy(11,wherey());
		res = nhap(SO,4);
		if(res=="thoat")return;
		hd.ngay.nam=toInt(res);
		
		do{
			cout << "\nMa nhan vien: ";
			res = nhap(CHU,15);
			if(res=="thoat")return;
			if(layNhanVien(res,tcNhanVien)==NULL){
				cout << "\nNhan vien nay KHONG ton tai, vui long nhap lai!";
			}else{
				break;
			}
		}while(1);
		hd.manv = res;
		
		do{
			cout << "\nLoai nhap<n> hoac xuat<x>: ";
			res = nhap(CHU,1);
			if(res=="thoat")return;
			if(res!="n" && res!="x"){
				cout << "\nLoai la n hoac x! vui long nhap lai...";
			}else{
				break;
			}
		}while(1);
		hd.lhd=res;
		
		themHoaDon(tcHoaDon,hd);
		DSHD t = layHoaDon(hd.sohd,tcHoaDon);
		if(hd.lhd=="x"){
			gdChiTietHoaDonXuat(t);
			layNhanVien(hd.manv,tcNhanVien)->nhanvien.shd++;
		}else{
			gdChiTietHoaDonNhap(t);
		}
		xoaManHinh();
		in(70,0,"| Tat ca cac hoa don\n");
		gotoxy(70,wherey());
		inTatCaHoaDon(70,tcHoaDon);
		
		gotoxy(0,0);
		cout << "NHAP HOA DON" << endl;
		cout << "\nSo hoa don: " << hd.sohd;
		cout << "\nNgay lap: " << xuLyNgay(hd.ngay);
		cout << "\nMa nhan vien: " << hd.manv;
		cout << "\nLoai: " << (hd.lhd=="n"?"nhap":"xuat");
		
		in(0,wherey(),"\n\nThem thanh cong!");
		cout << "\nNhan phim bat ki de nhap tiep, Escape de thoat...";
		c = getch();
	}while(c!=ESCAPE);
	flag = menuchinh;
}

void gdTatCaHoaDon(){
	xoaManHinh();
	cout << "CHI TIET TAT CA CAC HOA DON\n" << endl << endl;
	inTatCaHoaDon(wherex(),wherey(),tcHoaDon);
	cout << "\n\nNhan phim bat ki de thoat...";
	getch();
	flag = menuchinh;
}

void gdTopNV(){
	xoaManHinh();
	sapXepTopNV(tcNhanVien);
	cout << "TOP 10 NHAN VIEN CO SO HOA DON XUAT NHIEU NHAT" << endl << endl;
	int i=0;
	in(0,wherey(),"Ma nhan vien");
	in(15,wherey(),"Ten nhan vien");
	in(35,wherey(),"So hoa don xuat\n");
	for(DSNV p=tcNhanVien; p!=NULL; p=p->next){
		i++;
		in(0,wherey(),p->nhanvien.mnv);
		in(15,wherey(),p->nhanvien.ho+" "+p->nhanvien.ten);
		in(35,wherey(),toString(p->nhanvien.shd)+"\n");	
		if(i==10)break;	
	}
	cout << "\n\nNhan phim bat ki de thoat...";
	getch();
	flag = menuchinh;
}

void gdThongKeHoaDon(){
	xoaManHinh();
	cout << "THONG KE HOA DON TRONG THANG" << endl << endl;
	cout << "Thang:    Nam: ";
	gotoxy(7,wherey());
	string thang = nhap(SO,2);
	if(thang=="thoat")return;
	gotoxy(15,wherey());
	string nam = nhap(SO,4);
	if(nam=="thoat")return;
	
	DSHD temp;
	char x=0;
	int n = laySoNgay(toInt(thang),toInt(nam));
	for(DSHD p=tcHoaDon; p!=NULL; p=p->next){
		if((p->hoadon.ngay.ngay>=1 && p->hoadon.ngay.ngay<=n) && p->hoadon.ngay.thang == toInt(thang) && p->hoadon.ngay.nam == toInt(nam)){
			themHoaDon(temp,p->hoadon);
			x=x;						//magicccccc+++++++++
											//i decided to quit programming
		}
	}
	cout << endl << endl;
	inTatCaHoaDon(wherex(),wherey(),temp);
	cout << "\n\nNhan phim bat ki de thoat...";
	getch();
	flag = menuchinh;
}

void gdInFile(){
	xoaManHinh();
	cout << "IN FILE DU LIEU\n" << endl << endl;
	ghiHangHoa();
	ghiNhanVien();
	ghiHoaDon();
	for(int i=0;i<=10;i++){
		in(wherex(),wherey(),"..."+toString(i*10)+"%");
		Sleep(100);
	}
	cout << "\n\nNhan phim bat ki de thoat...";
	getch();
	flag = menuchinh;
}

/** main */
int main(int argc, char** argv) {
	reSize(1280,720);
	loadHangHoa();
	loadNhanVien();
	loadHoaDon();
	loadCTHoaDon();
	
	xoaManHinh();
	flag = menuchinh;
	while(flag!=thoat){
		switch(flag){
			case menuchinh:
				gdMenuChinh();
				break;
			case indshangtonkho:
				gdDanhSachHangTon();
				break;
			case nhapnv:
				gdNhapNhanvien();
				break;
			case indsnhanvien:
				gdDanhSachNhanVien();
				break;
			case laphd:
				gdLapHoaDon();
				break;
			case inhoadon:
				gdTatCaHoaDon();
				break;
			case thongkehd:
				gdThongKeHoaDon();
				break;
			case topnv:
				gdTopNV();
				break;
			case infile:
				gdInFile();
				break;
		}
	}
	return 0;
}
