/**
 *  Copyright notice
 *  
 *  This file is part of the Processing library `gwoptics' 
 *  http://www.gwoptics.org/processing/gwoptics_p5lib/
 *  
 *  Copyright (C) 2009 onwards Daniel Brown and Andreas Freise
 *  
 *  This library is free software; you can redistribute it and/or modify it under 
 *  the terms of the GNU Lesser General Public License version 2.1 as published 
 *  by the Free Software Foundation.
 *  
 *  This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 *  See the GNU Lesser General Public License for more details.
 *  
 *  You should have received a copy of the GNU Lesser General Public License along with 
 *  this library; if not, write to the Free Software Foundation, Inc., 59 Temple Place, 
 *  Suite 330, Boston, MA 02111-1307 USA 
 */

package org.gwoptics.graphics.graph2D;

import java.util.ArrayList;

import org.gwoptics.ValueType;
import org.gwoptics.graphics.GWColour;
import org.gwoptics.graphics.Renderable;
//import org.gwoptics.graphics.camera.Camera3D;

import processing.core.PApplet;
import processing.core.PConstants;
import processing.core.PFont;
import processing.core.PVector;

/**
 * <p>
 * Axis2D is a straight forward object for drawing 2D axes. It has all the functionality for
 * tick marks, minimum and maximum values, colour and size, tick labels and axis labels.
 * </p>
 * 
 * <p>
 * Once an axis object has been created it is down the the user to specify the necessary rotations of
 * labels to make it readable. All the functions beginning with set should be used to alter the axis.
 * </p>
 * 
 * @author Daniel Brown 13/7/09
 * @since 0.4.0
 */
public class Axis2D extends Renderable implements PConstants  {

	private PVector _unitVec;
	protected PVector length;
	private int _length;
	private float _minShow;
	private float _maxShow;
	protected int _axisLineWidth;
	protected int _axisTickLineWidth;
	protected static PFont _font;
	protected String _label;
	protected PVector _labelDirection;
	protected float _majorTickSpacing;
	protected int _minorTicks;
	protected int _majorTickSize;
	protected int _minorTickSize;
	protected int _axisTickLblSize;
	protected int _axisTickLblOffset;
	protected int _axisLblSize;
	protected float _axisTickLblRotation;
	protected Alignment _axisTickLblAlign;
	protected float _axisLblRotation;
	protected float _axisLblOffset;
	protected LabelPos _axisLblPos;
	protected GWColour _axisColour;
	protected GWColour _fontColour;
	protected boolean _drawTicks;
	protected boolean _drawTickLabels;
	protected boolean _drawName;
	protected ValueType _tickLblType;
	protected int _accuracy;	
	private float _posConv;	/** Value is the number of pixels a value of 1 unit represents, eg 50 means 1unit is 50pixels along the axis */
	protected float _longestLabel = 0;
	protected ArrayList<Integer> _majorTickPositions;
	protected ArrayList<Float> _majorTickLabels;
	protected ArrayList<Integer> _minorTickPositions;
	protected boolean _generateTicks;
	protected boolean _offsetByLabelWidth;
	
	protected final static int MIN_TICK_SPACING = 3;	
	
	/**
	 * Encapsulates the 3 alignment constants already present in the PConstants
	 * interface. The three are singled out here to provide only the 3 options
	 * needed.
	 * 
	 * @author Daniel Brown
	 */
	public enum Alignment{
		LEFT(PConstants.LEFT),
		CENTER(PConstants.CENTER),
		RIGHT(PConstants.RIGHT);
		
