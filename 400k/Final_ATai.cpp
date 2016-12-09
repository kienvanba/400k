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
	xoaManHinh();  //xoa trang man hinh
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
		s = nhap(SO,1); // nhap(kieu nhap, so luong ki tu) vd: SO: chi duoc nhap so, 1: nhap 1 ki tu
		if(s=="thoat" || s=="0"){ // neu so vua nhap la 0 thi quay lai bat nhap tiep
			return;
		}else{
			break;
		}
	}while(1);
	flag = toInt(s); // toInt(chuoi chu) la de doi chuoi chu thanh so int;
}

void gdDanhSachHangTon(){
	xoaManHinh();
	cout << "CHI TIET CAC MAT HANG TRONG KHO" << endl << endl;
	inDSHangTonKho(wherex(),wherey(),tcHangHoa); //in danh sach hang ton kho inDSHangTonKho(int x, int y, chuoi) x,y la vi tri can in tren man hinh
	cout << "\n\nNhan phim bat ki de thoat...";
	getch(); // lay hoat dong bam nut cua nguoi dung
	flag = menuchinh; //doi sang menu chinh
}

void gdNhapNhanvien(){
	int c=0;
	do{
		xoaManHinh();
		in(70,0,"| Tat ca cac nhan vien\n"); // in chuoi "tat ca cac nhan vien" ra vi tri x=70 y=0 tren man hinh
		gotoxy(70,wherey()); // dua con tro ve vi tri x=70, wherey() la vi tri hien tai cua con tro
		inDSNhanVien(70,tcNhanVien); //in danh sach nhan vien ra vi tri x=70 va wherey();
		
		gotoxy(0,0);
		NhanVien nv; // tao 1 khoi nhan vien chua thong tin nhan vien
		cout << "NHAP NHAN VIEN" << endl;
		string manv="";
		do{
			cout << "\nMa nhan vien: ";	
			manv = nhap(CHU,10); //nhap kieu chu, so ki tu la 10 va gan cho manv
			if(manv=="thoat")return; //neu dang nhap ma nhan escape thi thoat;
			if(layNhanVien(manv,tcNhanVien)!=NULL){ //lay nhan vien la de lay 1 nhan vien theo manv, neu khac NULL thi bat nhap lai manv
				cout << "\nNhan vien nay da ton tai, vui long nhap lai!";
			}else{ // neu nhan vien khong ton tai thi tiep tuc
				break;
			}
		}while(1);
		nv.mnv = manv;
		
		cout << "\nHo nhan vien: ";
		string res = nhap(CHU,30); // nhap kieu chu vs 30 ki tu
		if(res=="thoat")return; // neu dang nhap ma nhan escape thi thoat;
		nv.ho=res; // cap thong tin ho nhan vien vao khoi nhanvien
		
		cout << "\nTen nhan vien: ";
		res = nhap(CHU,30); // nhap ten nhan vien kieu chu 30 ki tu
		if(res=="thoat")return;
		nv.ten=res; // cap thong tin ten nhan vien vao khoi nhanvien
		
		do{//vong lap kiem tra
			cout << "\nPhai <nam> hoac <nu>: ";
			res = nhap(CHU,10); //nhap gioi tinh
			if(res=="thoat")return;
			if(res!="nam" && res!="nu"){
				cout << "\nPhai la nam hoac nu! vui long nhap lai...";
			}else{
				break;
			}
		}while(1);
		nv.phai=res;
		nv.shd=0; // nhan vien moi, khong co so hoa don
		
		themNhanVien(tcNhanVien,nv); // them nhan vien vao danh sach tat ca nhan vien
		
		
		//cap nhat lai thong tin nhan vien tren goc phai
		int lasty = wherey();
		in(70,0,"| Tat ca cac nhan vien\n");
		gotoxy(70,wherey());
		inDSNhanVien(70,tcNhanVien);
		
		
		in(0,lasty,"\n\nThem thanh cong!");
		cout << "\nNhan phim bat ki de nhap tiep, Escape de thoat...";
		c = getch(); // lay hoat dong nhan phim cua nguoi dung
	}while(c!=ESCAPE);
	flag = menuchinh; // thoat thi tro ve menu chinh
}

