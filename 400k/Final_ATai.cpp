#include <iostream>
#include <mylib.h>
#include <Windows.h>
#include <string.h>
#include <fstream>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include <ctime>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAXLIST 100
#define menuchinh 0
#define nhaphh 1
#define indshangtonkho 2
#define nhapnv 3
#define indsnhanvien 4
#define laphd 5
#define inhoadon 6
#define thongkehd 7
#define topnv 8
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


//=============== cac ham phu ================
void reSize(int w,int h){
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, w, h, TRUE);
}
void in(int x, int y, string s){ //ham nay giup in 1 chuoi bat ki ra man hinh, bat dau tu vi tri (x,y)
	gotoxy(x,y);
	cout << s;
}
string khoangTrang(int h){//tao ra 1 chuoi khoang trang co chieu dai = 'h'
	string s;
	for(int i=0;i<h;i++){
		s+=" ";
	}
	return s;
}
void xoaManHinh(){//xoa trang man hinh
	system("cls");
}
bool ktChu(char ch){// kiem tra xem ki tu 'ch' co phai la chu hay ko
	return (tolower(ch)>='a' && tolower(ch)<='z' || ch==63);
}
bool ktSo(char ch){// kiem tra xem ki tu 'ch' co phai la so hay ko
	if(ch>=48 && ch<=57){
		return true;
	}
	return false;
}
string toString(float n){
	stringstream ss;
	ss << n;
	string s = ss.str();
	return s;
}
int toInt(string s){
	return atof(s.c_str());
}
float toFloat(string s){
	return atof(s.c_str());
}
//============== End Others ===================
//============== khai bao =======================
typedef struct{
	int ngay;
	int thang;
	int nam;
}Ngay;
/** Hang Hoa */
typedef struct{
	string tenhh;
	string dvt;
	int slt;
}HangHoa;
struct hang_hoa{
	float mahh;
	HangHoa hanghoa;
	struct hang_hoa *left;
	struct hang_hoa *right;
};
typedef struct hang_hoa *DSHH;

/** Nhan Vien */
typedef struct{
	string mnv;
	string ho;
	string ten;
	string phai;
}NhanVien;
struct nhan_vien{
	NhanVien nhanvien;
	struct nhan_vien *next;
};
typedef struct nhan_vien *DSNV;

/** Chi Tiet Hoa Don */
typedef struct{
	string mahh;
	int soluong;
	float dongia;
	float vat;
}CTHoaDon;
struct ct_hoa_don{
	int n;
	CTHoaDon ds[MAXLIST];
};
typedef struct ct_hoa_don CTHD;

/** Hoa Don */
typedef struct{
	string sohd;
	Ngay ngay;
	string manv;
	string lhd;
	CTHD cthd;
}HoaDon;
struct hoa_don{
	HoaDon hoadon;
	hoa_don* next;
};
typedef struct hoa_don* DSHD;


DSHH tcHangHoa;
DSNV tcNhanVien;
DSHD tcHoaDon;
int flag;
//========= end khai bao =========================

//========= code chuong trinh ====================
/** Hang Hoa */
DSHH taoHangHoa(float mahh,HangHoa hanghoa){
	DSHH temp;
	temp=new hang_hoa;
	temp->mahh = mahh;
	temp->hanghoa = hanghoa;
	temp->left=NULL;
	temp->right=NULL;
	return temp;
}

void themHangHoa(DSHH &ds, float mahh, HangHoa hanghoa){
	if(ds==NULL){
		ds=taoHangHoa(mahh,hanghoa);
	}else{
		if(ds->mahh>mahh){
			themHangHoa(ds->left,mahh,hanghoa);
		}else{
			themHangHoa(ds->right,mahh,hanghoa);
		}
	}
}

void inTatCaHangHoa(int x,DSHH &ds){
	if(ds!=NULL){
		inTatCaHangHoa(x,ds->left);
		in(x,wherey(),khoangTrang(50));
		in(x,wherey(),"| "+toString(ds->mahh)+" -- "+ds->hanghoa.tenhh+"\n");
		inTatCaHangHoa(x,ds->right);
	}
}

