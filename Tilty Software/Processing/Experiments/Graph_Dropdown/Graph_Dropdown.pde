/**
 * ControlP5 Canvas
 *
 * by andreas schlegel, 2011
 * www.sojamo.de/libraries/controlp5
 * 
 */
 
import controlP5.*;

import org.gwoptics.graphics.graph2D.Graph2D;
import org.gwoptics.graphics.graph2D.traces.ILine2DEquation;
import org.gwoptics.graphics.graph2D.traces.RollingLine2DTrace;
  
ControlP5 cp5;
  
void setup() {
  size(400,600);
  smooth();
  
  cp5 = new ControlP5(this);
  cp5.addGroup("myGroup")
     .setLabel("Testing Canvas")
     .setPosition(100,200)
     .setWidth(200)
     .addCanvas(new TestCanvas())
     ;
}

void draw() {
  background(127);
}


class TestCanvas extends Canvas {
  
  RollingLine2DTrace r,r2,r3;
  Graph2D g;
  
  class eq implements ILine2DEquation{
    public double computePoint(double x,int pos) {
      return mouseX;
    }    
  }
  
  float n;
  float a;
  
  public void setup(PApplet p) {
    r  = new RollingLine2DTrace(new eq() ,100,0.1f);
    r.setTraceColour(0, 255, 0);
     
    g = new Graph2D(p, 150, 50, false);
    g.setYAxisMax(600);
    g.addTrace(r);
    g.position.y = 0;
    g.position.x = 0;
    g.setYAxisTickSpacing(50);
    g.setXAxisMax(5f);
  }
  public void draw(PApplet p) {
    g.draw();
  }
}
