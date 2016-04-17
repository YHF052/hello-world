#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <sstream>
using namespace std;
const int MAXN = 30 + 5;
vector<int> r[MAXN],c[MAXN];//row & col
int m,n;
int out[MAXN][MAXN]={};//output
int rmin[MAXN][MAXN]={},cmin[MAXN][MAXN]={};//剪枝
int rst[MAXN]={},cst[MAXN]={};//nowsection
int rlg[MAXN]={},clg[MAXN]={};//nowlength

int check(int row,int col)
{
	if(out[row][col] > 0){//填
		if(rst[row] >= r[row].size())	return 0;//st爆掉 不合
		if(cst[col] >= c[col].size())	return 0;//ex size = 1 st只能 = 0
		if(rlg[row] > r[row][ rst[row] ])	return 0;//lg爆掉 不合
		if(clg[col] > c[col][ cst[col] ])	return 0;//因為已填 不會有st=-1
		if(n-1 - col < rmin[row][ rst[row] ] + r[row][ rst[row] ] - rlg[row])	return 0;
		if(m-1 - row < cmin[col][ cst[col] ] + c[col][ cst[col] ] - clg[col])	return 0;
	}else{//不填
		if(rst[row] == -1 && n-1 - col < rmin[row][0] + r[row][0]) return 0;
		if(cst[col] == -1 && m-1 - row < cmin[col][0] + c[col][0]) return 0;
		if(rst[row] != -1 && n-1 - col < rmin[row][ rst[row] ] - 1)	return 0;
		if(cst[col] != -1 && m-1 - row < cmin[col][ cst[col] ] - 1)	return 0;
	}
	return 1;
}

void nono(int row, int col)
{
	if(row == m){//final && output
		for(int i = 0; i < m; i++){
			for(int j = 0; j < n; j++){
				if(out[i][j] > 0) printf("#");
				else printf(".");
			}	puts("");
		}	exit(0);
	}
	
	int fill_r = 0,fill_c = 0,conflict = 0;
	if(rst[row] != -1){
		if(rlg[row] > r[row][ rst[row] ])	return;
		else if(rlg[row] == r[row][ rst[row] ])	fill_r = -1;//必不填
		else if(rlg[row] != 0)	fill_r = 1;//必填
	}
	if(cst[col] != -1){
		if(clg[col] > c[col][ cst[col] ])	return;
		else if(clg[col] == c[col][ cst[col] ])	fill_c = -1;//必不填
		else if(clg[col] != 0)	fill_c = 1;//必填
	}
	if(fill_r * fill_c < 0)	conflict = 1;
	if(out[row][col] == 2 && (fill_r == -1 || fill_c == -1)) conflict = 1;
	if(conflict)	return;
	
	if(out[row][col] == 2){//必填
		if(rlg[row] == 0)	rst[row]++;//初始化成-1的用意
		if(clg[col] == 0)	cst[col]++;//前面沒填後面就st++
		rlg[row]++;//填 lg++
		clg[col]++;
		if(check(row,col)){//確認
			if(col != n-1)	nono(row,col+1);//遞迴
			else	nono(row+1,0);
		}
		rlg[row]--;//錯誤、出遞迴
		clg[col]--;//回復原狀
		if(rlg[row] == 0)	rst[row]--;
		if(clg[col] == 0)	cst[col]--;		
	}else{//brute
		if(fill_r != -1 && fill_c != -1){//沒有必不填
			out[row][col] = 1;//填
			if(rlg[row] == 0)	rst[row]++;//初始化成-1的用意
			if(clg[col] == 0)	cst[col]++;//前面沒填後面就st++
			rlg[row]++;//填 lg++
			clg[col]++;
			if(check(row,col)){//確認
				if(col != n-1)	nono(row,col+1);//遞迴
				else	nono(row+1,0);
			}
			rlg[row]--;//錯誤、出遞迴
			clg[col]--;//回復原狀
			if(rlg[row] == 0)	rst[row]--;
			if(clg[col] == 0)	cst[col]--;
		}
		if(fill_r != 1 && fill_c != 1){//沒有必填
			out[row][col] = 0;//不填
			int tempr = rlg[row];//紀錄
			int tempc = clg[col];
			rlg[row] = 0;
			clg[col] = 0;
			if(check(row,col)){	//確認
				if(col != n-1) nono(row,col+1);
				else nono(row+1,0);
			}
			rlg[row] = tempr;//錯誤、出遞迴
			clg[col] = tempc;//回復原狀
		}
	}
	return;
}

