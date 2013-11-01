import org.gwoptics.graphics.graph2D.Graph2D;
import org.gwoptics.graphics.graph2D.traces.ILine2DEquation;
import org.gwoptics.graphics.graph2D.traces.RollingLine2DTrace;

/*
********************************
Might be better off implementing graph in ControlP5
********************************
*/


public class ControlFrame extends PApplet {

  int w, h;

  int abc = 100;
  
  class eq implements ILine2DEquation{
    public double computePoint(double x,int pos) {
      return mouseX;
    }    
  }
  
  class eq2 implements ILine2DEquation{
    public double computePoint(double x,int pos) {
      return mouseY;
    }    
  }
  
  class eq3 implements ILine2DEquation{
    public double computePoint(double x,int pos) {
      if(mousePressed)
        return 400;
      else
        return 0;
    }    
  }

RollingLine2DTrace r,r2,r3;
Graph2D g;
Graph2D gp;
  
  public void setup() {
    size(600,300);
    
    frameRate(50);
    
    r3 = new RollingLine2DTrace(new eq3(),20,0.02f);
    r3.setTraceColour(0, 0, 255);
     
    g = new Graph2D(this, (width / 3) * 2, (height / 3) * 2, false);
    g.setYAxisMax(width);
    //g.addTrace(r);
    //g.addTrace(r2);
    g.addTrace(r3);
    g.position.y = 10;
    g.position.x = 125;
    g.setYAxisTickSpacing(100);
    g.setXAxisMax(5f);
    
    gui = new ControlP5(this);
    gui.addButton("CloseGraph", 1);
    gui.addToggle("X", false);
    gui.addToggle("Y", false);
  }
  
  void CloseGraph(int theValue) {
    f.setVisible(false);
  }
  
  void X (boolean toggle) {
    if (toggle) {
      r  = new RollingLine2DTrace(new eq() ,20,0.02f);
      r.setTraceColour(0, 255, 0);
      g.addTrace(r);
    }
    else {
      g.removeTrace(r);
    }
  }
  
  void Y (boolean toggle) {
    if (toggle) {
      r2 = new RollingLine2DTrace(new eq2(),20,0.02f);
      r2.setTraceColour(255, 0, 0);
      g.addTrace(r2);
    }
    else {
      g.removeTrace(r2);
    }
  }

boolean paused = false;

  public void draw() {
      background(abc);
      g.draw();
  }
  
  void keyPressed() {
    if (keyCode == TAB) {
      paused = !paused;
      println("Paused: " + paused);
    }
  }
//  private ControlFrame() {
//  }

  public ControlFrame(Object theParent, int theWidth, int theHeight) {
    parent = theParent;
    w = theWidth;
    h = theHeight;
  }


  public ControlP5 control() {
    return gui;
  }
  
  
  ControlP5 gui;

  Object parent;

  
}
