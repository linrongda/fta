/*
����Ŀ�ѿ�Դ����https://github.com/linrongda/fta
*/

#include<bits/stdc++.h>
using namespace std;

int door_num,event_num,max_gate_num;//���������¼�����,��������¼���
// int dr[100];//�����¼��i���ŵ����ͣ�0Ϊ���š�1Ϊ����
// int msj[100];//�����¼��i�����µ��¼���
// char dre[100];//��¼��i�����ϵ��¼���ֻ��������¹�����
// int tree[100][100];//��¼�¹����ı��
// int Mree[100][100];//����m,n�õı��
// int ans[100][100];//���㲼����ı��
// int col_max[30],row_max;//��i�е������ֵ���е����ֵ
// int srt[1000];//������ʱ���������
// double sj[1000];//��¼�����¼��ṹ��Ҫ��
// int col_max_tmp[1000];
int i,j,m,n,Mree[100][100];
char tmp1,tmp2;

vector<int> dr,msj,col_max,srt,col_max_tmp;
vector<char> dre;
vector<double> sj;
vector<vector<int> > tree,ans;

int main(){
	//��������
	cout<<"��������������";
	cin>>door_num;
	cout<<"����������¼�������";
	cin>>event_num;
	cout<<"��������������¼�����";
	cin>>max_gate_num;
	cout << "--------------------------------------------------------------------------------" << endl;
	cout<<"������ʾ(����ǰ����ϸ�Ķ�)��\n";
	cout<<"����0Ϊ���š�1Ϊ����,�м��¼��ô�дA~Z��ʾ�������¼���Сдa~z��ʾ��\n";
	cout << "--------------------------------------------------------------------------------" << endl;
	for(i=0;i<door_num;i++)
	{
		printf("�������%d���ŵ�����������Ԫ�ظ������ÿո����:",i+1);
		scanf("%d %d",&tmp1,&tmp2);
		dr.push_back(tmp1);
		msj.push_back(tmp2);
		getchar();
	}
	for(i=0;i<door_num;i++)
	{vector<int> v1;
	 for(j=0;j<msj[i];j++)
	  {
		printf("�������%d�����еĵ�%d���¼�:",i+1,j+1);
		cin>>tmp1;
		v1.push_back((int)tmp1);
		getchar();
	  }
	  tree.push_back(v1);
	  }
    dre.push_back('T');
	for(i=1;i<door_num;i++)dre.push_back((char)(64+i));
	//����¹���
	for(i=0;i<door_num;i++)
	{
		if(dr[i]==0)printf("%c AND ",(char)dre[i]);
		else printf("%c OR  ",(char)dre[i]);
		for(j=0;j<msj[i];j++) cout<<left<<(char)tree[i][j]<<' ';
		cout<<'\n';
	}
	 //����m
	 for(i=0;i<door_num;i++)
	 for(j=0;j<max_gate_num;j++)Mree[i][j]=tree[i][j];//�������ݿ���
	for(i=0;i<door_num;i++)
	 for(j=0;j<max_gate_num;j++){if(Mree[i][j]>=97)Mree[i][j]=1; }//�������¼���ȨΪ1 
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
	//����n
	memset(Mree,0,sizeof(Mree));//����Mree��ά��
	for(i=0;i<door_num;i++)
	 for(j=0;j<max_gate_num;j++)Mree[i][j]=tree[i][j];//���½������ݿ���
	for(i=0;i<door_num;i++)
	 for(j=0;j<max_gate_num;j++)
	 {
	 if(Mree[i][j]>=97){Mree[i][j]=1;}
	 }//�������¼���ȨΪ1
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
	printf("����¹�����m=%d,n=%d��\n",m,n);
	//����С�
	vector<int> vv;
	vv.push_back((int)'T');
	ans.push_back(vv);//�����ʼ�����
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
	//�Ը����ȥ��
	for(auto& row:ans){
		sort(row.begin(),row.end());
		row.erase(unique(row.begin(), row.end()), row.end());
	}
	cout<<"���¹�������С�����:\n";
	for(auto x:ans)
	{for(auto y:x)
	cout<<(char)y<<",";
	cout<<endl;}
	//����ṹ��Ҫ��
	for(i=0;i<event_num;i++){
		float Ip=0;
		for(auto row:ans){
			if(find(row.begin(),row.end(),i+97)!=row.end())
			{
				Ip+=1/pow(2,row.size()-1);
			}
		}
		printf("�����¼�%c����Ҫ�ȵ���%.2f.\n",i+97,Ip);
	}
	system("pause");
	return 0;
}
