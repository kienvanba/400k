#include <iostream>
#include <string>
#include <sstream>
#include <mylib.h>
#include <Windows.h>

#define MAXLIST 500
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

using namespace std;


int flag;

typedef struct{
	int ngay;
	int thang;
	int nam;
}Ngay; // tao 1 khoi chua ngay thang nam;

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
int laySoNgay(int thang, int year){
	switch(thang){
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			return 31;
		case 4:
		case 6:
		case 9:
		case 11:
			return 30;
		case 2:
			return (year%4==0?29:28);
	}
}
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

Ngay nhap(){
	string ngay="", thang="", nam="";
	Ngay n;
	n.ngay = toInt(ngay);
	n.thang = toInt(thang);
	n.nam = toInt(nam);
	int startx = wherex();
	int starty = wherey();
	int currentType=0;
	cout <<"  /  /";
	gotoxy(startx,starty);
	int c=0;
	while(1){
		short x= wherex(),y=wherey();
		if(ktSo(c) || c==32){
			switch(currentType){
				case 0:
					if(ngay.length()<2){
						ngay+=c;
						if(toInt(ngay)>31)ngay="31";
						in(startx,starty,ngay);
					}
					break;
				case 1:
					if(thang.length()<2){
						thang+=c;
						if(toInt(thang)>12)thang="12";
						in(startx+3,starty,thang);
					}
					break;
				case 2:
					if(nam.length()<4){
						nam+=c;
						in(startx+6,starty,nam);
					}
					break;
			}
		}else if(c==ESCAPE){
			flag = menuchinh;
			n.ngay=1000;
			break;
		}else if(c==BACKSPACE){
//			in(startx,starty,khoangTrang(res.length()));
//			res = res.substr(0,res.length()-1);
//			in(startx,starty,res);
			switch(currentType){
				case 0:
					in(startx,starty,khoangTrang(ngay.length()));
					ngay = ngay.substr(0,ngay.length()-1);
					in(startx,starty,ngay);
					break;
				case 1:
					in(startx+3,starty,khoangTrang(thang.length()));
					thang = thang.substr(0,thang.length()-1);
					in(startx+3,starty,thang);
					break;
				case 2:
					in(startx+6,starty,khoangTrang(nam.length()));
					nam = nam.substr(0,nam.length()-1);
					in(startx+6,starty,nam);
					break;
			}
		}else if(c==ENTER){
			switch(currentType){
				case 0:
					if(ngay==""){
						ngay = "1";
						in(startx,starty,ngay);
					}
					currentType=1;
					gotoxy(startx+3,starty);
					break;
				case 1:
					if(thang==""){
						thang = "1";
						in(startx+3,starty,thang);
					}
					if(toInt(ngay)>laySoNgay(toInt(thang),4)){
						ngay = toString(laySoNgay(toInt(thang),4));
						in(startx,starty,ngay);
					}
					currentType=2;
					gotoxy(startx+6,starty);
					break;
				case 2:
					if(nam==""){
						nam = "2016";
						in(startx+6,starty,nam);
					}
					if(toInt(ngay)==29 && toInt(thang)==2 && toInt(nam)%4!=0){
						ngay = "28";
						in(startx,starty,ngay);
					}
					n.ngay = toInt(ngay);
					n.thang = toInt(thang);
					n.nam = toInt(nam);
					return n;
			}
		}
		c=getch();
	}
	return n;
}
