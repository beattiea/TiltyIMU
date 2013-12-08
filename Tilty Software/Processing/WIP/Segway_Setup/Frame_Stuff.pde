

String FRAME_TITLE = "TiltyIMU Segway Setup";

int FRAME_X = 1024;
int FRAME_Y = 700;

ImageIcon FRAME_ICON;


void setupFrame() {
  // Icon setting doesn't work
  FRAME_ICON = new ImageIcon(getToolkit().getImage(dataPath("Resources/icon.png")));
  frame.setIconImage(FRAME_ICON.getImage());
  
  frame.setTitle(FRAME_TITLE);
  
  size(FRAME_X, FRAME_Y);
  frame.setResizable(false);
  
  noStroke();
  smooth(4);
}
