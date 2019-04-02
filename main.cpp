#include <iostream>
#include<fstream>
#include<string.h>
using namespace std;
 ifstream f("Date2.txt");


void citire_stari(int &n,int &n2, char &q0, char *q[], char *fi[])
{
    int i;
    f>>n;
    *q=new char[n];
    for(i=0;i<n;i++)
      f>>(*q)[i];
    f>>q0>>n2;

    *fi=new char[n2];
    for(i=0;i<n2;i++)
          f>>(*fi)[i];

}
void citire_simboluri(int &m, char *s[])
{
    f>>m;
    *s=new char[m];
    f>>*s;
}

void creare_automat(int n, int m, char ***d ,char *s,char *q)
{
    char u,v; /// u, v sunt stari intre care exista o muchie cu simbolul c
    int i, j;
    char c;

  *d=new char*[n];
    for(i=0;i<n;i++)
       {
           (*d)[i]=new char[m];
           for(j=0;j<m;j++)
            (*d)[i][j]='-';
       }


   while( f>>u>>c>>v)
   {
     for(j=0;j<n;j++)
      if(q[j]==u)
        for(i=0;i<m;i++)
        if(s[i]==c)
        (*d)[j][i]=v;

   }

}

int verificare(char *s, char **d,char q0, char *fi, char*q, int n2,int n, char *cuv)
{
  int i, j,ok;
  if(strlen(cuv)==0||cuv[0]=='l')             /// l= lamda
   { cout<< "ultima stare: "<<q0<<"\n";
     for(i=0;i<n2;i++)
       if(fi[i]==q0)
        return 1;

     return 0;
    }
  if(strchr(s,cuv[0])==NULL)
    return 0;

  for(i=0;i<n;i++)
    if(q[i]==q0)
      for(j=0;j<strlen(s);j++)
       if(cuv[0]==s[j])
         if(d[i][j]=='-')
           return 0;
          else
            ok= verificare(s,d,d[i][j],fi,q,n2,n,cuv+1);

    return ok;
}

int main()
{
    int i,j,n,n2,m;
    char *q, *fi, q0 , **d;
    char *s,cuv[1000];

    citire_stari(n,n2,q0,&q, &fi);

    citire_simboluri(m,&s);
    cout<<"Alfabet: "<<s<<"\n";
    creare_automat(n,m,&d,s,q);

    cout<<"Introdu cuvant de verificat: ";
    cin>>cuv;

    int ok=verificare(s,d,q0,fi,q,n2,n,cuv);

    if(ok==0)
    cout<<"NU!"<<endl;
    else
    cout<<"DA!"<<endl;

    return 0;
}
