package game;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.io.IOException;

import javax.imageio.ImageIO;

import figures.Bishop;
import figures.Figure;
import figures.King;
import figures.Knight;
import figures.Pawn;
import figures.Queen;
import figures.Rock;

public class ChessBoard {
	public final static int WIDTH = 8;
	public final static int HEIGHT = 8;
	public final static int WIDTH_FIELD = 60;
	public final static int HEIGHT_FIELD = 60;
	
	public static Figure[][] figuresCoordinate;
	
	private BufferedImage image;
	
	private BufferedImage wPawn;
	private BufferedImage wRock;
	private BufferedImage wKnight;
	private BufferedImage wBishop;
	private BufferedImage wQueen;
	private BufferedImage wKing;
	
	private BufferedImage bPawn;
	private BufferedImage bRock;
	private BufferedImage bKnight;
	private BufferedImage bBishop;
	private BufferedImage bQueen;
	private BufferedImage bKing;
	
	public ChessBoard() {
		figuresCoordinate = new Figure[8][8];
		
		
		try {
			image = ImageIO.read(getClass().getResourceAsStream("/Chess_Pieces_Sprite.svg.png") );
		} catch (IOException e) {
			e.printStackTrace();
		}
		final int HORIZONTAL_NUMBER_OF_ELEMENTS = 6;
		final int VERTICAL_NUMBER_OF_ELEMENTS = 2;
		
		final int BOX_WIDTH = image.getWidth() / HORIZONTAL_NUMBER_OF_ELEMENTS;
		final int BOX_HEIGHT = image.getHeight() / VERTICAL_NUMBER_OF_ELEMENTS;
		
		int xCoordinate = 0;
		wKing = image.getSubimage(xCoordinate, 0, BOX_WIDTH, BOX_HEIGHT);
		bKing = image.getSubimage(xCoordinate, BOX_HEIGHT , BOX_WIDTH, BOX_HEIGHT);
		
		xCoordinate += BOX_WIDTH;
		wQueen = image.getSubimage(xCoordinate, 0, BOX_WIDTH, BOX_HEIGHT);
		bQueen = image.getSubimage(xCoordinate, BOX_HEIGHT, BOX_WIDTH , BOX_HEIGHT);
		
		xCoordinate += BOX_WIDTH;
		wBishop = image.getSubimage(xCoordinate, 0, BOX_WIDTH, BOX_HEIGHT);
		bBishop = image.getSubimage(xCoordinate, BOX_HEIGHT , BOX_WIDTH, BOX_HEIGHT);
		
		xCoordinate += BOX_WIDTH;
		wKnight = image.getSubimage(xCoordinate, 0, BOX_WIDTH, BOX_HEIGHT);
		bKnight = image.getSubimage(xCoordinate, BOX_HEIGHT, BOX_WIDTH , BOX_HEIGHT);
		
		xCoordinate += BOX_WIDTH;
		wRock = image.getSubimage(xCoordinate, 0, BOX_WIDTH, BOX_HEIGHT);
		bRock = image.getSubimage(xCoordinate, BOX_HEIGHT , BOX_WIDTH, BOX_HEIGHT);
		
		xCoordinate += BOX_WIDTH;
		wPawn = image.getSubimage(xCoordinate, 0, BOX_WIDTH, BOX_HEIGHT);
		bPawn = image.getSubimage(xCoordinate, BOX_HEIGHT, BOX_WIDTH , BOX_HEIGHT);
		
	}
	