void gdDanhSachNhanVien(){
	xoaManHinh();
	sapXepNV(tcNhanVien); // sap xep nhan vien theo thu tu tang dan theo ten
	sapXepNV(tcNhanVien); // dam bao nhan vien vua nhap vao dung vi tri sap xep
	cout << "CAC NHAN VIEN SAP XEP THEO TEN\n" << endl << endl;
	inDSNhanVien(wherex(),wherey(),tcNhanVien); //in danh sach nhan vien tai vi tri x,y hien tai
	cout << "\n\nNhan phim bat ki de thoat...";
	getch();
	flag = menuchinh; //thoat ra menu chinh
}

void gdChiTietHoaDonNhap(DSHD &hd){ //DSHD hd de xac dinh chi tiet hoa don thuoc hoa don nao.
	int c=0;
	do{
		xoaManHinh();
		in(70,0,"| Tat ca cac mat hang\n");
		gotoxy(70,wherey());
		inTatCaHangHoa(70,tcHangHoa); // in tat ca cac hang hoa t?i vitri ...
		
		gotoxy(0,0);
		HangHoa hh; //tao khoi hang hoa
		CTHoaDon cthd; //tao khoi chi tiet hoa don
		cout << "CHI TIET HOA DON NHAP HANG" << endl;
		string mahh="",res=""; // tao string ma hang hoa de chua ma hang, va res de chua cac thong tin khac
		cout << "\nMa hang hoa: ";
		mahh = nhap(SO,10); //nhap ma hang hoa kieu so, 10 ki tu
		
		if(mahh=="thoat")return;
		
		cthd.mahh = toFloat(mahh); //doi chuoi thanh kieu so float
		DSHH h = layHangHoa(toFloat(mahh),tcHangHoa); // lay hang hoa trong danh sach tat ca hang hoa bang ma hang hoa vua nhap
		if(h!=NULL){ // neu hang hoa lay ra khac NULL
			cout << "\nTen hang hoa: " << h->hanghoa.tenhh; // xuat thong tin ten hang hoa
 			cout << "\nDon vi tinh: " << h->hanghoa.dvt; // xuat ra don vi tinh
			cout << "\nSo luong ton: " << h->hanghoa.slt;
			cout << "\nSo luong them: ";
			res = nhap(SO,10); // nhap so luong hang hoa muon them voa
			if(res=="thoat")return;
			h->hanghoa.slt+=toInt(res); // so luong ton se bang so luong ton cu~ + so luong vua nhap (slt+=toInt(res) ~ slt= slt+toInt(res))
			
			cthd.soluong = toInt(res); // so luong vua nhap
		}else{ // neu hang lay ra = NULL
			cout << "\nTen hang hoa: "; // yeu cau nhap ten nhu 1 hang hoa moi 
			res = nhap(CHU,30);
			if(res=="thoat")return;
			hh.tenhh=res; //cap thong tin ten hang cho khoi hanghoa hh
			
			cout << "\nDon vi tinh: ";
			res = nhap(CHU,10);
			if(res=="thoat")return;
			hh.dvt=res; //don vi tinh ciua khoi hang hoa
			
			cout << "\nSo luong: ";
			res = nhap(SO,10);
			if(res=="thoat")return;
			hh.slt = toInt(res); // so luong cua khoi hang hoa
			
			cthd.soluong = toInt(res); //so luon cua chi tiet hoa don 
			
			themHangHoa(tcHangHoa,toFloat(mahh),hh); // them hang hoa vao tat ca hang hoa
		}
		cout << "\nDon gia: ";
		res = nhap(SO,10);
		if(res=="thoat")return;
		cthd.dongia = toFloat(res); // don gia cua hang hoa vua nhap vao
		
		cout << "\n% VAT: ";
		res = nhap(SO,10);
		if(res=="thoat")return;
		cthd.vat = toFloat(res); // ma VAT cua chi tiet hoa don
 		
		themCTHoaDon(hd->hoadon.cthd,cthd); // hd->hoadon.cthd là danh sach chi tiet hoa don cua hoa don hd, ham nay de them chi tiet hoa don cthd vao ds cthoadon cua hd
		
		//cap nhap lai thong tin hang o ben phai man hinh
		int lasty = wherey();
		in(70,0,"| Tat ca cac mat hang\n");
		gotoxy(70,wherey());
		inTatCaHangHoa(70,tcHangHoa);
		
		
		in(0,lasty,"\n\nThem thanh cong!");
		cout << "\nNhan phim bat ki de nhap tiep, Escape de thoat...";
		c = getch();
	}while(c!=ESCAPE);
	flag = menuchinh; //thaot ra
}

