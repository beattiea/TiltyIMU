import org.gwoptics.graphics.graph2D.Graph2D;
import org.gwoptics.graphics.graph2D.traces.ILine2DEquation;
import org.gwoptics.graphics.graph2D.traces.RollingLine2DTrace;

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
  
  public void setup() {
    //size(600,300);
    
    r  = new RollingLine2DTrace(new eq() ,10,0.01f);
    r.setTraceColour(0, 255, 0);
    
    r2 = new RollingLine2DTrace(new eq2(),10,0.01f);
    r2.setTraceColour(255, 0, 0);
    
    r3 = new RollingLine2DTrace(new eq3(),10,0.01f);
    r3.setTraceColour(0, 0, 255);
     
    g = new Graph2D(this, 400, 200, false);
    g.setYAxisMax(600);
    g.addTrace(r);
    g.addTrace(r2);
    g.addTrace(r3);
    g.position.y = 50;
    g.position.x = 100;
    g.setYAxisTickSpacing(100);
    g.setXAxisMax(5f);
    
    cp5 = new ControlP5(this);
    cp5.addButton("CloseGraph", 1);
  }
  
  void CloseGraph(int theValue) {
    f.setVisible(false);
  }

  public void draw() {
      background(abc);
      g.draw();
      println(frameRate);
  }
  
//  private ControlFrame() {
//  }

  public ControlFrame(Object theParent, int theWidth, int theHeight) {
    parent = theParent;
    w = theWidth;
    h = theHeight;
  }


  public ControlP5 control() {
    return cp5;
  }
  
  
  ControlP5 cp5;

  Object parent;

  
}