	public void initializeFigures(){
		
		// Pawns
		for(int i=0; i< WIDTH; i++)
			figuresCoordinate[i][1] = new Pawn(i, 1, "white");
		
		for(int i=0; i< WIDTH; i++)
			figuresCoordinate[i][HEIGHT - 2] = new Pawn(i, HEIGHT - 2, "black");
		
		// white piece
		figuresCoordinate[0][0] = new Rock(0,0,"white");
		figuresCoordinate[1][0] = new Knight(1,0,"white");
		figuresCoordinate[2][0] = new Bishop(2,0,"white");
		figuresCoordinate[3][0] = new Queen(3,0,"white");
		figuresCoordinate[4][0] = new King(4,0,"white");
		figuresCoordinate[5][0] = new Bishop(5,0,"white");
		figuresCoordinate[6][0] = new Knight(6,0,"white");
		figuresCoordinate[7][0] = new Rock(7,0,"white");
		
		// black piece
		figuresCoordinate[0][HEIGHT - 1] = new Rock(0,HEIGHT - 1,"black");
		figuresCoordinate[1][HEIGHT - 1] = new Knight(1,HEIGHT - 1,"black");
		figuresCoordinate[2][HEIGHT - 1] = new Bishop(2,HEIGHT - 1,"black");
		figuresCoordinate[3][HEIGHT - 1] = new Queen(3,HEIGHT - 1,"black");
		figuresCoordinate[4][HEIGHT - 1] = new King(4,HEIGHT - 1,"black");
		figuresCoordinate[5][HEIGHT - 1] = new Bishop(5,HEIGHT - 1,"black");
		figuresCoordinate[6][HEIGHT - 1] = new Knight(6,HEIGHT - 1,"black");
		figuresCoordinate[7][HEIGHT - 1] = new Rock(7,HEIGHT - 1,"black");
		
		// clear middle field
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 2; j < HEIGHT - 2; j++) {
				figuresCoordinate[i][j] = null;
			}
		}
	}
	
	public void drawBoard(Graphics g) {
		final int BLACK = 1;
		
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				if( (i + j) % 2 == BLACK )
					g.setColor(Color.GRAY);
				else
					g.setColor(Color.WHITE);
				
				g.fillRect(i * WIDTH_FIELD, j * HEIGHT_FIELD, WIDTH_FIELD, HEIGHT_FIELD);
			}
		}
	}
	
	public void drawFigures(Graphics g) {
		final int OFFSET_X = 10;
		final int OFFSET_Y = 10;
		
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				int y = HEIGHT - 1 - j;
				int x = i;
				if( figuresCoordinate[i][j] != null){
					TypeOfFigure figure = figuresCoordinate[i][j].getType();
					String player = figuresCoordinate[i][j].getPlayer();
					
					switch( figure){
						case PAWN:
							if(player == "white")
								g.drawImage(wPawn, x * WIDTH_FIELD + OFFSET_X, y * HEIGHT_FIELD + OFFSET_Y, null);
							else
								g.drawImage(bPawn, x * WIDTH_FIELD + OFFSET_X, y * HEIGHT_FIELD + OFFSET_Y, null);
						break;	
						case BISHOP:
							if(player == "white")
								g.drawImage(wBishop, x * WIDTH_FIELD + OFFSET_X, y * HEIGHT_FIELD + OFFSET_Y, null);
							else
								g.drawImage(bBishop, x * WIDTH_FIELD + OFFSET_X, y * HEIGHT_FIELD + OFFSET_Y, null);
						break;
						case KNIGHT:
							if(player == "white")
								g.drawImage(wKnight, x * WIDTH_FIELD + OFFSET_X, y * HEIGHT_FIELD + OFFSET_Y, null);
							else
								g.drawImage(bKnight, x * WIDTH_FIELD + OFFSET_X, y * HEIGHT_FIELD + OFFSET_Y, null);
							break;
						case KING:
							if(player == "white")
								g.drawImage(wKing, x * WIDTH_FIELD + OFFSET_X, y * HEIGHT_FIELD + OFFSET_Y, null);
							else
								g.drawImage(bKing, x * WIDTH_FIELD + OFFSET_X, y * HEIGHT_FIELD + OFFSET_Y, null);
							break;
						case QUEEN:
							if(player == "white")
								g.drawImage(wQueen, x * WIDTH_FIELD + OFFSET_X, y * HEIGHT_FIELD + OFFSET_Y, null);
							else
								g.drawImage(bQueen, x * WIDTH_FIELD + OFFSET_X, y * HEIGHT_FIELD + OFFSET_Y, null);
							break;
						case ROCK:
							if(player == "white")
								g.drawImage(wRock, x * WIDTH_FIELD + OFFSET_X, y * HEIGHT_FIELD + OFFSET_Y, null);
							else
								g.drawImage(bRock, x * WIDTH_FIELD + OFFSET_X, y * HEIGHT_FIELD + OFFSET_Y, null);
							break;
						default:
							break;	
					}
					
				}
			}
		}
	}
}