int main()
{
	scanf("%d%d",&m,&n);
	for(int i = 0; i < m; i++){//input
		string s;	int tok;
		scanf("%d",&tok); r[i].push_back(tok);
		getline(cin,s);
		istringstream in(s);
		while(in >> tok)
			r[i].push_back(tok);
	}
	for(int i = 0; i < n; i++){//input
		string s;	int tok;
		scanf("%d",&tok); c[i].push_back(tok);
		getline(cin,s);
		istringstream in(s);
		while(in >> tok)
			c[i].push_back(tok);
	}
	
	for(int i = 0; i < MAXN; i++)
		rst[i] = cst[i] = -1;
	
	for(int i = 0; i < m; i++)//建表
		for(int j = r[i].size() - 1; j >= 0 ; j--){
			if(j == r[i].size() - 1)	rmin[i][j] = 0;
			else	rmin[i][j] = rmin[i][j+1] + r[i][j+1] + 1;
		} 
	for(int i = 0; i < n; i++)//建表
		for(int j = c[i].size() - 1; j >= 0 ; j--){
			if(j == c[i].size() - 1)	cmin[i][j] = 0;
			else	cmin[i][j] = cmin[i][j+1] + c[i][j+1] + 1;
		}
	
	for(int i = 0; i < m; i++){//intersection
		int sum = r[i].size() - 1;
		for(int j = 0; j < r[i].size(); j++)
			sum += r[i][j];
		
		int pos = 0;
		for(int j = 0; j < r[i].size(); j++){
			int tmp = n - sum;
			for(int k = 0; k < r[i][j]; k++){
				if(tmp <= 0) out[i][pos + k] = 2; //2=must filled
				tmp--;
			}
			pos += r[i][j] + 1;
		}
	}
	for(int i = 0; i < n; i++){//intersection
		int sum = c[i].size() - 1;
		for(int j = 0; j < c[i].size(); j++)
			sum += c[i][j];
		int pos = 0;
		for(int j = 0; j < c[i].size(); j++){
			int tmp = m - sum;
			for(int k = 0; k < c[i][j]; k++){
				if(tmp <= 0) out[pos + k][i] = 2;
				tmp--;
			}
			pos += c[i][j] + 1;
		}
	}
	
	for(int i = 0; i < m; i++){//fill more
		for(int j = 0; j < r[i][0]; j++){
			if(out[i][j]){
				for(; j < r[i][0]; j++)
					out[i][j] = 2;
			}
		}
		for(int j = 0; j < r[i][ r[i].size()-1 ]; j++){
			if(out[i][n-1-j]){
				for(; j < r[i][ r[i].size()-1 ]; j++)
					out[i][n-1-j] = 2;
			}
		}
	}
	for(int i = 0; i < n; i++){//fill more
		for(int j = 0; j < c[i][0]; j++){
			if(out[j][i]){
				for(; j < c[i][0]; j++)
					out[j][i] = 2;
			}
		}
		for(int j = 0; j < c[i][ c[i].size()-1 ]; j++){
			if(out[m-1-j][i]){
				for(; j < c[i][ c[i].size()-1 ]; j++)
					out[m-1-j][i] = 2;
			}	
		}
	}
	nono(0,0);
	return 0;
}