// All These values are experimental testing will be done later .........

const int black = 0;
const int white = 1;
const int nill = -1;
const int boardSize = 12;
/*
	Win value you all know what it means ;).
*/
const int winValue = 500000;//10000000
/*
	This constant will be used to reward a piece when it has safely reached second last row
	and is in no danger in future.
*/
const int pieceAlmostWinValue = 10000;
/*
	This constant will be used when the piece is in horizontal formation with other pieces.
*/
const int pieceHorizontalConnectionValue = 20; // 15
/*
	This constant will be used when the piece is in vertical formation with other pieces.
*/
const int pieceVerticalConnectionValue = 10; // 10
/*
	Pieces in home ground are more imporant so this constant rewards such pieces appropriately.
	It is taken as an array because some home row pawn are more valuable than other.
	These values will be used when the piece is in it's home row.
*/
const int pieceHomeGroundValue[] = {200,150,150,80,80,150,150,80,80,150,150,200}; // 15 30
const int pieceSecondGroundValue[] = {100,0,0,0,0,0,0,0,0,0,0,100};
/*
	Each piece will have it's some initial value this will be determined by this constant.
*/
const int pieceValue = 130;//1500
/*
	Each piece will attack several oppostion pieces and it will be rewarded accordingly.
*/
const int pieceAttackValue = 25; // 15
/*
	Each piece will be protected by several other pieces and it will be rewarded accordingly.
*/
const int pieceProtectionValue = 20; // 25
/*
	Pieces on the edges are not as important as the pieces in middle, So this constant will
	reduce piece worth accordingly.
*/
const int pieceEdgeValue = -5; // -50
/*
	Each row will have different worth value. The rows nearer to home row and nearer to goal
	row are more valuable than other and pieces in these rows must be rewarded accordingly.
*/
const int rowWorthValue[] = {50,10,10,13,20,20,20,20,25,35,45,70};
/*
	The piece having more mobility is more worthy.
*/
const int pieceMobilityValue = 10;
/*
	It is not a good idea to leave a column with no pawn in it.
*/
const int pieceColumnHoleValue = -50;//-25
