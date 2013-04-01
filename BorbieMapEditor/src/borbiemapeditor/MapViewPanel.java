package borbiemapeditor;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Image;
import java.io.File;
import javax.imageio.ImageIO;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

/**
 *
 * @author richard
 */
public class MapViewPanel extends JPanel {
    
    
    private MainWindow mainWindow;
    private MapPanel mapPanel;
    
    
    // CONSTRUCTOR: build the MapViewPanel (initially with no map inside):
    //  sets up a temporary background color, and adds the border layout to
    //  the panel.
    public MapViewPanel(MainWindow mainWindow) {
        super();
        
        this.mainWindow = mainWindow;
        this.setBackground(Color.BLACK);
        this.setLayout(new BorderLayout());
    }
    
    
    // Add the image given by the provided file as the current map image.
    //  Clears existing image first (if one exists). If the provided file
    //  is bad (i.e. null or not an image file), an exception will be thrown.
    public void setMapImage(File imgFile) throws Exception {
        // try to get the image from the file
        Image mapImg = ImageIO.read(imgFile);
        
        // remove all components (clear the panel of any existing images)
        this.removeAll();
        
        // create the MapPanel and add it to a scrollpane to the map view panel
        mapPanel = new MapPanel(mainWindow, mapImg);
        JScrollPane scroller = new JScrollPane(mapPanel);
        this.add(scroller);
    }
    
    
    // Returns the inner MapPanel (null if not yet set)
    public MapPanel getMapPanel(){
        return this.mapPanel;
    }
}
