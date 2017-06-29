package figures;

import game.ChessBoard;
import game.Main;
import game.TypeOfFigure;

public class Pawn extends Figure {

	public Pawn(int i, int j, String playerX) {
		super(i, j, playerX);
	}

	@Override
	public boolean checkPosition(int x, int y) {
		if( this.y == 1 || this.y == ChessBoard.HEIGHT - 2)
			if( Math.abs(this.y - y) == 2 && this.x == x &&
				 ChessBoard.figuresCoordinate[x][y] == null)
			{
				return true;
			}
				
		if( this.player == "white"){
			if( y - this.y == 1 && x == this.x)
				if( ChessBoard.figuresCoordinate[x][y] == null)
					return true;
			
			if( y - this.y == 1 && Math.abs( x - this.x) == 1)
				if( ChessBoard.figuresCoordinate[x][y] != null &&
					ChessBoard.figuresCoordinate[x][y].player == "black")
				{
					return true;
				}
		}

		if( this.player == "black"){
			if( this.y - y == 1 && x == this.x)
				if( ChessBoard.figuresCoordinate[x][y] == null)
					return true;
			
			if( this.y - y == 1 && Math.abs( x - this.x) == 1)
				if( ChessBoard.figuresCoordinate[x][y] != null &&
					ChessBoard.figuresCoordinate[x][y].player == "white")
				{
					return true;
				}
		}
		
		if(Math.abs(Main.lastMove1Y - Main.lastMove2Y) == 2){
			Figure fig = ChessBoard.figuresCoordinate[Main.lastMove2X][Main.lastMove2Y];
			TypeOfFigure typ = fig.getType();
			
			if( typ == TypeOfFigure.PAWN){
				if( this.player == "black"){
					if( this.y == 3 && x == Main.lastMove2X)
						return true;
				}
				if( this.player == "white"){
					if( this.y == 4 && x == Main.lastMove2X)
						return true;
				}
				
			}
			
		}
		
		return false;
	}

	@Override
	public TypeOfFigure getType() {
		return TypeOfFigure.PAWN;
	}

}
