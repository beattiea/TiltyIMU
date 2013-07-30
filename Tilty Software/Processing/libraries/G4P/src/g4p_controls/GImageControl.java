/*
  Part of the GUI for Processing library 
  	http://www.lagers.org.uk/g4p/index.html
	http://gui4processing.googlecode.com/svn/trunk/

  Copyright (c) 2008-13 Peter Lager

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
 */

package g4p_controls;

import g4p_controls.HotSpot.HSalpha;
import g4p_controls.HotSpot.HSmask;
import processing.core.PApplet;
import processing.core.PImage;

/**
 * Intermediary class for control based on images.
 * 
 * It will create an array (minimum size 3) of PImage objects one for each image file.
 * 
 * @author Peter Lager
 */
abstract class GImageControl extends GAbstractControl {

	protected PImage[] bimage = null;
	public PImage mask = null;

	public GImageControl(PApplet theApplet, float p0, float p1, float p2, float p3,
			String[] fnames, String fnameMask) {
		super(theApplet, p0, p1, p2, p3);
		// These will be zero if we are to use the image size
		int controlWidth = (int)width, controlHeight = (int)height;
		//=======================================================
		// First of all load images
		bimage = new PImage[3];
		if(fnames == null || fnames.length == 0){
			fnames = new String[] { "err0.png", "err1.png", "err2.png" };
			bimage = new PImage[3];
		}
		else {
			bimage = new PImage[PApplet.max(3, fnames.length)];
		}

		for(int i = 0; i < fnames.length; i++){
			bimage[i] = winApp.loadImage(fnames[i]);
			if(bimage[i] == null)
				bimage[i] = winApp.loadImage("err" + (i%3) + ".png");
		}
		for(int i = fnames.length; i < 3; i++)
			bimage[i] = bimage[i-1];

		// Get mask image if available
		if(fnameMask != null)
			mask = winApp.loadImage(fnameMask);
		//=======================================================
		// So now we need to decide whether to resize the images or control
		if(width > 0 && height > 0){
			// Resize images
			for(int i = 0; i < bimage.length; i++){
				if(bimage[i].width != controlWidth || bimage[i].height != height)
					bimage[i].resize(controlWidth, controlHeight);					
			}
			if(mask != null && (mask.width != controlWidth || mask.height != controlHeight))
				mask.resize(controlWidth, controlHeight);
		}
		else {
			// resize control
			width = bimage[0].width;
			height = bimage[0].height;
			halfWidth = width/2;
			halfHeight = height/2;
			// Recalculate corners or centre  depending on contro;_mode
			switch(G4P.control_mode){
			case CORNER:
			case CORNERS:
				x = p0;
				y = p1;
				cx = x + halfWidth;
				cy = y + halfHeight;
				break;
			case CENTER:
				cx = p0;
				cy = p1;
				x = cx - halfWidth;
				y = cy - halfHeight;
				break;
			}
		}
		if(mask != null){	// if we have a mask use it for the hot spot
			hotspots = new HotSpot[]{
					new HSmask(1, mask)
			};
		}
		else {   // no mask then use alpha channel of the OFF image
			hotspots = new HotSpot[]{
					new HSalpha(1, 0, 0, bimage[0], PApplet.CORNER)
			};
		}

	}


}
