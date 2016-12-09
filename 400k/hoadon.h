#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>
#include <fstream>

using namespace std;

//---------------------khai bao-------------------
/** Chi Tiet Hoa Don */

typedef struct{
	float mahh;
	int soluong;
	float dongia;
	float vat;
}CTHoaDon;
struct ct_hoa_don{
	int n;
	CTHoaDon ds[MAXLIST];
};
typedef struct ct_hoa_don CTHD; // danh sach tuyen tinh

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
typedef struct hoa_don* DSHD; // danh sach lien ket don

DSHD tcHoaDon;

//----------------het khai bao----------------

/** chi tiet hoa don */
void themCTHoaDon(CTHD &ds, CTHoaDon cthd){
	if(ds.n==MAXLIST){
		return;
	}
	ds.ds[ds.n] = cthd;
	ds.n++;
}

void inCTHoaDon(int x, CTHD &ds){
	if(ds.n==0){
		return;
	}
	for(int i=0;i<ds.n;i++){
		in(x,wherey(),"| "+toString(ds.ds[i].mahh)+" -- "+toString(ds.ds[i].soluong));
	}
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
		in(x+5,y+i,toString(ds.ds[i].mahh));
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

void loadCTHoaDon(DSHD &ds){
	string filename = ds->hoadon.sohd+".txt";
	fstream file(filename.c_str(),ios::in);
	if(!file){
		return;
	}else{
		string line;
		while(!file.eof()){
			CTHoaDon cthd;
			getline(file,line);
			if(line=="")break;
			cthd.mahh = toFloat(line);
			
			getline(file,line);
			cthd.soluong = toInt(line);
			
			getline(file,line);
			cthd.dongia = toFloat(line);
			
			getline(file,line);
			cthd.vat = toFloat(line);
			
			themCTHoaDon(ds->hoadon.cthd,cthd);
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
			if(line=="")break;
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
			DSHD dshd = layHoaDon(p.sohd,tcHoaDon);
			loadCTHoaDon(dshd);
		}
	}
	file.close();
}
void ghiCTHoaDon(DSHD &ds){
	string filename = ds->hoadon.sohd+".txt";
	fstream file(filename.c_str(),ios::app);
	if(!file){
		return;
	}
	for(int i=0;i<ds->hoadon.cthd.n;i++){
		file << ds->hoadon.cthd.ds[i].mahh<< endl
		<< ds->hoadon.cthd.ds[i].soluong << endl
		<< ds->hoadon.cthd.ds[i].dongia << endl
		<< ds->hoadon.cthd.ds[i].vat << endl;
	}
	file.close();
}
void ghiHoaDon(){
	string filename = "hoadon.txt";
	fstream file(filename.c_str(),ios::out);
	if(!file){
		return;
	}
	for(DSHD p=tcHoaDon; p!=NULL; p=p->next){
		file << p->hoadon.sohd << endl
		<< p->hoadon.ngay.ngay << endl
		<< p->hoadon.ngay.thang << endl
		<< p->hoadon.ngay.nam << endl
		<< p->hoadon.manv << endl
		<< p->hoadon.lhd << endl;
		ghiCTHoaDon(p);
	}
	file.close();
}
