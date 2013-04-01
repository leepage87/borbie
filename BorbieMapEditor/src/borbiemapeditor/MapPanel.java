package borbiemapeditor;

import borbiemapeditor.MenuPanel.MenuSelection;
import java.awt.Color;
import java.awt.Cursor;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Point;
import java.awt.Toolkit;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import javax.imageio.ImageIO;
import javax.swing.JPanel;


/**
 *
 * @author richard
 */
public class MapPanel extends JPanel {
    
    // final colors (as drawn on the screen)
    private final Color underglowColor = Color.CYAN;
    private final Color selectionColor = new Color(255, 255, 255, 100);
    
    // references to internal Image and the Main Window.
    private final MainWindow mainWindow;
    private Image mapImg;
    
    // image and internal object sizes
    private int imgW;
    private int imgH;
    private int objectWidth;
    private int objectHeight;
    private int dotWidth;
    private int dotHeight;
    
    // drag selection variables
    private boolean selecting;
    private int selX1;
    private int selY1;
    private int selX2;
    private int selY2;
    
    // object dragging variables
    private boolean dragging;
    private int lastMouseX;
    private int lastMouseY;
    
    // pointers to mapped objects
    private ArrayList<MapObject> mapObjects;
    
    // list of all copied objects
    private ArrayList<MapObject> copyObjects;
    
