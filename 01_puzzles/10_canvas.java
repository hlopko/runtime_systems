//Jaky bude vystup metody main?

//Tento program lze spustit jak v jazyce Java, tak v jazyce Groovy. Bude se vystup obou jazyku nejak lisit?

//--------------------------------------------------------------------------------

class DispatchE {
    public static void main(String[] argv) {
        Shape[] shapes = new Shape[2];
        shapes[0] = new Circle(10,10,5);
        shapes[1] = new Square(20,20,15,15);

        Canvas canvas = new
            ScreenCanvas();
            //PostScriptCanvas();
        
        canvas.drawingStarts();
        for (int i = 0; i < shapes.length; i++) {
        	canvas.draw(shapes[i]);
        }
        canvas.drawingDone();
    }
}

class Shape {   
    /* Base class */
	public void drawOn(Canvas c) {
		c.draw(this);
	};
}

class Circle extends Shape { 
    public int x;
    public int y;
    public int radius;
    public Circle(int x, int y, int radius) {
        this.x = x;
        this.y = y;
        this.radius = radius;
    }
	public void drawOn(Canvas c) {
		c.draw(this);
	};
}

class Square extends Shape {
    public int x;
    public int y;
    public int width;
    public int height;

    public Square(int x, int y, int width, int height) {
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
    }
	public void drawOn(Canvas c) {
		c.draw(this);
	};

}

class Canvas {
    public void drawingStarts() {
    }

    public void draw(Circle c) {
        throw new RuntimeException("Don't know how to draw a circle");
    }

    public void draw(Square s) {
        throw new RuntimeException("Don't know how to draw a square");
    }

    public void draw(Shape s) {
        throw new RuntimeException("Don't know how to draw an instance of " + s.getClass().getName());
    }

    public void drawingDone() {
    }
}

class PostScriptCanvas extends Canvas {
    public void drawingStarts() {
        System.out.println("%!PS-Adobe-3.0 EPSF-3.0");
        System.out.println("%%BoundingBox: 0 0 100 100");
    }

    public void draw(Circle c) {            
        System.out.println(c.x + " " + c.y + " " + c.radius + " 0 360 arc");
    }

    public void draw(Square s) {
        System.out.println(  s.x +            " " + s.y              + " moveto");
        System.out.println( (s.x + s.width) + " " + s.y              + " lineto");
        System.out.println( (s.x + s.width) + " " + (s.y + s.height) + " lineto");
        System.out.println(  s.x            + " " + (s.y + s.height) + " lineto");
        System.out.println(  s.x +            " " + s.y              + " lineto");
    }

    public void drawingDone() {
        System.out.println("stroke");        
    }
}

class ScreenCanvas extends Canvas {
    public void draw(Circle c) {
        System.out.println(" ___");        
        System.out.println("/   \\");        
        System.out.println("|   |");        
        System.out.println("\\___/");        
    }

    public void draw(Square s) {
        System.out.println("+---+");        
        System.out.println("|   |");        
        System.out.println("+---+");        
    }
}
