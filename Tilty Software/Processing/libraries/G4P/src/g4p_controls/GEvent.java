/*
  Part of the GUI for Processing library 
  	http://www.lagers.org.uk/g4p/index.html
	http://gui4processing.googlecode.com/svn/trunk/

  Copyright (c) 2008-12 Peter Lager

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

/**
 * Enumeration of events that can be fired by G4P.
 * 
 * @author Peter Lager
 *
 */
public enum GEvent {

	CHANGED 			( "Text has changed" ),
	SELECTION_CHANGED 	( "Text selection has changed" ),
	ENTERED			 	( "Enter/return key typed" ),
	
	// GPanel component
	COLLAPSED  			( "Control was collapsed" ),
	EXPANDED 			( "Control was expanded" ),
	DRAGGED 			( "Control is being dragged" ),

	// GButton
	CLICKED  			( "Mouse button was clicked" ),
	PRESSED  			( "Mouse button was pressed" ),
	RELEASED  			( "Mouse button was released" ),

	VALUE_CHANGING		( "Value is changing" ),
	VALUE_STEADY		( "Value has reached a steady state" ),
	DRAGGING			( "The mouse is being dragged over a component "),
	
	// GCheckbox & GOption
	SELECTED			( "Option selected" ),
	DESELECTED			( "Option de-selected" );

	
	private String description;
	
	private GEvent(String desc ){
		description = desc;
	}
	
	public String toString(){
		return description;
	}
}
