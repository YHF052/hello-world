#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
using namespace std;

struct data{
	int user;
	int item;
	int res;
	int time;
};
struct cntusr{
	int user;
	int cnt;
};
vector<data> usr,itm_u,itm_t;
vector<data>::iterator iter;
vector<cntusr> ucnt;
vector<int> bufint;
vector<int> bufint2;
vector<int> bufint3;

int maxm,maxc;

bool operator==(const data& x, const data& y)//data ==
{
	return x.user == y.user && x.item == y.item && x.res == y.res && x.time == y.time;
}

int cmp1(const data &d1,const data &d2)//u>i>t for accept & items & ratio
{
	if(d1.user == d2.user){
		if(d1.item == d2.item) 
			return d1.time < d2.time;
		else return d1.item < d2.item;
	}else return d1.user < d2.user;
}
int cmp2(const data &d1,const data &d2)//i>u>t for findtime_item
{
	if(d1.item == d2.item){
		if(d1.user == d2.user) 
			return d1.time < d2.time;
		else return d1.user < d2.user;
	}else return d1.item < d2.item;
}
int cmp3(const data &d1,const data &d2)//i>t>u for users
{
	if(d1.item == d2.item){
		if(d1.time == d2.time) 
			return d1.user < d2.user;
		else return d1.time < d2.time;
	}else return d1.item < d2.item;
}
int cmp4(const cntusr &c1,const cntusr &c2)// for ucnt
{
	return c1.cnt < c2.cnt;
}


FILE *in;//輸入優化
int hasEOF = 0;
int readchar()
{
    static int N = 1<<20;
    static char buf[1<<20];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, in)) == buf) {
            hasEOF = 1;
            return EOF;    
        }
        p = buf;
    }
    return *p++;
}
int ReadInt(int *x)
{
    char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}

void accept()
{
	int u,i,t;//晚點試試readint2?
	scanf("%d%d%d",&u,&i,&t);
	data temp1 = {u,i,-1,t},temp2 = {u,i,1,t};
	int idx = lower_bound(usr.begin(),usr.end(),temp1,cmp1) - usr.begin();//
	if(usr[idx] == temp1)	puts("-1");
	else if(usr[idx] == temp2)	puts("1");
	else puts("0");
}

void items()
{
	int u1,u2; scanf("%d%d",&u1,&u2);
	data temp1 = {u1,0,0,0}, temp2 = {u1,2147483647,0,2147483647};
	int low = lower_bound(usr.begin(),usr.end(),temp1,cmp1) - usr.begin();
	int up = upper_bound(usr.begin(),usr.end(),temp2,cmp1) - usr.begin();
	for(int i = low; i < up; i++)
		bufint.push_back(usr[i].item);
	sort(bufint.begin(),bufint.end());
	int bsize = unique(bufint.begin(),bufint.end()) - bufint.begin();
	bufint.resize(bsize);
	
	data temp3 = {u2,0,0,0}, temp4 = {u2,2147483647,0,2147483647};
	low = lower_bound(usr.begin(),usr.end(),temp3,cmp1) - usr.begin();
	up = upper_bound(usr.begin(),usr.end(),temp4,cmp1) - usr.begin();
	for(int i = low; i < up; i++)
		bufint2.push_back(usr[i].item);
	sort(bufint2.begin(),bufint2.end());
	int b2size = unique(bufint2.begin(),bufint2.end()) - bufint2.begin();
	bufint2.resize(b2size);
	
	set_intersection(bufint.begin(),bufint.end(),bufint2.begin(),bufint2.end(),back_inserter(bufint3));
	int msize = bufint3.size();
	if(msize == 0) puts("EMPTY");
	else{
		for(int i = 0; i < msize; i++)
			printf("%d\n",bufint3[i]);
	}
	bufint.clear();
	bufint2.clear();
	bufint3.clear();
}

