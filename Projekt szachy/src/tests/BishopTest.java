package tests;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import org.junit.Test;

import figures.Bishop;

public class BishopTest {
	Bishop b = new Bishop(1,1,"white");
	@Test
	public void From1And1To5And5() {
		
		assertTrue( b.checkPosition(5, 5) );
	}

	@Test
	public void From5And5To1And1() {
		Bishop b2 = new Bishop(5,5,"black");
		assertTrue( b2.checkPosition(1, 1) );
	}
	
	@Test
	public void From1And1To1And1() {
		assertTrue( b.checkPosition(1, 1) );
	}
	
	@Test
	public void From1And1To10And1() {
		assertFalse( b.checkPosition(10, 1) );
	}
}
