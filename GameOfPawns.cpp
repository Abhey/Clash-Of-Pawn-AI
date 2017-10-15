#include <bits/stdc++.h>
#include "Evaluate.h"
#define pb push_back
#define mp make_pair
#define fr first
#define sec second
#define PII pair<int,int>
#define PPI pair<PII,PII>
#define PPP pair<int,PPI>
#define VPP vector<PPI>
#define VI vector<int>
#define VP vector<PII>
using namespace std;
int maxdepth,me;
clock_t start;
int dx[3]={-1,0,1};
int board[boardSize][boardSize],table[12][12][3];
map <int,PII> m;
bool cmpd (const pair<int,PPI> &p1,const pair<int,PPI> &p2)
{
    return p1.fr>p2.fr;
}
bool CheckValid(int x1,int y1,int x2,int y2,int player)
{
   if(x2<0||x2>=boardSize||y2<0||y2>=boardSize) return false;
   if(board[x2][y2]==nill) return true;
   if(board[x2][y2]==player) return false;
   if((y1==y2)&&(board[x2][y2]==1-player)) return false;
   return true;
}
bool CheckValid2(int x1,int y1,int x2,int y2,int player)
{
    if(board[x2][y2]==nill) return true;
    return false;
}
int PlayerCount(int player)
{
   int cnt=0;
   for(int i=0;i<boardSize;i++)
      for(int j=0;j<boardSize;j++)
      if(board[i][j]==player)
      cnt++;
   return cnt;
}
int WhichMove(int me)
{
   int cnt=0;
   if(me==white)
   {
      for(int i=2;i<boardSize;i++)
      for(int j=0;j<boardSize;j++)
      if(board[i][j]==white)
      cnt+=i-1;
      for(int i=0;i<boardSize;i++)
      if(board[0][i]==nill)
      cnt++;
   }
   else
   {
      for(int i=0;i<boardSize-2;i++)
      for(int j=0;j<boardSize;j++)
      if(board[i][j]==black)
      cnt+=10-i+1;
      for(int i=0;i<boardSize;i++)
      if(board[11][i]==nill)
      cnt++;
   }
   return cnt;
}
void initTable()
{
    srand(time(NULL));
    for(int i=0;i<boardSize;i++)
        for(int j=0;j<boardSize;j++)
        for(int k=0;k<3;k++)
        table[i][j][k]=(rand()%INT_MAX);
    return;
}
int getHashValue()
{
    int Hash=0;
    for(int i=0;i<boardSize;i++)
    for(int j=0;j<boardSize;j++)
    {
        if(board[i][j]==-1)
            Hash^=table[i][j][0];
        else if(board[i][j]==0)
            Hash^=table[i][j][1];
        else Hash^=table[i][j][2];
    }
    return Hash;
}
int minimax(int depth,bool ismaxturn,int alpha,int beta)
{
   int player;
    if(ismaxturn) player=me;
    else player=1-me;
   int currentColor = (ismaxturn) ? !me : me;

   int eval = evaluate(board,me,currentColor);
   if(me==white&&whiteWonGame==true) return 10*winValue-depth;
   if(me==white&&blackWonGame==true) return -10*winValue+depth;
   if(me==black&&blackWonGame==true) return 10*winValue-depth;
   if(me==black&&whiteWonGame==true) return -10*winValue+depth;

    clock_t finish=clock();
    if((double)(finish-start)/CLOCKS_PER_SEC>1.5)
    {return eval;}

   if(depth==maxdepth) {return eval;}

   int dy=(player==white)?1:-1;

//////////////MOVE ORDERING////////////////////
PII src,dst;
vector<pair<int,PPI> > v;
for(int i=0;i<boardSize;i++)
    for(int j=0;j<boardSize;j++)
{
    if(board[i][j]==player)
    {
        src=mp(i,j);
        for(int k=0;k<3;k++)
        {
            dst=mp(i+dy,j+dx[k]);
            if(CheckValid(src.fr,src.sec,dst.fr,dst.sec,player))
            {
                int prev_state=board[dst.fr][dst.sec];
                board[dst.fr][dst.sec]=player;
                board[src.fr][src.sec]=-1;
                int evl=evaluate(board,me,player);
                board[dst.fr][dst.sec]=prev_state;
                board[src.fr][src.sec]=player;
                v.pb(mp(evl,mp(src,dst)));
            }
        }
////////////////////////////Add Special Moves///////////////////////////

      /*  if(player==white)
        {
            if((src.fr==5&&src.sec==2)||(src.fr==5&&src.sec==3))
            {
                dst=mp(i+1,j+6);
                if(CheckValid2(src.fr,src.sec,dst.fr,dst.sec,player))
                {
                    int prev_state=board[dst.fr][dst.sec];
                    board[dst.fr][dst.sec]=player;
                    board[src.fr][src.sec]=nill;
                    int evl=evaluate(board,me,player);
                    board[dst.fr][dst.sec]=prev_state;
                    board[src.fr][src.sec]=player;
                    v.pb(mp(evl,mp(src,dst)));
                }
            }
            else if((src.fr==5&&src.sec==8)||(src.fr==5&&src.sec==9))
            {
                dst=mp(i+1,j-6);
                if(CheckValid2(src.fr,src.sec,dst.fr,dst.sec,player))
                {
                    int prev_state=board[dst.fr][dst.sec];
                    board[dst.fr][dst.sec]=player;
                    board[src.fr][src.sec]=-1;
                    int evl=evaluate(board,me,player);
                    board[dst.fr][dst.sec]=prev_state;
                    board[src.fr][src.sec]=player;
                    v.pb(mp(evl,mp(src,dst)));
                }
            }
        }
        else if(player==black)
        {
            if((src.fr==6&&src.sec==2)||(src.fr==6&&src.sec==3))
            {
                dst=mp(i-1,j+6);
                if(CheckValid2(src.fr,src.sec,dst.fr,dst.sec,player))
                {
                    int prev_state=board[dst.fr][dst.sec];
                    board[dst.fr][dst.sec]=player;
                    board[src.fr][src.sec]=-1;
                    int evl=evaluate(board,me,player);
                    board[dst.fr][dst.sec]=prev_state;
                    board[src.fr][src.sec]=player;
                    v.pb(mp(evl,mp(src,dst)));
                }
            }
            else if((src.fr==6&&src.sec==8)||(src.fr==6&&src.sec==9))
            {
                dst=mp(i-1,j-6);
                if(CheckValid2(src.fr,src.sec,dst.fr,dst.sec,player))
                {
                    int prev_state=board[dst.fr][dst.sec];
                    board[dst.fr][dst.sec]=player;
                    board[src.fr][src.sec]=-1;
                    int evl=evaluate(board,me,player);
                    board[dst.fr][dst.sec]=prev_state;
                    board[src.fr][src.sec]=player;
                    v.pb(mp(evl,mp(src,dst)));
                }
            }
        }*/
    }
}
///////////////////////////ADD SPECIAL MOVE//////////////////////////////////////////////////

if(ismaxturn) sort(v.begin(),v.end(),&cmpd);
else sort(v.begin(),v.end());

//////////////MOVE ORDERING///////////////////
   PII source,dest;
   int val;
   if(ismaxturn)
   {
      val=INT_MIN;
      for(int i=0;i<v.size();i++)
      {
            source=v[i].sec.fr;
            dest=v[i].sec.sec;

            int prev_state=board[dest.fr][dest.sec];
            board[dest.fr][dest.sec]=player;
            board[source.fr][source.sec]=-1;
            int calc=minimax(depth+1,!ismaxturn,alpha,beta);
            val = max(val,calc);
            alpha=max(val,alpha);
            board[dest.fr][dest.sec]=prev_state;
            board[source.fr][source.sec]=player;
            if(alpha>=beta) {return val;}
            clock_t finish=clock();
            if((double)(finish-start)/CLOCKS_PER_SEC>1.5)
            return val;
      }
    }

   else
   {
      val=INT_MAX;
      for(int i=0;i<v.size();i++)
      {
        source=v[i].sec.fr;
        dest=v[i].sec.sec;
        int prev_state=board[dest.fr][dest.sec];
        board[source.fr][source.sec]=-1;
        board[dest.fr][dest.sec]=player;
        int calc=minimax(depth+1,!ismaxturn,alpha,beta);
        val=min(val,calc);
        beta=min(beta,val);
        board[source.fr][source.sec]=player;
        board[dest.fr][dest.sec]=prev_state;
        if(alpha>=beta) {return val;}
        clock_t finish=clock();
        if((double)(finish-start)/CLOCKS_PER_SEC>1.5)
        return val;
      }
    }
  //  m[Hash]=mp(val,depth);
   return val;
}
PPP FindBestMove(int depth,bool ismaxturn,int alpha,int beta)
{
   PII source,dest;
   PPP bestmove;
   int player;
   if(ismaxturn) player=me;
   else player=1-me;
   int dy=(player==white)?1:-1;
   int bestval=INT_MIN;
   for(int i=0;i<boardSize;i++)
   for(int j=0;j<boardSize;j++)
      if(board[i][j]==player)
      {
         source=mp(i,j);
         for(int k=0;k<3;k++)
         {
            dest=mp(i+dy,j+dx[k]);
            if(CheckValid(source.fr,source.sec,dest.fr,dest.sec,player))
            {
               int prev_state=board[dest.fr][dest.sec];
               board[source.fr][source.sec]=-1;
               board[dest.fr][dest.sec]=player;
               int val=minimax(depth,false,alpha,beta);
               /*if(me==white){
               if(val>=bestval)
               {
                  bestval=val;
                  bestmove.fr=bestval;
                  bestmove.sec.fr=source;
                  bestmove.sec.sec=dest;
               }}*/
               //else{
                if(val>bestval)
               {
                  bestval=val;
                  bestmove.fr=bestval;
                  bestmove.sec.fr=source;
                  bestmove.sec.sec=dest;
               }
		// }
               board[dest.fr][dest.sec]=prev_state;
               board[source.fr][source.sec]=player;


            }
            clock_t finish=clock();
            if((double)(finish-start)/CLOCKS_PER_SEC>1.5)
                return bestmove;
         }

      }
   return bestmove;
}
PPI iterativeDeepening(int depth,bool ismaxturn,int alpha,int beta)
{
    PPP finalMove;
    start=clock();
    maxdepth=1;
   // PPP temp=FindBestMove(1,true,alpha,beta);
    while(maxdepth<7)
    {
        PPP temp=FindBestMove(1,true,alpha,beta);
        clock_t finish=clock();
        if((double)(finish-start)/CLOCKS_PER_SEC>1.5)
            {
                //if(temp.fr>finalMove.fr)
                    //return temp.sec;
                    //cout<<"kala\n";
                return finalMove.sec;
            }
        finalMove=temp;
        maxdepth++;
    }
    return finalMove.sec;
}
int main()
{
   //Input
   int opponent,alpha=-1000000000,beta=1000000000;
  // start=clock();
   scanf("%d",&me);
   for(int i=0;i<boardSize;i++)
      for(int j=0;j<boardSize;j++)
      scanf("%d",&board[i][j]);
   opponent=(me==black)?white:black;
   PPI Move=iterativeDeepening(1,true,alpha,beta);
   printf("%d %d %d %d\n",Move.fr.fr,Move.fr.sec,Move.sec.fr,Move.sec.sec);
   return 0;
}
