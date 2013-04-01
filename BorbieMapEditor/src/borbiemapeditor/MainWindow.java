package borbiemapeditor;


import borbiemapeditor.MenuPanel.MenuSelection;
import java.awt.Dimension;
import java.awt.Toolkit;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.File;
import java.util.List;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JSplitPane;

/**
 *
 * @author richard
 */
public class MainWindow extends JFrame {
    
    
    // references to sub-panels that the main window will send messages to
    private EditorMenuBar menuBar;
    private MapViewPanel mapPanel;
    private MenuPanel menuPanel;
    
    // reference to the splitPane for repositioning divider if window is resized
    private JSplitPane splitPane;
    
    
    // global keyboard toggles
    public boolean multiSelect;
    
    
    
    // CONSTRUCTOR: builds the main JFrame window, and inserts the primary
    //  components into a JSplitPane (left side = map, right side = menu).
    // PARAMETERS: desired window width and height, respectively.
    public MainWindow(int windowWidth, int windowHeight) {
        // create the JFrame from super call
        super("Borbie Map Editor");
        
        // make window quit program when exit
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        // set window width and height as given by parameters
        this.setSize(windowWidth, windowHeight);
        
        // center window on the screen
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        int locX = (screenSize.width / 2) - (windowWidth / 2);
        int locY = (screenSize.height / 2) - (windowHeight / 2);
        this.setLocation(locX, locY);
        
        // attempt to set the window icon
        /*URL iconURL = this.getClass().getClassLoader()
                .getResource("borbie.jpg");
        if(iconURL == null){
            System.err.println("ERROR: Can't load \"borbie.jpg\".");
            System.exit(-1);
        }
        this.setIconImage(Toolkit.getDefaultToolkit().getImage(iconURL));*/
        
        // prevent resizing
        //this.setResizable(false);
        
        
        // default keyboard toggles
        multiSelect = false;
        
        
        /*** ADD COMPONENTS ***/
        
        // add the main menu
        menuBar = new EditorMenuBar(this);
        this.setJMenuBar(menuBar);
        
        // add the split pane as the primary component
        splitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT);
        splitPane.setEnabled(false); // prevent moving the divider
        splitPane.setDividerLocation(windowWidth - 200);
        
        // add the map viewer to the left
        mapPanel = new MapViewPanel(this);
        splitPane.setLeftComponent(mapPanel);
        
        // add the menu panel to the right
        menuPanel = new MenuPanel();
        splitPane.setRightComponent(menuPanel);
        
        this.add(splitPane);
        
        
        // add resize listener: adjust splitPane divider accordingly
        this.addComponentListener(new ComponentAdapter() {
            @Override
            public void componentResized(ComponentEvent e) {
                splitPane.setDividerLocation(getWidth() - 200);
            }
        });
        
        
        // NOTE: loses focus to JButtons. Make sure all JButtons are
        //  myJButton.setFocusable(false);
        // add keyboard toggle listener
        this.addKeyListener(new KeyListener() {
            @Override
            public void keyTyped(KeyEvent e){}
            @Override
            public void keyPressed(KeyEvent e){
                // if shift key, toggle the mutli-select flag true
                if(e.getKeyCode() == KeyEvent.VK_SHIFT)
                    multiSelect = true;
            }
            @Override
            public void keyReleased(KeyEvent e){
                // if shift key, disable multi-select flag
                if(e.getKeyCode() == KeyEvent.VK_SHIFT)
                    multiSelect = false;
            }
        });

        
        this.setVisible(true);
    }
    
    
    // Returns the current MenuPanel selection (which editor button is selected)
    public MenuSelection getCurSelection(){
        return this.menuPanel.getCurSelection();
    }
    
    
    // Returns a pointer to the current Menu Panel
    public MenuPanel getMenuPanel(){
        return this.menuPanel;
    }
    
    
    // Returns a pointer to the current inner map panel (if available).
    //  RETURNS NULL if the inner map panel is not yet available.
    public MapPanel getMapPanel(){
        return this.mapPanel.getMapPanel();
    }
    
    
    // Queries the user to open an image via a standard open dialog, and
    //  then tries to add that image to the screen.
    public void loadMapImage(){
        JFileChooser chooser = new JFileChooser();
        int retVal = chooser.showOpenDialog(null);
        
        // if chooser gets a file approved, try to load it
        if(retVal == JFileChooser.APPROVE_OPTION) {
            File file = chooser.getSelectedFile();
            try{
                // set the new file
                mapPanel.setMapImage(file);
                mapPanel.revalidate();
                
                // enable editing modes
                menuBar.setEditMode();
                menuPanel.setEditMode();
            }
            catch(Exception e){
                JOptionPane.showMessageDialog(this,
                    "File \"" + file.getName() + "\" could not be opened.\n" +
                        "Please choose an appropriate image file.",
                    "File Open Error",
                    JOptionPane.ERROR_MESSAGE);
            }
        }
    }
    
    
    public void exportCoordinates(){
        JFileChooser chooser = new JFileChooser();
        int retVal = chooser.showSaveDialog(null);
        
        // if user selected to save, get the file path and attempt to save it
        if(retVal == JFileChooser.APPROVE_OPTION) {
            File file = chooser.getSelectedFile();
            String filePath = file.getPath();
            
            // get the map: if it's NULL, just quit (shouldn't be here anyway)
            MapPanel map = this.getMapPanel();
            if(map == null)
                return;
            
            int mapW = map.getMapWidth();
            int mapH = map.getMapHeight();
            List<MapObject> mapObjects = map.getMapObjects();
            
            try{
                // try to write the new file to the given file name
                CoordinateFileManager.exportCoordinatesToFile(
                        mapObjects, mapW, mapH, filePath);
            }
            catch(Exception e){
                JOptionPane.showMessageDialog(this,
                    "Sorry! There was a problem writing the file.\n" +
                        "Mission aborted!",
                    "File Write Error",
                    JOptionPane.ERROR_MESSAGE);
            }
        }
    }
}
