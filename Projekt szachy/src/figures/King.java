package figures;

import game.ChessBoard;
import game.TypeOfFigure;

public class King extends Figure {
	public boolean beforeCastling = true;
	public boolean makedMove = false;
	
	public King(int i, int j, String playerX) {
		super(i, j, playerX);
	}

	@Override
	public boolean checkPosition(int x, int y) {
		boolean xOk = Math.abs( this.x - x) <= 1;
		boolean yOk = Math.abs( this.y - y) <= 1;
		
		if(beforeCastling && this.y == y && Math.abs(this.x - x) == 2){
			
			Figure fig;
			Rock rock;
			// long castling
			if( this.x - x > 0){
				
				if( !checkTheRoadBetweenPositions(x, y))
					return false;
				
				fig = ChessBoard.figuresCoordinate[0][y];
				if(fig == null || fig.getType() != TypeOfFigure.ROCK)
					return false;
				
				rock = (Rock) fig;
				
				if( !makedMove &&  !Rock.makedMove && rock.getPlayer() == this.player){
						
					
					return true;
				}
				
			}
			// short castling
			else if(this.x - x < 0){ 
				
				if( !checkTheRoadBetweenPositions(x, y))
					return false;
				
				fig = ChessBoard.figuresCoordinate[ChessBoard.WIDTH-1][y];
				if( fig == null || fig.getType() != TypeOfFigure.ROCK)
					return false;
				
				rock = (Rock) fig;
				
				if( !makedMove &&  !Rock.makedMove && rock.getPlayer() == this.player){
						
					
					return true;
					
				}
				
				
			}
			
			
			
			
			
			
		}
		return xOk && yOk;
	}

	@Override
	public TypeOfFigure getType() {
		return TypeOfFigure.KING;
	}

}
