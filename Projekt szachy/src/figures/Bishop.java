package figures;

import game.TypeOfFigure;

public class Bishop extends Figure {

	public Bishop(int i, int j, String playerX) {
		super(i, j, playerX);
	}

	@Override
	public boolean checkPosition(int x, int y) {
		
		int xx = Math.abs( this.x - x);
		int yy = Math.abs( this.y - y);
		
		return xx == yy;
	}

	@Override
	public TypeOfFigure getType() {
		return TypeOfFigure.BISHOP;
		
	}
	
}
