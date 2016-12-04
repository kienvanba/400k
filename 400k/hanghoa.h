#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>
#include <fstream>

using namespace std;

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

DSHH tcHangHoa;

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
		in(x,wherey(),"| "+toString(ds->mahh)+" -- "+ds->hanghoa.tenhh+" -- "+toString(ds->hanghoa.slt)+"\n");
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
			if(line=="")break;
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

void ghiHangHoa(){
	string filename = "hanghoa.txt";
	fstream file(filename.c_str(),ios::out);
	if(!file){
		return;
	}
	const int StackSize =500;
	DSHH stack[StackSize];
	int sp=-1;
	DSHH p = tcHangHoa;
	while(p!=NULL){
		file << p->mahh << endl
		<< p->hanghoa.tenhh << endl
		<< p->hanghoa.dvt << endl
		<< p->hanghoa.slt << endl;
		
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
	file.close();
}
