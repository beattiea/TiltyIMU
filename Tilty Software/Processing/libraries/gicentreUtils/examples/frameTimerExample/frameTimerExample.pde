import org.gicentre.utils.FrameTimer;      // Needed for the frame timer.

// Sketch to demonstrate a frame timer that reports at regular intervals.
// Version 1.0, 31st July, 2012.
// Author Jo Wood.

private FrameTimer timer;
private int numEllipses;

void setup()
{
  size(500, 200);
  smooth();
  timer = new FrameTimer(2, 4);  // Report once every 4 seconds after a 2 second delay.
  numEllipses = 1024;
  textSize(18);
  textAlign(RIGHT, TOP);
}

void draw()
{
  background(255);
  timer.update();  // This is only needed if we are using a time-based frame counter.

  // Do some drawing of randomly placed and coloured ellipses.
  stroke(0, 120);
  for (int i=0; i<numEllipses; i++)
  {
    fill(random(0, 150), random(0, 150), random(0, 150), 80);
    ellipse(random(10, width-10), random(30, height-10), random(8, 20), random(8, 20));
  }

  fill(0, 160);
  String fps = timer.getFrameRateAsText();
  if (fps.length()>0)
  {
    text(numEllipses+" ellipses drawn at "+fps+" fps", width-5, 0);
  }
}

void keyPressed()
{
  if (key == CODED)
  {
    if ((keyCode == LEFT) && (numEllipses>1))
    {
      numEllipses /=2;
    }
    else if (keyCode == RIGHT)
    {
      numEllipses *=2;
    }
  }
}