void inDSHangTonKho(int x, int y, DSHH &ds){
	const int StackSize =500;
	DSHH stack[StackSize];
	int sp=-1;
	DSHH p = ds;
	int i=1;
	in(x,y,"STT");
	in(x+5,y,"Ma HH");
	in(x+15,y,"Ten Hang Hoa");
	in(x+50,y,"So Luong");
	in(x+60,y,"Don Vi");
	y++;
	while(p!=NULL){
		in(x,y,toString(i)); 					//in so thu tu
		in(x+5,y,toString(p->mahh));			//in ma hang hoa
		in(x+15,y,p->hanghoa.tenhh);			//in ten hang hoa 
		in(x+50,y,toString(p->hanghoa.slt));	//in so luong hang hoa
		in(x+60,y,p->hanghoa.dvt);				//in don vi tinh
		y++;
		i++;
		if(p->right!=NULL){
			stack[++sp]=p->right;
		}
		if(p->left!=NULL){
			p = p->left;
		}else{
			if(sp==-1){
				break;
			}else{
				p=stack[sp--];
			}
		}
	}
}

DSHH layHangHoa(float mahh, DSHH &ds){
	DSHH p;
	p=ds;
	while(p!=NULL && p->mahh!=mahh){
		if(p->mahh>mahh){
			p=p->left;
		}else{
			p=p->right;
		}
	}
	return p;
}

/** nhan vien **/
void themNhanVien(DSNV &ds, NhanVien nhanvien){
	DSNV p;
	p=new nhan_vien;
	p->nhanvien = nhanvien;
	if(ds==NULL){
		ds=p;
		ds->next=NULL;
	}else{
		p->next=ds;
		ds = p;
	}
}
string toLowerCase(string s){
	string res = "";
	for(int i=0;i<s.length();i++){
		res+=tolower(s[i]);
	}
	return res;
}
void sapXepNV(DSNV &ds){
	if(ds==NULL){
		return;
	}
	for(DSNV p=ds; p->next!=NULL; p=p->next){
		string ten1 = toLowerCase(p->nhanvien.ten);
		for(DSNV q=p->next; q!=NULL; q=q->next){
			string ten2 = toLowerCase(q->nhanvien.ten);
			if(ten2[0]<=ten1[0]){
				DSNV temp = q;
				q=p;
				p=temp;
			}
		}
	}
}

DSNV layNhanVien(string manv, DSNV &ds){
	for(DSNV p=ds; p!=NULL; p=p->next){
		if(p->nhanvien.mnv==manv){
			return p;
		}
	}
	return NULL;
}

void inDSNhanVien(int x, DSNV &ds){
	for(DSNV p=ds; p!=NULL; p=p->next){
		in(x,wherey(),khoangTrang(50));
		in(x,wherey(),"| "+p->nhanvien.mnv+" -- "+p->nhanvien.ho+" "+p->nhanvien.ten+"\n");
	}
}

void inDSNhanVien(int x, int y, DSNV &ds){
	in(x,y,"STT");
	in(x+5,y,"Ma NV");
	in(x+20,y,"Ho Ten NV");
	in(x+55,y,"Phai");
	y++;
	int i=1;
	for(DSNV p=ds; p!=NULL; p=p->next){
		in(x,y,toString(i));
		in(x+5,y,p->nhanvien.mnv);
		in(x+20,y,p->nhanvien.ho + " " + p->nhanvien.ten);
		in(x+55,y,p->nhanvien.phai);
		y++;
		i++;
	}
}

/** chi tiet hoa don */
void themCTHoaDon(CTHD &ds, CTHoaDon cthd){
	if(ds.n==MAXLIST){
		return;
	}
	ds.ds[ds.n] = cthd;
	ds.n++;
}

