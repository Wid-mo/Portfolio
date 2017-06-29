package game;

import java.awt.Color;
import java.awt.Cursor;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.util.Enumeration;

import javax.swing.AbstractButton;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.SwingUtilities;

import figures.Bishop;
import figures.Figure;
import figures.King;
import figures.Knight;
import figures.Pawn;
import figures.Queen;
import figures.Rock;

public class Main extends JPanel implements MouseListener, MouseMotionListener, ActionListener {

	private static final long serialVersionUID = 1L;
	private static final int WINDOW_WIDTH = 800;
	private static final int WINDOW_HEIGHT = 600;

	private boolean whiteMove = true;
	private int selectedX = -1;
	private int selectedY = -1;
	
	private int checkedKingX = -1;
	private int checkedKingY = -1;

	public int lastMove1X = -1;
	public static int lastMove1Y = -1;
	public static int lastMove2X = -1;
	public static int lastMove2Y = -1;

	private boolean clicked = false;
	private boolean beforeSelected = false;
	private boolean hideFigures = false;
	private boolean gameStopped = false;
	
	private int tempolaryX = -1;
	private int tempolaryY = -1;
	private String tempolaryPlayer = null;
	
	private JButton bNewGame;
	private JCheckBox cBlindChess;
	private ButtonGroup bG;
	private JRadioButton RBQueen;
	private JRadioButton RBRock;
	private JRadioButton RBBishop;
	private JRadioButton RBKnight;
	private JButton bAccept;
	
	
	private ChessBoard cB;