void users()
{
	int i1,i2,t1,t2;
	//if i1==i2
	scanf("%d%d%d%d",&i1,&i2,&t1,&t2);
	data temp1 = {0,i1,0,t1}, temp2 = {2147483647,i1,0,t2};
	int low = lower_bound(itm_t.begin(),itm_t.end(),temp1,cmp3) - itm_t.begin();
	int up = upper_bound(itm_t.begin(),itm_t.end(),temp2,cmp3) - itm_t.begin();
	for(int i = low; i < up; i++)
		bufint.push_back(itm_t[i].user);
	sort(bufint.begin(),bufint.end());
	int bsize = unique(bufint.begin(),bufint.end()) - bufint.begin();
	bufint.resize(bsize);
	
	data temp3 = {0,i2,0,t1}, temp4 = {2147483647,i2,0,t2};
	low = lower_bound(itm_t.begin(),itm_t.end(),temp3,cmp3) - itm_t.begin();
	up = upper_bound(itm_t.begin(),itm_t.end(),temp4,cmp3) - itm_t.begin();
	for(int i = low; i < up; i++)
		bufint2.push_back(itm_t[i].user);
	sort(bufint2.begin(),bufint2.end());
	int b2size = unique(bufint2.begin(),bufint2.end()) - bufint2.begin(); 
	bufint2.resize(b2size);
	
	set_intersection(bufint.begin(),bufint.end(),bufint2.begin(),bufint2.end(),back_inserter(bufint3));
	int msize = bufint3.size();
	if(msize == 0) puts("EMPTY");
	else{
		for(int i = 0; i < msize; i++)
			printf("%d\n",bufint3[i]);
	}
	bufint.clear();
	bufint2.clear();
	bufint3.clear();
}

void ratio()
{
	int i,thre,ac = 0,to = 0;
	scanf("%d%d",&i,&thre);
	cntusr temp1 = {0,thre+1};
	int idx = lower_bound(ucnt.begin(),ucnt.end(),temp1,cmp4) - ucnt.begin();
	for(int k = idx; k < maxc; k++){
		to++;
		data temp2 = {ucnt[k].user,i,0,0};
		int idx1 = lower_bound(usr.begin(),usr.end(),temp2,cmp1) - usr.begin();
		while(idx1 < maxm && usr[idx1].user == ucnt[k].user && usr[idx1].item == i){
			if(usr[idx1].res == 1) {ac++;	break;}
			idx1++;
		}
	}
	printf("%d/%d\n",ac,to);
}

void findtime_item()
{
	int i; scanf("%d",&i);
	/* char s[1<<20];	fgets(s,1<<20,stdin);
	char de[] = " ";
	char *ptr;
	ptr = strtok(s,de);
	vector<int> us;
	while(ptr != NULL){
		char temps[15];
		strcpy(temps,ptr);
		us.push_back(atoi(temps));
		ptr = strtok(NULL,de);
	} */
	int next;
	vector<int> us; 
	string s; getline(cin,s);
	istringstream in(s);
	while(in >> next)
		us.push_back(next); 
	int usize = unique(us.begin(),us.end()) - us.begin();
	us.resize(usize);
	for(int k = 0; k < usize; k++){
		data temp = {us[k],i,0,0};
		int idx = lower_bound(itm_u.begin(),itm_u.end(),temp,cmp2) - itm_u.begin();
		while(idx < maxm && itm_u[idx].item == i && itm_u[idx].user == us[k]){
			bufint.push_back(itm_u[idx].time);
			idx++;
		}
	}
	sort(bufint.begin(),bufint.end());
	int bsize = unique(bufint.begin(),bufint.end()) - bufint.begin();
	bufint.resize(bsize);
	if(bsize == 0) puts("EMPTY");
	else{
		for(int k = 0; k < bsize; k++)
			printf("%d\n",bufint[k]);
	}
	bufint.clear();
}

int main() 
{
    int u,i,t,r;
	in = fopen("/tmp2/KDDCUP2012/track1/rec_log_train.txt","rb");
    while (ReadInt(&u)== 1) {
        ReadInt(&i);	ReadInt(&r);	ReadInt(&t);
		usr.push_back({u,i,r,t});
	}
	fclose(in);
	
	sort(usr.begin(),usr.end(),cmp1);
	maxm = unique(usr.begin(),usr.end()) - usr.begin();
	usr.resize(maxm);
	itm_u = usr;
	sort(itm_u.begin(),itm_u.end(),cmp2);
	itm_t = itm_u;
	sort(itm_t.begin(),itm_t.end(),cmp3);
	
	
	int tempu = usr[0].user,cnt = 1;//
	for(iter = usr.begin()+1;iter != usr.end(); iter++){
		if(iter->user != tempu){
			ucnt.push_back({tempu,cnt});
			tempu = iter->user;
			cnt = 1;
		}else cnt++;
	}
	ucnt.push_back({tempu,cnt});
	sort(ucnt.begin(),ucnt.end(),cmp4);
	maxc = ucnt.size();
	
	int n; scanf("%d",&n);
	string cmd;
	while(n--){
		cin >> cmd;
		if(cmd == "accept"){
			accept();
		}else if(cmd == "items"){
			items();
		}else if(cmd == "users"){
			users();
		}else if(cmd == "ratio"){
			ratio();
		}else if(cmd == "findtime_item"){
			findtime_item();
		}
	}
	return 0;
}