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

package org.gwoptics.graphics.graph2D.backgrounds;

import org.gwoptics.graphics.GWColour;

public class GridBackground extends SolidColourBackground {
	protected GWColour _gridColour;
	
	/** Sets the colour of the major grid lines **/
	public void setGridColour(int R, int G, int B){_gridColour = new GWColour(R, G, B);}
	/** Removes major grid lines **/
	public void setNoGrid(){_gridColour = null;}
	
	public GridBackground(GWColour gridColour, GWColour background){
		super(background);
		_gridColour = gridColour;
	}
	
	public void draw() {
		super.draw();
		
		if(_parent != null && _gridColour != null){	
			_parent.stroke(_gridColour.toInt());
			
			if(_ax.getMajorTickPositions() != null){
				for (Integer i : _ax.getMajorTickPositions()) {
					_parent.line(i, 0, i, -_ay.getLength());
				}
			}
			
			if(_ay.getMajorTickPositions() != null){
				for (Integer i : _ay.getMajorTickPositions()) {
					_parent.line(0, -i, _ax.getLength(), -i);
				}
			}
		}
	}
}