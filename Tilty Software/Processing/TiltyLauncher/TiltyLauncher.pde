import controlP5.*;

ControlP5 gui;

//  Window size variables  //
int x_size = 640;
int y_size = x_size * 3/4;
float scale = x_size / 320;

boolean launcher_ready = false;//  Indicates whether the launcher has finished setup()

PImage logo1, logo2;//  Tilty Logo Image variable
PFont font = createFont("Arial", 10 * scale, true); ;
ControlFont Cfont = new ControlFont(font, int(10 * scale));

void setup() {
  gui = new ControlP5(this);
  
  size(x_size, y_size);
  frame.setTitle("Tilty Launcher");
  loadLogo();
  setupButtons();
  
  pushMatrix();
  popMatrix();
  frame.setLocation(displayWidth / 2 - width / 2, displayHeight / 2 - height / 2);//  Sets the launcher window to center screen
  
  launcher_ready = true;//  Indicates the setup is complete and the launcher is ready
}

void draw() {
  background(127);
  drawLogo();
}

void newTiltyWay(int theValue) {
  println("Open a new 2D project");
  open(sketchPath("data/") + "New_2D_Setup.app");
  exit();
}

//  Rotates and displays the Tilty Logo
void drawLogo() {
  int rot = mouseX;
  int rot_range = 10;
  
  pushMatrix();
  
  translate(logo1.width / 2 + 10*scale, logo1.height / 2 + 2*scale);
  rotate(-radians(map(rot, 0, width, -rot_range, rot_range)));
  translate(-logo1.width / 2, -logo1.height / 2);
  image(logo1, 0, 0);//  displays "T"
  
  popMatrix();//  Resets translation and rotation
  
  image(logo2, 100*scale, 5*scale);//  Displays "ilty"
}




//  Loads the two parts of the Tilty logo and resizes them according to screen size  //
void loadLogo() {
  logo1 = loadImage("T.png");
  logo1.resize(int(width * 0.301) - int(width * 0.301)/10, logo1.height * ((int(width * 0.301) - int(width * 0.301)/10) / logo1.width));
  
  logo2 = loadImage("ilty.png");
  logo2.resize(int(width * 0.699) - int(width * 0.699)/10, logo2.height * ((int(width * 0.699) - int(width * 0.699)/10) / logo2.width));
}

//  Sets up the GUI buttons
void setupButtons() {
  //PImage[] logos = {logo, logo, logo};//  Only used if an image button is used
  gui.addButton("newTiltyWay")
     .setBroadcast(false)
     .setValue(0)
     .setBroadcast(true)
     .setPosition(10 * scale, 105 * scale)
     //  Uncomment below code to use an image button  // NO IMAGE DESIGNED YET
     //.setImages(logos)
     //.updateSize()
     
     //  Comment out below code when using an image button  //
     .setSize(int(100 * scale), int(30 * scale))
     .setCaptionLabel("New 2D Project")
     .getCaptionLabel().setFont(Cfont);
     ;
}