    // object images
    private Image buildingImage;
    private Image roadImage;
    private Image lampImage;
    private Image treeImage;
    private Image eraseImage;
    
    
    // CONSTRUCTOR: keeps track of the image to be displayed, and sets
    //  its own size in accordance to the image size.
    public MapPanel(final MainWindow mainWindow, Image mapImg) {
        this.mainWindow = mainWindow;
        this.mapImg = mapImg;
        
        // scale image size by 2 (so it's not too big)
        this.imgW = mapImg.getWidth(this);
        this.imgH = mapImg.getHeight(this);
        
        // set panel size based on image size (scaled)
        this.setPreferredSize(new Dimension(imgW, imgH));
        
        // set object width and height to be scaled (standard building size)
        //  (50 objects per img height/width)
        objectWidth = (int)Math.round(imgW / 50.0);
        objectHeight = (int)Math.round(imgH / 50.0);
        // dots are half of the standard building width
        dotWidth = objectWidth / 2;
        dotHeight = objectWidth / 2;
        
        // initially NOT selecting
        selecting = false;
        selX1 = selX2 = selY1 = selY2 = 0; // 0 all selection values
        
        // initially NOT dragging
        dragging = false;
        lastMouseX = 0;
        lastMouseY = 0;
        
        // try to set up all images
        buildingImage = getScaledImage("buildingSquare.png");
        roadImage = getScaledImage("road.png"); // SQUARE ?
        lampImage = getScaledImage("yellowDot.png", dotWidth, dotHeight);
        treeImage = getScaledImage("greenDot.png", dotWidth, dotHeight);
        eraseImage = getScaledImage("eraser.png");
        
        // set up the map objects arraylists
        this.mapObjects = new ArrayList<MapObject>();
        this.copyObjects = new ArrayList<MapObject>();
        
        
        // add mouse listener: standard mouse events
        this.addMouseListener(new MouseListener(){
            @Override
            public void mouseClicked(MouseEvent e){}
            @Override
            public void mouseEntered(MouseEvent e){
                MenuSelection curSel = mainWindow.getCurSelection();
                mainWindow.setCursor(getCustomCursor(curSel));
            }
            @Override
            public void mouseExited(MouseEvent e){
                mainWindow.setCursor(
                        Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
            }
            @Override
            public void mousePressed(MouseEvent e){
                MenuSelection curSel = mainWindow.getCurSelection();
                setObject(curSel, e.getX(), e.getY());
            }
            @Override
            public void mouseReleased(MouseEvent e){
                // if was selecting, toggle it off and clear the selection drawing
                if(selecting){
                    selecting = false;
                    repaint();
                }
                // if dragging, once mouse is lifted, drag no more
                dragging = false;
            }
        });
        
        // add mouse listener: mouse movement
        this.addMouseMotionListener(new MouseMotionListener(){
            @Override
            public void mouseDragged(MouseEvent e){
                if(selecting){
                    selX2 = e.getX();
                    selY2 = e.getY();
                    checkSelectedArea();
                    repaint();
                }
                else if(dragging){
                    dragSelected(e.getX(), e.getY());
                }
            }
            @Override
            public void mouseMoved(MouseEvent e){}
        });
    }
    
    
    // add an object (based on the menu's current selection) at the given
    //  x, y position. If the eraser is selected, erase all objects within
    //  the appropriate radius of the eraser.
    // TODO: fix the roads
    private void setObject(MenuSelection curSel, int xPos, int yPos){
        switch(curSel){
            case POINTER: // if pointer, check if any object is to be selected
                checkSelectedPoint(xPos, yPos);
                break;
            case BUILDING: // if building, add a new building to the map
                this.mapObjects.add(
                        new MapObject(xPos, yPos, objectWidth, objectHeight,
                                MapObject.TYPE_BUILDING));
                break;
            case ROAD:
                //this.roads.add(new MapObject(xPos, yPos));
                break;
            case LAMP: // if lamp, add a new lamp to the map
                this.mapObjects.add(
                        new MapObject(xPos, yPos, dotWidth, dotHeight,
                                MapObject.TYPE_LAMP));
                break;
            case TREE: // if tree, add a new tree to the map
                this.mapObjects.add(
                        new MapObject(xPos, yPos, dotWidth, dotHeight,
                                MapObject.TYPE_TREE));
                break;
            case ERASE: // if eraser, check if any objects is to be deleted
                checkDelete(xPos, yPos);
                break;
            case SELECT: // reset select pos and toggle it on
                this.selX1 = this.selX2 = xPos;
                this.selY1 = this.selY2 = yPos;
                this.selecting = true;
                checkSelectedArea(); // initially, check selected area
                break;
            default: // if nothing matches, do nothing
                break;
        }
        
        // redraw the panel
        repaint();
    }
    
    
    // If an object is present at the given x, y location, then it is selected.
    //  Otherwise, all objects that do NOT intersect this point are deselected.
    //  HOWEVER, if the global multiSelect (mainWindow) flag is toggled,
    //  deselection does not take place.
    private void checkSelectedPoint(int x, int y){
        int numObjects = this.mapObjects.size();
        
        // Check all map objects to see if any intersect the select click.
        //  Go in reverse order to ensure top-down selection
        for(int i=numObjects-1; i>=0; i--){
            // get object and intersected (clicked) status
            MapObject mapObj = mapObjects.get(i);
            boolean clicked = mapObj.intersects(x, y);
            
            // if clicked, already selected, and multi-select is on, then
            //  deselect this particular object
            if(clicked && mapObj.selected && mainWindow.multiSelect){
                mapObj.selected = false;
                return;
            }
            
            // if clicked and already selected, go into drag-and-drop mode.
            //  Initialize last mouse point to current position
            else if(clicked && mapObj.selected){
                dragging = true;
                lastMouseX = x;
                lastMouseY = y;
                return;
            }
            
            // otherwise, if clicked and multi-select is enabled, add this one
            //  to the list of selected
            else if(clicked && mainWindow.multiSelect){
                mapObj.selected = true;
                return;
            }
            
            // otherwise, if only clicked, deselect all except this one
            else if(clicked){
                deselectAll();
                mapObj.selected = true;
                return;
            }
        }
        
        // if nothing is clicked, and multi-selected is not on, deselect all
        if(!mainWindow.multiSelect)
            deselectAll();
    }
    
    
    // If an object is selected in the selection area, given by the
    //  selX1, selX2, selY1, selY2 variables, then it is highlighted.
    //  All other objects NOT in the area are immediately deselected
    //  unless multi-select is enabled.
    private void checkSelectedArea(){
        // first, calculate which of the selection values are low and high
        int lowSelX = 0;
        int highSelX = 0;
        int lowSelY = 0;
        int highSelY = 0;
        // figure out high and low X values
        if(selX1 <= selX2){
            lowSelX = selX1;
            highSelX = selX2;
        }
        else{
            lowSelX = selX2;
            highSelX = selX1;
        }
        // figure out high and low Y values
        if(selY1 <= selY2){
            lowSelY = selY1;
            highSelY = selY2;
        }
        else{
            lowSelY = selY2;
            highSelY = selY1;
        }
        
        // Check all map objects to see if any intersect the select box.
        int numObjects = this.mapObjects.size();
        for(int i=0; i<numObjects; i++){
            MapObject mapObj = mapObjects.get(i);
            
            boolean intersects =
                    mapObj.intersects(lowSelX, lowSelY, highSelX, highSelY);
            
            if(intersects)
                mapObj.selected = true;
            else if(!mainWindow.multiSelect)
                mapObj.selected = false;
        }
    }
    
    
    // drags all selected variables by the delta (by however much mouse was
    //  moved since last time). All necessary mouse pointer history is also
    //  updated (i.e. lastMouseX and lastMouseY)
    private void dragSelected(int curMouseX, int curMouseY){
        // get mouse change since last position
        int mouseDeltaX = curMouseX - lastMouseX;
        int mouseDeltaY = curMouseY - lastMouseY;
        
        // drag all selected
        int numObjects = this.mapObjects.size();
        for(int i=0; i<numObjects; i++){
            MapObject mapObj = mapObjects.get(i);
            if(mapObj.selected){
                mapObj.x += mouseDeltaX;
                mapObj.y += mouseDeltaY;
            }
        }
        
        // update the last mouse position to the current one
        lastMouseX = curMouseX;
        lastMouseY = curMouseY;
        
        // update graphics to reflect new positions
        repaint();
    }
    
    
    // Deselect ALL map objects
    private void deselectAll(){
        int numObjects = this.mapObjects.size();
        
        for(int i=0; i<numObjects; i++){
            mapObjects.get(i).selected = false;
        }
    }
    
    
    // If an object is present at the given x, y location, then it is deleted.
    //  If the object is selected, ALL SELECTED OBJECTS are deleted with it.
    // RETURNS true if something was deleted, false if nothing changed.
    private boolean checkDelete(int x, int y){
        int numObjects = this.mapObjects.size();
        
        // check all map objects to see if any intersect the delete click
        for(int i=0; i<numObjects; i++){
            MapObject mapObj = mapObjects.get(i);
            if(mapObj.intersects(x, y)){
                if(mapObj.selected)
                    deleteAllSelected();
                else
                    mapObjects.remove(i);
                return true;
            }
        }
        return false;
    }
    
    
    // helper method: copies all of the selected objects into the copy buffer,
    //  and if cut is TRUE, then it also removes those objects from the map.
    // NOTE: all objects placed into the copy buffer ARE SELECTED.
    // NOTE: all copied objects are CLONED into the copy buffer.
    private void copyCutAllSelected(boolean cut){
        // first, clear the copy buffer if anything was in there
        this.copyObjects.clear();
        
        int numObjects = this.mapObjects.size();
        
        for(int i=0; i<numObjects; i++){
            MapObject mapObj = mapObjects.get(i);
            // if selected, copy it
            if(mapObj.selected){
                copyObjects.add(mapObj.clone());
                // if cut is enabled, also delete it from the map
                if(cut){
                    mapObjects.remove(i);
                    numObjects--;
                    i--;
                }
            }
        }
    }
    
    
    // copy all selected objects (put them into the copy list), AND
    //  deletes all of the ones that were copied
    public void cutAllSelected(){
        copyCutAllSelected(true);
        repaint();
    }
    
    
    // copy all selected objects (put them into the copy list)
    public void copyAllSelected(){
        copyCutAllSelected(false);
    }
    
    
    // add all of the objects from the copy buffer into the mapObjects buffer.
    // NOTE: they will be pasted as selected, and all other selected objects
    //  will first be deselected.
    // NOTE: pasted objects are CLONED from the copy buffer to ensure individual
    //  instances.
    public void pasteCopiedObjects(){
        deselectAll();
        
        // copy in new instances of each copied object
        int numCopied = this.copyObjects.size();
        for(int i=0; i<numCopied; i++){
            this.mapObjects.add(this.copyObjects.get(i).clone());
        }
        
        // update the UI to show the new changes
        repaint();
    }
    
    
    // delete all selected objects on the map
    public void deleteAllSelected(){
        int numObjects = this.mapObjects.size();
        
        for(int i=0; i<numObjects; i++){
            MapObject mapObj = mapObjects.get(i);
            if(mapObj.selected){
                mapObjects.remove(i);
                i--;
                numObjects--;
            }
        }
        
        repaint();
    }
    
    
    // Select ALL map objects
    public void selectAll(){
        int numObjects = this.mapObjects.size();
        
        for(int i=0; i<numObjects; i++){
            mapObjects.get(i).selected = true;
        }
        
        repaint();
    }
    
    
    // Call a delete to ALL MAP OBJECTS: warning -- can't be undone (for now)
    public void deleteAll(){
        this.mapObjects.clear();
        repaint();
    }
    
    
    // Get a custom cursor based on the given input
    private Cursor getCustomCursor(MenuSelection curSel) {
        Image selectedImg = null;
        Point hotSpot = null;
        
        // choose the cursor based on the currently selected menu button
        switch(curSel){
            case POINTER: // return the standard default cursor for the pointer
                return Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR);
            case BUILDING:
                selectedImg = buildingImage;
                break;
            case ROAD:
                selectedImg = roadImage;
                break;
            case LAMP:
                selectedImg = lampImage;
                break;
            case TREE:
                selectedImg = treeImage;
                break;
            case ERASE: // in this case, also set the hotspot to the bottom left
                selectedImg = eraseImage;
                hotSpot = new Point(
                        eraseImage.getWidth(this) / 4,
                        3 * eraseImage.getHeight(this) / 4);
                break;
            case SELECT: // return the standard "selection" cursor for the selector
                return Cursor.getPredefinedCursor(Cursor.CROSSHAIR_CURSOR);
            default: // if nothing matches, return default cursor
                return Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR);
        }
        
