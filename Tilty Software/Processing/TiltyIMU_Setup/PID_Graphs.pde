import org.gwoptics.graphics.graph2D.Graph2D;
import org.gwoptics.graphics.graph2D.traces.ILine2DEquation;
import org.gwoptics.graphics.graph2D.traces.RollingLine2DTrace;

class P_eq implements ILine2DEquation {
  public double computePoint(double x, int pos) {
    if (myPort != null) {
      return map(P, -500, 500, Y_MIN, Y_MAX);
    }
    else {  return 0;}
  }
}

class I_eq implements ILine2DEquation {
  public double computePoint(double x, int pos) {
    if (myPort != null) {
      return map(I, -500, 500, Y_MIN, Y_MAX);
    }
    else {  return 0;}
  }
}

class D_eq implements ILine2DEquation {
  public double computePoint(double x, int pos) {
    if (myPort != null) {
      return map(D, -500, 500, Y_MIN, Y_MAX);
    }
    else {  return 0;}
  }
}

class Power_eq implements ILine2DEquation {
  public double computePoint(double x, int pos) {
    if (myPort != null) {
      return map(P + I + D, -500, 500, Y_MIN, Y_MAX);
    }
    else {  return 0;}
  }
}

class Angle_eq implements ILine2DEquation {
  public double computePoint(double x, int pos) {
    if (myPort != null) {
      return angle;
    }
    else {  return 0;}
  }
}

class zero_eq implements ILine2DEquation {//  Should eventually remove this and just draw a line at startup so it doesn't need to be graphed actively
  public double computePoint(double x, int pos) {
    return 0;
  }
}

RollingLine2DTrace P_line, I_line, D_line, PID_line, Angle_line, zero_line;
Graph2D PID_graph;

int update_freq = 25;
int Y_MAX = 100;
int Y_MIN = -100;
int line_width = 2;
//float x_increment = 0.1f;

void setupGraphs() {
  setupPIDGraphs(75, 275, width - 100, 200, update_freq, (update_freq / 100.0) * 0.1);
}

void setupPIDGraphs(int x, int y, int x_length, int y_length, int update_frequency, float x_increment) {
  //I_line = new RollingLine2DTrace(new I_eq(), update_freq, x_increment);
  //D_line = new RollingLine2DTrace(new D_eq(), update_freq, x_increment);
  //PID_line = new RollingLine2DTrace(new Power_eq(), update_freq, x_increment);
  //Angle_line = new RollingLine2DTrace(new Angle_eq(), update_freq, x_increment);
  zero_line = new RollingLine2DTrace(new zero_eq(), update_freq, x_increment);
  
  PID_graph = new Graph2D(this, x_length, y_length, false);
  PID_graph.setBorderColour(0, 0, 0);
  
  //P_line.setTraceColour(bR, bG, bB);
  //I_line.setTraceColour(bR, bG, bB);
  //D_line.setTraceColour(bR, bG, bB);
  //PID_line.setTraceColour(bR, bG, bB);
  //Angle_line.setTraceColour(bR, bG, bB);
  zero_line.setTraceColour(50, 50, 50);
  /*
  PID_graph.addTrace(I_line);
  PID_graph.addTrace(D_line);
  PID_graph.addTrace(PID_line);
  PID_graph.addTrace(Angle_line);
  */
  PID_graph.addTrace(zero_line);
  
  PID_graph.setYAxisMax(Y_MAX);
  PID_graph.setYAxisMin(Y_MIN);
  PID_graph.setYAxisTickSpacing(int((Y_MAX - Y_MIN) / 10));
  PID_graph.setXAxisTickSpacing(0.5);
  PID_graph.position.y = y;
  PID_graph.position.x = x;
  PID_graph.setXAxisMax(10);
}