	public Main() {
		this.setPreferredSize(new Dimension(WINDOW_WIDTH, WINDOW_HEIGHT));
		setLayout( null);
		
		cBlindChess = new JCheckBox("Blind chess",false);
		cBlindChess.setBounds(ChessBoard.WIDTH *ChessBoard.WIDTH_FIELD, 10, 100, 15);
		add(cBlindChess);
		
		bNewGame = new JButton("New Game");
		bNewGame.setBounds(ChessBoard.WIDTH *ChessBoard.WIDTH_FIELD, 30, 100, 15);
		add(bNewGame);
		
		// Promotion Pawn
		bG = new ButtonGroup();
		RBQueen = new JRadioButton("Queen",true);
		RBQueen.setBounds(ChessBoard.WIDTH *ChessBoard.WIDTH_FIELD, 80, 100, 15);
		bG.add(RBQueen);
		
		RBRock = new JRadioButton("Rock");
		RBRock.setBounds(ChessBoard.WIDTH *ChessBoard.WIDTH_FIELD, 100, 100, 15);
		bG.add(RBRock);
		
		RBBishop = new JRadioButton("Bishop");
		RBBishop.setBounds(ChessBoard.WIDTH *ChessBoard.WIDTH_FIELD, 120, 100, 15);
		bG.add(RBBishop);
		
		RBKnight = new JRadioButton("Knight");
		RBKnight.setBounds(ChessBoard.WIDTH *ChessBoard.WIDTH_FIELD, 140, 100, 15);
		bG.add(RBKnight);
		
		add(RBQueen);
		add(RBRock);
		add(RBBishop);
		add(RBKnight);
		RBQueen.setVisible(false);
		RBRock.setVisible(false);
		RBBishop.setVisible(false);
		RBKnight.setVisible(false);
		
		bAccept = new JButton("Accept");
		bAccept.setBounds(ChessBoard.WIDTH *ChessBoard.WIDTH_FIELD+100, 100, 100, 15);
		add(bAccept);
		bAccept.setVisible(false);
		
		cBlindChess.addActionListener(this);
		bAccept.addActionListener(this);
		bNewGame.addActionListener(this);
		addMouseListener(this);
		addMouseMotionListener(this);
		
		cB = new ChessBoard();
		cB.initializeFigures();

		Thread gameThread = new Thread() {
			public void run() {
				while (true) {

				}
			}

		};
		gameThread.start(); // Callback run()
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		Object source = e.getSource();
		
		if(source == cBlindChess){
			hideFigures = !hideFigures;
			repaint();
		}
		else if(source == bNewGame){
			cB.initializeFigures();
			whiteMove = true;
			
			lastMove1X = -1;
			lastMove1Y = -1;
			lastMove2X = -1;
			lastMove2Y = -1;
			beforeSelected = false;
			selectedX = -1;
			selectedY = -1;
			checkedKingX = -1;
			checkedKingY = -1;
			
			
			King king = (King)ChessBoard.figuresCoordinate[4][0];
			king.makedMove = false;
			king.beforeCastling = true;
			king = (King)ChessBoard.figuresCoordinate[4][ChessBoard.HEIGHT - 1];
			king.makedMove = false;
			king.beforeCastling = true;
			
			repaint();
		}
		else if(source == bAccept){
			RBQueen.setVisible(false);
			RBRock.setVisible(false);
			RBBishop.setVisible(false);
			RBKnight.setVisible(false);
			bAccept.setVisible(false);
			
			gameStopped = false;
			
			String stringFig = "Queen";
			for(Enumeration<AbstractButton> buttons = bG.getElements(); buttons.hasMoreElements(); ){
				AbstractButton button = buttons.nextElement();
				
				if(button.isSelected()){
					stringFig = button.getText();
					break;
				}
			}
			
			switch(stringFig){
				case "Queen":
					ChessBoard.figuresCoordinate[tempolaryX][tempolaryY] = new Queen(tempolaryX,tempolaryY,tempolaryPlayer);
					break;	
				case "Rock":
					ChessBoard.figuresCoordinate[tempolaryX][tempolaryY] = new Rock(tempolaryX,tempolaryY,tempolaryPlayer);
					break;	
				case "Bishop":
					ChessBoard.figuresCoordinate[tempolaryX][tempolaryY] = new Bishop(tempolaryX,tempolaryY,tempolaryPlayer);
					break;	
				case "Knight":
					ChessBoard.figuresCoordinate[tempolaryX][tempolaryY] = new Knight(tempolaryX,tempolaryY,tempolaryPlayer);
					break;	
			
			}
			
			if( !moveMakeCheck(tempolaryPlayer)){
				checkedKingX = -1;
				checkedKingY = -1;
			}
			 
			tempolaryX= -1;
			tempolaryY= -1;
			tempolaryPlayer= null;
			clicked = false;
			RBQueen.setSelected(true);
			
			repaint();
		}
		
	}
	
	
	@Override
	public void paintComponent(Graphics g) {
		super.paintComponent(g); // Paint background

		cB.drawBoard(g);

		if (selectedX != -1) 
			drawSelect(g);

		if (lastMove1X != -1) 
			drawLastMove(g);
		
		if( checkedKingX != -1)
			drawAttackedFieldInKing(g);

		if (!hideFigures)
			cB.drawFigures(g);
	}

	
	private void drawAttackedFieldInKing(Graphics g) {
		final int xPosition = checkedKingX * ChessBoard.WIDTH_FIELD;
		final int y = ChessBoard.HEIGHT - 1 - checkedKingY;
		final int yPosition = y * ChessBoard.HEIGHT_FIELD;

		g.setColor(Color.RED);
		g.fillRect(xPosition, yPosition, ChessBoard.WIDTH_FIELD, ChessBoard.HEIGHT_FIELD);
	}

	private void drawLastMove(Graphics g) {
		final int xPosition1 = lastMove1X * ChessBoard.WIDTH_FIELD;
		final int y1 = ChessBoard.HEIGHT - 1 - lastMove1Y;
		final int yPosition1 = y1 * ChessBoard.HEIGHT_FIELD;

		final int xPosition2 = lastMove2X * ChessBoard.WIDTH_FIELD;
		final int y2 = ChessBoard.HEIGHT - 1 - lastMove2Y;
		final int yPosition2 = y2 * ChessBoard.HEIGHT_FIELD;

		g.setColor(Color.ORANGE);
		g.fillRect(xPosition1, yPosition1, ChessBoard.WIDTH_FIELD, ChessBoard.HEIGHT_FIELD);
		g.fillRect(xPosition2, yPosition2, ChessBoard.WIDTH_FIELD, ChessBoard.HEIGHT_FIELD);
	}

