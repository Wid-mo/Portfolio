package figures;

import java.math.BigInteger;

import game.ChessBoard;
import game.TypeOfFigure;

public abstract class Figure {
	protected int x;
	protected int y;
	protected String player;
	
	
	public Figure(int i, int j, String playerX) {
		x = i;
		y = j;
		player = playerX;
	}
	
	

	public int getX() {
		return x;
	}



	public int getY() {
		return y;
	}



	public String getPlayer() {
		return player;
	}



	public abstract boolean checkPosition(int x, int y);

	public abstract TypeOfFigure getType();

	public boolean checkTheRoadBetweenPositions( int x, int y){

		int rX = -(this.x - x);
		int rY = -(this.y - y);
		int numberField= GCD(rX, rY) - 1;
		int dX = rX / (numberField + 1 );
		int dY = rY / (numberField + 1 );
		
		int orgX = this.x + dX;
		int orgY = this.y + dY;
		
		for (int i = 0; i < numberField; i++) {
			if( ChessBoard.figuresCoordinate[orgX][orgY] != null)
				return false;
			
			
			orgX += dX;
			orgY += dY;
			
		}
		
		return true;
		
		
	}

	private static int GCD(int a, int b){
		BigInteger b1 = BigInteger.valueOf(a);
		BigInteger b2 = BigInteger.valueOf(b);
		BigInteger gcd = b1.gcd(b2);
		
		return gcd.intValue();
	}
	
}
