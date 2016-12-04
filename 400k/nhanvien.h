#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>
#include <fstream>

using namespace std;

typedef struct{
	string mnv;
	string ho;
	string ten;
	string phai;
	int shd;
}NhanVien;
struct nhan_vien{
	NhanVien nhanvien;
	struct nhan_vien *next;
};
typedef struct nhan_vien *DSNV;

DSNV tcNhanVien;

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
	if(ds==NULL)return;
	for(DSNV p=ds; p->next!=NULL; p=p->next){
		string ten1 = toLowerCase(p->nhanvien.ten);
		for(DSNV q=p->next; q!=NULL; q=q->next){
			string ten2 = toLowerCase(q->nhanvien.ten);
			if(strcmp(ten1.c_str(),ten2.c_str())>0){
				NhanVien temp = q->nhanvien;
				q->nhanvien=p->nhanvien;
				p->nhanvien=temp;
			}
		}
	}
}

void sapXepTopNV(DSNV &ds){
	if(ds==NULL)return;
	for(DSNV p=ds; p->next!=NULL; p=p->next){
		for(DSNV q=p->next; q!=NULL;q=q->next){
			if(p->nhanvien.shd <= q->nhanvien.shd){
				NhanVien temp = p->nhanvien;
				p->nhanvien = q->nhanvien;
				q->nhanvien = temp;
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
			if(line=="")break;
			p.mnv = line;
			getline(file,line);
			p.ho = line;
			getline(file,line);
			p.ten = line;
			getline(file,line);
			p.phai = line;
			getline(file,line);
			p.shd=toInt(line);
			themNhanVien(tcNhanVien, p);
		}
	}
	file.close();
}
void ghiNhanVien(){
	string filename = "nhanvien.txt";
	fstream file(filename.c_str(),ios::out);
	if(!file){
		return;
	}
	for(DSNV p=tcNhanVien; p!=NULL; p=p->next){
		file << p->nhanvien.mnv << endl
		<< p->nhanvien.ho << endl
		<< p->nhanvien.ten << endl
		<< p->nhanvien.phai << endl
		<< p->nhanvien.shd << endl;
	}
	file.close();
}
