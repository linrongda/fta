/*
本项目已开源至：https://github.com/linrongda/fta
*/

#include<bits/stdc++.h>
using namespace std;

int door_num,event_num,max_gate_num;//门总数、事件总数,门下最大事件数
// int dr[100];//这个记录第i个门的类型，0为与门、1为或门
// int msj[100];//这个记录第i个门下的事件数
// char dre[100];//记录第i个门上的事件（只用于输出事故树）
// int tree[100][100];//记录事故树的表格
// int Mree[100][100];//计算m,n用的表格
// int ans[100][100];//计算布尔割集的表格
// int col_max[30],row_max;//第i行的列最大值与行的最大值
// int srt[1000];//用于临时排序的数组
// double sj[1000];//记录基本事件结构重要度
// int col_max_tmp[1000];
int i,j,m,n,Mree[100][100];
char tmp1,tmp2;

vector<int> dr,msj,col_max,srt,col_max_tmp;
vector<char> dre;
vector<double> sj;
vector<vector<int> > tree,ans;

int main(){
	//数据输入
	cout<<"请输入门总数：";
	cin>>door_num;
	cout<<"请输入基本事件总数：";
	cin>>event_num;
	cout<<"请输入门下最大事件数：";
	cin>>max_gate_num;
	cout << "--------------------------------------------------------------------------------" << endl;
	cout<<"输入提示(输入前请仔细阅读)：\n";
	cout<<"定义0为与门、1为或门,中间事件用大写A~Z表示，基本事件用小写a~z表示。\n";
	cout << "--------------------------------------------------------------------------------" << endl;
	for(i=0;i<door_num;i++)
	{
		printf("请输入第%d个门的类型与门下元素个数，用空格隔开:",i+1);
		scanf("%d %d",&tmp1,&tmp2);
		dr.push_back(tmp1);
		msj.push_back(tmp2);
		getchar();
	}
	for(i=0;i<door_num;i++)
	{vector<int> v1;
	 for(j=0;j<msj[i];j++)
	  {
		printf("请输入第%d个门中的第%d个事件:",i+1,j+1);
		cin>>tmp1;
		v1.push_back((int)tmp1);
		getchar();
	  }
	  tree.push_back(v1);
	  }
    dre.push_back('T');
	for(i=1;i<door_num;i++)dre.push_back((char)(64+i));
	//输出事故树
	for(i=0;i<door_num;i++)
	{
		if(dr[i]==0)printf("%c AND ",(char)dre[i]);
		else printf("%c OR  ",(char)dre[i]);
		for(j=0;j<msj[i];j++) cout<<left<<(char)tree[i][j]<<' ';
		cout<<'\n';
	}
	 //计算m
	 for(i=0;i<door_num;i++)
	 for(j=0;j<max_gate_num;j++)Mree[i][j]=tree[i][j];//进行数据拷贝
	for(i=0;i<door_num;i++)
	 for(j=0;j<max_gate_num;j++){if(Mree[i][j]>=97)Mree[i][j]=1; }//给基本事件赋权为1 
	for(i=door_num-1;i>=0;i--)
	{
		if(dr[i]==0)
		{
			m=Mree[i][0];
			for(j=1;j<msj[i];j++)m*=Mree[i][j];
		}
		if(dr[i]==1)
		{
			m=0;
			for(j=0;j<msj[i];j++)m+=Mree[i][j];
		}
		for(int x=0;x<door_num;x++)
		 for(int y=0;y<max_gate_num;y++)
		 {
			if(tree[x][y]==64+i)Mree[x][y]=m;
		 }
	}
	//计算n
	memset(Mree,0,sizeof(Mree));//重置Mree二维表
	for(i=0;i<door_num;i++)
	 for(j=0;j<max_gate_num;j++)Mree[i][j]=tree[i][j];//重新进行数据拷贝
	for(i=0;i<door_num;i++)
	 for(j=0;j<max_gate_num;j++)
	 {
	 if(Mree[i][j]>=97){Mree[i][j]=1;}
	 }//给基本事件赋权为1
	for(i=door_num-1;i>=0;i--)
	{
		if(dr[i]==1)
		{
			n=Mree[i][0];
			for(j=1;j<msj[i];j++)if(n<Mree[i][j])n=Mree[i][j];
		}
		if(dr[i]==0)
		{
			n=0;
			for(j=0;j<msj[i];j++)n+=Mree[i][j];
		}
		for(int x=0;x<door_num;x++)
		 for(int y=0;y<max_gate_num;y++)
		 {
			if(Mree[x][y]==64+i)Mree[x][y]=n;
		 }
	}
	printf("这棵事故树的m=%d,n=%d。\n",m,n);
	//求最小割集
	vector<int> vv;
	vv.push_back((int)'T');
	ans.push_back(vv);//定义初始布尔割集
	for(i=0;i<door_num;i++){
		if(dr[i]==0){
			for(int k=0;k<ans.size();k++) {
				if(find(ans[k].begin(),ans[k].end(),(int)dre[i])!=ans[k].end()){
					int index=distance(ans[k].begin(),find(ans[k].begin(),ans[k].end(),(int)dre[i]));
					ans[k].erase(ans[k].begin()+index);
					for(j=0;j<tree[i].size();j++)
					ans[k].push_back(tree[i][j]);
				}
			}
		}
		if(dr[i]==1){
			for(int k=0;k<ans.size();k++){
				if(find(ans[k].begin(),ans[k].end(),(int)dre[i])!=ans[k].end()){
					int index=distance(ans[k].begin(),find(ans[k].begin(),ans[k].end(),(int)dre[i]));
					ans[k].erase(ans[k].begin()+index);
					for(j=0;j<tree[i].size();j++)
					{
						vector<int> t;
						t.assign(ans[k].begin(),ans[k].end());
						t.push_back(tree[i][j]);
						ans.push_back(t);
					}
					ans.erase(ans.begin()+k);
				}
			}
		}
	}
	//对割集排序，去重
	for(auto& row:ans){
		sort(row.begin(),row.end());
		row.erase(unique(row.begin(), row.end()), row.end());
	}
	cout<<"本事故树的最小割集如下:\n";
	for(auto x:ans)
	{for(auto y:x)
	cout<<(char)y<<",";
	cout<<endl;}
	//计算结构重要度
	for(i=0;i<event_num;i++){
		float Ip=0;
		for(auto row:ans){
			if(find(row.begin(),row.end(),i+97)!=row.end())
			{
				Ip+=1/pow(2,row.size()-1);
			}
		}
		printf("基本事件%c的重要度等于%.2f.\n",i+97,Ip);
	}
	system("pause");
	return 0;
}