		private int value;
		private Alignment(int v){this.value = v;}
		/** Gets the int value the constant represents */
		public int getValue(){return value;}
	}
	/** Sets the axis line colour from RGB values */
	public void setAxisColour(int R,int G, int B){setAxisColour(new GWColour(R,G,B));}	
	/** Sets the axis line colour from a Colour object */
	public void setAxisColour(GWColour c){
		if(c == null)
			throw new NullPointerException("Colour argument cannot be null");		
		_axisColour = c;
	}	
	/** Sets the labels font colour from RGB values */
	public void setFontColour(int R,int G, int B){setFontColour(new GWColour(R,G,B));}	
	/** Sets the labels font colour from a Colour object */
	public void setFontColour(GWColour c){
		if(c == null)
			throw new NullPointerException("Colour argument cannot be null");		
		_fontColour = c;
	}	
	/** Sets whether or not to draw the tick marks on the axis */
	public void setDrawTicks(boolean value){_drawTicks = value;}
	/** Sets whether or not to draw the tick major tick labels */
	public void setDrawTickLabels(boolean value){_drawTickLabels = value;}
	/** Sets whether or not to draw the axis label */
	public void setDrawAxisLabel(boolean value){_drawName = value;}
	/** Sets the label of the axis */
	public void setAxisLabel(String lbl) {_label = lbl;}
    /** Sets the position of the axis label along the axis 
     * @param lblpos position can be START, MIDDLE, END or OUTSIDE*/
	public void setAxisLabelPos(LabelPos lblpos) {_axisLblPos=lblpos;}
	/** Sets an offset that is to be applied to the axis label.
	 * 	This offset is applied in the direction of the ticks away
	 *  from the axis.*/
	public void setLabelOffset(float val) {_axisLblOffset = val;}
	/** Sets whether to offset the label by the longest tick label that has been rendered.
	 * This is used in situations with vertical axes and the tick labels vary in length
	 * as the values get larger.*/
	public void setOffsetLabelByTickLength(boolean value){_offsetByLabelWidth = value;}
	/** Sets an offset that is to be applied to the major tick labels.
	 * 	This offset is applied in the direction of the ticks away
	 *  from the axis.*/
	public void setTickLabelOffset(int val) {_axisTickLblOffset = val;}
	/** Sets the alignment of the major tick labels, from the Alignment enum */
	public void setTickLabelAlignment(Alignment a) {_axisTickLblAlign = a;}
	/** Sets the rotation to be applied to each tick label*/
	public void setTickLabelRotation(float val) {_axisTickLblRotation = val;}
	/** Sets the rotation to be applied to the main axis label */
	public void setLabelRotation(float val) {_axisLblRotation = val;}
	/** Sets the direction as a PVector, of which way the ticks and labels should be
	 *  from the main axis line.*/
	public void setLabelDirection(PVector vlbl) {vlbl.normalize();_labelDirection = vlbl;}
	/** Sets the direction in which the axis is drawn */
	public void setAxesDirection(PVector uv) {uv.normalize();_unitVec = uv;}
	/** Sets the spacing between each tick in graph space */
	public void setTickSpacing(float spacing){_majorTickSpacing = spacing;_generateTicks = true;}
	/** Sets the number of minor ticks to show */
	public void setMinorTicks(int t) {_minorTicks = t;_generateTicks = true;}
	/** Sets the type of number to display on the graph
	 * 	@see ValueType */
	public void setTickLabelType(ValueType v){_tickLblType = v;}
	/** Sets the number of decimal places to display in each tick label.
	 *  Only valid for tick valueTypes of DECIAML or EXPONENT*/
	public void setTickLabelAccuracy(int v){_accuracy = v;}
	/** Sets the length of the major ticks, using a negative length
	 * extends ticks into the graph rather than to the labels
	 * @param val length of the major ticks */
	public void setMajorTickLength(int val) {_majorTickSize = val;}
	/** Sets the length of the minor ticks, using a negative length
	 * extends ticks into the graph rather than to the labels
	 * @param val length of the major ticks*/
	public void setMinorTickLength(int val) {_minorTickSize = val;}
	/** Sets the maximum value to show on the axis */
	public void setMaxValue(float val) {		
		_maxShow = val;				
		_posConv = (_length-1) / (_maxShow - _minShow);
		_generateTicks = true;			
	}
	/** Sets the minimum value to show on the axis */
	public void setMinValue(float val) {
		_minShow = val;				
		_posConv = (_length-1) / (_maxShow - _minShow);
		_generateTicks = true;
	}	

	/* Getters */
	/** Gets the number of major ticks on the axis*/
	public float getMajorTickSpacing(){return _majorTickSpacing;}
	/** returns the maximum value of the axis range */
	public float getMaxValue() {return _maxShow;}
	/**returns the minimum value of the axis range*/
	public float getMinValue() {return _minShow;}
	/**returns the length of the axis in world space.*/
	public int getLength(){return _length;}

	public Integer[] getMajorTickPositions(){
		if(_majorTickPositions != null){
			Integer[] rtn = new Integer[_majorTickPositions.size()];
			rtn = _majorTickPositions.toArray(rtn);
			return rtn;
		}else
			return null;
	}
	
	public Integer[] getMinorTickPositions(){
		if(_minorTickPositions != null){
			Integer[] rtn = new Integer[_minorTickPositions.size()];
			rtn = _minorTickPositions.toArray(rtn);
			return rtn;
		}else
			return null;
	}
	
