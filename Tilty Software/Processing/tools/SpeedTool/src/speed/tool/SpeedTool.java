/**
 * you can put a one sentence description of your tool here.
 *
 * Lars Kaltenbach, 2013
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA  02111-1307  USA
 * 
 * @author		Lars Kaltenbach
 * @modified	15/07/13
 * @version		001
 */

 package speed.tool;
 
 import processing.app.*;
import processing.app.tools.*;
 import speed.tool.BracketCloser;

 import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
 
 
 public class SpeedTool implements Tool, KeyListener {
	 Editor editor;
	 BracketCloser bc;
	 boolean isRunning = false;
	 
	public String getMenuTitle() {
		return "Speed Tool";
	}
 
	public void init(Editor editor) {
		this.editor = editor;
		bc = new BracketCloser( editor ); 
	}
 
	public void run() {
		if(!isRunning) {
			editor.getTextArea().addKeyListener(this);  
			System.out.println( "Speed Tool 0.2 (beta) - Lars Kaltenbach 2013 - http://larskaltenbach.de" );
			isRunning = true;
		} else {	
			System.out.println( "Speed Tool is already active" );
		}
	}

	@Override
	public void keyPressed(KeyEvent e) {
		// listen for keyboard input and update BracketCloser
		bc.update( e.getKeyChar() );
	}

	@Override
	public void keyReleased(KeyEvent e) { }

	@Override
	public void keyTyped(KeyEvent e) { }
 }



