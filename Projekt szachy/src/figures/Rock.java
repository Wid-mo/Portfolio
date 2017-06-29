package figures;

import game.TypeOfFigure;

public class Rock extends Figure {
	public static boolean makedMove = false;
	
	public Rock(int i, int j, String playerX) {
		super(i, j, playerX);
	}

	@Override
	public boolean checkPosition(int x, int y) {
		return (this.x == x) || (this.y == y);
	}

	@Override
	public TypeOfFigure getType() {
		return TypeOfFigure.ROCK;
	}

}
