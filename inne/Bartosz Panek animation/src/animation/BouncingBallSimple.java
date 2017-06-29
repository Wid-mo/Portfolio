package animation;

import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

import javax.imageio.ImageIO;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class BouncingBallSimple extends JPanel {

	private static final long serialVersionUID = 5617994995530990532L;
	// it must be change for resolution on your computer
	private static final int BOX_WIDTH = 1300;
	private static final int BOX_HEIGHT = 700;
	private static final int UPDATE_RATE = 30; // Number of refresh per second

	private BufferedImage playground;

	private ArrayList<Ball> balls;
	private static final int NUMBER_OF_BALLS = 30;
	
	public static final double GRAVITY = 0.5;
	
	/** Constructor to create the UI components and init game objects. */
	public BouncingBallSimple() {
		this.setPreferredSize(new Dimension(BOX_WIDTH, BOX_HEIGHT));

		balls = new ArrayList<Ball>();
		for (int i = 0; i < NUMBER_OF_BALLS; i++)
			balls.add(new Ball());

		// read images
		BufferedImage image = null;
		try {
			image = ImageIO.read(new File("Ball.png"));
			playground = ImageIO.read(new File("Boisko-nr-3.jpg"));
		} catch (IOException e) {
		}
		Ball.image = image;
		
		// Start the ball bouncing (in its own thread)
		Thread gameThread = new Thread() {
			public void run() {
				
				int counter = 0;
				while (true) {
					// update all balls
					for (Ball ball : balls)
						ball.update();

					// add all balls additional energy
					if (counter++ % 100 == 0) {
						for (Ball ball : balls) {
							ball.setSpeedY(Math.random() * 30 - 25);
							ball.setSpeedX(Math.random() * 30 - 15);
						}
					}
					// Refresh the display
					repaint();
					// Delay for timing control and give other threads a chance
					try {
						Thread.sleep(1000 / UPDATE_RATE); // milliseconds
					} catch (InterruptedException ex) {
					}
				}
			}

		};
		gameThread.start(); // Callback run()
	}

	/** Custom rendering codes for drawing the JPanel */
	@Override
	public void paintComponent(Graphics g) {
		super.paintComponent(g); // Paint background
		Graphics2D g2D = (Graphics2D) g;

		g.drawImage(playground, 0, 0, BOX_WIDTH, BOX_HEIGHT, null);
		for (Ball ball : balls) {
			ball.draw(g, g2D);
		}

	}


	/** main program (entry point) */
	public static void main(String[] args) {
		// Run GUI in the Event Dispatcher Thread (EDT) instead of main thread.
		javax.swing.SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				// Set up main window (using Swing's JFrame)
				JFrame frame = new JFrame("A Bouncing Ball");
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				frame.setContentPane(new BouncingBallSimple());
				frame.pack();
				frame.setVisible(true);
			}
		});
	}
}