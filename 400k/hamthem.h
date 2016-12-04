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