void gdChiTietHoaDonXuat(DSHD &hd){
	int c=0;
	do{
		xoaManHinh();
		in(70,0,"| Tat ca cac mat hang\n");
		gotoxy(70,wherey());
		inTatCaHangHoa(70,tcHangHoa); //xuat cac hang hoa ben goc phai
		
		gotoxy(0,0);
		CTHoaDon cthd; // tao khoi chi tiet hoa don
		cout << "CHI TIET HOA DON XUAT HANG" << endl;
		string mahh="",res=""; // tao chuoi chua ma hang hoa va cac thong tin cua chi tiet hoa don
		DSHH hh;
		do{ // bat dau kiem tra ma hang hao co ton tai hay không
			cout << "\nMa hang hoa: ";
			mahh = nhap(SO,10); //nhap ma hang hoa
			if(mahh=="thoat")return;
			hh = layHangHoa(toFloat(mahh),tcHangHoa); //lay hang hoa theo ma hang hoa trong danh sach tat cac hang hoa
			if(hh==NULL){ // neu ma hang hoa lay ra = NULL thi bat nhap lai
				cout << "\nHang hoa nay KHONG ton tai, vui long nhap lai...";
			}else{ //neu khac NULL thi tiep tuc
				break;
			}
		}while(1);
		
		cthd.mahh = toFloat(mahh); // them thong tin ma hang hoa cho chi tiet hoa don
		cout << "\nTen hang hoa: " << hh->hanghoa.tenhh; 
		cout << "\nDon vi tinh: " << hh->hanghoa.dvt;
		cout << "\nSo luong ton: " << hh->hanghoa.slt;
		do{
			cout << "\nSo luong hang xuat ra: ";
			res = nhap(SO,10); //nhap so luong muon xuat ra
			if(res=="thoat")return;
			if(toInt(res)>hh->hanghoa.slt){
				cout << "So luong xuat lon hon so luong ton, vui long nhap lai...";
			}else{
				break;
			}
		}while(1);
		
		cthd.soluong = toInt(res);
		hh->hanghoa.slt-=toInt(res); // sau khi nhap so luong xuat thi phai tru so luong ton cua hang hoa xuong
		
		cout << "\nDon gia: ";
		res = nhap(SO,10);
		if(res=="thoat")return;
		cthd.dongia = toFloat(res); // thong tin don gia cua chi tiet hoa don
		
		cout << "\n% VAT: ";
		res = nhap(SO,10);
		if(res=="thoat")return;
		cthd.vat = toFloat(res); // thong tin VAT
		
		themCTHoaDon(hd->hoadon.cthd,cthd); // them chi tiet hoa don vao hoa don hd
				
		// cap nhat lai thong tin hang hoa ben phai man hinh
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
		inTatCaHoaDon(70,tcHoaDon); //in thong in tat ca hoa don len goc phai man hinh
		
		gotoxy(0,0);
		HoaDon hd; // tao khoi hoa don
		cout << "NHAP HOA DON" << endl;
		string sohd=""; //chuoi chua so hoa don
		do{
			cout << "\nSo hoa don: ";
			sohd = nhap(CHU,10); // so hoa don la kieu chu 10 ki tu
			if(sohd=="thoat")return;
			if(layHoaDon(sohd,tcHoaDon)!=NULL){ // kiem tra xem hoa don da ton tai hay chua
				cout << "\nHoa don nay da ton tai, vui long nhap lai...";
			}else{
				break;
			}
		}while(1);
		hd.sohd = sohd;
		
		string res="";
		cout << "\nNgay: ";
		Ngay ngay = nhap();
		if(ngay.ngay==1000)return;
		hd.ngay = ngay;
		
		
		do{
			cout << "\nMa nhan vien: ";
			res = nhap(CHU,15); //nhap ma nhan vien
			if(res=="thoat")return;
			if(layNhanVien(res,tcNhanVien)==NULL){ // kiem tra xem ma nha veien co ton tai hay ko
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
			if(res!="n" && res!="x"){ // kiem tra xem nhap co dung loai hay ko (chi dc n hoac x)
				cout << "\nLoai la n hoac x! vui long nhap lai...";
			}else{
				break;
			}
		}while(1);
		hd.lhd=res;
		
		themHoaDon(tcHoaDon,hd); // them hoa don vao tat ca hoa don
		DSHD t = layHoaDon(hd.sohd,tcHoaDon);
		if(hd.lhd=="x"){ // neu hoa don la kieu xuat thi chay giao dien chi tiet hoa don xuat
			gdChiTietHoaDonXuat(t);
			layNhanVien(hd.manv,tcNhanVien)->nhanvien.shd++;
		}else{
			gdChiTietHoaDonNhap(t); // chay gd hoa don nhap
		}
		
		//cap nhat lai man hinh thong bao da them hoa don thanh cong
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
	flag = menuchinh; // ve menu chinh	
}

void gdTatCaHoaDon(){
	xoaManHinh();
	cout << "CHI TIET TAT CA CAC HOA DON\n" << endl << endl;
	inTatCaHoaDon(wherex(),wherey(),tcHoaDon); // in tat ca cac hoa don va chi tiet hoa don ra man hinh
	cout << "\n\nNhan phim bat ki de thoat...";
	getch();
	flag = menuchinh;
}

void gdTopNV(){
	xoaManHinh();
	sapXepTopNV(tcNhanVien); // sap xep nhan vien theo so hoa don xuat
	cout << "TOP 10 NHAN VIEN CO SO HOA DON XUAT NHIEU NHAT" << endl << endl;
	int i=0; //khoi tao i=0
	in(0,wherey(),"Ma nhan vien");
	in(15,wherey(),"Ten nhan vien");
	in(35,wherey(),"So hoa don xuat\n");
	for(DSNV p=tcNhanVien; p!=NULL; p=p->next){ // vong lap xuat cac nhan vien ra man hinh
		i++;
		in(0,wherey(),p->nhanvien.mnv);
		in(15,wherey(),p->nhanvien.ho+" "+p->nhanvien.ten);
		in(35,wherey(),toString(p->nhanvien.shd)+"\n");	
		if(i==10)break;	//neu da du 10 nhan vien thi thaot ko xuat nua
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
	
	DSHD temp; //dach sach hoa don tam thoi chua cac hoa don cua thang nay.
	char x=0;
	int n = laySoNgay(toInt(thang),toInt(nam));
	for(DSHD p=tcHoaDon; p!=NULL; p=p->next){ // duyet danh sach tat ca cac hoa don
		if((p->hoadon.ngay.ngay>=1 && p->hoadon.ngay.ngay<=n) && p->hoadon.ngay.thang == toInt(thang) && p->hoadon.ngay.nam == toInt(nam)){ // kiem tra hoa don nao thuoc thang va nam hien tai dang chon
			themHoaDon(temp,p->hoadon); // them hoa don du dieu kien vao danh sach tam thoi
			x++;						//magicccccc+++++++++
											//i decided to quit programming
		}
	} //sau khi chay xong vong lap thi danh sach tam se chua tat ca cac hoa don cua thang nay
	cout << endl << endl;
	inTatCaHoaDon(wherex(),wherey(),temp); // in tat ca cac hoa don trong danh sach tam
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
	reSize(1280,720); // thay doi kich co man hinh theo thong so nhap vao
	loadHangHoa(); // lay thong tin thu file txt vao he thong
	loadNhanVien();
	loadHoaDon();
	
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