	/** Axis2D constructor accepting the parent PApplet and the length of the axis in pixels */ 
	public Axis2D(PApplet parent, int length) {
		super(parent);
		
		_axisColour = new GWColour(0,0,0);
		_fontColour = new GWColour(0,0,0);
		
		_drawTicks = true;
		_drawTickLabels = true;
		_drawName = true;
		
		_tickLblType = ValueType.DECIMAL;
		_accuracy = 1;
		
		_unitVec = new PVector(1,0);
		_labelDirection = new PVector(0,1);
		_axisTickLblRotation  = 0;
		_axisLblRotation = 0;
		_length = length;
		_minShow = 0f;
		_maxShow = 1f;
		_majorTickSpacing = 0.5f;
		_minorTicks = 2;
		_majorTickSize = 6;
		_minorTickSize = 3;
		_axisTickLblSize = 12;
		_axisLblSize = 12;
		_axisLblOffset = 4;
		_axisLblPos = LabelPos.MIDDLE;
		_axisLineWidth = 1;
		_axisTickLineWidth = 1;		
		_axisTickLblAlign = Alignment.CENTER;
		_axisTickLblOffset = 6;
		_generateTicks = true;
		
		_posConv = _length / (_maxShow - _minShow);
		_offsetByLabelWidth = false;
		
		parent.registerPre(this);
		
		if(_font == null) {//Font is a static member so only load if noone has before
			// adf 150310 changed to createFont because loadFont would not work with
			// getFont().getSize() below
			//_font = parent.loadFont("Arial-BoldMT-12.vlw");
			_font = parent.createFont("Arial-BoldMT",12);
			}
		}

	
	public void pre(){
		if(_generateTicks){
			_generateTicks();
			_generateTicks = false;
		}
	}
	
	@Override
	public void draw() {		
		
		_parent.pushMatrix();
		_parent.pushStyle();
		_parent.translate(position.x,position.y);

		length = PVector.mult(_unitVec, _length);
		
		_drawAxisLine();
		
		if(_drawTicks || _drawTickLabels)
			_drawTicksAndLabels();
		
		if(_drawName)
			_drawAxisLabel();
		
		_parent.popStyle();
		_parent.popMatrix();
	}
	
	/** For a given graph value it provides the position it is on the axis to the nearest pixel */
	public int valueToPosition(float value){return Math.round((value - _minShow) * _posConv);}
	public int valueToPosition(double value){return (int) Math.round((value - _minShow) * _posConv);}
	
	/** For a given number of pixels along the axis, the value it represents is returned*/
	public float positionToValue(int pixel){return _minShow + ((float)(pixel)/(_posConv));}
	
	/** Internal method too draw the main axis line */
	protected void _drawAxisLine(){
		_parent.pushStyle();
		
		_parent.stroke(_axisColour.toInt());
		_parent.strokeWeight(_axisLineWidth);
		
		_parent.beginShape(PConstants.LINE);
		_parent.vertex(0, 0);
		_parent.vertex(length.x, length.y);
		_parent.endShape();
		
		_parent.popStyle();
	}
	
	protected void _generateTicks(){
		_majorTickLabels = new ArrayList<Float>();
		_majorTickPositions = new ArrayList<Integer>();
		_minorTickPositions = new ArrayList<Integer>();
		
		float spcDivMn = _minShow/_majorTickSpacing;
		  
		float firstTickOffset = (float) (Math.ceil(spcDivMn) * _majorTickSpacing - _minShow);
		float currTickValue = _minShow + firstTickOffset;
		float minorTickSpc = _majorTickSpacing / (_minorTicks + 1); //graph space	
		float currMinorTickValue = currTickValue;
		
		//This loop may seem out of place. Because the main draw loop draws minor
		//ticks after the major ticks, no minor ticks are drawn before the first
		//major tick. There is probably more elegant ways of doing this, like
		//looping for every minor tick possible then determining if the current
		//tick is a major or minor. this works though...		
		//offset initial minor tick
		currMinorTickValue -= minorTickSpc;
		
		while(currMinorTickValue >= _minShow){
			//same as with major ticks, get start and end points			
			_minorTickPositions.add(valueToPosition(currMinorTickValue));						
			currMinorTickValue -= minorTickSpc;
		}
		
		while(currTickValue <= _maxShow){			
			_majorTickPositions.add(valueToPosition(currTickValue));
			_majorTickLabels.add(currTickValue);
			
			currMinorTickValue = currTickValue + minorTickSpc; //graph space
			
			while(currMinorTickValue <= _maxShow && currMinorTickValue < currTickValue + _majorTickSpacing){
				//same as with major ticks, get start and end points
				_minorTickPositions.add(valueToPosition(currMinorTickValue));				
				currMinorTickValue += minorTickSpc;
			}			
			
			currTickValue += _majorTickSpacing;
		}
		
	}
 
