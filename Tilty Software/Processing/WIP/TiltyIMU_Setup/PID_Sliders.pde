//Need a reset button to reset scalars?
Slider kP_slider, kI_slider, kD_slider, steering_slider;

void setupPIDsliders() {
  setupPslider(200, 50);
  setupIslider(200, 100);
  setupDslider(200, 150);
}

void setupPslider(int x, int y) {
  kP_slider = cp5.addSlider("Pscale")
                .setPosition(x, y)
                .setSize(100, 20)
                .setRange(1, 200)
                .setValue(100)
                .setDecimalPrecision(1)
                .setSliderMode(Slider.FIX)
                ;
     
   kP_slider.setLabelVisible(true)
           .setCaptionLabel("P Scalar %")
           .getCaptionLabel().setFont(createFont("arial", 10))
           .align(ControlP5.RIGHT, ControlP5.BOTTOM_OUTSIDE).setPaddingX(0)
           ;
}

void setupIslider(int x, int y) {
  kI_slider = cp5.addSlider("IScale")
                 .setPosition(x, y)
                 .setSize(100, 20)
                 .setRange(1, 200)
                 .setValue(100)
                 .setDecimalPrecision(0)
                 .setSliderMode(Slider.FIX)
                 ;
     
   kI_slider.setLabelVisible(true)
            .setCaptionLabel("I Scalar %")
            .getCaptionLabel().setFont(createFont("arial", 10))
            .align(ControlP5.RIGHT, ControlP5.BOTTOM_OUTSIDE).setPaddingX(0)
            ;
}

void setupDslider(int x, int y) {
  kD_slider = cp5.addSlider("DScale")
                 .setPosition(x, y)
                 .setSize(100, 20)
                 .setRange(1, 200)
                 .setValue(100)
                 .setDecimalPrecision(0)
                 .setSliderMode(Slider.FIX)
                 ;
     
   kD_slider.setLabelVisible(true)
            .setCaptionLabel("D Scalar %")
            .getCaptionLabel().setFont(createFont("arial", 10))
            .align(ControlP5.RIGHT, ControlP5.BOTTOM_OUTSIDE).setPaddingX(0)
            ;
}

//  Functions that are called when a toggle is clicked  //
int pScale;
void Pscale(int value) {
  pScale = value;
  println(pScale);
}
