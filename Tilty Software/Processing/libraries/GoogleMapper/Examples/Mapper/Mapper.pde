import googlemapper.*;

PImage map;
GoogleMapper gMapper;
 
public void setup() {
 
    size(640,480);
   
    double maCenterLat = 40.7782667;
    double mapCenterLon = -90.9698797;
    int zoomLevel = 12;
    String mapType = GoogleMapper.MAPTYPE_HYBRID;
    int mapWidth=640;
    int mapHeight=480;
   
    gMapper = new GoogleMapper(maCenterLat, mapCenterLon, zoomLevel, mapType, mapWidth,mapHeight);
   
    map = gMapper.getMap();
}
 
public void draw() {
   
    image(map,0,0);
   
    saveFrame("map.jpg");
   
    println(gMapper.y2lat(240));//outputs 40.7782667
    println(gMapper.x2lon(320));//outputs -73.9698797
    println(gMapper.lat2y(40.7782667));//outputs 240.0
    println(gMapper.lon2x(-73.9698797));//outputs 320.0
   
    noLoop();
}
