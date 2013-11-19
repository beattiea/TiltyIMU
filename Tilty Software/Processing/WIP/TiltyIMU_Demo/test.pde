import java.awt.MenuComponent;
import java.awt.MenuBar;
import java.awt.Menu;
import java.awt.MenuItem;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

MenuBar myMenu;
Menu menu1;
MenuItem item1;

void setupMenuBar() {
  if (System.getProperty("os.name").equals("Mac OS X")) {
    System.setProperty("apple.laf.useScreenMenuBar", "true");
  }
  myMenu = new MenuBar();
  menu1 = new Menu("File");
  item1 = new MenuItem("Update");
  item1.addActionListener(Update);
  
  frame.setMenuBar(myMenu);
  myMenu.add(menu1);
  menu1.add(item1);
}

ActionListener Update = new ActionListener() {
  public void actionPerformed(ActionEvent arg0) {
    println("Hello World!");
  }
};