void inCTHoaDon(int x, int y, CTHD &ds){
	if(ds.n==0){
		return;
	}
	in(x,y,"| STT");
	in(x+5,y,"Ma HH");
	in(x+20,y,"So Luong");
	in(x+35,y,"Don Gia");
	in(x+55,y,"% VAT");
	y++;
	for(int i=0;i<ds.n;i++){
		in(x,y+i,"| "+toString(i+1));
		in(x+5,y+i,ds.ds[i].mahh);
		in(x+20,y+i,toString(ds.ds[i].soluong));
		in(x+35,y+i,toString(ds.ds[i].dongia));
		in(x+55,y+i,toString(ds.ds[i].vat));
	}
	cout << endl << endl;
}

/** hoa don */
void themHoaDon(DSHD &ds, HoaDon hoadon){
	DSHD p;
	p=new hoa_don;
	p->hoadon = hoadon;
	if(ds==NULL){
		ds=p;
		ds->next=NULL;
	}else{
		p->next=ds;
		ds = p;
	}
}

string xuLyNgay(Ngay n){
	return toString(n.ngay)+"/"+toString(n.thang)+"/"+toString(n.nam);
}

DSHD layHoaDon(string sohd, DSHD &ds){
	for(DSHD p=ds; p!=NULL; p=p->next){
		if(p->hoadon.sohd == sohd){
			return p;
		}
	}
	return NULL;
}

void inTatCaHoaDon(int x, DSHD &ds){
	for(DSHD p=ds; p!=NULL; p=p->next){
		in(x,wherey(),khoangTrang(50));
		in(x,wherey(),"| "+p->hoadon.sohd+" -- "+xuLyNgay(p->hoadon.ngay)+"\n");
	}
}

void inTatCaHoaDon(int x, int y, DSHD &ds){
	in(x,wherey(),"So HD");
	in(x+10,wherey(),"Ngay Lap");
	in(x+40,wherey(),"Ma NV");
	in(x+55,wherey(),"Loai\n");
	int i=1;
	for(DSHD p=ds; p!=NULL; p=p->next){
		in(x,wherey(),toString(i));
		in(x+10,wherey(),xuLyNgay(p->hoadon.ngay));
		in(x+40,wherey(),p->hoadon.manv);
		in(x+55,wherey(),p->hoadon.lhd+"\n");
		in(x,wherey(),"-------------------------------------------------------------------------\n");
		
		inCTHoaDon(x+5,wherey(),p->hoadon.cthd);
		i++;
	}
}

int demSoHoaDonXuat(string manv){
	int tong=0;
	for(DSHD p=tcHoaDon; p!=NULL; p=p->next){
		if(p->hoadon.manv==manv && p->hoadon.lhd=="x"){
			tong++;
		}
	}
	return tong;
}

/** doc file */
void loadHangHoa(){
	string filename = "hanghoa.txt";
	fstream file(filename.c_str(),ios::in);
	if(!file){
		return;
	}else{
		string line;
		while(!file.eof()){
			HangHoa p;
			getline(file,line);
			float mahh = toFloat(line);
			getline(file,line);
			p.tenhh = line;
			getline(file,line);
			p.dvt = line;
			getline(file,line);
			p.slt = toInt(line);
			themHangHoa(tcHangHoa,mahh,p);
		}
	}
	file.close();
}
void loadNhanVien(){
	string filename = "nhanvien.txt";
	fstream file(filename.c_str(),ios::in);
	if(!file){
		return;
	}else{
		string line;
		while(!file.eof()){
			NhanVien p;
			getline(file,line);
			p.mnv = line;
			getline(file,line);
			p.ho = line;
			getline(file,line);
			p.ten = line;
			getline(file,line);
			p.phai = line;
			themNhanVien(tcNhanVien, p);
		}
	}
	file.close();
}
void loadHoaDon(){
	string filename = "hoadon.txt";
	fstream file(filename.c_str(),ios::in);
	if(!file){
		return;
	}else{
		string line;
		while(!file.eof()){
			HoaDon p;
			getline(file,line);
			p.sohd = line;
			getline(file,line);
			p.ngay.ngay = toInt(line);
			getline(file,line);
			p.ngay.thang = toInt(line);
			getline(file,line);
			p.ngay.nam = toInt(line);
			getline(file,line);
			p.manv = line;
			getline(file,line);
			p.lhd = line;
			p.cthd.n=0;
			themHoaDon(tcHoaDon, p);
		}
	}
	file.close();
}
void loadCTHoaDon(){
	string filename = "cthoadon.txt";
	fstream file(filename.c_str(),ios::in);
	if(!file){
		return;
	}else{
		string line;
		while(!file.eof()){
			CTHoaDon cthd;
			getline(file,line);
			DSHD hd = layHoaDon(line,tcHoaDon);
			
			getline(file,line);
			cthd.mahh = line;
			
			getline(file,line);
			cthd.soluong = toInt(line);
			
			getline(file,line);
			cthd.dongia = toFloat(line);
			
			getline(file,line);
			cthd.vat = toFloat(line);
			
			themCTHoaDon(hd->hoadon.cthd,cthd);
		}
	}
	file.close();
}
/** giao dien */

