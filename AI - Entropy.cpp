#include <bits/stdc++.h>
#define ll long long
#define endl "\n"
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)
using namespace std;

int random(){
	srand(time(NULL));
	srand(time(NULL)+rand());
	return rand();
}

string inpstr;
int score=0;
int inpint,turncount=1;
int board[7][7]={};
int colorleft[8]={7,7,7,7,7,7,7,7};
int maxup,maxdown,maxleft,maxright;
void debugchangeboard(){
	board[3][1]=1;
	board[3][6]=1;
}
void settheboard(int i, int j, int x){
	board[i][j]=x;
}	
void movetheboard(int i,int j, int k, int l){
	swap(board[i][j],board[k][l]);
}
void debugboard(){
	cout<<endl;
	for(int i =0;i<7;i++){
		for (int j=0;j<7;j++){
			cout<<board[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}
void rangeoforder(int x, int y){
	maxleft=0;
	maxright=6;
	maxup=0;
	maxdown=6;
	for (int i=x-1;i>=0;i--){
		if (board[i][y]!=0){
			maxleft=i+1;
			break;
		}
	}
	for (int i=x+1;i<7;i++){
		if (board[i][y]!=0){
			maxright=i-1;
			break;
		}
	}
	for (int i=y-1;i>=0;i--){
		if (board[x][i]!=0){
			maxup=i+1;
			break;
		}
	}
	for (int i=y+1;i<7;i++){
		if (board[x][i]!=0){
			maxdown=i-1;
			break;
		}
	}
} 

int scorereturn(int x, int y){
	//cout<<x<<" "<<y<<endl;
	//debugboard();
	int sreturn =0;
	for (int i =0;i<7;i++){
		if (board[x][i]==board[x][y]&& i!=y && board[x][i]!=0){
			bool up=true;
			int op=i,en=y;
			if (op>en) swap(op,en);
			op++; en--;
			while (op<en){
				if (board[x][op]!=board[x][en]||(board[x][op]==0 || board[x][en]==0)){
					up=false;
					break;
				}
				op++;
				en--;
			}
			if (up)
			sreturn+=abs(i-y)+1;
			
		}
	}
	for (int i =0;i<7;i++){
		if (board[i][y]==board[x][y]&& i!=x && board[i][y]!=0){
			bool up=true;
			int op=i,en=x;
			if (op>en) swap(op,en);
			op++; en--;
			while (op<en){
				if (board[op][y]!=board[en][y]||(board[op][y]==0 || board[en][y]==0)){
					up=false;
					break;
				}
				op++;
				en--;
			}
			if (up)
			sreturn+=abs(i-y)+1;
			
		}
	}
	//cout<<sreturn<<endl;
	return sreturn;
}

int minimax(int depth, bool ismax)
{	
	//cout<<"notok\n";
    if(depth == 0)
    {	
    	//debugboard();
     	//cout<<score<<"\n";
        return score;

    }
    if(ismax)
    {   
    	//cout<<"ok\n";
        int oldscore = score;
        int best = INT_MIN;
        for(int i = 0 ; i < 7 ; i++)
        {
            for(int j = 0; j < 7 ;j++)
            {
                if(board[i][j] != 0)
                {   
                	//debugboard();
                	int minuscore=scorereturn(i,j);
                	//cout<<i<<" "<<j<<" "<<minuscore<<endl;
                    rangeoforder(i,j);
                    for (int st =maxleft;st<=maxright;st++){
                    	score-=minuscore;
                    	//debugboard();
                    	//cout<<score<<endl;
                    	movetheboard(i,st,i,j);
                    	score+=scorereturn(i,st);
                    	//cout<<minuscore<<endl;
                    	//cout<<score<<endl;
                    	//debugboard();
                    	best=max(best,minimax(depth-1,false));
                    	//cout<<score<<"\n";
                    	score=oldscore;
                    	movetheboard(i,st,i,j);
                    	//debugboard();
					}
					for (int st=maxup;st<=maxdown;st++ ){
						score-=minuscore;
						movetheboard(i,j,st,j);
						score+=scorereturn(st,j);
						best=max(best,minimax(depth-1,false));
						//cout<<score<<"\n";
						score=oldscore;
						movetheboard(i,j,st,j);
						//debugboard();
					}
                }
            }
        }
        return best;
    }
    else
    {
        int oldscore = score;
        int best = INT_MAX;
        //cout<<"okn't\n";
        for(int i = 0 ; i < 7 ; i++)
        {
            for(int j = 0 ; j < 7 ; j++)
            {
                if(board[i][j] == 0)
                {
                    for(int k = 1 ;k <= 7 ; k++)
                    {
                        board[i][j] = k;
                        //debugboard();
                        score +=scorereturn(i,j);
                        best = min(best,minimax(depth - 1, true));
                        //cout<<score<<"\n";
                        score =oldscore;
                        board[i][j] = 0;
                    }
            	}
            }
        }
        return best;
    }
}

void bestmovefororder(string ip){
	int best=INT_MAX, choice,bestx,besty,stx,sty;
	//debugboard();
	for (int i=0;i<7;i++){
		for (int j =0;j<7;j++){
			if (board[i][j]!=0){
				stx=i;
				sty=j;
				bestx=i;
				besty=j;
				int minuscore=scorereturn(i,j);
				int oldscore=score;
                rangeoforder(i,j);
                for (int st =maxleft;st<=maxright;st++){
                    score-=minuscore;
                    movetheboard(i,st,i,j);
                    score+=scorereturn(i,st);
                   	choice=minimax(1,false);
                   	if (best<choice){
                   		choice=best;
                   		stx=i; sty=j;
                   		bestx=i; besty=st;
					}else if (best==choice&&random()%2==0){
						choice=best;
                   		stx=i; sty=j;
                   		bestx=i; besty=st;
					}
                 	score=oldscore;
                   	movetheboard(i,st,i,j);
                   	//cout<<stx<<" "<<sty<<" "<<bestx<<" "<<besty<<endl;
				}
				for (int st=maxup;st<=maxdown;st++ ){
					score-=minuscore;
					movetheboard(i,j,st,j);
					score+=scorereturn(st,j);
					choice=minimax(1,false);
					if (best<choice){
						choice=best;
						stx=i;sty=j;
						bestx=st;besty=j;
					}
					score=oldscore;
					movetheboard(i,j,st,j);
				}
				//cout<<stx<<" "<<sty<<" "<<bestx<<" "<<besty<<endl;
			}
		}
	}
	//cout<<stx<<" "<<sty<<" "<<bestx<<" "<<besty<<endl;
	movetheboard(stx,sty,bestx,besty);
	score-=scorereturn(stx,sty);
	score+=scorereturn(bestx,besty);
	cout<<char('A'+stx)<<char('a'+sty)<<char('A'+bestx)<<char('a'+besty)<<endl;
	cout.flush();
	return;
}
void bestmoveforchaos(int color){
	int bestx,besty,best=INT_MAX;
	int oldscore=score;
	//debugboard();
	for (int i =0;i<7;i++){
		for (int j =0;j<7;j++){
			if (board[i][j]==0){ 
				//cout<<"?\n";
				board[i][j]=color;
				int choice=minimax(2,true);
				//cout<<"x,y: "<<i<<" "<<j<<" score: "<<choice<<endl;
				score+=scorereturn(i,j);
				if (best>choice){
					bestx=i;
					besty=j;
					best=choice;
				}else if (best==choice){
					if (random()%2==0){
						bestx=i;
						besty=j;
					}
				}
				board[i][j]=0;
				score=oldscore;
			}
		}
	}
	score+=scorereturn(bestx,besty);
	board[bestx][besty]=color;
	cout<<char(bestx+'A')<<char(besty+'a')<<endl;
	cout.flush();
	return;
	
}

int main(){
	fastio;
	cin>>inpstr;
	if (inpstr=="Start"){
		cin>>inpint;
		board[3][3]=inpint;
		turncount=2;
		cout<<"Dd\n";
		cout.flush();
		while(turncount<=98){
			if (turncount%2==0){
				cin>>inpstr;
				movetheboard(int(inpstr[0]-'A'),int(inpstr[1]-'a'),int(inpstr[2]-'A'),int(inpstr[3]-'a'));
			}else{
				cin>>inpint;
				//debugboard();
				bestmoveforchaos(inpint);
				cout.flush();
			}
			turncount++;
			//debugboard();
		}
		cin>>inpstr;
	}else{
		turncount=2;
		settheboard(int(inpstr[1]-'A'),int(inpstr[2]-'a'),int(inpstr[0]-'0'));
		while(turncount<=98){
			if(turncount%2==1){
				cin>>inpstr;
				settheboard(int(inpstr[1]-'A'),int(inpstr[2]-'a'),int(inpstr[0]-'0'));				
			}
			else{
				bestmovefororder(inpstr);
			}
			turncount++;
			//debugboard();
		}
		cin>>inpstr;
	}
	
}








