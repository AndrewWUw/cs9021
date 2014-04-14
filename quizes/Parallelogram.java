
import java.awt.*;

/** A parallelogram with horizontal length l1 and the other length l2
    with a leaning factor d.
    
         (x,y)___________________      This parallelogram has 
              |                  |     leaning factor d = 0.
              |__________________|
              
         (x,y)  ___________________      This parallelogram has a positive
               /                  /      leaning factor. d is the number of
              /__________________/       pixels from the leftmost part of the
                                         parallelogram to its top-left corner
                                         
         (x,y)  ___________________      This parallelogram has a negative
                \                  \     leaning factor. d is the number of
                 \__________________\    pixels from the bottom-left corner to
                                         the leftmost part of the parallelogram
                                        
                                         
             */
public class Parallelogram extends Shape {
    int l1; // The parallelogram has a horizontal side of length l1
    int l2; // and the other side has length l2. If right-leaning, d >= 0 and
    int d;  // the top line start d units to the right of point (x,y)
            // If left-leaning, d is negative and the bottom line
            // starts abs(d) units to the right of point (x,y)

    /** Constructor: a parallelogram at (xp, yp) of side lengths
           lp1 (horizontal side) and lp2, dp pixels from (xp, yp) */
    public Parallelogram(int xp, int yp, int lp1, int lp2, int dp) {
       super(xp, yp);
       l1= lp1; l2= lp2; d= dp;
    }
    
    
    /** Draw parallelogram using graphics g */
    public void drawShape(Graphics g) {
       // Set xt and xb to the horizontal coordinates of left pt of top
       // and bottom lines
        int xt= x+d;           
        int xb= x;           
        if (d < 0) {
            xt= x; 
            xb= x+(-d);
        }

          
       // Set yb to the vertical coordinate of the bottom left point
          int yb= y+(int)(Math.round(Math.sqrt(l2*l2 - d*d)));
    
       // Draw the four lines
          g.drawLine(xt, y, xt+l1, y);
          g.drawLine(xt+l1, y, xb+l1, yb);
          g.drawLine(xb+l1, yb, xb, yb);
          g.drawLine(xb, yb, xt, y);
    }
    
    /** = description of this parallelogram */
    public String toString() {
      return "parallelogram at " + super.toString() + ", sides " +
             l1 + " and " + l2 + ", distance " + d + " from " + x;
    }

}
