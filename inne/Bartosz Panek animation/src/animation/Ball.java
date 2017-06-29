package animation;

import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;

public final class Ball {
	// it must be change for resolution on your computer
	private static final int BOX_WIDTH = 1300;
	private static final int BOX_HEIGHT = 700;

	private static final double BOUNCE_REDUCE = 0.7;

	private static final int MIN_RADIUS = 25;
	private static final int MAX_RADIUS = 45;
	
	public static BufferedImage image;
	// constants
	public final double rotateSpeed;

	/** Image properties **/
	public float radius;

	// Starts value
	private float x; // center of object
	private float y; // center of object
	private double speedX;
	private double speedY;
	double angle;
	
	public Ball() {
		radius = (float) (Math.random() * (MAX_RADIUS - MIN_RADIUS)) + MIN_RADIUS;
		x = (float) (Math.random() * (BOX_WIDTH - 2 * radius) + radius);
		y = (float) (radius / 2 + Math.random() * 100);
		speedX = Math.random() * 10 - 5;
		speedY = Math.random() * 10;
		angle = Math.random() * 15;
		rotateSpeed = Math.random() * 0.03;
	}

	public void update() {

		// Calculate the ball's new position
		x += speedX;
		y += speedY;
		speedY += BouncingBallSimple.GRAVITY;
		// calculate new angle of rotation the ball
		angle += rotateSpeed * getSpeedX();

		// Check if the ball moves over the bounds
		if (leftBorder()) {
			speedX = -speedX * BOUNCE_REDUCE; // Reflect along normal
			x = Math.abs(x - radius) + radius; // Re-position the ball at the
			// edge
		} else if (rightBorder()) {
			speedX = -speedX * BOUNCE_REDUCE;
			x = 2 * (BOX_WIDTH - radius) - x;
		}
		// May cross both x and y bounds
		if (upBorder()) {
			speedY = -speedY * BOUNCE_REDUCE;
			y = Math.abs(y - radius) + radius;
		} else if (downBorder()) {
			speedY = -speedY * BOUNCE_REDUCE;
			final float downBorder = BOX_HEIGHT / ((MAX_RADIUS - radius) / (MAX_RADIUS - MIN_RADIUS) + 1);
			y = 2 * (downBorder - radius) - y;
		}

		// Near the ground and small velocity Y
		if (Math.abs(speedY) <= 2 && nearGround())
			speedY = 0;

	}

	private boolean nearGround() {
		final float downBorder = BOX_HEIGHT / ((MAX_RADIUS - radius) / (MAX_RADIUS - MIN_RADIUS) + 1);
		final float downImage = y + radius;
		return downBorder - downImage <= 9;
	}

	private boolean downBorder() {
		final float downBorder = BOX_HEIGHT / ((MAX_RADIUS - radius) / (MAX_RADIUS - MIN_RADIUS) + 1);
		final float downImage = y + radius;
		return downImage > downBorder;
	}

	private boolean upBorder() {
		final float upImage = y - radius;
		return upImage < 0;
	}

	private boolean rightBorder() {
		final float rightImage = x + radius;
		return rightImage > BOX_WIDTH;
	}

	private boolean leftBorder() {
		final float leftImage = x - radius;
		return leftImage < 0;
	}
	

	public void draw(Graphics g, Graphics2D g2D) {
		final int ballBeginX = (int) (x - radius);
		final int ballBeginY = (int) (y - radius);
		final double ballAngle = angle;
		final int ballDiameter = (int) (2 * radius);

		// draw ball after rotate all plane
		g2D.rotate(ballAngle, x, y);
		g.drawImage(image, ballBeginX, ballBeginY, ballDiameter, ballDiameter, null);
		g2D.rotate(-ballAngle, x, y);
	}
	
	
	

	public void setSpeedX(double speedX) {
		this.speedX = speedX;
	}

	public void setSpeedY(double speedY) {
		this.speedY = speedY;
	}

	public double getSpeedX() {
		return speedX;
	}

	public double getSpeedY() {
		return speedY;
	}

	public float getRadius() {
		return radius;
	}

	public float getX() {
		return x;
	}

	public float getY() {
		return y;
	}

	public double getPreviousAngle() {
		return angle;
	}

	public double getRotateSpeed() {
		return rotateSpeed;
	}

	public void setPreviousAngle(double previousAngle) {
		this.angle = previousAngle;
	}

}
