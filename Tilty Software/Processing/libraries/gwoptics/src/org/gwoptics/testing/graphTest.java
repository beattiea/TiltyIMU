package org.gwoptics.testing;

/*


<<<<<<< .mine
=======
import guicomponents.*;
import org.gwoptics.gui.button.*;

>>>>>>> .r65
<<<<<<< .mine
import org.gwoptics.graphics.GWColour;
import org.gwoptics.graphics.graph2D.Graph2D;
import org.gwoptics.graphics.graph2D.backgrounds.GridBackground;
import org.gwoptics.graphics.graph2D.traces.ILine2DEquation;
import org.gwoptics.graphics.graph2D.traces.Line2DTrace;
import org.gwoptics.gui.slider.gwSlider;

=======
>>>>>>> .r65
import processing.core.PApplet;
<<<<<<< .mine
import org.gwoptics.gui.slider.*;
import guicomponents.GSlider;
import org.gwoptics.ValueType;
=======
import processing.core.PImage;
>>>>>>> .r65

@SuppressWarnings("serial")
public class graphTest extends PApplet{
<<<<<<< .mine

	gwSlider sl,sl1,sl2,sl3,sl4;
=======
>>>>>>> .r65
	
<<<<<<< .mine
=======
	gwButton btn;

>>>>>>> .r65
	public void setup(){
<<<<<<< .mine
		size(400, 300); //Use P3D for now, openGl seems to have some issues
		  
		  //Throughout example note the output in the PDE console
		  //you should see an integer and float output, retrieved by
		  //getValue() (for integer) and getValuef (for float). The reason
		  //behind this is to do with inheriting from the g4p library 
		  //certain functions which can't be overriden.
		  
		  //simple default slider
		  //constructor is Parent applet, x, y, length
		  sl = new gwSlider(this,20,20,300);
		  
		  
		  sl2 = new gwSlider(this,20,140,300);
		  sl2.setValueType(ValueType.DECIMAL);
		  sl2.setLimits(0.5f, 0f, 1.0f);
		  sl2.setTickCount(3); 
		  sl2.setRenderMaxMinLabel(false); //hides labels
		  sl2.setRenderValueLabel(false);	//hides value label
		  sl2.setStickToTicks(true);//false by default this sticks
		  							//the handle to ticks so no inbetween
		  							//values are possible
		  
		  //Last example shows small float numbers used and settings
		  //the accuracy of the display labels
		  sl3 = new gwSlider(this,20,190,300);
		  sl3.setValueType(ValueType.EXPONENT);
		  sl3.setLimits((int)2E-10, 0, (int)3E-10);
		  sl3.setTickCount(10); 
		  sl3.setPrecision(1);
		  
		  //Can also add custom labels to ticks
		  //Note: setTickCount() is overriden by
		  //the length of the input array, and 
		  //vice versa
		  String[] l = new String[4];
		  l[0] = "A";
		  l[1] = "B";
		  l[2] = "C";
		  l[3] = "D";
		  sl4 = new gwSlider(this,20,240,300);
		  sl4.setTickLabels(l);
		  sl4.setStickToTicks(true);
		  sl4.setValue(56);//notice that we are setting a value that isnt exactly a tick
		  				   //when stick to tick is true, setValue will stick to nearest tick
		  				   //value
		
=======
		  size(300,300);
		    
		  btn = new gwButton(this,"test",10,10,200,200);
		  
		  PImage imgNorm = loadImage("norm.png");
		  PImage imgOver = loadImage("over.png");
		  PImage imgPressed = loadImage("pressed.png");
		  
		  btn.setUseImages(true);
		  btn.setImages(imgNorm,imgOver,imgPressed);
>>>>>>> .r65
	}
	
<<<<<<< .mine
	public void draw(){
		  background(200);
	}
=======
	public void draw(){}
>>>>>>> .r65
	
	void handleSliderEvents(gwSlider slider) {
		println("integer value:" + slider.getValue() + " float value:" + slider.getValuef());
	}
}
*/