	private void drawSelect(Graphics g) {
		final int xPosition = selectedX * ChessBoard.WIDTH_FIELD;
		final int y = ChessBoard.HEIGHT - 1 - selectedY;
		final int yPosition = y * ChessBoard.HEIGHT_FIELD;

		g.setColor(Color.BLUE);
		g.fillRect(xPosition, yPosition, ChessBoard.WIDTH_FIELD, ChessBoard.HEIGHT_FIELD);
	}

	/** main program (entry point) */
	public static void main(String[] args) {

		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				JFrame frame = new JFrame("Chess");
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				frame.setContentPane(new Main());
				
				frame.pack();
				frame.setVisible(true);
			}
		});
	}

	@Override
	public void mousePressed(MouseEvent e) {
		if( gameStopped)
			return;
		
		if (!clicked) {

			int x = e.getX() / ChessBoard.WIDTH_FIELD;
			int y = e.getY() / ChessBoard.HEIGHT_FIELD;
			y = ChessBoard.HEIGHT - 1 - y;

			if (illegalCoordinate(x, y))
				return;

			Figure fSrc = ChessBoard.figuresCoordinate[x][y];
			String player = getPlayerOfFigure(fSrc);

			if( selectedX == -1){
				
				if (isOwnFigureClicked(player)) {

					selectedX = x;
					selectedY = y;
				}
			}
			else
				checkMoveTakeit(x, y);
				

			clicked = true;
			repaint();
		}
		
	}

	private String getPlayerOfFigure(Figure fSrc) {
		String player = null;
		if (fSrc != null)
			player = fSrc.getPlayer();

		return player;
	}

	private boolean illegalCoordinate(int x, int y) {
		return x >= ChessBoard.WIDTH || x < 0 || y >= ChessBoard.HEIGHT || y < 0;
	}

	private boolean isOwnFigureClicked(String player) {
		return (player == "white" && whiteMove) || (player == "black" && !whiteMove);
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		if( gameStopped)
			return;
		
		int x = e.getX() / ChessBoard.WIDTH_FIELD;
		int y = e.getY() / ChessBoard.HEIGHT_FIELD;
		y = ChessBoard.HEIGHT - 1 - y;

		if (illegalCoordinate(x, y))
			return;

		
		if (x == selectedX && y == selectedY) {
			
			if(beforeSelected)
				deselectFigure();
			
		} 
		else if( selectedX != -1)
			checkMoveTakeit(x, y);
		

		clicked = false;
		this.setCursor(new Cursor(Cursor.HAND_CURSOR));
		repaint();
	}

	private void checkMoveTakeit(int x, int y) {
		Figure fSource = ChessBoard.figuresCoordinate[selectedX][selectedY];

		Figure fDest = ChessBoard.figuresCoordinate[x][y];
		String finPlayer = getPlayerOfFigure(fDest);
		
		if (ifNoClickedOwnsFigure(finPlayer)) {

			// Do you can make move
			if (fSource.checkPosition(x, y) && fSource.checkTheRoadBetweenPositions( x, y) 
					&& makeMoveWhichKingDontAttacked(fSource, x, y)) {

				// delete figure
				ChessBoard.figuresCoordinate[selectedX][selectedY] = null;
				
				String player = fSource.getPlayer();
				
				// move rock after castling
				if(fSource.getType() == TypeOfFigure.KING)
					if( KingMakeCastling(fSource, x) )
						moveRook(fSource, player, x);
					
				boolean lineTransformation = false;
				if(fSource.getType() == TypeOfFigure.PAWN){
					
					// Er Passant deleted pawn
					if( Math.abs(lastMove1Y - lastMove2Y) == 2){
						Figure fig = ChessBoard.figuresCoordinate[lastMove2X][lastMove2Y];
						
						if( fig.getType() == TypeOfFigure.PAWN){
							if( player == "black"){
								if( selectedY == 3 && x == lastMove2X)
									ChessBoard.figuresCoordinate[lastMove2X][lastMove2Y] = null;
							}
							if( player == "white"){
								if( selectedY == ChessBoard.HEIGHT - 4 && x == lastMove2X)
									ChessBoard.figuresCoordinate[lastMove2X][lastMove2Y] = null;
							}
							
						}
						
					}
					
					// promotion
					lineTransformation = entranceToTheLineTransformation(y, fSource);
					if( lineTransformation){
						
						gameStopped = true;
						RBQueen.setVisible(true);
						RBRock.setVisible(true);
						RBBishop.setVisible(true);
						RBKnight.setVisible(true);
						bAccept.setVisible(true);
						
						ChessBoard.figuresCoordinate[x][y] = new Queen(x,y, player);
						tempolaryX= x;
						tempolaryY= y;
						tempolaryPlayer= player;
						
					}
					else{
						
						ChessBoard.figuresCoordinate[x][y] = createNewFigure(fSource, x, y);

					}
				}
				
				// insert figure in new position
				if( !lineTransformation)
					ChessBoard.figuresCoordinate[x][y] = createNewFigure(fSource, x, y);
				
				// last move selected
				lastMove1X = selectedX;
				lastMove1Y = selectedY;
				lastMove2X = x;
				lastMove2Y = y;
				
				// if check select
				if( !moveMakeCheck(player)){
					checkedKingX = -1;
					checkedKingY = -1;
				}

				whiteMove = !whiteMove;
			} 
			
			
			deselectFigure();
		}
		else{
			if (x == selectedX && y == selectedY) {
				beforeSelected = !beforeSelected;
			}
			selectedX = x;
			selectedY = y;
			
		}
	}

	private boolean KingMakeCastling(Figure fKing, int x) {
		return Math.abs(fKing.getX() - x) == 2;
	}

	private void moveRook(Figure fKing, String player, int x) {
		if( shortCastling(fKing, x)){
			ChessBoard.figuresCoordinate[0][selectedY] = null;
			ChessBoard.figuresCoordinate[x + 1][selectedY] = new Rock(x + 1,selectedY, player);
		}
		else if( longCastling(fKing, x)){
			ChessBoard.figuresCoordinate[ChessBoard.HEIGHT-1][selectedY] = null;
			ChessBoard.figuresCoordinate[x - 1][selectedY] = new Rock(x - 1,selectedY, player);
		}
	}

	private boolean shortCastling(Figure fKing, int x) {
		return fKing.getX() - x  == 2;
	}

	private boolean longCastling(Figure fKing, int x) {
		return fKing.getX() - x == -2;
	}

	private boolean entranceToTheLineTransformation(int y, Figure fSource) {
		return fSource.getType() == TypeOfFigure.PAWN &&
				(fSource.getPlayer() == "white" && y == ChessBoard.HEIGHT - 1) ||
				(fSource.getPlayer() == "black" && y == 0);
	}

	private boolean moveMakeCheck(String player) {
		
		
		int kingPosY = 0;
		int kingPosX = 0;
		// find enemy king position
		for (int i = 0; i < ChessBoard.WIDTH; i++) {
			for (int j = 0; j < ChessBoard.HEIGHT; j++) {
				if( ChessBoard.figuresCoordinate[i][j] != null &&
						ChessBoard.figuresCoordinate[i][j].getPlayer() != player &&
						ChessBoard.figuresCoordinate[i][j].getType() == TypeOfFigure.KING ){
						
					kingPosX = i;
					kingPosY = j;
					
				}
			}
		}
		
		for (int i = 0; i < ChessBoard.WIDTH; i++) {
			for (int j = 0; j < ChessBoard.HEIGHT; j++) {
				if( ChessBoard.figuresCoordinate[i][j] != null &&
					ChessBoard.figuresCoordinate[i][j].getPlayer() == player ){
					
					Figure myFigure = ChessBoard.figuresCoordinate[i][j];
					
					if(myFigure.checkPosition(kingPosX, kingPosY)
							&& myFigure.checkTheRoadBetweenPositions( kingPosX, kingPosY)){
						
						checkedKingX = kingPosX;
						checkedKingY = kingPosY;
						
						return true;
					}
					
				}
			}
		}
		
		return false;
	}

	private boolean makeMoveWhichKingDontAttacked(Figure fSource, int x, int y) {
		
		ChessBoard.figuresCoordinate[selectedX][selectedY] = null;
		Figure temp = ChessBoard.figuresCoordinate[x][y];
		ChessBoard.figuresCoordinate[x][y] = createNewFigure(fSource, x, y);
		
		String player= fSource.getPlayer();
		
		
		int kingPosY = 0;
		int kingPosX = 0;
		// find own king position
		for (int i = 0; i < ChessBoard.WIDTH; i++) {
			for (int j = 0; j < ChessBoard.HEIGHT; j++) {
				if( ChessBoard.figuresCoordinate[i][j] != null &&
						ChessBoard.figuresCoordinate[i][j].getPlayer() == player &&
						ChessBoard.figuresCoordinate[i][j].getType() == TypeOfFigure.KING ){
						
					kingPosX = i;
					kingPosY = j;
					
				}
			}
		}
		
		for (int i = 0; i < ChessBoard.WIDTH; i++) {
			for (int j = 0; j < ChessBoard.HEIGHT; j++) {
				if( ChessBoard.figuresCoordinate[i][j] != null &&
					ChessBoard.figuresCoordinate[i][j].getPlayer() != player ){
					
					Figure opponentFigure = ChessBoard.figuresCoordinate[i][j];
					
					if(opponentFigure.checkPosition(kingPosX, kingPosY)
							&& opponentFigure.checkTheRoadBetweenPositions( kingPosX, kingPosY)){
						
						
						ChessBoard.figuresCoordinate[selectedX][selectedY] = fSource;
						ChessBoard.figuresCoordinate[x][y] = temp;
						return false;
					}
					
				}
			}
		}
		
		ChessBoard.figuresCoordinate[selectedX][selectedY] = fSource;
		ChessBoard.figuresCoordinate[x][y] = temp;
		return true;
	}

	private void deselectFigure() {
		
		selectedX = -1;
		selectedY = -1;
		beforeSelected = false;
	}

	private boolean ifNoClickedOwnsFigure(String finPlayer) {
		return (finPlayer != "white" && whiteMove) || (finPlayer != "black" && !whiteMove);
	}


	private Figure createNewFigure(Figure sdDest, int x, int y) {
		TypeOfFigure fig = sdDest.getType();

		switch (fig) {
		case BISHOP:
			return new Bishop(x, y, sdDest.getPlayer());
		case PAWN:
			return new Pawn(x, y, sdDest.getPlayer());
		case KING:
			return new King(x, y, sdDest.getPlayer());
		case QUEEN:
			return new Queen(x, y, sdDest.getPlayer());
		case KNIGHT:
			return new Knight(x, y, sdDest.getPlayer());
		case ROCK:
			return new Rock(x, y, sdDest.getPlayer());

		}

		return null;
	}
	
	
	@Override
	public void mouseClicked(MouseEvent e) {
		
	}

	@Override
	public void mouseEntered(MouseEvent e) {

	}

	@Override
	public void mouseExited(MouseEvent e) {

	}

	@Override
	public void mouseDragged(MouseEvent e) {
		if(selectedX != -1)
			setCursor(new Cursor(Cursor.MOVE_CURSOR));
		else
			setCursor(new Cursor(Cursor.HAND_CURSOR));
	}

	@Override
	public void mouseMoved(MouseEvent e) {
		final int x = e.getX();
		final int y = e.getY();
		
		final boolean xInsideBoard = x< ChessBoard.WIDTH * ChessBoard.WIDTH_FIELD  && x > 0;
		final boolean yInsideBoard = y< ChessBoard.HEIGHT* ChessBoard.HEIGHT_FIELD && y> 0;
		if( xInsideBoard && yInsideBoard){
			this.setCursor(new Cursor(Cursor.HAND_CURSOR));
		}
		else{
			this.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
		}
		
	}

}