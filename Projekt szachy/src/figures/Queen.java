package figures;

import game.TypeOfFigure;

public class Queen extends Figure {

	public Queen(int i, int j, String playerX) {
		super(i, j, playerX);
	}

	@Override
	public boolean checkPosition(int x, int y) {
		final Rock r = new Rock(this.x, this.y, null);
		final Bishop b = new Bishop(this.x, this.y, null);
		
		return r.checkPosition(x, y) || b.checkPosition(x, y);
	}

	@Override
	public TypeOfFigure getType() {
		return TypeOfFigure.QUEEN;
	}

}