	/** Internal method to draw tick marks and labels */
	protected void _drawTicksAndLabels(){
		PVector tickLblPos = new PVector(0, 0);
		PVector tickPos = new PVector(0, 0);
		PVector tickEnd = new PVector(0, 0);
		PVector tickPosMinor = new PVector(0, 0);
		PVector tickEndMinor = new PVector(0, 0);
		
		String tickLbl = "";
		
		//setup tick properties
		_parent.pushStyle();
		_parent.strokeWeight(_axisTickLineWidth);
		_parent.textFont(_font, _axisTickLblSize);
		_parent.stroke(_axisColour.toInt());
		_parent.strokeWeight(_axisLineWidth);
		
		if(_axisTickLblAlign == null)
			_parent.textAlign(CENTER);
		else
			_parent.textAlign(_axisTickLblAlign.getValue());		
		
		for (int i = 0; i < _majorTickPositions.size(); i++) {
			int pos = _majorTickPositions.get(i);
			float val = _majorTickLabels.get(i);
			
			// position of tick along the axis
			tickPos = PVector.mult(_unitVec, pos);
			//also determine point where the tick should end, based on label direction and length
			tickEnd = PVector.add(tickPos, PVector.mult(_labelDirection,-_majorTickSize));
			
			//next draw the tick label
			if(_drawTickLabels){			
				// Make tick label
				switch (_tickLblType) {
					case DECIMAL:			
						tickLbl = String.format(" %." + _accuracy + "f",(float)(val));		
						break;
					case EXPONENT:	
						tickLbl = String.format(" %." + _accuracy + "E",(float)(val));				
						break;
					case INTEGER:	
						tickLbl = String.format(" %d", Math.round(val));				
						break;
				}
				
				//to define where the major tick label is, we take the current tick position
				//and move in the label direction depending on width of the text and the major
				//tick size
				tickLblPos = PVector.add(tickPos, PVector.mult(_labelDirection, _axisTickLblOffset + Math.abs(_majorTickSize)));				
				
				// determine if this is the longest label for main axis label
				// placement later
				float lblSize = _parent.textWidth(tickLbl);
				
				if (lblSize > _longestLabel) {
					_longestLabel = lblSize + 5;
				}
				
				_parent.pushMatrix();
				_parent.translate(tickLblPos.x, tickLblPos.y);
								
				_parent.rotate(_axisTickLblRotation);
				_parent.fill(_fontColour.toInt());
				_parent.text(tickLbl, 0, 0.4f * _axisTickLblSize, 0);
				_parent.popMatrix();
			}
			
			if(_drawTicks){				
				//draw the tick line
				_parent.beginShape(PConstants.LINE);
				_parent.vertex(tickPos.x, tickPos.y);
				_parent.vertex(tickEnd.x, tickEnd.y);
				_parent.endShape();						
			}
		}

		if(_drawTicks){	
			for (Integer i : _minorTickPositions) {				
				//same as with major ticks, get start and end points
				tickPosMinor = PVector.mult(_unitVec, i);
				tickEndMinor = PVector.add(tickPosMinor, PVector.mult(_labelDirection, -_minorTickSize));

				_parent.beginShape(PConstants.LINE);
				_parent.vertex(tickPosMinor.x, tickPosMinor.y);
				_parent.vertex(tickEndMinor.x, tickEndMinor.y);
				_parent.endShape();										
			}
		}
		
		_parent.popStyle();			
	}
	
	/** internal method that draws the axis label */
	protected void _drawAxisLabel(){
		// Add Label
		_parent.fill(_fontColour.toInt());
		_parent.textAlign(CENTER);
		_parent.textFont(_font, _axisLblSize);
		
		PVector lblPos=new PVector(0,0,0);
		// label position will be half way along the axis
		switch (_axisLblPos){
		case MIDDLE:
			lblPos = PVector.div(length, 2);
			break;
		case START:
			lblPos = new PVector(0,0,0);
			break;
		case END:
			lblPos = length;
			break;
		case OUTSIDE:
			lblPos = PVector.mult(length, 1.1f);
			break;
		}
		
		
		// next need to offset in the label direction			
		if(_offsetByLabelWidth)
			lblPos.add(PVector.mult(_labelDirection, _longestLabel + _axisLblOffset + _axisTickLblOffset + Math.abs(_majorTickSize) ));
		else
			lblPos.add(PVector.mult(_labelDirection, _axisLblSize + _axisLblOffset + _axisTickLblOffset + Math.abs(_majorTickSize) ));
			
		// Draw the label
		_parent.pushMatrix();
		//move into a local space about the label centre so we can easily rotate it
		_parent.translate(lblPos.x, lblPos.y);						
		_parent.rotate(_axisLblRotation);
		_parent.text(String.valueOf(_label), 0, 0.25f * _font.getFont().getSize(), 0);
		_parent.popMatrix();
	}
}
