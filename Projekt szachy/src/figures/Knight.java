package figures;

import game.TypeOfFigure;

public class Knight extends Figure {

	public Knight(int i, int j, String playerX) {
		super(i, j, playerX);
	}

	@Override
	public boolean checkPosition(int x, int y) {
		int sqrDistanceX = (this.x-x) * (this.x-x);
		int sqrDistanceY = (this.y-y) * (this.y-y);
		return sqrDistanceX + sqrDistanceY == 5;
	}

	@Override
	public TypeOfFigure getType() {
		return TypeOfFigure.KNIGHT;
	}


}
