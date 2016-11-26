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

//=============== cac ham phu ================
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
float toInt(string s){
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

void inDSHangTonKho(int x, int y, DSHH &ds){
	const int StackSize =500;
	DSHH stack[StackSize];
	int sp=-1;
	DSHH p = ds;
	int i=1;
	in(x,y,"STT");
	in(x+5,y,"Ma HH");
	in(x+25,y,"Ten Hang Hoa");
	in(x+60,y,"So Luong");
	in(x+70,y,"Don Vi");
	y++;
	while(p!=NULL){
		in(x,y,toString(i)); 					//in so thu tu
		in(x+5,y,toString(p->mahh));			//in ma hang hoa
		in(x+25,y,p->hanghoa.tenhh);			//in ten hang hoa 
		in(x+60,y,toString(p->hanghoa.slt));	//in so luong hang hoa
		in(x+70,y,p->hanghoa.dvt);				//in don vi tinh
		y++;
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
		for(DSNV q=p->next; q!=NULL; q=q->next){
			if(q->nhanvien.ten[0]<p->nhanvien.ten[0]){
				DSNV temp = q;
				q=p;
				p=temp;
			}
		}
	}
}

/** hoa don */


int main(int argc, char** argv) {
	cout << toLowerCase("DD a ABCCCCCdddDDDDddDDD");
	return 0;
}
