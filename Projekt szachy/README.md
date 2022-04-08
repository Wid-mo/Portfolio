# Blind Chess

![szachy](https://user-images.githubusercontent.com/22799520/162438665-c2ac7ed5-e0bf-41ba-a1b4-df8a8f783158.png)
![szachy2](https://user-images.githubusercontent.com/22799520/162438700-0a331ccf-c5dc-4d01-b16b-a1ab4d45017c.png)

In this game made in Java you can play in chess **on blind**.

## some interesting feature

- promote pawn on the figure selected by the user
- you can move figure on 2 various ways (drag & drop, click & click)
- backlight last move
- king can make castlings

## About interesting solutions

1. Fun, Simple checkPosition methods for: [Knight](https://github.com/Wid-mo/Portfolio/blob/master/Projekt%20szachy/src/figures/Knight.java), [Bishop](https://github.com/Wid-mo/Portfolio/blob/master/Projekt%20szachy/src/figures/Bishop.java), [Rook](https://github.com/Wid-mo/Portfolio/blob/master/Projekt%20szachy/src/figures/Rock.java), [Queen](https://github.com/Wid-mo/Portfolio/blob/master/Projekt%20szachy/src/figures/Queen.java) 
2. You can easily add new kind of figure
   * create new class
   * Add name of this class to TypeOfFigure.java
   * implement checkPosition method (define rules for moving this new object)
3. Note that you don't need to worry about implement method for each figure class which check Does road between source position and destination position are occupy.
I come up with very smart solution and I create [general method](https://github.com/Wid-mo/Portfolio/blob/master/Projekt%20szachy/src/figures/Figure.java) in parent class figure.
I named it checkTheRoadBetweenPositions(int x, int y).
It use mathematical function gcd(a, b) to count how many field is between source position and destination position. Next in for loop check each position does it is empty.

### Example data for checkTheRoadBetweenPositions method

Bishop from (1,1) to (5,5).
So you must check positions: (2,2), (3,3), (4,4).
``numberField = gcd(4, 4) - 1 = 3``

Rook from (1,1) to (7,1).
So you must check positions: (2,1), (3,1), (4,1), (5,1), (6,1).
``numberField = gcd(6, 0) - 1 = 5``

*gcd method returns other argument if argument is equal 0.*

---

Super Knight (which I made up) from (1,1) to (7,4).
So you must check positions: (3,2), (5,3).
``numberField = gcd(6, 3) - 1 = 2``

## Unit tests

I write some [unit test for bishop](https://github.com/Wid-mo/Portfolio/blob/master/Projekt%20szachy/src/tests/BishopTest.java).