        // if hotspot wasn't setup above, set it up here and put it into the center
        //  of the image
        if(hotSpot == null){
            hotSpot = new Point(
                    selectedImg.getWidth(this) / 2,
                    selectedImg.getHeight(this) / 2);
        }
        
        // return the custom cursor given by the data provided
        return Toolkit.getDefaultToolkit().createCustomCursor(
                selectedImg, hotSpot, "CustomCursor");
    }
    
    
    // get an image scaled based on the main Image size (cursor/plot point img):
    //  this is the "default" arguments method
    private Image getScaledImage(String imgName){
        return getScaledImage(imgName, objectWidth, objectHeight);
    }
    
    // get the image scaled based on the given parameters
    private Image getScaledImage(String imgName, int width, int height) {
        URL imgURL = this.getClass().getClassLoader().getResource(imgName);
        Image cursorImg = null;
        try {
            cursorImg = ImageIO.read(imgURL);
        }
        catch(Exception e){ // if failed to load, return nothing
            System.err.println("ERROR: Couldn't load image \"" + imgName + "\".");
            return null;
        }
        
        // scale the image and return it
        return cursorImg.getScaledInstance(
                width, height, Image.SCALE_SMOOTH);
    }
    
    
    // Draw the containing image, and all other current data,
    //  to the screen.
    @Override
    public void paintComponent(Graphics gs){
        super.paintComponent(gs);
        
        Graphics2D g = (Graphics2D)gs;
        
        // draw the main image background
        g.drawImage(this.mapImg, 0, 0, imgW, imgH, this);
        
        // set color for filling underglow if necessary
        g.setColor(this.underglowColor);
        
        // draw each of the map objects
        int numObjects = this.mapObjects.size();
        for(int i=0; i<numObjects; i++){
            MapObject mapObj = this.mapObjects.get(i);
            int imgX = mapObj.x - mapObj.width/2;
            int imgY = mapObj.y - mapObj.height/2;
            Image img = null;
            switch(mapObj.type){
                case MapObject.TYPE_BUILDING:
                    img = this.buildingImage;
                    break;
                case MapObject.TYPE_LAMP:
                    img = this.lampImage;
                    break;
                case MapObject.TYPE_TREE:
                    img = this.treeImage;
                    break;
                default:
                    break;
            }
            if(mapObj.selected) // if selected, draw an underglow
                g.fillRect(imgX, imgY, mapObj.width, mapObj.height);
            g.drawImage(img, imgX, imgY, this);
        }
        
        
        // draw the selection square if currently selecting
        if(selecting){
            // set the hightlight color to light and transparent
            g.setColor(this.selectionColor);
            // calculate which x-point is smaller, and start there
            int selX = 0;
            int selWidth = 0;
            if(selX1 <= selX2){
                selX = selX1;
                selWidth = selX2 - selX1;
            }
            else{
                selX = selX2;
                selWidth = selX1 - selX2;
            }
            // calculate which y-point is smaller, and start there
            int selY = 0;
            int selHeight = 0;
            if(selY1 <= selY2){
                selY = selY1;
                selHeight = selY2 - selY1;
            }
            else{
                selY = selY2;
                selHeight = selY1 - selY2;
            }
            // draw the sel rect based on the calculated values
            g.fillRect(selX, selY, selWidth, selHeight);
        }
    }
    
    
    // PUBLIC GETTER: image (map) width
    public int getMapWidth(){
        return this.imgW;
    }
    
    // PUBLIC GETTER: image (map) height
    public int getMapHeight(){
        return this.imgH;
    }
    
    // PUBLIC GETTER: List of all map object
    public List<MapObject> getMapObjects(){
        return this.mapObjects;
    }
}