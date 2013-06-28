// The following short XML file called "mammals.xml" is parsed 
// in the code below. It must be in the project's "data" folder.
//
// <?xml version="1.0"?>
// <mammals>
//   <animal id="0" species="Capra hircus">Goat</animal>
//   <animal id="1" species="Panthera pardus">Leopard</animal>
//   <animal id="2" species="Equus zebra">Zebra</animal>
// </mammals>

XML xml;

void setup() {
  xml = loadXML("People.xml");
  //XML firstChild = xml.getChild("animal");
  //xml.removeChild(firstChild);
  xml.setName("People");
  xml.addChild("Name");
  XML nameChild = xml.getChild("Name");
  nameChild.setString("First", "Alex");
  nameChild.setString("Last", "Beattie");
  nameChild.setInt("Age", 22);
  saveXML(xml, "PeoplesNames");
}

// Sketch saves the following to a file called "subset.xml":
// <?xml version="1.0"?>
// <mammals>
//   <animal id="1" species="Panthera pardus">Leopard</animal>
//   <animal id="2" species="Equus zebra">Zebra</animal>
// </mammals>