string nhap(int kieu, int size){
	string res="";
	int startx = wherex();
	int starty = wherey();
	int c=0;
	while(1){
		short x= wherex(),y=wherey();
		if((ktChu(c) || ktSo(c) || c==32) && kieu==CHU && res.length()<size){
			res+=c;
			in(startx,starty,res);
		}else if(ktSo(c) && kieu==SO && res.length()<size){
			res+=c;
			in(startx,starty,res);
		}else if(c==ESCAPE){
			flag = menuchinh;
			res = "thoat";
			break;
		}else if(c==BACKSPACE){
			in(startx,starty,khoangTrang(res.length()));
			res = res.substr(0,res.length()-1);
			in(startx,starty,res);
		}else if(c==ENTER){
			break;
		}
		c=getch();
	}
	return res;
}

void gdMenuChinh(){
	xoaManHinh();
	cout<< "QUAN LY XUAT NHAP HANG"<< endl << endl;
	cout << "1.Nhap hang." << endl;
	cout << "2.In danh sach hang ton kho." << endl;
	cout << "3.Nhap nhan vien." << endl;
	cout << "4.In danh sach nhan vien theo thu tu tang dan." << endl;
	cout << "5.Lap hoa don." << endl;
	cout << "6.In hoa don." << endl;
	cout << "7.Thong ke hoa don." << endl;
	cout << "8.Top 10 nhan vien co so phieu xuat cao nhat." << endl;
	cout << "9.Thoat." << endl;
	cout << "Moi ban chon menu tu 1->8: ";
	string s="9";
	do{
		s = nhap(SO,1);
		if(s=="thoat"){
			return;
		}
	}while(toInt(s)<=0);
	flag = toInt(s);
}

void gdNhapHang(){
	int c=0;
	do{
		xoaManHinh();
		in(70,0,"| Tat ca cac mat hang\n");
		gotoxy(70,wherey());
		inTatCaHangHoa(70,tcHangHoa);
		
		gotoxy(0,0);
		HangHoa hh;
		cout << "NHAP HANG" << endl;
		cout << "Ma hang hoa: ";
		string mahh="";
		do{
			mahh = nhap(SO,10);
			if(mahh=="thoat")return;
			if(layHangHoa(toFloat(mahh),tcHangHoa)!=NULL){
				cout << "\nHang nay da ton tai, vui long nhap lai! \nMa hang hoa: ";
			}else{
				break;
			}
		}while(1);
		cout << "\nTen hang hoa: ";
		string res = nhap(CHU,30);
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
		
		themHangHoa(tcHangHoa,toFloat(mahh),hh);
		
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
	cout << "CAC NHAN VIEN SAP XEP THEO TEN\n" << endl << endl;
	inDSNhanVien(wherex(),wherey(),tcNhanVien);
	cout << "\n\nNhan phim bat ki de thoat...";
	getch();
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
				
		int lasty = wherey();
		in(70,0,"| Tat ca cac hoa don\n");
		gotoxy(70,wherey());
		inTatCaHoaDon(70,tcHoaDon);
		
		
		in(0,lasty,"\n\nThem thanh cong!");
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
			case nhaphh:
				gdNhapHang();
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
		}
	}
	
	gdMenuChinh();
	cout << flag;
	return 0;
}
