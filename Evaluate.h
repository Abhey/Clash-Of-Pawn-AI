#include "Constants.h"

int evaluate(int board[][boardSize], int playerColor, int currentColor);
int getPieceValue(int board[][boardSize], int row, int col, int currentColor);
int getOppositeColor(int color);
int getValidMoveCount(int board[][boardSize], int row, int col);

// Remember draw is impossible in this game ..........
// Complexity of evaluate function : O(boardSize * boardSize) .........

bool whiteWonGame = false;
bool blackWonGame = false;
/*bool unsafe(int row,int col,int player)
{
    if(player==white)
    {
        if((col-1>=0&&board[row+1][col-1]==nill&&board[row][col]==nill)) danger=true;
        else if((col-1)>=0&&(col+1<boardSize)&&(board[row+1][col]==nill)&&board[row][col-1]==nill&&board[row][col+1]==nill) danger=true;
        else if(col==0&&)
    }
}
int howMany(int player)
{
    int cnt=0;
    if(player==white)
    {
        for(int i=0;i<12;i++)
            if(unsafe(0,i,player)) cnt++;
    }
    return cnt;
}*/
int evaluate(int board[][boardSize], int playerColor, int currentColor){

	int boardVal = 0;

	whiteWonGame = false;
	blackWonGame = false;

	int remainingWhitePieces = 0;
	int remainingBlackPieces = 0;

	// Our Code is playing as white ........
	if(playerColor == white){

		// For white, home row will be 0 and goal row will be 11 ......
		// j reprsents column and i repsent row .......

		for(int j = 0 ; j < boardSize ; j ++){

			bool blackColumnHole = true, whiteColumnHole = true;

			for(int i = 0 ; i < boardSize ; i ++){

				if(board[i][j] == white){

					remainingWhitePieces ++;
					whiteColumnHole = false;
					boardVal += getPieceValue(board,i,j,currentColor);
					if(i == boardSize - 1) whiteWonGame = true;

				}

				else if(board[i][j] == black){

					remainingBlackPieces ++;
					blackColumnHole = false;
					boardVal -= getPieceValue(board,i,j,currentColor);
					if(i == 0) blackWonGame = true;

				}

			}

			if(whiteColumnHole) boardVal += pieceColumnHoleValue;
			if(blackColumnHole) boardVal -= pieceColumnHoleValue;

		}

		if(remainingBlackPieces == 0) whiteWonGame = true;
		if(remainingBlackPieces == 0) blackWonGame = true;

		if(whiteWonGame) boardVal += winValue;
		if(blackWonGame) boardVal -= winValue;

	}

	// Our Code is playing as black .......

	else{

		// For black home row will be 11 and goal row will be 0 .......

		for(int j = 0 ; j < boardSize ; j ++){

			bool blackColumnHole = true, whiteColumnHole = true;

			for(int i = 0 ; i < boardSize ; i ++){

				if(board[i][j] == white){

					remainingWhitePieces ++;
					whiteColumnHole = false;
					boardVal -= getPieceValue(board,i,j,currentColor);
					if(i == boardSize - 1) whiteWonGame = true;

				}

				else if(board[i][j] == black){

					remainingBlackPieces ++;
					blackColumnHole = false;
					boardVal += getPieceValue(board,i,j,currentColor);
					if(i == 0) blackWonGame = true;

				}

			}

			if(whiteColumnHole) boardVal -= pieceColumnHoleValue;
			if(blackColumnHole) boardVal += pieceColumnHoleValue;

		}

		if(remainingBlackPieces == 0) whiteWonGame = true;
		if(remainingWhitePieces == 0) blackWonGame = true;

		if(whiteWonGame) boardVal -= winValue;
		if(blackWonGame) boardVal += winValue;

	}

	return boardVal;

}

// Think about get piece value function rest all will follow up ..................

int getPieceValue(int board[][boardSize], int row, int col, int currentColor){

	int pieceVal = pieceValue;
	int pieceColor = board[row][col];

	// Adding row worth value .......


	if(pieceColor == white)
		pieceVal += rowWorthValue[row];
	else
		pieceVal += rowWorthValue[boardSize - row - 1];

	// Adding vertical connection value .......

	bool verticalConnected = false;
	if(row - 1 >= 0 && board[row][col] == board[row -1][col]) verticalConnected = true;
	if(row + 1 < boardSize && board[row][col] == board[row + 1][col]) verticalConnected = true;
	if(verticalConnected) pieceVal += pieceVerticalConnectionValue;

	// Adding horizontal connection value .......
	bool horizontalConnected = false;
	if(col - 1 >= 0 && board[row][col] == board[row][col - 1]) horizontalConnected = true;
	if(col + 1 < boardSize && board[row][col] == board[row][col + 1]) horizontalConnected = true;
	if(horizontalConnected) pieceVal += pieceHorizontalConnectionValue;

	int val = 1;
	if(pieceColor == currentColor) val = -1;

	bool dangerA = false, dangerB = false;

	// Right now considering just three moves one forward and two diagonally forward .......

	int mDir;

	if(pieceColor == white){

		if(row == 0)
			pieceVal += pieceHomeGroundValue[col];
        if(row == 1)
			pieceVal += pieceSecondGroundValue[col];
		mDir = 1;

	}

	else if(pieceColor == black){

		if(row == boardSize - 1)
			pieceVal += pieceHomeGroundValue[col];
        if(row == boardSize-2)
			pieceVal += pieceSecondGroundValue[col];
		mDir = -1;

	}

	if(row + mDir >= 0 && row + mDir < boardSize){

		if(col - 1 >= 0 && pieceColor == board[row + mDir][col - 1]) pieceVal += pieceProtectionValue;
		if(col + 1 < boardSize && pieceColor == board[row + mDir][col + 1]) pieceVal += pieceProtectionValue;
		if(col - 1 >= 0 && pieceColor == getOppositeColor(board[row + mDir][col -1])){
			pieceVal += val*pieceAttackValue;
			if(pieceColor == white && row == boardSize - 2 && val == -1) dangerA = true;
			if(pieceColor == black && row == 1 && val == -1) dangerA = true;
		}
		if(col + 1 < boardSize && pieceColor == getOppositeColor(board[row + mDir][col + 1])){
			pieceVal += val*pieceAttackValue;
			if(pieceColor == white && row == boardSize - 2 && val == -1) dangerB = true;
			if(pieceColor == black && row == 1 && val == -1) dangerB = true;
		}
		if(pieceColor == board[row + mDir][col]){
			pieceVal += pieceProtectionValue;
		}

	}

	int validMoveCount = getValidMoveCount(board,row,col);
	pieceVal += pieceMobilityValue * validMoveCount;

	if(!dangerA && !dangerB)
		pieceVal += pieceAlmostWinValue;

	if(col == 0 || col == boardSize - 1)
		pieceVal += pieceEdgeValue;

	return pieceVal;

}

int getOppositeColor(int color){

	if(color == black) return white;
	if(color == white) return black;
	if(color == nill) return nill;

}

int getValidMoveCount(int board[][boardSize], int row, int col){

	int pieceColor = board[row][col];
	int mDir = 1;

	if(pieceColor == black) mDir = -1;
	int validMove = 0;

	if(row + mDir >= 0 && row + mDir < boardSize){

		if(col - 1 >= 0 && board[row + mDir][col - 1] != pieceColor) validMove ++;
		if(col + 1 < boardSize && board[row + mDir][col + 1] != pieceColor) validMove ++;
		if(board[row + mDir][col] == nill) validMove ++;

	}

	return validMove;

}
